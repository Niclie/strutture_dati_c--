#ifndef INTERPRETE_H_
#define INTERPRETE_H_

#include "../Lista/List.h"
#include <fstream>
#include <algorithm>
#include "../Stack/Stack.h"
using std::string;

typedef struct{
	char var;
	int num;
} Equation;

class Interpete{
private:
	List<Equation> list;

public:
	List<string> infixToPostfix(List<string>);
	bool isOperator(string s);

	int getValue(char c){
		for(List<Equation>::Position i = list.begin(); !list.end(i); i = list.next(i)){
			if(c == list.read(i).var)
				return list.read(i).num;
		}
	}

	bool isAssignment(std::string s){
		if(s.at(0) == '(' && s.at(2) == '=')
			return true;
		else
			return false;
	}

	int evaluatePostfix(List<string> exp);

	void readFile(std::string fileName){
		std::string istruction;

		std::ifstream file(fileName);
		while (std::getline(file, istruction)){
			removeSpaces(istruction);

			if(isAssignment(istruction)){
				if(istruction.at(3) == '('){
					Equation eq;

					eq.var = istruction.at(1);
					eq.num = 0;

					for(int i = 3; i < istruction.length(); i++){
						if(isdigit(istruction[i])){
							int j = 1;
							while(isdigit(istruction[i + j])){
								j++;
							}
							eq.num = eq.num + std::stoi(istruction.substr(i, j));
							i = i + j - 1;
						}
						else{
							string value = istruction.substr(i, 1);
							if(!isOperator(value) && value != "(" && value != ")"){
								for(List<Equation>::Position k = list.begin(); !list.end(k); k = list.next(k)){
									if(list.read(k).var == value.at(0)){
										eq.num = eq.num + list.read(k).num;
										break;
									}
								}
							}
						}
					}

					list.pushBack(eq);
				}
				else{
					Equation eq;
					eq.var = istruction.at(1);
					eq.num = (int) istruction.at(3) - '0';
					list.pushBack(eq);
				}
			}
			else{
				List<string> eq;
				for(int i = 0; i < istruction.length(); i++){
					if(istruction.at(i) != ' '){
						if(isdigit(istruction[i])){
							int j = 1;
							while(isdigit(istruction[i + j])){
								j++;
							}
							eq.pushBack(istruction.substr(i, j));
							i = i + j - 1;
						}
						else{
							string value = istruction.substr(i, 1);
							if(!isOperator(value) && value != "(" && value != ")"){
								for(List<Equation>::Position k = list.begin(); !list.end(k); k = list.next(k)){
									if(list.read(k).var == value.at(0)){
										eq.pushBack(std::to_string(list.read(k).num));
										break;
									}
								}
							}
							else
								eq.pushBack(value);
						}
					}
				}
				cout<<evaluatePostfix(infixToPostfix(eq));//TODO
			}
		}

		file.close();
	}

	void removeSpaces(string& str){
	    str.erase(remove(str.begin(), str.end(), ' '), str.end());
	}

	int operation(string s){
		int r = 0;
		for(int i = 1; i < s.length(); i = i + 2){
			if(s.at(i) == 'x' || s.at(1) == 'y'){
				r = r + getValue(s.at(1));
			}
			else if(s.at(2) == '+')
				r = r + (s.at(i) - '0');
			else if(s.at(2) == '-')
				r = r - (s.at(i) - '0');
			else if(s.at(2) == '*')
				r = r * (s.at(i) - '0');
		}

		return r;
	}
};

int priority(string s){
    if(s == "+" || s == "-")
    	return 1;
    else if(s == "*" || s == "/")
    	return 2;

    return 0;
}


bool Interpete::isOperator(string s){
    if(s == "+" || s == "-" || s == "*" || s == "/")
        return true;

    return false;
}

bool isNumber(const string& s){
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

List<string> Interpete::infixToPostfix(List<string> s){
    Stack<string> st;
    List<string> ns;

    for(List<string>::Position it = s.begin(); !s.end(it); it = s.next(it)){
    	if(isNumber(s.read(it)))
    		ns.pushBack(s.read(it));

    	else if(s.read(it) == "(")
        	st.inpila("(");

    	else if(isOperator(s.read(it))){
        	bool found = false;
            do{
            	if(st.empty()){
                    st.inpila(s.read(it));

                    found = true;
                }
                else if(st.leggiPila() == "("){
                    st.inpila(s.read(it));

                    found = true;
                }
                else if(priority(s.read(it)) >= priority(st.leggiPila())){
                    st.inpila(s.read(it));

                    found = true;
                }
                else{
                	ns.pushBack(st.leggiPila());
                    st.fuoriPila();
                }
            }while(!found);
        }
        else if(s.read(it) == ")"){
            while(st.leggiPila() != "(" && !isNumber(s.read(it))){
            	ns.pushBack(st.leggiPila());
            	st.fuoriPila();
            }
            if(st.leggiPila() == "("){
                st.fuoriPila();
            }
        }
    }

    return ns;
}

int Interpete::evaluatePostfix(List<string> exp)  {
    int i;
    Stack<int> stack;

    for (List<string>::Position it = exp.begin(); !exp.end(it); it = exp.next(it)){
        if (isNumber(exp.read(it)))
            stack.inpila(std::stof(exp.read(it)));
        else{
            int val1 = stack.leggiPila();
            stack.fuoriPila();
            int val2 = stack.leggiPila();
            stack.fuoriPila();

            string v = exp.read(it);
            if(v == "+")
            	stack.inpila(val2 + val1);
            else if(v == "-")
            	stack.inpila(val2 - val1);
            else if(v == "*")
            	stack.inpila(val2 * val1);
            else if(v == "/")
            	stack.inpila(val2 / val1);
        }
    }

    return stack.leggiPila();
}


#endif /* INTERPRETE_H_ */
