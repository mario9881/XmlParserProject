#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H
#include<iostream>
#include<string>
using std::cout;
using std::endl;
using std::string;

class Attribute{
    string key;
    string value;
    
public:
    Attribute(){
        key = value = "";
    }
    
    Attribute(const string& _key, const string& _value){
        key = _key;
        value = _value; 
    }
    
    string getKey() const{
        return key;
    }
    
    string getValue() const{
        return value;
    }
    
    void setValue(const string& _value){
        value = _value;
    }
};

#endif