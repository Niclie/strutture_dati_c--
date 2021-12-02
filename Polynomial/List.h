/*
 * Lista.h
 *
 *  Created on: 26 dic 2020
 *      Author: Nicola
 *
 *      Realizzazione lista con puntatori
 */

#ifndef LIST_H_
#define LIST_H_

#include "LinearList.h"

template<class T>
class List;

template<class T>
class _ListNode{
friend class List<T>;
private:
	T value;
	_ListNode<T>* next;
	_ListNode<T>* prev;
};


template<class T>
class List : public LinearList<T, _ListNode<T>*>{
public:
	typedef typename LinearList<T, _ListNode<T>*>::Position Position;
	typedef typename LinearList<T, _ListNode<T>*>::ValueType ValueType;

private:
	int d;
	_ListNode<T>* head;


	//Metodi per il quicksort
	void quicksort(Position&, Position&);
	void quicksort(Position);
	Position partition(Position&, Position&);

	//Metodi per il mergesort
	void distribuisci(List<T>, List<T>&, List<T>&);
	void merge(List<T>, List<T>, List<T>&, int&);
	void fondiCatena(Position&, List<T>, Position&, List<T>, Position&, List<T>&);
	void copiaCatena(Position&, List<T>, Position&, List<T>&);
	void copia(Position&, List<T>, Position&, List<T>&, bool&);

public:

	List();
	//~List();
	void create();
	void clear();

	bool empty() const;

	void write(Position, const ValueType &);
	ValueType read(const Position&) const;

	Position begin() const;
	Position last() const;

	bool end(Position) const;

	Position next(Position) const;
	Position previous(Position) const;

	void insert(Position, const ValueType& );
	void erase(Position);

	int size() const;

	void pushFront(const ValueType &);
	void pushBack(const ValueType &);
	void popFront();
	void popBack();

	List<T>& operator=(const List<T>&);
	bool operator==(const List<T>&) const;

	void inverti();//una funzione in grado di invertire l'ordine di una lista senza utilizzare una lista di supporto
	void swap(Position, Position);// scambia i valori di due posizioni
	void ordina();//Ordina una lista in ordine crescente
	bool appartiene(ValueType);

	void naturalMergeSort();

	List<T> somma(List<T>, List<T>);
};

template<class T>
List<T>::List(){
	create();
}

/*template<class T>
List<T>::~List(){
	clear();
}*/

template<class T>
void List<T>::create(){
	d = 0;
	head = new _ListNode<T>;
	head->next = head;
	head->prev = head;
}

template <class T>
void List<T>::clear(){
	if(!empty())
		while(!empty())
			erase(begin());
}

template<class T>
bool List<T>::empty() const{
	return d == 0;
}

template<class T>
void List<T>::write(Position p, const ValueType &v){
	p->value = v;
}

template<class T>
typename List<T>::ValueType List<T>::read(const Position &p) const{
	return p->value;
}

template<class T>
typename List<T>::Position List<T>::begin() const{
	return head->next;
}

template<class T>
typename List<T>::Position List<T>::last() const{
	return head->prev;
}

template<class T>
bool List<T>::end(Position p) const{
	return p == head;
}

template<class T>
typename List<T>::Position List<T>::next(Position p) const{
	return p->next;
}

template<class T>
typename List<T>::Position List<T>::previous(Position p) const{
	if(p == begin())
		return head->prev;

	if(p != head)
		return p->prev;
}

template<class T>
void List<T>::insert(Position p, const ValueType& v){
	if(p == begin()){
		pushFront(v);
	}
	else if(end(p)){
		pushBack(v);
	}
	else{
		int i = 1;
		for(Position it = begin(); !end(it) && it != p; it = next(it), i++);
		Position t = new _ListNode<T>;
		t->value = v;
		if(i > (d + 1)/2){
			t->next = p->next;
			t->prev = p;
			p->next = t;
			t->next->prev = t;
		}
		else{
			t->next = p;
			t->prev = p->prev;
			p->prev->next = t;
			p->prev = t;
		}

		d++;
	}

	/*Position t = new _Node<T>;
	t->value = v;

	t->next = p;
	t->prev = p->prev;
	p->prev->next = t;
	p->prev = t;

	d++;*/
}

template<class T>
void List<T>::erase(Position p){
	p->prev->next = p->next;
	p->next->prev = p->prev;

	d--;
	delete p;
}

template<class T>
int List<T>::size() const{
	return d;
}

template<class T>
void List<T>::pushFront(const ValueType& v){
	Position temp = new _ListNode<T>;
	temp->value = v;
	temp->next = head->next;
	temp->prev = head;

	if(empty())
		head->prev = temp;
	else
		head->next->prev = temp;
	head->next = temp;

	d++;
}

template<class T>
void List<T>::pushBack(const ValueType& v){
	Position last = head->prev;

	last->next = new _ListNode<T>;
	last->next->value = v;
	last->next->next = head;
	last->next->prev = last;

	head->prev = last->next;

	d++;
}

template<class T>
void List<T>::popFront(){
	if(!empty()){
		Position node = begin();

		node->next->prev = head->next->prev;
		head->next = node->next;

		d--;
		delete node;
	}
}

template<class T>
void List<T>::popBack(){
	if(!empty()){
		Position last = head->prev;

		head->prev = last->prev;
		last->prev->next = head;

		d--;
		delete last;
	}
}


template<class T>
List<T>& List<T>::operator=(const List<T>& l){
	this->clear();

	for(Position i = l.begin(); !l.end(i); i = l.next(i))
			this->pushBack(l.read(i));

	return *this;
}


template<class T>
bool List<T>::operator==(const List<T> &l) const{
	if (l.size() != d)
		return false;
	Position p, pL;
	p = begin();
	pL = l.begin();
	while (!end(p)){
		if (p->value != pL->value)
			return false;
		p = p->next;
		pL = pL->next;
	}
	return true;
}

template<class T>
void List<T>::inverti(){
	if(!empty()){
		Position i = begin();
		Position j = last();

		for(int k = 0; k < d/2; k++, i = i->next, j = j->prev)
			swap(i, j);
	}
}

template<class T>
void List<T>::swap(Position p1, Position p2){
	T temp = read(p1);

	p1->value = read(p2);
	p2->value = temp;
}

template<class T>
void List<T>::ordina(){
	quicksort(head->next);
}

template<class T>
void List<T>::quicksort(Position head){
    // Find last node
    Position h = last();

    // Call the recursive QuickSort
    quicksort(head, h);
}

template<class T>
void List<T>::quicksort(Position& start, Position& end){
    if (end != head && start != end && start != end->next)
    {
        Position p = partition(start, end);
        quicksort(start, p->prev);
        quicksort(p->next, end);
    }
}

template<class T>
typename List<T>::Position List<T>::partition(Position& l, Position& h){
    // set pivot as h element
    T x = h->value;

    // similar to i = l-1 for array implementation
    Position i = l->prev;

    // Similar to "for (int j = l; j <= h- 1; j++)"
    for (Position j = l; j != h; j = j->next)
    {
        if (j->value <= x)
        {
            // Similar to i++ for array
            i = (i == NULL)? l : i->next;

            swap(i, j);
        }
    }
    i = (i == NULL)? l : i->next; // Similar to i++
    swap(i, h);

    return i;
}

template<class T>
bool List<T>::appartiene(ValueType v){
	for(Position i = begin(); !end(i); i = next(i))
		if(read(i) == v)
			return true;

	return false;
}

template<class T>//List<T>& l
void List<T>::naturalMergeSort(){
	int numeroCatene;

	do{
		List<T> a = List<T>();
		List<T> b = List<T>();
		distribuisci(*this, a, b);
		numeroCatene = 0;
		*this = List<T>();
		merge(a, b, *this, numeroCatene);
	}while(numeroCatene != 1);
}

template<class T>
void List<T>::distribuisci(List<T> l, List<T>& a, List<T>& b){
	Position pl = l.begin();
	Position pa = a.begin();
	Position pb = b.begin();

	do{
		copiaCatena(pl, l, pa, a);
		if(!l.end(pl))
			copiaCatena(pl, l, pb, b);

	}while(!l.end(pl));
}

template<class T>
void List<T>::copiaCatena(Position& pa, List<T> a, Position& pb, List<T> &b){
	bool finecatena;
	do
		copia(pa, a, pb, b, finecatena);
	while(!finecatena);
}

template<class T>
void List<T>::copia(Position& pa, List<T> a, Position& pl, List<T>& l, bool& finecatena){
	ValueType elemento = a.read(pa);

	l.pushBack(elemento);
	pa = a.next(pa);
	pl = l.next(pl);
	if(a.end(pa))
		finecatena = true;
	else
		finecatena = (elemento > a.read(pa));
}

template<class T>
void List<T>::merge(List<T> a, List<T> b, List<T>& l, int& numeroCatene){
	Position pa = a.begin();
	Position pb = b.begin();
	Position pl = l.begin();

	while(!a.end(pa) && !b.end(pb)){
		fondiCatena(pa, a, pb, b, pl, l);
		numeroCatene = numeroCatene + 1;

		while(!a.end(pa)){
			copiaCatena(pa, a, pl, l);
			numeroCatene = numeroCatene + 1;
		}

		while(!b.end(pb)){
			copiaCatena(pb, b, pl, l);
			numeroCatene = numeroCatene + 1;
		}
	}

}

template<class T>
void List<T>::fondiCatena(Position& pa, List<T> a, Position& pb, List<T> b, Position& pl, List<T>& l){
	bool finecatena;

	do{
		if(a.read(pa) < b.read(pb)){
			copia(pa, a, pl, l, finecatena);
			if(finecatena)
				copiaCatena(pb, b, pl, l);
		}
		else{
			copia(pb, b, pl, l, finecatena);
			if(finecatena)
				copiaCatena(pa, a, pl, l);
		}

	}while(!finecatena);
}

template<typename T>
List<T> List<T>::somma(List<T> l1, List<T> l2){
	List<T> l3;

	_ListNode<T>* p1 = l1.begin();
	_ListNode<T>* p2 = l2.begin();

	while(!l1.end(p1) && !l2.end(p2)){
		l3.pushBack(l1.read(p1) + l2.read(p2));

		p1 = l1.next(p1);
		p2 = l2.next(p2);
	}

	if(!l1.end(p1)){
		while(!l1.end(p1)){
			l3.pushBack(l1.read(p1));

			p1 = l1.next(p1);
		}
	}

	if(!l2.end(p2)){
		while(!l2.end(p2)){
			l3.pushBack(l2.read(p2));

			p2 = l2.next(p2);
		}
	}

	return l3;
}

#endif /* LIST_H_ */
