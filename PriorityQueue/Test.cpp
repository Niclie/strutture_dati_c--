#include "PriorityQueue.h"

int main() {
	PriorityQueue<int> t;

	/*t.inserisci(9);
	t.inserisci(13);
	t.inserisci(11);
	t.inserisci(16);
	t.inserisci(18);
	t.inserisci(22);
	t.inserisci(20);
	t.print();

	cout<<t.min()<<endl;

	t.cancellaMin();
	t.print();*/

	t.inserisci(9);
	t.inserisci(11);
	t.inserisci(13);
	t.inserisci(18);
	t.inserisci(22);
	t.inserisci(17);
	t.inserisci(16);
	t.inserisci(7);
	t.print();
	t.cancellaMin();
	t.print();

	system("pause");
	return 0;
}
