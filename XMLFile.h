#ifndef XMLFILE_H
#define XMLFILE_H
#include<fstream>
#include<string>
#include"XMLElement.h"
using std::ifstream;
using std::ofstream;
using std::string;

class XMLFile{
    string path;
    XMLElement* root;

public:
    XMLFile(){
        path = "";
        root = nullptr;
    }
  
    // TODO: Fix
    void openFile(const string& _path){
        path = _path;
        ifstream in(path.c_str());
     
        XMLElement* imaginaryParentOfRoot = new XMLElement;
        XMLElement* currentElement = imaginaryParentOfRoot;
        char currentSymbol;

        while(true){
            in >> currentSymbol;

            cout << "currentSymbol: " << currentSymbol << '\n';

            if(currentSymbol == '<'){
                string currentTagName;
                in >> currentTagName;
                
                if(currentTagName[0] == '/') {      // Тагът е затварящ
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
                    XMLElement* newElement = new XMLElement(currentTagName, currentElement);
                    currentElement->addChild(newElement);
                    currentElement = newElement;

                    in >> currentSymbol;

                    while(currentSymbol != '>'){
                        string attributeKey;
                        getline(in, attributeKey, '=');     //Read attributeKey till =
                        in.ignore();                        //Ignore one "
                        
                        attributeKey = currentSymbol + attributeKey;

                        string attributeValue;
                        getline(in, attributeValue, '"' );
                        
                        Attribute newAttribute(attributeKey, attributeValue);
                        currentElement->addAttribute(newAttribute);

                        in >> currentSymbol;
                    }
                }
            }
        }

        root->printElement();
    } 
    
    void closeFile(){
        path = "";
        //TODO
        root = nullptr;
    }   
};

#endif