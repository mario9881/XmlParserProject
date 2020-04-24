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
    
public:
    XMLElement(){
        tagName = "";
        attributes = {};
        children = {};        
    }
    
    XMLElement(const string& _tagName){
        tagName = _tagName;
        attributes = {};
        children = {};          
    }
    
    void addAttribute(const Attribute& newAttribute){
        attributes.addElement(newAttribute);
    }
    
    void addChild(XMLElement* newChild){
        children.addElement(newChild);
    }
    
    void printElement() const{
        cout << "<" << tagName;
        for(int i = 0; i < attributes.getNumberOfElements(); i++){
            cout << " " << attributes[i].getKey() << "=" << '"' << attributes[i].getValue() << '"';
        }
        cout << ">";
    }
};

#endif