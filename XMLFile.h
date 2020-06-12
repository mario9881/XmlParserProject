#ifndef XMLFILE_H
#define XMLFILE_H
#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include"functions.h"
#include"XMLElement.h"
using std::ifstream;
using std::ofstream;
using std::string;
using std::map;
using std::to_string;
using std::cin;

class XMLFile{
    string path;
    XMLElement* root;
    map<string, XMLElement*> elementsWithIDs;

    void deleteXMLElementsTree() {
        root->deleteAllChildren();
        delete root;
        root = nullptr;
    }

    bool idExists(const string& id) const {
        return elementsWithIDs.count(id);
    }

    string firstFreeId() const{
        int i = 0;
        while(idExists(to_string(i))){
            i++;
        }
        return to_string(i);
    }

    int numberOfIdsStartingWith(const string& givenId) const {
        int count = 0;

        for(auto pair : elementsWithIDs) {
            if(startsWith(givenId + "_", pair.first)) {
                count++;
            }
        }
        return count;
    }

    string idWithSuffix(const string& givenId) const{
        
        int numberOfIdsStartingWithGivenId = numberOfIdsStartingWith(givenId);

        return givenId + "_" + to_string(numberOfIdsStartingWithGivenId + 1);
    }

public:
    XMLFile(){
        path = "";
        root = nullptr;
        elementsWithIDs = map<string, XMLElement*>();
    }
  
    ~XMLFile() {
        deleteXMLElementsTree();
    }

    void openFile(){
        string openedPath;
        cin >> openedPath;

        path = openedPath;
        ifstream in(path.c_str());
     
        XMLElement* imaginaryParentOfRoot = new XMLElement;
        XMLElement* currentElement = imaginaryParentOfRoot;
        char currentSymbol;

        while(true){
            in >> currentSymbol;

            //cout << "currentSymbol: " << currentSymbol << '\n';

            if(currentSymbol == '<'){
                string newTagName;

                char tagNameSymbol;
                while(in.peek() != ' ' && in.peek() != '>') {
                    in >> tagNameSymbol;
                    newTagName.push_back(tagNameSymbol);
                }

                if(newTagName[0] == '/') {      // Тагът е затварящ
                    if(currentElement->getParent() == imaginaryParentOfRoot) {
                        root = imaginaryParentOfRoot->getChild(0);
                        root->makeParentNull();
                        delete imaginaryParentOfRoot;
                        break;
                    }
                    // Ако родителя не е nullptr...
                    currentElement = currentElement->getParent();
                }
                else {                              // Тагът е отварящ
                    XMLElement* newElement = new XMLElement(newTagName, currentElement, "");
                    currentElement->addChild(newElement);
                    currentElement = newElement;

                    in >> currentSymbol;

                    while(currentSymbol != '>'){
                        string attributeKey;
                        getline(in, attributeKey, '=');     //Read attributeKey till =
                        in.ignore();                        //Ignore one "
                        
                        attributeKey = currentSymbol + attributeKey;

                        string attributeValue;
                        getline(in, attributeValue, '"');
                        
                        Attribute newAttribute(attributeKey, attributeValue);
                        currentElement->addAttribute(newAttribute);

                        in >> currentSymbol;
                    }

                    string givenId = newElement->getValueOfAttribute("id");

                    if(givenId == "ERROR") {
                        elementsWithIDs[firstFreeId()] = newElement;
                    }
                    else if(idExists(givenId)) {
                        elementsWithIDs[idWithSuffix(givenId)] = newElement;
                    }
                    else {
                        elementsWithIDs[givenId] = newElement;
                    }
                }
            }
            else {
                string content;
                content.push_back(currentSymbol);

                while(in.peek() != '<') {
                    content.push_back(in.get());
                }
                content = trim(content);
                currentElement->setContent(content);
            }
        }
    } 
    
    void closeFile(){
        path = "";
        
        deleteXMLElementsTree();

        elementsWithIDs.clear();
    } 

    //For testing
    void printElemWithIds() const{
        for(auto pair : elementsWithIDs){
            cout << pair.first << " " << pair.second->getTagName() << endl;
        }
    }

    void saveFile(){
        ofstream out(path.c_str());
        
        root->printElement(out);
        
        out.close();
    }

    void saveAsFile(){
        string newPath;

        cin >> newPath;

        ofstream out(newPath.c_str());

        root->printElement(out);
        
        out.close();
    }

    void help(){

    }

    void printXML(){
        root->printElement(cout);
    }

    void selectAttribute(){
        string id;
        cin >> id;
        
        string key;
        cin >> key;

        if(idExists(id)){
            if(elementsWithIDs[id]->getValueOfAttribute(key) != "ERROR"){
                cout << elementsWithIDs[id]->getValueOfAttribute(key);
            }
            else{
                cout << "Invalid key" << endl;
            }
        }
        else{
            cout << "Invalid ID" << endl;
        }
    }

    void setAttribute(){
        string id;
        string key;
        string value;

        cin >> id >> key >> value;

        if(idExists(id)){
            elementsWithIDs[id]->setValueOfAttribute(key, value);    
        }
        else{
            cout << "Invalid ID" << endl;
        }
    }

    void printChildrenAttributes() {
        string id;
        cin >> id;

        if(idExists(id)){
            for(int i = 0; i < elementsWithIDs[id]->getNumberOfChildren(); i++){
                elementsWithIDs[id]->getChild(i)->printElementAttributes();
            }
        }
        else{
            cout << "Invalid ID" << endl;
        }

    }

    void printChild(){
        string id;
        int n;

        cin >> id >> n;

        if(idExists(id)){
            elementsWithIDs[id]->getChild(n)->printElement(cout);
        }
        else{
            cout << "Invalid ID" << endl;
        }
    }

    void printElementText(){
        string id;
        cin >> id;

        if(idExists(id)){
            cout << elementsWithIDs[id]->getContent();
        }
        else{
            cout << "Invalid ID" << endl;
        }
    }

    void deleteAttribute(){
        string id;
        string key;
        cin >> id >> key;

        if(idExists(id)){
            if(elementsWithIDs[id]->getValueOfAttribute(key) != "ERROR"){
                elementsWithIDs[id]->deleteAttribute(key);
            }
            else{
                cout << "Invalid key" << endl;
            }
        }
        else{
            cout << "Invalid ID" << endl;
        }
    }

    void newChild(){
        string id;
        cin >> id;

        if(idExists(id)){
            XMLElement* newChild = new XMLElement("newchild");
            elementsWithIDs[id]->addChild(newChild);
            elementsWithIDs[firstFreeId()] = newChild;
        }
        else{
            cout << "Invalid ID" << endl;
        }

    }

    void xpath(){

    }
};

#endif