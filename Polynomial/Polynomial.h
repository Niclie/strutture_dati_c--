/*
Un polinomio di grado d può essere rappresentato con una lista lineare di d+1 elementi, in cui ogni elemento rappresenta un coefficiente
del polinomio (l'elemento i-esimo della lista è il coefficiente dell'i-esimo termine, c_i x^d, del polinomio).
Definire una classe C++ polynomial che metta a disposizione i seguenti metodi

 * polynomial() - crea un polinomio di grado zero
 * grado() - restituisce il grado di un polinomio
 * input(inStream) - acquisisce un polinomio dallo stream di input inStream. Possiamo assumere che l'input sia il grado del polinomio seguito dai valori dei coefficienti.
 * output(outStream) - visualizza il polinomio
 * somma(b) - somma con il polinomio b
 * moltiplica(b) - moltiplica con il polinomio b
 * valore(x) - restituisce il valore del polinomio nel punto x
*/

#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include "List.h"
#include <math.h>

class Polynomial{
private:
	List<int> poly;

public:
	Polynomial(){
		poly = List<int>();
	}

	int grado(){
		return poly.size() - 1;
	}

	void input();
	void output();
	Polynomial somma(Polynomial);
	Polynomial moltiplica(Polynomial);
	int valore(int);
};

void Polynomial::input(){
	int grado = 0;
	cout<<"Inserisci il grado del polinomio: ";
	cin>>grado;

	for(int i = grado; i >= 0; i--){
		float temp;
		cout<<"Inserisci il coefficente di grado "<<i<<": ";
		cin>>temp;
		poly.pushBack(temp);
	}
}

void Polynomial::output(){
	int g = grado();

	if(g == 0)
		return;

	if(g > 1){
		if(poly.read(poly.begin()) == 1)
			cout<<"x^"<<g;
		else if(poly.read(poly.begin()) == -1)
			cout<<"-x^"<<g;
		else
			cout<<poly.read(poly.begin())<<"x^"<<g;
	}
	else{
		if(poly.read(poly.begin()) == 1)
			cout<<"x";
		else if(poly.read(poly.begin()) == -1)
			cout<<"-x";
		else
			cout<<poly.read(poly.begin())<<"x";
	}
	g--;

	for(List<int>::Position it = poly.next(poly.begin()); it != poly.last(); it = poly.next(it), g--){
		float temp = poly.read(it);
		if(g > 1){
			if(temp == 1)
				cout<<"+x^"<<g;
			else if(temp == -1)
				cout<<"-x^"<<g;
			else if(temp > 0)
				cout<<"+"<<temp<<"x^"<<g;
			else
				cout<<temp<<"x^"<<g;
		}
		else{
			if(temp == 1)
				cout<<"+x";
			else if(temp == -1)
				cout<<"-x";
			else if(temp > 0)
				cout<<"+"<<temp<<"x";
			else
				cout<<temp<<"x";
		}
	}

	if(poly.read(poly.last()) > 0)
		cout<<"+"<<poly.read(poly.last());
	else
		cout<<poly.read(poly.last());

	cout<<endl;
}

Polynomial Polynomial::somma(Polynomial p2){
	Polynomial p3;
	List<int> l1;
	List<int> l2;

	l1 = poly;
	l2 = p2.poly;

	l1.inverti();
	l2.inverti();

	p3.poly = l1.somma(l1, l2);

	p3.poly.inverti();

	return p3;
}

Polynomial Polynomial::moltiplica(Polynomial p2){
	Polynomial p3;
	int d = this->poly.size() + p2.poly.size() - 1;
	int mul[d];

	int k = 0;
	for(k = 0; k < d; k++)
		mul[k] = 0;

	k = 0;
	for(List<int>::Position i = this->poly.begin(); !this->poly.end(i); i = this->poly.next(i), k++){
		int z = 0;
		for(List<int>::Position j = p2.poly.begin(); !p2.poly.end(j); j = p2.poly.next(j), z++)
			mul[k + z] += this->poly.read(i) * p2.poly.read(j);
	}

	for(k = 0; k < d; k++)
		p3.poly.pushBack(mul[k]);

	return p3;
}

int Polynomial::valore(int x){
	List<int>::Position i = this->poly.begin();
	int g = grado();
	int res = 0;
	for(int j = g; j > 0; j--, i = this->poly.next(i))
		res += std::pow(x, j) * this->poly.read(i);

	return res + this->poly.read(i);
}

#endif /* POLYNOMIAL_H_ */
