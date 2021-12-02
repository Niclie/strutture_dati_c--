#include "Polynomial.h"

int main(){
	Polynomial p1, p2;
	cout<<"p1: "<<endl;
	p1.input();

	p1.output();

	/*cout<<"p2: "<<endl;
	p2.input();

	p2.output();

	cout<<endl;
	p1.somma(p2).output();
	p1.moltiplica(p2).output();*/
	cout<<p1.valore(2)<<endl;
	return 0;
}
