#include "grafo.h"

int main() {
	/*
	Grafo<char, int> g;

	Nodo<char, int>* n1 = new Nodo<char, int>;
	n1->setLabel('a');
	Nodo<char, int>* n2 = new Nodo<char, int>;
	n2->setLabel('b');
	Nodo<char, int>* n3 = new Nodo<char, int>;
	n3->setLabel('c');
	Nodo<char, int>* n4 = new Nodo<char, int>;
	n4->setLabel('d');

	g.insNodo(n1);
	g.insNodo(n2);
	g.insNodo(n3);
	g.insNodo(n4);

	g.insArco(n1, n2, 1);
	g.insArco(n2, n3, 1);
	g.insArco(n4, n2, 1);
	//g.insArco(n1, n3, 1);
	//g.insArco(n3, n2, 1);
	//g.insArco(n1, n3, 1);
	//g.insArco(n3, n1, 1);
	//g.insArco(n2, n3, 1);
	g.print();

	cout<<g.numeroNodi()<<endl;
	cout<<g.numeroArchi()<<endl;

	cout<<endl;

	cout<<g.findPath(n1, n4)<<endl;*/

	Grafo<char, int> g;

	Nodo<char, int>* n1 = new Nodo<char, int>;
	n1->setLabel('x');
	Nodo<char, int>* n2 = new Nodo<char, int>;
	n2->setLabel('a');
	Nodo<char, int>* n3 = new Nodo<char, int>;
	n3->setLabel('b');
	Nodo<char, int>* n4 = new Nodo<char, int>;
	n4->setLabel('c');
	Nodo<char, int>* n5 = new Nodo<char, int>;
	n5->setLabel('d');
	Nodo<char, int>* n6 = new Nodo<char, int>;
	n6->setLabel('e');
	Nodo<char, int>* n7 = new Nodo<char, int>;
	n7->setLabel('y');

	g.insNodo(n1);
	g.insNodo(n2);
	g.insNodo(n3);
	g.insNodo(n4);
	g.insNodo(n5);
	g.insNodo(n6);
	g.insNodo(n7);

	g.insArco(n1, n2, 2);
	g.insArco(n1, n5, 8);
	g.insArco(n2, n3, 6);
	g.insArco(n2, n4, 2);
	g.insArco(n3, n7, 5);
	g.insArco(n4, n5, 2);
	g.insArco(n4, n6, 9);
	g.insArco(n5, n6, 3);
	g.insArco(n6, n7, 1);

	g.print();

	cout<<g.camminiMinimi(n1)<<endl;

	List<Nodo<char, int>*> s;
	s = g.cammino(n7, n1);

	for(typename List<Nodo<char, int>*>::Position j = s.begin(); !s.end(j); j = s.next(j)){
		cout<<s.read(j)->getLabel()<<" ";
	}

	cout<<g.findPath(n7, n1);

	/*g.bfs(n1);
	g.ripristinaVisitato();
	cout<<endl;
	g.dfs(n1);*/

	return 0;
}
