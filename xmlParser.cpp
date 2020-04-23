#include<iostream>
#include<fstream>
#include<string>
using namespace std;

template<typename T>        
class Vector {              
    T* arr;
    int numberOfElements;
    int capacity;

    // Заделя двойно по-голяма памет и премества елементите в нея
    void resize() {
        T* newArr = new T[2 * capacity];

        for (int i = 0; i < numberOfElements; i++) {
            newArr[i] = arr[i];
        }
        
        capacity *= 2;
        delete[] arr;
        arr = newArr;
    }

public:
    bool hasElement(T element) const {
        for (int i = 0; i < numberOfElements; i++) {
            if (arr[i] == element) {
                return true;
            }
        }
        return false;
    }

    Vector() {
        numberOfElements = 0;
        capacity = 8;
        arr = new T[capacity];
    }

    Vector(const Vector<T>& other) {
        numberOfElements = other.numberOfElements;
        capacity = other.capacity;
        arr = new T[capacity];

        for (int i = 0; i < numberOfElements; i++) {
            arr[i] = other.arr[i];
        }
    }

    Vector& operator=(const Vector<T>& other) {
        if (this != &other) {
            delete[] arr;

            numberOfElements = other.numberOfElements;
            capacity = other.capacity;
            arr = new T[capacity];

            for (int i = 0; i < numberOfElements; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    ~Vector() {
        delete[] arr;
    }

    void addElement(T element) {
        if (capacity == numberOfElements) {
            resize();
        }
        arr[numberOfElements] = element;
        numberOfElements++;
    }

    int getNumberOfElements() const {
        return numberOfElements;
    }

    T& operator[](int i) {
        return arr[i];
    }

    T operator[](int i) const {
        return arr[i];
    }

    void removeAt(int i) {
        for (int k = i + 1; k < numberOfElements; k++) {
            arr[k - 1] = arr[k];
        }
        numberOfElements--;
    }

    void removeValue(T value) {
        for (int i = 0; i < numberOfElements; i++) {
            if (arr[i] == value) {
                removeAt(i);
                i--;
            }
        }
    }

    void removeDuplicates() {
        for (int i = 0; i < numberOfElements; i++) {
            for (int k = i + 1; k < numberOfElements; k++) {
                if (arr[i] == arr[k]) {
                    removeAt(k);
                    k--;
                }
            }
        }
    }
};

bool isWhiteSpace(char symbol) {
    return symbol == ' ' || symbol == '\n' || symbol == '\t';
}

bool isInteger(string s) {
    if (s == "-") {         // Създава се временен масив от символи с един символ - тире
        return false;       // От този масив с конструктора горе се създава нов string
    }                       // Сравняват се двата string-a

    if (s[0] != '-' && (s[0] < '0' || '9' < s[0])) {
        return false;
    }

    for (int i = 1; i < s.size(); i++) {
        if (s[i] < '0' || '9' < s[i]) {
            return false;
        }
    }

    return true;
}

class Attribute{
    string key;
    string value;
    
public:
    Attribute(){
        key = value = ""; //Oператор = не е void
    }
    
    Attribute(string _key, string _value ){
        key = _key;
        value = _value; 
    }
    
    string getKey() const{
        return key;
    }
    
    string getValue() const{
        return value;
    }
    
    void setValue(string _value){
        value = _value;
    }
    
};

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
    
    XMLElement(string _tagName){
        tagName = _tagName;
        attributes = {};
        children = {};          
    }
    
    void addAttribute(Attribute newAttribute){
        attributes.addElement(newAttribute);
    }
    
    void addChild(XMLElement* newChild){
        children.addElement(newChild);
    }
    
    void printElement(){
        cout<< "<"<<tagName;
        for(int i=0; i < attributes.getNumberOfElements(); i++){
            cout<<" "<<attributes[i].getKey<<"="<<'"'<<attributes[i].getValue<<'"';
        }
        cout<<">";
    }
};

class XMLFile{
    string path;
    XMLElement* root;

public:
    XMLFile(){
        path = "";
        root = nullptr;
    }
  
    void openFile(string _path){
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
                    getline(in, attributeKey, '=');//Четем атрибуткий до знака =
                    in.ignore(); //прескачаме една двойна кавичка
                    string attributeValue;
                    getline(in, attributeValue, '"' );
                    Attribute newAttribute(attributeKey, attributeValue);
                    root->addAttribute(newAttribute);
                    in >> currentSymbol;
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


int main() {

    XMLFile file01;
    //file01.openFile("01.xml");


    return 0;

    XMLFile file;

    bool weHaveEnteredExit = false;
    string command;

    while (!weHaveEnteredExit) {
        cin >> command;
        if (command == "open") {
            string openedPath;
            cin >> openedPath;
            file.openFile(openedPath);
        }
        else if (command == "close") {
            file.closeFile();
        }
        /*else if (command == "save") {
            file.saveFile();
        }
        else if (command == "save_as") {
            file.saveAsFile();
        }
        else if (command == "help") {
            file.help();
        }
    
    
        else if (command == "print") {
            file.printXML();
        }
        else if (command == "select") {
            file.selectAttribute();
        }
        else if (command == "set") {
            file.setAttribute();
        }
        else if (command == "children") {
            file.childrenlist();
        }
        else if (command == "child") {
            file.printChild();
        }
        else if (command == "text") {
            file.printElementtext();
        }
        else if (command == "delete") {
            file.deleteAttribute();
        }
        else if (command == "newchild") {
            file.newchild();
        }
        else if (command == "xpath") {
            file.xpath();
        }*/
        else if (command == "exit") {
            weHaveEnteredExit = true;
        }
        else {
            cout << "Unknown command " << command << endl;
        }
        cout << endl;
    }
    return 0;
}