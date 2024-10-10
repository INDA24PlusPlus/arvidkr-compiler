#include "ast.h"

map<int, vector<Token> > code;


void dfs(AST* start){
    cout << start->id << " " << start->value << endl;
    for (int i = 0; i < start->children.size(); i++){
        cout << "Now travelling by: " << start->edgeID[i] << " from " << start->id << " to " << start->children[i]->id << endl;
        dfs(start->children[i]);
    }
    cout << endl;
}

void create_ast(){
    AST Program;
    code = tokenize_file();
    Program.id = "Program";

    vector<bool> isVisited(false, 200001);
    int currLine = 1;

    int endingLine = 0;

    vector<vector<Token> > program;

    while (true){
        if (currLine == endingLine){
            break;
        }
        cout << currLine << endl;

        vector<Token> v = code[currLine];
        if (currLine == 1){
            endingLine = v[1].value;
        } else {
            program.push_back(v);
        }
        if (v[v.size()-1].value == 0)currLine++;
        else currLine = v[v.size()-1].value;

    }

    Program.add_body(program);
    for (int i = 0; i < Program.children.size(); i++){
        cout << "PROGRAM TRAVEL! " << Program.edgeID[i] << " " << Program.children[i]->id << endl;
        dfs(Program.children[i]);
    }

}