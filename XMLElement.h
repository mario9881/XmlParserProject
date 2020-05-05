#ifndef XMLELEMENT_H
#define XMLELEMENT_H
#include<fstream>
#include<string>
#include"Vector.h"
#include"Attribute.h"
using std::endl;
using std::ostream;
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

    void printNSpaces(ostream& out, int n) const{
        for(int i = 0; i < n; i++){
            out << " ";
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
    
    void printOpeningTag(ostream& out) const {
        out << "<" << tagName;
        for(int i = 0; i < attributes.getNumberOfElements(); i++){
            out << " " << attributes[i].getKey() << "=" << '"' << attributes[i].getValue() << '"';
        }
        out << ">";
    }

    void printClosingTag(ostream& out) const {
        out << "</" << tagName << ">";
    }

    void printElement(ostream& out, int spaces = 0) const{
        if(children.getNumberOfElements() == 0) {
            printNSpaces(out, spaces);
            printOpeningTag(out);
            out << content;
            printClosingTag(out);
            out<<endl;
        }
        else {
            printNSpaces(out, spaces);
            printOpeningTag(out);
            out << endl;

            for(int i = 0; i < children.getNumberOfElements(); i++){
                children[i]->printElement(out, spaces + 4);
            }        
            
            printNSpaces(out, spaces);
            printClosingTag(out);
            out << endl;
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

    void deleteAllChildren() {
        for(int i = 0; i < children.getNumberOfElements(); i++){
            children[i]->deleteAllChildren();
            delete children[i];
        }
    }
};

#endif