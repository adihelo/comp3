#include "symbolsTable.hpp"
void symbolsTable::Insert(const string &name, const string &type, bool funcArg) {
    if(offsets->empty()){
        if(funcArg){
            offsets->push_back(-1);
        } else{
            offsets->push_back(0);
        }
    }
    VarDecleration decleration(name,type, offsets->back());
    if(offsets->back() < 0){
        offsets->back() -= 1;
    } else{
        offsets->back() += 1;
    }
    names->back().push_back(decleration);

}

void symbolsTable::closeScope() {
    for (auto & i : names->back()) {
        output::printID(i.getName(), i.getOffset(), i.getType());
    }
    offsets->pop_back();
    names->pop_back();
}

void symbolsTable::openScope() {
    vector<VarDecleration> new_vec;
    names->push_back(new_vec);
    if(offsets->empty()){
        return;
    }
    if(offsets->back() < 0){
        offsets->push_back(0);
    } else{
        offsets->push_back(offsets->back()+1);
    }
}

string symbolsTable::checkVariableDeclared(const string &var_name) {
    string var_type;
    for(int i= names->size()-1 ; i>=0 ; i--){
        for(int j=0; j<= names[i].size() ; j++){
            if((*names)[i][j].getName() == var_name){
                var_type = (*names)[i][j].getType();
            }
        }
    }
    return var_type;
}

FuncsTable::FuncsTable() : functions(new vector<FuncDecleration>()){
    vector<string> print_vec{"STRING"};
    vector<string> printi_vec{"INT"};
    Insert("print", "VOID", print_vec);
    Insert("printi", "VOID", printi_vec);
}

void FuncsTable::Insert(string name, string ret_type, vector<string> args_type) {
    FuncDecleration function = FuncDecleration(name, ret_type, args_type);
    functions->push_back(function);
}

string FuncsTable::checkArgsValid(string func_name, vector<string> args) {
    bool exists = false;
    string ret_type;
    for (auto & function : *functions) {
        if(function.getName() == func_name){
            exists = true;
            ret_type = function.getType();
            for (int j = 0; j < function.getArgs().size(); ++j) {
                if(args[j] != (function.getArgs())[j]){
                    vector<string> args_v = function.getArgs();
                    output::errorPrototypeMismatch(yylineno, func_name, args_v);
                    exit(0);
                }
            }
        }
    }
    if(!exists){
        output::errorUndefFunc(yylineno, func_name);
        exit(0);
    }
    return ret_type;
}

void FuncsTable::printTable() {
    for (auto & function : *functions) {
        vector<string> args_v = function.getArgs();
        string func_type = output::makeFunctionType(function.getType(), args_v);
        output::printID(function.getName(),0,func_type);
    }
}
