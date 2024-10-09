#include "lexer.h"

typedef long long ll;

map<int, vector<Token>> M;

int binarystrb10(string bina){
    int ret = 0;
    for (int i = 0; i < bina.size(); i++){
        ret += (bina[i]-'0')*pow(2, bina.size()-i-1);
    }
    return ret;
}

int stringint(string numb){
    if (numb[0] == 'b'){
        string ns = "";
        for (int i = 1; i < numb.size(); i++) ns += numb[i];
        return stoi(ns);
    }
    return binarystrb10(numb);
}

vector<Token> tokenize_row(string row){
    vector<string> whitespacesplit;
    vector<Token> ret;
    string t = "";
    for (char c : row){
        if (c == ' '){
            whitespacesplit.push_back(t);
            t = "";
        }
        else t += c;
    }
    if (t != "")whitespacesplit.push_back(t);

    int line = 0;
    for (int i = 0; i < whitespacesplit.size(); i++){
        string untokenized = whitespacesplit[i];
        Token T;
        if (i == 0){
            T.token_id = "Line-ID";
            T.value = stringint(untokenized);
            T.index = ret.size();
            line = T.value;
        }
        else if (untokenized == "0000!"){
            i++;
            T.token_id = "Integer";
            T.value = stringint(whitespacesplit[i]);
            T.index = ret.size();
        }
        else if (untokenized == "0001!"){
            i++;
            T.token_id = "Operator";
            T.value = stringint(whitespacesplit[i]);
            T.index = ret.size();
        }
        else if (untokenized == "0010!"){
            i++;
            T.token_id = "Set-Operator";
            T.value = stringint(whitespacesplit[i]);
            T.index = ret.size();
        }
        else if (untokenized == "0011!"){
            i++;
            T.token_id = "Boolean-Operator";
            T.value = stringint(whitespacesplit[i]);
            T.index = ret.size();
        }
        else if (untokenized == "0100!"){
            T.token_id = "If-Statement";
            T.value = -1;
            T.index = ret.size();
        }
        else if (untokenized == "0101!"){
            T.token_id = "NIf-Statement";
            T.value = -1;
            T.index = ret.size();
        }
        else if (untokenized == "0110!"){
            i++;
            T.token_id = "Variable";
            T.value = stringint(whitespacesplit[i]);
            T.index = ret.size();
        }
        else if (untokenized == "0111!"){
            T.token_id = "Print";
            T.value = -1;
            T.index = ret.size();
        }
        else if (untokenized == "1000!"){
            i++;
            T.token_id = "Go-To";
            T.value = stringint(whitespacesplit[i]);
            T.index = ret.size();
        }
        else if (untokenized == "1111!"){
            i++;
            T.token_id = "EOF-Declaration";
            T.value = stringint(whitespacesplit[i]);
            T.index = ret.size();
        }
        else {
            cout << "ERROR, NO TYPE FOUND" << endl;
            return {};
        }

        ret.push_back(T);
    }

    M[line] = ret;

    return ret;
}


vector<Token> tokenize_file(){
    vector<Token> ret;
    string line;
    while (getline(cin, line)){
        vector<Token> temp = tokenize_row(line);
        for (Token T : temp)ret.push_back(T);
    }
    return ret;
}

string token_to_string(Token T){
    string ret = T.token_id;
    if (T.value == -1)return ret;
    ret += '(';
    string ts = to_string(T.value);
    for (auto c : ts){
        ret += c;
    }
    ret += ')';
    return ret;
}

void print_tokens(vector<int> whatrows){
    for (auto row_id : whatrows){
        vector<Token> row = M[row_id];
        vector<string> row_strings;
        for (Token T : row){
            row_strings.push_back(token_to_string(T));
        }
        for (auto e : row_strings)cout << e << " , ";
        cout << endl;
    }
}