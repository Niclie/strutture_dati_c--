/**
#ifndef SCONTRINOV2_H_
#define SCONTRINOV2_H_

#include "../OrderedList/OrderedList.h"
using std::string;


class Prodotto{
public:
	string nome;
	double prezzo;

	bool operator==(const Prodotto& p) const{
		if(nome == p.nome && prezzo == p.prezzo)
			return true;

		return false;
	}

	bool operator>=(const Prodotto& p) const{
		if(nome >= p.nome)
			return true;

		return false;
	}

	bool operator>(const Prodotto& p) const{
		if(nome > p.nome)
			return true;

		return false;
	}

	bool operator<=(const Prodotto& p) const{
		if(nome <= p.nome)
			return true;

		return false;
	}

	bool operator<(const Prodotto& p) const{
		if(nome < p.nome)
			return true;

		return false;
	}

	Prodotto& operator=(const Prodotto& p){
		this->nome = p.nome;
		this->prezzo = p.prezzo;

		return *this;
	}

	bool operator!=(const Prodotto& p) const{
		if(this->nome != p.nome)
			return true;

		return false;
	}
};

class Scontrino{
private:
	OrderedList<Prodotto> l;

public:
	void aggiungi(Prodotto);
	void rimuovi(Prodotto);
	double totale();
	Prodotto costoso();
	void stampa();
};

void Scontrino::aggiungi(Prodotto p){
	l.insert(p);
}

void Scontrino::rimuovi(Prodotto p){
	l.erase(l.search(p));
}

double Scontrino::totale(){
	double sum = 0;
	for(OrderedList<Prodotto>::Position it = l.begin(); !l.end(it); it = l.next(it))
		sum += l.read(it).prezzo;

	return sum;
}

void Scontrino::stampa(){
	for(OrderedList<Prodotto>::Position it = l.begin(); !l.end(it); it = l.next(it))
		cout<<"Nome: "<<l.read(it).nome<<endl<<"Prezzo: "<<l.read(it).prezzo<<endl<<endl;
}

Prodotto Scontrino::costoso(){
	Prodotto max = l.read(l.begin());

	for(OrderedList<Prodotto>::Position it = l.next(l.begin()); !l.end(it); it = l.next(it))
		if(l.read(it).prezzo > max.prezzo)
			max = l.read(it);

	return max;
}

#endif /* SCONTRINOV2_H_ */