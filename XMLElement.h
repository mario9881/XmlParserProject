#ifndef XMLELEMENT_H
#define XMLELEMENT_H
#include<fstream>
#include<string>
#include"Vector.h"
#include"Attribute.h"
using std::endl;
using std::ostream;
using std::istream;
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

    XMLElement(const string& _tagName){
        tagName = _tagName;
        attributes = {};
        children = {};        
        parent = nullptr;
        content = "";
    }


    void setContent(const string& _content){
        content = _content;
    }
    
    void addAttribute(const Attribute& newAttribute){
        attributes.addElement(newAttribute);
    }
    
    void deleteAttribute(const string& key){
        for(int i = 0; i < attributes.getNumberOfElements(); i++){
            if (attributes[i].getKey() == key) {
                attributes.removeAt(i);
            }
        }
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

    void printElementAttributes() const{
        for(int i = 0; i < attributes.getNumberOfElements(); i++){
            cout << attributes[i].getKey() << '=' <<  '"' << attributes[i].getValue() << '"' << ' ';
        }
    }


    string getTagName() const{
        return tagName;
    }

    string getContent() const{
        return content;
    }

    XMLElement* getParent() const {
        return parent;
    }

    XMLElement* getChild(int i) const {
        return children[i];
    }

    int getNumberOfChildren() const{
        return children.getNumberOfElements();
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


    string getValueOfAttribute(const string& key) const{
        for(int i = 0; i < attributes.getNumberOfElements(); i++){
            if(attributes[i].getKey() == key){
                return attributes[i].getValue();
            }
        }
        return "ERROR";
    }

    void setValueOfAttribute(const string& key, const string& value) {
         for(int i = 0; i < attributes.getNumberOfElements(); i++){
             if(attributes[i].getKey() == key){
                 attributes[i].setValue(value);
                 return;
             }
         }
         addAttribute(Attribute(key, value));
    }

    void readAttributes(istream& in){
        char currentSymbol;
        
        in >> currentSymbol;

        while(currentSymbol != '>'){
            string attributeKey;
            getline(in, attributeKey, '=');     //Read attributeKey till =
            in.ignore();                        //Ignore one "
            
            attributeKey = currentSymbol + attributeKey;

            string attributeValue;
            getline(in, attributeValue, '"');
            
            Attribute newAttribute(attributeKey, attributeValue);
            addAttribute(newAttribute);

            in >> currentSymbol;
        }
    }

    void readContent(istream& in, char currentSymbol){
        string content;
        content.push_back(currentSymbol);

        while(in.peek() != '<') {
            content.push_back(in.get());
        }
        content = trim(content);
        setContent(content);
    }
};

#endif