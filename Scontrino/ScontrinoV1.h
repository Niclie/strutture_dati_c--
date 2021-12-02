#ifndef SCONTRINOV1_H_
#define SCONTRINOV1_H_


#include "../Lista/List.h"
using std::string;

typedef struct{
	string nome;
	double prezzo;
}Prodotto;

class Scontrino{
private:
	List<Prodotto> scontrino;

public:
	void aggiungi(Prodotto);
	void rimuovi(Prodotto);
	double totale();
	Prodotto costoso();
	void stampa();
};


void Scontrino::aggiungi(Prodotto p){
	scontrino.pushBack(p);
}

void Scontrino::rimuovi(Prodotto p){
	for(List<Prodotto>::Position it = scontrino.begin(); !scontrino.end(it); it = scontrino.next(it))
		if(scontrino.read(it).nome == p.nome)
			scontrino.erase(it);
}

double Scontrino::totale(){
	double sum = 0;

	for(List<Prodotto>::Position it = scontrino.begin(); !scontrino.end(it); it = scontrino.next(it))
		sum += scontrino.read(it).prezzo;

	return sum;
}

Prodotto Scontrino::costoso(){
	Prodotto max = scontrino.read(scontrino.begin());

	for(List<Prodotto>::Position it = scontrino.next(scontrino.begin()); !scontrino.end(it); it = scontrino.next(it))
		if(scontrino.read(it).prezzo > max.prezzo)
			max = scontrino.read(it);

	return max;
}

void Scontrino::stampa(){
	for(List<Prodotto>::Position it = scontrino.begin(); !scontrino.end(it); it = scontrino.next(it))
		cout<<"Nome: "<<scontrino.read(it).nome<<endl<<"Prezzo: "<<scontrino.read(it).prezzo<<endl<<endl;
}

#endif /* SCONTRINOV1_H_ */
