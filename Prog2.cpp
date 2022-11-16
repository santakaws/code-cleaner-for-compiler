#include <iomanip>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <istream>

using namespace std;

bool isReserved(string subCode) {
    char reservedWords[4][10]={ "cout<<", "for", "int", "while"};
    for (int i = 0; i < 4; ++i) {
        if (subCode == reservedWords[i]) {
            return true;
        }
    }
    return false;
}

bool isOperator(string subCode) {
    char oper[6][3]={ "+", "-", "*", "/", "++", "--"};
    for (int i = 0; i < 6; ++i) {
        if (subCode == oper[i]) {
            return true;
        }
    }
    return false;
}

bool isSpecial(string subCode) {
    char special[6][3]={"=" , ";" , "(" , ")" , "<=" ,","};
    for (int i = 0; i < 7; ++i) {
        if (subCode == special[i]) {
            return true;
        }
    }
    return false;
}

int main() {
    ofstream output("newdata.txt");
    char tok;
    vector<char> inChars;
    vector<string> tokens;
    ifstream readFile("data.txt");

    char reservedWords[4][10]={ "cout<<", "for", "int", "while"};
    char oper[6][3]={ "+", "-", "*", "/", "++", "--"};
    char special[6][3]={"=" , ";" , "(" , ")" , "<=" ,","};

    while (readFile.get(tok)) {
        if (tok == '/' && readFile.peek() == '/') {
            while (tok != '\n') {
                readFile.get(tok);
            }
        }
        if (tok == '\r') {
            continue;
        }
        if (tok == '\n') {
            continue;
        }
        if (tok == ' ') {
            continue;
        }
        inChars.push_back(tok);

    }
    readFile.close();

    string checkToken = "";
    string chkLongTok = "";

    for (int i = 0; i < inChars.size(); ++i) {
            checkToken += inChars[i];
            chkLongTok += inChars[i];
            if (isReserved(chkLongTok)) {
                for (int j = 0; i < chkLongTok.size() - 1; ++i) {
                    tokens.pop_back();
                }
                tokens.push_back(checkToken);
                tokens.push_back(" ");
                chkLongTok = "";
                checkToken = "";
            }
            else if (isOperator(checkToken)) {
                tokens.push_back(" ");
                tokens.push_back(checkToken);
                tokens.push_back(" ");
                chkLongTok = "";
                checkToken = "";
            }
            else if (isSpecial(checkToken)) {
                tokens.push_back(" ");
                tokens.push_back(checkToken);
                tokens.push_back(" ");
                if (checkToken == ";") {
                    tokens.push_back("\n");
                    checkToken = "";
                }
                chkLongTok = "";
                checkToken = "";
            }
            else {
                tokens.push_back(checkToken);
                checkToken = "";
            }
    }
    for (int i = 0; i < tokens.size(); ++i) {
        output << tokens[i];
    }
}