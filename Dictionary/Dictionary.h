#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include "Dizionario.h"
#include "../Lista/List.h"

template<class T>
class Hash{
public:
  size_t operator()(const T the_key) const;
};


/* a specialization with type string */
template <>
class Hash<string>{
public:
	size_t operator()(const string the_key) const {
		unsigned long hash_value = 0;
	    int length = (int) the_key.length();
	    for (int i = 0; i < length; i++)
	      hash_value = 5 * hash_value + the_key.at(i);
	    return size_t(hash_value);
	  }
};

/* a specialization with type int */
template <>
class Hash<int>{
public:
	size_t operator()(const int the_key) const {
		unsigned long hash_value = 0;
	    int length = (int) the_key;
	    for (int i = 0; i < length; i++)
	      hash_value = 5 * hash_value / the_key;
	    return size_t(hash_value);
	  }
};

/* a specialization with type int */
template <>
class Hash<char>{
public:
	size_t operator()(const char the_key) const {
		unsigned long hash_value = 0;
	    int length = (int) the_key;
	    for (int i = 0; i < length; i++)
	      hash_value = 5 * hash_value / the_key;
	    return size_t(hash_value);
	  }
};

template<class K, class V>
class Dictionary : Dizionario<K, V>{

private:
	Pair<K, V>** table;
	Hash<K> h;
	int dim;
	int maxDim;


public:
	//Costruttori e distruttori di base
	Dictionary();
	Dictionary(int);
	void create();
	//~Dictionary();
	void clear();

	bool empty() const;
	int size() const;
	int search(const K&) const;//Restituisce la posizione della chiave all'interno dell'array table
	Pair<K, V>* find(const K&) const;
	void insert(Pair<K, V>&);
	void erase(const K&);
	void modify(const K&, const V&);
	bool containsKey(const K&);
	void printDictionary();


	/*containsValue(const E& e): restustuisce true se una o più chiavi sono mappate al valore e nel dizionario
	values(): restituisce la lista dei valori memorizzati nel dizionario
	keys(): restituisce la lista delle chiavi memorizzate nel dizionario*/

	bool containsValue(const V& v);
	List<V> values();
	List<K> keys();

};

template<class K, class V>
Dictionary<K, V>::Dictionary(int d){
	maxDim = d;
	dim = 0;
	table = new Pair<K, V>* [d];

	for(int i = 0; i < maxDim; i++)
		table[i] = NULL;
}

template<class K, class V>
void Dictionary<K, V>::create(){
	table = new Pair<K, V>* [maxDim];

	for(int i = 0; i < maxDim; i++)
		table[i] = NULL;
}

/*template<class K, class V>
Dictionary<K, V>::~Dictionary(){
	clear();
}*/

template<class K, class V>
void Dictionary<K, V>::clear(){
	for(int i = 0; i < maxDim; i++){
		table[i] = NULL;
		delete table[i];
	}

	dim = 0;
}

template<class K, class V>
bool Dictionary<K, V>::empty() const{
	return dim == 0;
}

template<class K, class V>
int Dictionary<K, V>::size() const{
	return dim;
}

template<class K, class V>
int Dictionary<K, V>::search(const K& k) const{
	int i = h(k) % maxDim;
	int j = i;

	do{
		if(table[j] == NULL || table[j]->key == k)
			return j;

		j = (j + 1) % maxDim;
	}while(j != i);

	return j;
}

template<class K, class V>
Pair<K, V>* Dictionary<K, V>::find(const K& k) const{
	int pos = search(k);

	if(table[pos] == NULL || table[pos]->key != k)
		return NULL;

	return table[pos];
}

template<class K, class V>
void Dictionary<K, V>::insert(Pair<K, V>& p){
	int pos = search(p.key);

	if(table[pos] == NULL){
		table[pos] = new Pair<K, V>(p);
		dim++;
	}
	else if(table[pos]->key == p.key)
		table[pos]->value = p.value;
	else
		cout<<"The table is full"<<endl;
}

template<class K, class V>
void Dictionary<K, V>::erase(const K& k){
	int pos = search(k);

	if(table[pos] != NULL && table[pos]->key == k){
		delete table[pos];
		table[pos] = NULL;

		dim--;
	}
}

template<class K, class V>
void Dictionary<K, V>::modify(const K& k, const V& v){
	int pos = search(k);

	if(table[pos] != NULL && table[pos]->key == k)
		table[pos]->value = v;
}

template<class K, class V>
bool Dictionary<K, V>::containsKey(const K& k){
	int pos = search(k);

	return table[pos] != NULL && table[pos]->key == k;
}

template <class K, class V>
void Dictionary<K, V>::printDictionary(){
	int j = 0;
	for(int i = 0; i < dim; i++, j++)
		if(table[j] != NULL)
			cout<<"[KEY]: "<<table[j]->key<< "  "<<"[VALUE]: "<<table[j]->value<<endl;
		else
			i--;
}

/*containsValue(const E& e): restustuisce true se una o più chiavi sono mappate al valore e nel dizionario
values(): restituisce la lista dei valori memorizzati nel dizionario
keys(): restituisce la lista delle chiavi memorizzate nel dizionario*/

template <class K, class V>
bool Dictionary<K, V>::containsValue(const V& v){
	for(int i = 0; i < maxDim; i++)
		if(table[i] != NULL && table[i]->value == v)
			return true;

	return false;
}

template <class K, class V>
List<V> Dictionary<K, V>::values(){
	List<V> val;

	for(int i = 0; i < maxDim; i++)
		if(table[i] != NULL)
			val.pushBack(table[i]->value);

	return val;
}

template <class K, class V>
List<K> Dictionary<K, V>::keys(){
	List<K> k;

	for(int i = 0; i < maxDim; i++)
		if(table[i] != NULL)
			k.pushBack(table[i]->key);

	return k;
}


#endif /* DICTIONARY_H_ */
