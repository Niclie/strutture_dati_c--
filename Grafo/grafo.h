#ifndef GRAFO_H_
#define GRAFO_H_


#include "../Lista/List.h"
#include "../Queue/Queue.h"
#define INFINITO 9999

template <typename T, typename P>
class Grafo;

template <typename T, typename P>
class Nodo;

template <typename T, typename P>
class Arco{
friend class Grafo<T, P>;

private:
	P peso;
	Nodo<T, P>*  to;

};

template <typename T, typename P>
class Nodo{
friend class Grafo<T, P>;

private:
	T label;
	int id;
	List<Arco<T, P>*> adiacenti;
	bool visitato;

public:
	Nodo(){}

	Nodo(int i){
		id = i;
	}

	void setId(int i){
		id = i;
	}

	int getId(){
		return id;
	}

	void setLabel(T val){
		label = val;
	}

	T getLabel(){
		return label;
	}

	int getArchi(){
		return adiacenti.size();
	}
};

template <typename T, typename P>
class Grafo{
public:
	typedef Nodo<T, P>* node;
	typedef Arco<T, P>* arco;
	typedef T etichetta;
	typedef P peso;

	Grafo();
	bool empty() const;
	typename List<node>::Position searchNode(node);
	typename List<arco>::Position searchArco(node, node);

	void insNodo(node);
	void insArco(node, node, peso);

	bool esisteNodo(node);
	bool esisteArco(node, node);

    etichetta leggiEtichetta(node) const;
    void scriviEtichetta(node, etichetta);
    bool esisteEtichetta(etichetta);

    peso leggiPeso(node, node);
    void scriviPeso(node, node, peso);

	void cancNodo(node);
	void cancArco(node, node);

	List<node> listaNodi();
	List<node> adiacenti(node);

	int inDegree(node); //per grafi orientati, che restituisce il numero di archi entranti in N
	int outDegree(node); //per grafi orientati, che restituisce il numero di archi uscenti da N
	double meanOutDegree(); //per grafi orientati, che restituisce la media del numero di archi uscenti per ogni nodo del grafo
	bool findPath(node, node); //che stabilisce se esiste un path dal nodo S al nodo D, e in caso positivo lo stampa a video

	int numeroNodi(){
		return numNodi;
	}
	int numeroArchi(){
		return numArchi;
	}

	void print();
	void dfs(node);
	void bfs(node);
	void ripristinaVisitato();//Pone il campo visitato di tutti i nodi del grafo = a false
	List<int> camminiMinimi(node);//restituisce una lista contenente la distanza minima da un nodo r a tutti i nodi del grafo
	List<node> cammino(node, node);//restituisce una lista contenente il cammino minimo (se esiste) da un nodo r ad un nodo u

private:
	List<node> grafo;
	int numArchi;
	int numNodi;
};

template <typename T, typename P>
Grafo<T, P>::Grafo(){
	numArchi = 0;
	numNodi = 0;
}

template <typename T, typename P>
bool Grafo<T, P>::empty() const{
	return grafo.empty();
}

template <typename T, typename P>
typename List<Nodo<T, P>*>::Position Grafo<T, P>::searchNode(node n){
	for(typename List<node>::Position i = grafo.begin(); !grafo.end(i); i = grafo.next(i))
		if(grafo.read(i) == n)
			return i;

	return NULL;
}

template <typename T, typename P>
typename List<Arco<T, P>*>::Position Grafo<T, P>::searchArco(node n1, node n2){
	for(typename List<arco>::Position i = n1->adiacenti.begin(); !n1->adiacenti.end(i); i = n1->adiacenti.next(i))
		if(n1->adiacenti.read(i)->to == n2)
			return i;

	return NULL;
}

template <typename T, typename P>
void Grafo<T, P>::insNodo(node n){
	if(!esisteNodo(n) && !esisteEtichetta(n->label)){
		n->id = numNodi;
		n->visitato = false;
		grafo.pushBack(n);
		numNodi++;
	}
}

template <typename T, typename P>
void Grafo<T, P>::insArco(node n1, node n2, peso p){
	if(!esisteArco(n1, n2)){
		arco a = new Arco<T, P>;
		a->to = n2;
		a->peso = p;
		n1->adiacenti.pushBack(a);
		numArchi++;
	}
}

template <typename T, typename P>
bool Grafo<T, P>::esisteNodo(node n){
	typename List<node>::Position p = searchNode(n);
	if(p == NULL)
		return false;

	return grafo.read(p) == n;
}

template <typename T, typename P>
bool Grafo<T, P>::esisteArco(node n1, node n2){
	typename List<arco>::Position p = searchArco(n1, n2);

	if(p == NULL)
		return false;

	return n1->adiacenti.read(p)->to == n2;
}

template <typename T, typename P>
typename Grafo<T, P>::etichetta Grafo<T, P>::leggiEtichetta(node n) const{
	return n->getLabel();
}

template <typename T, typename P>
void Grafo<T, P>::scriviEtichetta(node n, etichetta e){
	if(!esisteEtichetta(e))
		n->label = e;
}

template <typename T, typename P>
bool Grafo<T, P>::esisteEtichetta(etichetta e){
	for(typename List<node>::Position i = grafo.begin(); !grafo.end(i); i = grafo.next(i))
		if(grafo.read(i)->label == e)
			return true;

	return false;
}

template<typename T, typename P>
typename Grafo<T, P>::peso Grafo<T, P>::leggiPeso(node n1, node n2){
	typename List<arco>::Position p = searchArco(n1, n2);
	if(p != NULL)
		return n1->adiacenti.read(p)->peso;
}

template<typename T, typename P>
void Grafo<T, P>::scriviPeso(node n1, node n2, peso peso){
	typename List<arco>::Position p = searchArco(n1, n2);
	if(p != NULL)
		n1->adiacenti.read(p)->peso = peso;
}

template <typename T, typename P>
void Grafo<T, P>::cancNodo(node n){
	if(esisteNodo(n)){
		typename List<node>::Position p = searchNode(n);

		for(typename List<node>::Position i = grafo.begin(); !grafo.end(i); i = grafo.next(i))
			if(esisteArco(grafo.read(i), n))
				cancArco(grafo.read(i), n);

		grafo.erase(p);
		numNodi--;
	}

}

template <typename T, typename P>
void Grafo<T, P>::cancArco(node n1, node n2){
	if(esisteArco(n1, n2)){
		typename List<arco>::Position p = searchArco(n1, n2);
		n1->adiacenti.erase(p);
		numArchi--;
	}
}

template <typename T, typename P>
List<Nodo<T, P>*> Grafo<T,  P>::listaNodi(){
	return grafo;
}

template <typename T, typename P>
List<Nodo<T, P>*> Grafo<T, P>::adiacenti(node n){
	List<arco> l = n->adiacenti;
	List<node> ln;
	for(typename List<arco>::Position i = l.begin(); !l.end(i); i = l.next(i)){
		ln.pushBack(n->adiacenti.read(i)->to);
	}

	return ln;
}

template <typename T, typename P>
int Grafo<T, P>::inDegree(node n){
	int in_degree = 0;

	if(esisteNodo(n)){
		for(typename List<node>::Position i = grafo.begin(); !grafo.end(i); i = grafo.next(i))
			if(esisteArco(grafo.read(i), n))
				in_degree++;
	}

	return in_degree;
}

template <typename T, typename P>
int Grafo<T, P>::outDegree(node n){
	return n->getArchi();
}

template <typename T, typename P>
double Grafo<T, P>::meanOutDegree(){
	//per grafi orientati, che restituisce la media del numero di archi uscenti per ogni nodo del grafo

	List<node> l = listaNodi();
	int sum = 0;
	if(!l.empty())
		for(typename List<node>::Position i = l.begin(); !l.end(i); i = l.next(i))
			sum = sum + l.read(i)->adiacenti.size();

	return (double) sum / l.size();
}

template <typename T, typename P>
bool Grafo<T, P>::findPath(node s, node d){
	List<node> path = cammino(s, d);
	if(path.read(path.last()) == s)
		return false;
	else
		return true;
}

template <typename T, typename P>
void Grafo<T, P>::print(){
	for(typename List<node>::Position i = grafo.begin(); !grafo.end(i); i = grafo.next(i)){
		cout<<grafo.read(i)->getLabel()<<"("<<grafo.read(i)->getId()<<")"<<"-> ";
		cout<<"[";

		List<arco > l = grafo.read(i)->adiacenti;
		for(typename List<arco>::Position j = l.begin(); !l.end(j); j = l.next(j)){
			cout<<l.read(j)->to->label<<" ";
		}

		cout<<"]"<<endl;
	}
}

template<typename T, typename P>
void Grafo<T, P>::dfs(node n){
	n->visitato = true;
	cout<<n->getLabel()<<" ";

	List<arco> l = n->adiacenti;
	for(typename List<arco>::Position j = l.begin(); !l.end(j); j = l.next(j)){
		node temp = l.read(j)->to;
		if(!temp->visitato)
			dfs(temp);
	}
}

template<typename T, typename P>
void Grafo<T, P>::bfs(node n){
	Queue<node> q;
	q.inCoda(n);
	while(!q.empty()){
		n = q.leggiCoda();
		q.fuoriCoda();
		n->visitato = true;

		cout<<n->getLabel()<<" ";

		List<arco> l = n->adiacenti;
		for(typename List<arco>::Position j = l.begin(); !l.end(j); j = l.next(j)){
			node temp = l.read(j)->to;
			if(!temp->visitato && !q.appartiene(temp))
				q.inCoda(temp);
		}
	}
}

template<typename T, typename P>
void Grafo<T, P>::ripristinaVisitato(){
	for(typename List<node>::Position i = grafo.begin(); !grafo.end(i); i = grafo.next(i))
		grafo.read(i)->visitato = false;
}

template<typename T, typename P>
List<int> Grafo<T, P>::camminiMinimi(node r){
	List<node> s;
	//int t[numNodi];//Albero n-ario. vettore di padri (elementi rapp. con i rispettivi id)
	int dist[numNodi];


	for(int k = 0; k < numNodi; k++){
		//t[k] = r->getId();
		dist[k] = INFINITO;
		dist[r->getId()] = 0;

		s.pushFront(r);
		while(!s.empty()){
			node i = s.read(s.begin());
			s.popFront();

			List<arco> a = i->adiacenti;
			for(typename List<arco>::Position j = a.begin(); !a.end(j); j = a.next(j)){
				node temp = a.read(j)->to;
				if(dist[i->getId()] + leggiPeso(i, temp) < dist[temp->getId()]){
					//t[temp->getId()] = i->getId();
					dist[temp->getId()] = dist[i->getId()] + leggiPeso(i, temp);
				}

				if(!s.appartiene(temp))
					s.pushBack(temp);
			}
		}
	}



	List<int> distanze;
	for(int i = 0; i < numNodi; i++)
		distanze.pushBack(dist[i]);

	return distanze;
}

template<typename T, typename P>
List<Nodo<T, P>*> Grafo<T, P>::cammino(node sor, node des){
	List<node> q;
	int dist[numNodi];
	node precedente[numNodi];//contiene gli id dei Nodi precedenti in un percorso ottimale

	node nd = new Nodo<T, P>;
	nd->setId(-1);
	for(int k = 0; k < numNodi; k++){
		dist[k] = INFINITO;
		precedente[k] = nd;//consideriamo nd come "non definito"
	}

	q = grafo;
	dist[sor->getId()] = 0;
	while(!q.empty()){
		node u = q.read(q.begin());

		if(u->getId() == des->getId())
			break;

		q.popFront();

		if(dist[u->getId()] == INFINITO)
			break;

		List<arco> a = u->adiacenti;
		for(typename List<arco>::Position j = a.begin(); !a.end(j); j = a.next(j)){
			node temp = a.read(j)->to;
			if(dist[u->getId()] + leggiPeso(u, temp) < dist[temp->getId()]){
				precedente[temp->getId()] = u;
				dist[temp->getId()] = dist[u->getId()] + leggiPeso(u, temp);
			}
		}
	}

	List<node> s;
	node u = des;
	while(precedente[u->getId()] != nd){
		s.pushFront(u);
		u = precedente[u->getId()];
	}

	s.pushFront(sor);

	return s;
}


#endif /* GRAFO_H_ */
