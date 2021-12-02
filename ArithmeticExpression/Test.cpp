#include "ArithmeticExpression.h"

int main() {
	BinaryTree<string> t;
	ArithmeticExpression ar;

	//std::vector<string> postfix = {"10", "2", "*", "4", "5", "-", "+", "2", "/"};
	std::vector<string> postfix = {"7", "3", "/", "1", "4", "-", "2", "*", "/", "1", "+"};

	t = ar.constructTree(postfix);

	t.print();

	ar.print(t.root());
	cin.get();

	return 0;
}
