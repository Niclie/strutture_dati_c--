#include "OrderedList.h"

int main() {
	OrderedList<int> l;
	OrderedList<int> l1;
	OrderedList<int> l3;


	l.insert(10);
	l.insert(2);
	l.insert(3);
	l.insert(1);
	l.insert(0);
	l.insert(-1);
	l.insert(55);
	l.insert(11);
	l.insert(-1);
	l.insert(6);
	cout<<l;

	l1.insert(1);
	l1.insert(2);
	l1.insert(3);
	l1.insert(4);
	l1.insert(5);
	cout<<l1;

	l3 = l1.merge(l);
	cout<<l3;

	//l.write(l.next(l.begin()), 100);
	//cout<<l;

	//cout<<l.appartiene(55)<<endl;

	/*l.inverti();
	cout<<l;

	l.popBack();
	l.popFront();
	cout<<l;

	l.erase(l.next(l.begin()));
	cout<<l;

	l.clear();
	cout<<l;*/

	std::cin.get();
	return 0;
}
