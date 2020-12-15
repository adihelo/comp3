#ifndef _SYMBOLSTABLE_
#define _SYMBOLSTABLE_
#include <string>
#include <vector>
using namespace std;

class Decleration{
	string name;
	string type;
	int offset;
	
	public:
	Decleration(string new_name, string new_type, int new_offset) : name(new_name), type(new_type), offset(new_offset){}
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
};
   
    
#endif