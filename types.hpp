#ifndef _TYPES_
#define _TYPES_
#include <string>
#include <vector>
using namespace std;

    struct Node {
		string name;
		string type;
	};
	class Identifier: public Node {
		public:
		explicit Identifier(string new_name){
			name = new_name;
		}
	};
    
	class Type: public Node{
        public:
		explicit Type(string new_type) {
		    type = new_type;
		}
    
    };
    class Exp: public Node{  
        public:
        Exp(char* type){ 
            this->type = type;
        }
        Exp(string type){
            this->type = type;
        }
    };
    
    class ExpList: public Node{
        //vector for the explist, each element is of type exp
        vector<Exp> expList;
        
		public:
		explicit ExpList(Exp* exp){
			expList.push_back(*exp);
		}
        ExpList(Exp* exp, ExpList* list){
            expList = vector<Exp>(list);
            expList.emplace(expList.begin(),Exp); // at the begging of the vector
		}
	};
    class Call: public Node{
		public:
		explicit Call(string value){
		    type = value;
		}
	};
	
    #define YYSTYPE Node
    
#endif