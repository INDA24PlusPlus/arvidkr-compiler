#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>

using namespace std;


struct Token {
    string token_id;
    int value;
    int index;
}; 

int binarystrb10(std::string bina);
int stringint(std::string numb);
vector<Token> tokenize_row(std::string row);
map<int, vector<Token>> tokenize_file();
std::string token_to_string(Token T);
void print_tokens(std::vector<int> whatrows);





#endif /* LEXER_H */