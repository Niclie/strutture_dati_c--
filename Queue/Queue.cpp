#include "Queue.h"

int main() {
	Queue<int> q;

	cout<<"Coda vuota = "<<q.empty()<<endl;

	for(int i = 0; i < 10; i++)
		q.inCoda(i);

	q.print();
	cout<<"Coda vuota = "<<q.empty()<<endl;

	q.fuoriCoda();
	q.print();

	cout<<q.leggiCoda()<<endl;

	q.~Queue();
	q.print();

	system("pause");
	return 0;
}
