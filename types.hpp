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
	
    #define YYSTYPE Node
    
#endif