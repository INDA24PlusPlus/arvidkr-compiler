#ifndef AST_H
#define AST_H

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cmath>
#include "lexer.h"

using namespace std;

struct AST {
    string id;   
    int value;
    vector<AST*> children;
    vector<string> edgeID;

    void add_while(vector<vector<Token>> lines){
        cout << "now at add_while; line: " << lines[0][0].value << endl;
        //lines -> fulla rader, while till slut, 
        //den har tagit från whiles början tills den når slut eller befinner sig utanför while
        AST* nWhile = new AST();
        nWhile->id = "While";
        children.push_back(nWhile);
        edgeID.push_back("While");
        vector<Token> line1 = lines[0];
        //line1[0] är radnr, line1[1] är while, line1[2] är kanske variabel, line1[3] boolesk operation, line1[4] andra variabel/konstant, line1[5] är var den ska gå härnäst
        vector<Token> conditionLine = {line1[2], line1[3], line1[4]};
        nWhile->add_condition(conditionLine);
        vector<vector<Token> > bodies;
        for (int i = 1; i < lines.size(); i++)bodies.push_back(lines[i]);
        nWhile->add_body(bodies);
    }

    void add_nif(vector<vector<Token>> lines){
        cout << "now at add_nif; line: " << lines[0][0].value << endl;

        AST* nIf = new AST();
        children.push_back(nIf);
        edgeID.push_back("Something Done");
        nIf->id = "Nif";
        vector<Token> line1 = lines[0];
        //line1[0] är radnr, line1[1] är while, line1[2] är kanske variabel, line1[3] boolesk operation, line1[4] andra variabel/konstant, line1[5] är var den ska gå härnäst
        vector<Token> conditionLine = {line1[2], line1[3], line1[4]};
        nIf->add_condition(conditionLine);
        vector<vector<Token> > bodies;
        for (int i = 1; i < lines.size(); i++)bodies.push_back(lines[i]);
        nIf->add_body(bodies);
    }

    void add_print(Token T){
        AST* print = new AST();
        children.push_back(print);
        edgeID.push_back("PRINT");
        if (T.token_id == "Variable")print->add_variable(T);
        else if (T.token_id == "Constant")print->add_constant(T);
        else cout << "Cannot print of type " << T.token_id << endl;
        print->id = "Print";
    }

    void add_arithmetic(vector<Token> line){
        AST* arithmetic = new AST();
        children.push_back(arithmetic);
        edgeID.push_back("Operation");

        if (line.size() == 3){
            if (line[0].token_id == "Variable")arithmetic->add_variable(line[0]);
            else if (line[0].token_id == "Integer")arithmetic->add_constant(line[0]);
            else cout << "Crashed at add_arithmetic " << line[0].token_id << " is not Variable or Integer" << endl;

            if (line[1].value == 0)arithmetic->id = "+";
            else if (line[1].value == 1)arithmetic->id = "-";
            else if (line[1].value == 2)arithmetic->id = "*";
            else if (line[1].value == 3)arithmetic->id = "/";
            else if (line[1].value == 4)arithmetic->id = "^";
            else cout << "Crashed at add_arithmetic " << line[1].value << " is not valid" << endl;
            
            if (line[2].token_id == "Variable")arithmetic->add_variable(line[2]);
            else if (line[2].token_id == "Integer")arithmetic->add_constant(line[2]);
            else cout << "Crashed at add_arithmetic " << line[2].token_id << " is not Variable or Integer" << endl;
        }
        else {
            if (line[line.size()-2].value == 0)arithmetic->id = "+";
            else if (line[line.size()-2].value == 1)arithmetic->id = "-";
            else if (line[line.size()-2].value == 2)arithmetic->id = "*";
            else if (line[line.size()-2].value == 3)arithmetic->id = "/";
            else if (line[line.size()-2].value == 4)arithmetic->id = "^";
            else cout << "Crashed at add_arithmetic " << line[line.size()-2].value << " is not valid" << endl;

            vector<Token> nLine;
            for (int i = 0; i < line.size()-2; i++){
                nLine.push_back(line[i]);
            }
            arithmetic->add_arithmetic(nLine);

            if (line[line.size()-1].token_id == "Variable")arithmetic->add_variable(line[line.size()-1]);
            else if (line[line.size()-1].token_id == "Integer")arithmetic->add_constant(line[line.size()-1]);
            else cout << "Crashed at add_arithmetic " << line[line.size()-1].token_id << " is not Variable or Integer" << endl;
        }
    }

    void add_assign(vector<Token> line){
        AST* assign = new AST();
        children.push_back(assign);
        edgeID.push_back("Assign");
        assign->id = "copy-assign";
        assign->add_variable(line[0]);
        //första är vilken variabel, andra är vilken operator, resten är aritmetiskt påstående I guess, till slutet
        vector<Token> nLine;
        for (int i = 2; i < line.size(); i++){
            nLine.push_back(line[i]);
        }
        if (nLine.size() == 1){
            if (nLine[0].token_id == "Integer") assign->add_constant(nLine[0]);
            else assign->add_variable(nLine[0]);
        }
        else assign->add_arithmetic(nLine);
    }

    void add_body(vector<vector<Token> > lines){
        //i ordning, pls
        cout << "now at add_body; line: " << lines[0][0].value << endl;

        AST* body = new AST();
        children.push_back(body);
        edgeID.push_back("Body");
        body->id = "body";
        for (int i = 0; i < lines.size(); i++){
            vector<Token> v = lines[i];
            cout << "at row: " << v[0].value << endl;
            if (v[1].token_id == "While-Loop"){
                vector<vector<Token> > templines = {v};
                i++;
                for (; lines[i][0].value != v[1].value; i++)templines.push_back(lines[i]);
                i--;
                body->add_while(templines);
            }
            else if (v[1].token_id == "Variable"){
                vector<Token> line;
                line.push_back(v[1]);
                line.push_back(v[2]);
                if (v[2].token_id == "Set-Operator"){
                    for (int i = 3; i < v.size()-1; i++)line.push_back(v[i]);
                    body->add_assign(line);
                }
                else {
                    cout << "huh?" << endl;
                }
            }
            else if (v[1].token_id == "NIf-Statement"){
                vector<vector<Token> > templines = {v};
                i++;
                for (; lines[i][0].value != v[1].value; i++)templines.push_back(lines[i]);
                i--;
                body->add_nif(templines);
            }
            else if (v[1].token_id == "Print"){
                Token T = v[2];
                body->add_print(T);
            }
        }
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
        cout << "add_var" << endl;
        AST* nVariable = new AST();
        children.push_back(nVariable);
        edgeID.push_back("Variable");
        nVariable->id = "Variable";
        nVariable->value = T.value;
        return;
    }

    void add_condition(vector<Token> line){
        AST* condition = new AST();
        children.push_back(condition);
        edgeID.push_back("Condition");

        if (line[0].token_id == "Variable")condition->add_variable(line[0]);
        else if (line[0].token_id == "Integer")condition->add_constant(line[0]);
        else cout << "Crashed at add_arithmetic " << line[0].token_id << " is not Variable or Integer" << endl;

        if (line[1].value == 0)condition->id = "==";
        else if (line[1].value == 1)condition->id = ">";
        else if (line[1].value == 2)condition->id = "<";
        else if (line[1].value == 3)condition->id = ">=";
        else if (line[1].value == 4)condition->id = "<=";
        else if (line[1].value == 8)condition->id = "!=";
        else cout << "Crashed at add_arithmetic " << line[1].value << " is not valid" << endl;
        

        if (line[2].token_id == "Variable")condition->add_variable(line[2]);
        else if (line[2].token_id == "Integer")condition->add_constant(line[2]);
        else cout << "Crashed at add_arithmetic " << line[2].token_id << " is not Variable or Integer" << endl;
    }

    void add_eof(){
        AST* eofi = new AST();
        eofi->id = "EOF";
        children.push_back(eofi);
        edgeID.push_back("end");
    }
    
};


void dfs(AST* start, vector<pair<string, int>>& in_order_list);
void traverse(AST* curr, set<char>& declared_variables, int indent_flag, bool endline_flag);
void transpile_c(AST& Program, vector<pair<string, int> > in_order_list);
void create_ast(bool wants_to_compile, bool wants_to_run);



#endif /* AST_H */