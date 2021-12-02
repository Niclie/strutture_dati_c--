#include "Dictionary.h"

int main() {
	/*Dictionary<char, int> d(10);
	Pair<char, int> pair;

	pair.key = 'a';
	pair.value = 0;
	d.insert(pair);

	pair.key = 'b';
	pair.value = 1;
	d.insert(pair);

	pair.key = 'c';
	pair.value = 2;
	d.insert(pair);

	d.printDictionary();

	cout<<d.containsValue(1)<<endl;
	cout<<d.values();
	cout<<d.keys();*/

	Dictionary<int, string> d(10);
	Pair<int, string> pair;

	pair.key = 1;
	pair.value = "ab";
	d.insert(pair);

	pair.key = 0;
	pair.value = "a";
	d.insert(pair);

	pair.key = 2;
	pair.value = "abc";
	d.insert(pair);

	d.printDictionary();
	d.modify(0, "c");
	cout<<endl;
	d.printDictionary();

	cout<<"Contains key: "<<d.containsKey(3)<<endl;
	cout<<"Contains val: "<<d.containsValue("abc")<<endl;
	cout<<d.values();
	cout<<d.keys();

	d.clear();
	d.printDictionary();


	std::cin.get();
	return 0;
}
