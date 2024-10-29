#include "ast.h"

map<int, vector<Token> > code;


void dfs(AST* start, vector<pair<string, int>>& in_order_list){
    in_order_list.push_back({start->id, start->value});
    cout << start->id << " " << start->value << endl;
    for (int i = 0; i < start->children.size(); i++){
        cout << "Now travelling by: " << start->edgeID[i] << " from " << start->id << " to " << start->children[i]->id << endl;
        dfs(start->children[i], in_order_list);
    }
    cout << endl;
}

string alphabet = "abcdefghijklmnopqrstuvwxyz";

void traverse(AST* curr, set<char>& declared_variables, int indent_flag, bool endline_flag){
    string id = curr->id;
    int value = curr->value;
    if (id == "copy-assign"){
        for (int i = 0; i < indent_flag; i++)cout << "    ";
        traverse(curr->children[0], declared_variables, 0, 0);
        cout << " = ";
        traverse(curr->children[1], declared_variables, 0, 0);
        if (endline_flag)cout << ";" << endl;
    }
    else if (id == "Variable"){
        for (int i = 0; i < indent_flag; i++)cout << "    ";
        if (declared_variables.find(alphabet[value]) == declared_variables.end()){
            cout << "int ";
            declared_variables.insert(alphabet[value]);
        }
        cout << alphabet[value];
        if (endline_flag)cout << ";" << endl;
    }
    else if (id == "Constant"){
        for (int i = 0; i < indent_flag; i++)cout << "    ";
        cout << value;
        if (endline_flag)cout << ";" << endl;
    }
    else if (id == "While"){
        for (int i = 0; i < indent_flag; i++)cout << "    ";
        cout << "while(";
        traverse(curr->children[0], declared_variables, 0, 0);
        cout << "){" << endl;
        traverse(curr->children[1], declared_variables, indent_flag+1, 1);
        for (int i = 0; i < indent_flag; i++)cout << "    ";
        cout << "}" << endl;
    }
    else if (id == "body"){
        for (int i = 0; i < curr->children.size(); i++){
            traverse(curr->children[i], declared_variables, indent_flag, endline_flag);
        }
    }
    else if (id == "Print"){
        for (int i = 0; i < indent_flag; i++)cout << "    ";
        cout << "printf(\"\%d\\n\", ";
        traverse(curr->children[0], declared_variables, 0, 0);
        cout << ")";
        if (endline_flag)cout << ";" << endl;
    }
    else if (id == "==" || id == ">" || id == "<" || id == ">=" || id == "<=" || id == "!="){
        traverse(curr->children[0], declared_variables, 0, 0);
        cout << " " << id << " ";
        for (int i = 1; i < curr->children.size(); i++){
            traverse(curr->children[i], declared_variables, 0, 0);
        }
    } 
    else if (id == "+" || id == "*" || id == "/" || id == "-" || id == "^"){
        for (int i = 0; i < indent_flag; i++)cout << "    ";
        traverse(curr->children[0], declared_variables, 0, 0);
        cout << " " << id << " ";
        traverse(curr->children[1], declared_variables, 0, 0);
        if (endline_flag)cout << ";" << endl;
    }


}

void transpile_c(AST& Program, vector<pair<string, int> > in_order_list){
    freopen("code.c", "w", stdout);
    set<string> ids;

    for (auto p : in_order_list)ids.insert(p.first);

    if (ids.find("Print") != ids.end()){
        cout << "#include <stdio.h>" << endl << endl;
    }

    cout << "int main() {" << endl;

    set<char> declared_variables;

    traverse(Program.children[0], declared_variables, 1, 1);

    cout << "    return 0;" << endl << "}" << endl;

}


void create_ast(bool wants_to_compile, bool wants_to_run){
    freopen("ast-output.txt", "w", stdout);
    AST Program;
    code = tokenize_file();
    Program.id = "Program";

    bool isVisited[200001];
    int currLine = 1;

    int endingLine = 0;

    vector<vector<Token> > program;

    while (true){
        if (currLine == endingLine){
            break;
        }
        isVisited[currLine] = true;
        cout << currLine << endl;

        vector<Token> v = code[currLine];
        if (currLine == 1){
            endingLine = v[1].value;
        } else {
            program.push_back(v);
        }
        if (v[v.size()-1].value == 0)currLine++;
        else if (isVisited[v[v.size()-1].value]){
            currLine++;
        }
        else currLine = v[v.size()-1].value;

    }

    vector<pair<string, int> > v;
    Program.add_body(program);
    for (int i = 0; i < Program.children.size(); i++){
        cout << "PROGRAM TRAVEL! " << Program.edgeID[i] << " " << Program.children[i]->id << endl;
        dfs(Program.children[i], v);
    }

    transpile_c(Program, v);

    if (wants_to_compile){
        system("gcc code.c -o code");
    }
    freopen("code-output.txt", "w", stdout);
    if (wants_to_run){
        //fclose(stdout);
        system("./code");
    }
}