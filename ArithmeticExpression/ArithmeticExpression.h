#ifndef ARITHMETICEXPRESSION_H_
#define ARITHMETICEXPRESSION_H_

#include <iostream>
#include <string.h>
#include "../BinaryTree/BinaryTree.h"
#include "../Stack/Stack.h"
#include "vector"
using std::cin;
using std::cout;
using std::endl;
using std::string;

class ArithmeticExpression{
public:
	bool isOperator(string);
	BinaryTree<string> constructTree(std::vector<string>);

	void print(_Node<string>* n){
		if(n != NULL){
			if(n->sx == NULL && n->dx == NULL)
				cout<<n->value;
			else{
				cout<<"(";
				print(n->sx);
				cout<<n->value;
				print(n->dx);
				cout<<")";
			}
		}
	}
};

bool ArithmeticExpression::isOperator(string c){
	if(c == "+" || c == "-" || c == "*" || c == "/" || c == "^")
		return true;

	return false;
}

BinaryTree<string> ArithmeticExpression::constructTree(std::vector<string> postfix){
	BinaryTree<string> tree;
	Stack<_Node<string>*> st;
	_Node<string> *t, *t1, *t2;

	int d = postfix.size();
	for(int i = 0; i < d; i++){
		if(!isOperator(postfix[i])){
			t = new _Node<string>();
			t->value = postfix[i];
			st.inpila(t);
		}
		else{
			t = new _Node<string>();
			t->value = postfix[i];

			t1 = st.leggiPila();
			st.fuoriPila();
			t2 = st.leggiPila();
			st.fuoriPila();

			t2->parent = t;
			t1->parent = t;
			t->sx = t2;
			t->dx = t1;

			t2->subTreeNodes = tree.contaNodi(t2);
			t1->subTreeNodes = tree.contaNodi(t1);


			st.inpila(t);
		}
	}

	t = st.leggiPila();
	st.fuoriPila();

	t->subTreeNodes = t->sx->subTreeNodes + t->dx->subTreeNodes + 1;
	tree.insRoot(t->value);//precedentemente t

	return tree;
}


#endif /* ARITHMETICEXPRESSION_H_ */
