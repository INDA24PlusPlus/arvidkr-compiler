#include <iostream>
#include "lexer.h"
#include "ast.h"

using namespace std;

typedef long long ll;

int main(){
    cout << "What file to build AST and transpile to C? ";
    string fil; cin >> fil;
    const char *fili = fil.c_str();
    cout << "Do you also want to compile the code? y/n:   ";
    char choice; cin >> choice;
    cout << "Do you want to run it? (writes to code-output.txt)  y/n:   ";
    char sec_choice; cin >> sec_choice;
    freopen(fili, "r", stdin);
    create_ast(choice == 'y', sec_choice == 'y');

    freopen("parser-output.txt", "w", stdout);
    print_tokens({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});


    //cout << "hello there" << endl;
    

    return 0;
}
