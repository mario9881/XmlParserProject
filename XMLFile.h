#ifndef XMLFILE_H
#define XMLFILE_H
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

    void openFile(const string& _path){
        path = _path;
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

    }

    void setAttribute(){

    }

    void childrenList() {

    }

    void printChild(){

    }

    void printElementText(){

    }

    void deleteAttribute(){

    }

    void newChild(){

    }

    void xpath(){

    }
};

#endif