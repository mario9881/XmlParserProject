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

        char currentSymbol;

        while(!in.eof()){
            in >> currentSymbol;

            if(currentSymbol == '<'){
                string currentTagName;
                in >> currentTagName;
                root = new XMLElement(currentTagName);

                in >> currentSymbol;

                while(currentSymbol != '>'){
                    string attributeKey;
                    getline(in, attributeKey, '=');     //Read attributeKey till =
                    in.ignore();                        //Ignore one "
                    
                    string attributeValue;
                    getline(in, attributeValue, '"' );
                    
                    Attribute newAttribute(attributeKey, attributeValue);
                    root->addAttribute(newAttribute);

                    in >> currentSymbol;
                }
            }
        }

        // root->printElement();
    } 
    
    void closeFile(){
        path = "";
        //TODO
        root = nullptr;
    }   
};

#endif