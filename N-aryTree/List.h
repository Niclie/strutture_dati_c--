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
class _Node{
friend class List<T>;
private:
	T value;
	_Node<T>* next;
	_Node<T>* prev;
};


template<class T>
class List : public LinearList<T, _Node<T>*>{
public:
	typedef typename LinearList<T, _Node<T>*>::Position Position;
	typedef typename LinearList<T, _Node<T>*>::ValueType ValueType;

private:
	int d;
	_Node<T>* head;

	void quicksort(Position&, Position&);
	void quicksort(Position);
	Position partition(Position&, Position&);

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
	head = new _Node<T>;
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
	Position t = new _Node<T>;
	t->value = v;

	t->next = p;
	t->prev = p->prev;
	p->prev->next = t;
	p->prev = t;

	d++;
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
	Position temp = new _Node<T>;
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

	last->next = new _Node<T>;
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

#endif /* LIST_H_ */
