#ifndef _SYMBOLSTABLE_
#define _SYMBOLSTABLE_
#include <string>
#include <vector>
#include "hw3_output.hpp"
using namespace std;
extern int yylineno;

class VarDecleration{
    string name;
    string type;
    int offset;

public:
    VarDecleration(string new_name, string new_type, int new_offset) : name(new_name), type(new_type), offset(new_offset){}

    string getName(){
        return name;
    }
    string getType(){
        return type;
    }
    void setOffset(int new_offset){
        offset = new_offset;
    }
    int getOffset(){
        return offset;
    }
};

class FuncDecleration{
    string name;
    string retType;
    vector<string> argsType;
public:
    FuncDecleration(string func_name, string ret_type, vector<string> args_type) : name(func_name), retType(ret_type),
                                                                                   argsType(args_type){}
    string getName(){
        return name;
    }
    string getType(){
        return retType;
    }
    vector<string> getArgs(){
        return argsType;
    }
};


class symbolsTable{
    vector<int>* offsets;
    vector<vector<VarDecleration>>* names;

public:
    symbolsTable() : offsets(new vector<int>), names(new vector<vector<VarDecleration>>()){}

    /*
      This function inserts a new variable to the symbols table, it could be
      a new variable declared in the scope or a function argument.
    */
    void Insert(const string& name, const string& type, bool funcArg = false);

    void closeScope();

    void openScope();

    /*
       This function checks if a variable with var_name was declared in outer scopes and returns its type.
       Returns an empty string if wasn't found.
    */
    string checkVariableDeclared(const string& var_name);

};

class FuncsTable{
    vector<FuncDecleration>* functions;
public:
    FuncsTable();
    void Insert(string name, string ret_type, vector<string> args_type);


    /*
     * This function checks if the arguments supplied match with the called function arguments,
     * and if the function exists.
     * returned value: return type of the called function
     */
    string checkArgsValid(string func_name, vector<string> args);

    void printTable();

};


#endif