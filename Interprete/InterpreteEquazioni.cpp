#include "Interprete.h"

int main() {
	Interpete i;
	std::string fileName = "program";

	i.readFile(fileName);

	//"(((1+2)*3)+(4*1))"
	//i.infixToPostfix();
	//i.removeSpaces(eq);
	//cout<<eq<<endl;
	//cout<<evaluatePostfix(eq);

	std::cin.get();
	return 0;
}
