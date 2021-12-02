#include "Stack.h"

int main() {
	Stack<int> pila;

	cout<<"Pila vuota = "<<pila.empty()<<endl;

	for(int i = 0; i < 10; i++)
		pila.inpila(i);
	pila.print();

	cout<<"Pila vuota = "<<pila.empty()<<endl;

	cout<<pila.leggiPila()<<endl;


	pila.~Stack();

	pila.print();

	return 0;
}
