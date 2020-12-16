#ifndef _TYPES_
#define _TYPES_
#include <string>
using namespace std;

    struct Node {
		string name;
		string type;
	};
	class Identifier: public Node {
		public:
		Identifier(string new_name){
			name = new_name;
		}
	};
    
	class Integer: public Node{
		public:
		Integer(string new_type){
			type = new_type;
		}
	};
	
	class Byte: public Node{
		public:
		Byte(string new_type){
			type = new_type;
		}
	};
	
	class Bool: public Node{
		public:
		Bool(string new_type){
			type = new_type;
		}
	};	
    class Exp: public Node{  //to do 
        
    }
    
    class ExpList: public Node{
        //vector for the explist, each element is of type exp
        vector<Exp> expList;
        
		public:
		Call(Exp* exp){
			explist.push_back(exp);
		}
        Call(Exp* exp, ExpList* list){
            expList = vector<Exp>(list);
            expList.emplace(expList.begin(),Exp); // at the begging of the vector
		}
	};
    class Call: public Node{
		public:
		Call(string value):type(value){}
	};
	
    #define YYSTYPE Node
    
#endif