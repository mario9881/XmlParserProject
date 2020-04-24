#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include<string>
using std::string;

bool isWhiteSpace(char symbol) {
    return symbol == ' ' || symbol == '\n' || symbol == '\t';
}

bool isInteger(const string& s) {
    if (s == "-") {
        return false;
    }

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

#endif