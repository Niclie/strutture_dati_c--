#include "Bst.h"

int main() {
	Bst<int> t;

	t.insert(17);
	t.insert(26);
	t.insert(8);
	t.insert(50);
	t.insert(16);
	t.insert(19);
	t.insert(93);
	t.insert(4);
	t.insert(9);
	t.insert(55);
	t.insert(7);

	t.erase(t.read(t.minimum()));
	t.print();

	/*t.insert(1);
	t.insert(2);
	t.insert(3);
	t.insert(0);

	t.print();
	t.printInOrder();

	cout<<t.read(t.search(0))<<endl;
	cout<<t.read(t.minimum())<<endl;
	cout<<t.read(t.maximum())<<endl;

	cout<<t.read(t.predecessor(t.search(1)))<<endl;
	cout<<t.read(t.successor(t.search(1)))<<endl;

	t.erase(2);
	t.print();
	t.printInOrder();*/

	system("pause");
	return 0;
}
