#include "List.h"

int main() {
	List<int> l1;
	/*l1.insert(l1.begin(), 1);
	l1.insert(l1.next(l1.begin()), 2);
	l1.insert(l1.next(l1.next(l1.begin())), 3);
	l1.insert(l1.next(l1.begin()), 10);
	l1.insert(l1.previous(l1.last()), 20);
	l1.insert(l1.last(), 100);

	cout<<l1;
	l1.naturalMergeSort(l1);
	/*for(int i = 0; i < 10; i++)
		l1.pushFront(i);*/

	//82 16 14 15 84 25 77 13 75 4
	l1.pushBack(82);
	l1.pushBack(16);
	l1.pushBack(14);
	l1.pushBack(15);
	l1.pushBack(84);
	l1.pushBack(25);
	l1.pushBack(77);
	l1.pushBack(13);
	l1.pushBack(75);
	l1.pushBack(4);

	cout<<l1;

	l1.naturalMergeSort();
	cout<<l1;
	//l1.ordina();
	//cout<<l1;

	//cout<<l1.read(l1.previous(l1.next(l1.next(l1.begin()))));

	/*l1.erase(l1.begin());
	cout<<l1;

	l1.insert(l1.previous(l1.last()), 111);
	cout<<l1;*/

	/*l1.~List();
	cout<<l1;*/

	system("pause");
	return 0;
}
