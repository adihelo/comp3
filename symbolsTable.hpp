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
    /*bool checkparam(vector<string> par_vec){  // added
        for(int i=0; i<par_vec.size();i++){
            if((this->params[i] != par_vec[i])&& !( this->params[i]=="INT" && par_vec[i]=="BYTE"){
                return false;            
                          
            }
        }
        return true;
    }*/
    void setOffset(int new_offset){
        offset = new_offset;
    }
};

class FuncDecleration{
    string name;
    string retType;
    vector<string> argsType;
public:
    FuncDecleration(string func_name, string ret_type, vector<string> args_type){
        name = func_name;
        retType = ret_type;
        argsType = args_type;
    }
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
	int curr_offset;            // offset for new IDs decleration
	int func_arg_offset;        // offset for function decleration arguments   
	
	public:
	symbolsTable() : offsets(new vector<int>), names(new vector<vector<VarDecleration>>), curr_offset(0)
	                 ,func_arg_offset(-1){}
	
	/*
	  This function inserts a new variable to the symbols table, it could be
	  a new variable declared in the scope or a function argument.
	*/
	void Insert(string name, string type, bool newScope, bool funcArg){
		int offset = 0;
		VarDecleration dec = VarDecleration(name,type,offset);
		if (funcArg){
		    dec.setOffset(func_arg_offset);
			func_arg_offset -= 1;
			offset = func_arg_offset;
		}
		else{
			curr_offset += 1;
			offset = curr_offset;
		}
		
		if(newScope || names->size() == 0){
			offsets->push_back(offset);
			vector<VarDecleration> new_vec;
			new_vec.push_back(dec);
			names->push_back(new_vec);
			return;
		}
		names->back().push_back(dec);
		offsets->back() = offset;
	}
	
	void pop(){
		offsets->pop_back();
		names->pop_back();
	}
	
	/*
	   This function checks if a variable with var_name was declared in outer scopes and returns its type.
	   Returns an empty string if wasn't found.
	*/
	string checkVariableDeclared(string var_name){
		string var_type = "";
		for(int i= names->size()-1 ; i>=0 ; i--){
			for(int j=0; j<= names[i].size() ; j++){
				if(names[i][j].getName() == var_name){
					var_type = names[i][j].getType();
				}
			}
		}
		return var_type;
	}

};

class FuncsTable{
    vector<FuncDecleration>* functions;
public:
    FuncsTable(): functions(new vector<FuncDecleration>()){
        vector<string> print_vec{"STRING"};
        vector<string> printi_vec{"INT"};
        Insert("print", "VOID", print_vec);
        Insert("printi", "VOID", printi_vec);
    }
    Insert(string name, string ret_type, vector<string> args_type){
        FuncDecleration function = FuncDecleration(name, ret_type, args_type);
        functions->push_back(function);
    }


    /*
     * This function checks if the arguments supplied match with the called function arguments,
     * and if the function exists.
     * returned value: return type of the called function
     */
    string checkArgsValid(string func_name, vector<string> args){
        bool exists = false;
        string ret_type;
        for (int i = 0; i < functions->size(); ++i) {
            if(functions[i].getName() == func_name){
                exists = true;
                ret_type = functions[i].getType();
                for (int j = 0; j < functions[i].getArgs().size(); ++j) {
                    if(args[j] != (functions[i].getArgs())[j]){
                        output::errorPrototypeMismatch(yylineno, func_name, functions[i].getArgs());
                        exit(0);
                    }
                }
            }
        }
        if(!exists){
            output::errorUndefFunc(yylineno, name);
            exit(0);
        }
        return ret_type;
    }

    void printTable(){
        for (int i = 0; i < functions->size() ; ++i) {
            string func_type = output::makeFunctionType(functions[i].getType(), functions[i].getArgs());
            output::printID(functions[i].getName(),0,func_type);
        }
    }

};
   
    
#endif