#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>

using namespace std;


struct Token {
    std::string token_id;
    int value;
    int index;
}; 

int binarystrb10(std::string bina);
int stringint(std::string numb);
std::vector<Token> tokenize_row(std::string row);
std::vector<Token> tokenize_file();
std::string token_to_string(Token T);
void print_tokens(std::vector<int> whatrows);





#endif /* LEXER_H */