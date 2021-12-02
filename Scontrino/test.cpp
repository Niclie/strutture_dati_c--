#include "ScontrinoV1.h"

int main() {
	Scontrino s;

	Prodotto p;
	p.nome = "e";
	p.prezzo = 1.5;
	s.aggiungi(p);

	p.nome = "a";
	p.prezzo = 2;
	s.aggiungi(p);

	p.nome = "b";
	p.prezzo = 1.5;
	s.aggiungi(p);

	p.nome = "c";
	p.prezzo = 1.2;
	s.aggiungi(p);

	s.stampa();
	cout<<endl;

	p.nome = "e";
	p.prezzo = 1.5;

	s.rimuovi(p);
	s.stampa();

	cout<<"Totale: "<<s.totale()<<endl;
	cout<<"Costoso: "<<endl;
	cout<<"Nome: "<<s.costoso().nome<<endl<<"Prezzo: "<<s.costoso().prezzo<<endl;

	cout<<endl<<"Premere un tasto per continuare...";
	std::cin.get();
	return 0;
}
