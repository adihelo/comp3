#ifndef _SYMBOLSTABLE_
#define _SYMBOLSTABLE_
#include <string>
#include <vector>
using namespace std;

class Decleration{
	string name;
	string type;    
	int offset;
	vector<string> params; // added for function params (does not contain the return type)
	public:
	Decleration(string new_name, string new_type, int new_offset) : name(new_name), type(new_type), offset(new_offset){}
	Decleration(string new_name, string new_type, int new_offset, vector<string> param_vec){  //added
        this->name=new_name;
        this->type=new_type; 
        this->offset=new_offset;
        this->param = param_vec;
    }
    vector<string> getparam(){
        return this->params;
    
    }
    string getName(){
        return name;
    }
    string getType(){
        return type;
    }
    bool checkparam(vector<string> par_vec){  // added
        for(int i=0; i<par_vec.size();i++){
            if((this->params[i] != par_vec[i])&& !( this->params[i]=="INT" && par_vec[i]=="BYTE"){
                return false;            
                          
            }
                    
        }
        return true;
    }
};

class symbolsTable{
	vector<int>* offsets;
	vector<vector<Decleration>>* names;
	int curr_offset;
	
	public:
	symbolsTable() : offsets(new vector<int>), names(new vector<vector<Decleration>>), curr_offset(0){}
	void Insert(string name, string type, bool newScope){
		Decleration dec = Decleration(name, type, offset);
		curr_offset += 1;
		if(newScope){
			offsets->push_back(curr_offset);
			vector<Decleration> new_vec;
			new_vec.push_back(dec);
			names->push_back(new_vec);
			return;
		}
		
		names->back().push_back(dec);
		offsets->back() = curr_offset;
	}
	
	void pop(){
		offsets->pop_back();
		names->pop_back();
	}
    
    
    
    /*
     This function checks if the function with the id and explist is valid
    */
   string checkFuncExists(string id, vector<string> explist){
         for (auto it = names.rbegin(); it != names.rend(); ++it){
            for (auto it_dec = it->rbegin(); it_dec != it->rend(); ++it_dec){
                if(*(it_dec)->getName()==name){
                    //check the param list
                    if((*(it_dec)->getparam().size() != explist.size())||(!(*(it_dec)->checkparam(explist)))){
                       errorPrototypeMismatch(yylineno, id, *(it_dec)->getparam());
                       exit(0);
                    }
                   return *(it_dec)->getType(); // return type
                }
                output::errorUndefFunc(yylineno, id); //did not find a function with the given id
                exit(0);
            
            
            }
        
        
        }   
        
    }
};
   
    
#endif