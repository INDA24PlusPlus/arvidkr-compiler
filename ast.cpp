#include "ast.h"
#include "lexer.h"

map<int, vector<Token> > code;

struct AST {
    string id;   
    int value;
    vector<AST*> children;
    vector<string> edgeID;

    void add_while(vector<vector<Token>> lines){
        AST* nWhile = new AST();
        children.push_back(nWhile);
        edgeID.push_back("Something Done");
        vector<Token> line1 = lines[0];
        
    }

    void add_arithmetic(vector<Token> line){
        AST* arithmetic = new AST();
        children.push_back(arithmetic);
        edgeID.push_back("Operation");
        //BORDE INNEHÅLLA TRE TOKENS, VAD OPERATION VAD2
        if (line[0].)
    }

    void add_constant(Token T){
        AST* nConstant = new AST();
        children.push_back(nConstant);
        edgeID.push_back("Constant");
        nConstant->id = "Constant";
        nConstant->value = T.value;
        return;
    }

    void add_variable(Token T){
        AST* nVariable = new AST();
        children.push_back(nVariable);
        edgeID.push_back("Variable");
        nVariable->id = "Variable";
        nVariable->value = T.value;
        return;
    }

    void add_condition(vector<Token> line){

    }
    
};


void create_ast(){
    AST Program;
    code = tokenize_file();
    Program.id = "Program";

    while (true){

    }

}