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

// Source:
// https://stackoverflow.com/questions/25829143/trim-whitespace-from-a-string/25829178
string trim(const string& str) {
    int first = str.find_first_not_of(" \n\t");
    if (first == string::npos) {
        return str;
    }
    int last = str.find_last_not_of(" \n\t");
    int substr_length = last - first + 1;
    return str.substr(first, substr_length);
}

#endif