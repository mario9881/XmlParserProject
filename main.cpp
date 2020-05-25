#include<iostream>
#include<fstream>
#include<string>
#include"functions.h"
#include"XMLFile.h"
using namespace std;

int main() {
    XMLFile file;

    bool weHaveEnteredExit = false;
    string command;

    while (!weHaveEnteredExit) {
        cin >> command;
        if (command == "open") {
            file.openFile();
        }
        else if (command == "close") {
            file.closeFile();
        }
        else if (command == "save") {
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
            file.printChildrenAttributes();
        }
        else if (command == "child") {
            file.printChild();
        }
        else if (command == "text") {
            file.printElementText();
        }
        else if (command == "delete") {
            file.deleteAttribute();
        }
        else if (command == "newchild") {
            file.newChild();
        }
        else if (command == "xpath") {
            file.xpath();
        }
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