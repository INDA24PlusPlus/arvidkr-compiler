#include <iostream>
#include "lexer.h"

using namespace std;

typedef long long ll;

int main(){
    freopen("example.txt", "r", stdin);
    vector<Token> v = tokenize_file();
    print_tokens({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
    //cout << "hello there" << endl;
    

    return 0;
}