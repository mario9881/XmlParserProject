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

public:
    XMLElement(){
        tagName = "";
        attributes = {};
        children = {};        
        parent = nullptr;
    }
    
    XMLElement(const string& _tagName, XMLElement* _parent){
        tagName = _tagName;
        attributes = {};
        children = {};
        parent = _parent;
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

    // TODO: Print NOT only the opening tag
    void printElement() const{
        printOpeningTag();
        cout << endl;
        for(int i = 0; i < children.getNumberOfElements(); i++){
            children[i]->printElement();
        }
        printClosingTag();
        cout << endl;
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