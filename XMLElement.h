#ifndef XMLELEMENT_H
#define XMLELEMENT_H
#include<iostream>
#include<string>
#include"Vector.h"
#include"Attribute.h"
using std::cout;
using std::endl;
using std::string;

/*
<bookstore>
    <book category="children" id="40">
        <title>Harry Potter</title>
        <author>J K. Rowling</author>
        <year>2005</year>
        <price>29.99</price>
    </book>

    <notebook category="school">
        <pages>60</pages>
        <price>3.95</price>
    </notebook>
</bookstore>
*/
class XMLElement{
    string tagName;                 // book
    Vector<Attribute> attributes;   // { category="children", id="40" }
    Vector<XMLElement*> children;   // {<title>...</title>, <author>...</author>}
    XMLElement* parent;             // <parent>...</parent>
    string content;                 // Harry Potter

    void printNSpaces(int n) const{
        for(int i = 0; i < n; i++){
            cout << " ";
        }
    }

public:
    XMLElement(){
        tagName = "";
        attributes = {};
        children = {};        
        parent = nullptr;
        content = "";
    }
    
    XMLElement(const string& _tagName, XMLElement* _parent, const string& _content){
        tagName = _tagName;
        attributes = {};
        children = {};
        parent = _parent;
        content = _content;
    }

    void setContent(const string& _content){
        content = _content;
    }
    
    void addAttribute(const Attribute& newAttribute){
        attributes.addElement(newAttribute);
    }
    
    void addChild(XMLElement* newChild){
        children.addElement(newChild);
        newChild->parent = this;
    }
    
    void printOpeningTag() const {
        cout << "<" << tagName;
        for(int i = 0; i < attributes.getNumberOfElements(); i++){
            cout << " " << attributes[i].getKey() << "=" << '"' << attributes[i].getValue() << '"';
        }
        cout << ">";
    }

    void printClosingTag() const {
        cout << "</" << tagName << ">";
    }

    void printElement(int spaces) const{
        if(children.getNumberOfElements() == 0) {
            printNSpaces(spaces);
            printOpeningTag();
            cout << content;
            printClosingTag();
            cout<<endl;
        }
        else {
            printNSpaces(spaces);
            printOpeningTag();
            cout << endl;

            for(int i = 0; i < children.getNumberOfElements(); i++){
                children[i]->printElement(spaces + 4);
            }        
            
            printNSpaces(spaces);
            printClosingTag();
            cout << endl;
        }
    }

    XMLElement* getParent() const {
        return parent;
    }

    XMLElement* getChild(int i) const {
        return children[i];
    }

    void makeParentNull() {
        parent = nullptr;
    }
};

#endif