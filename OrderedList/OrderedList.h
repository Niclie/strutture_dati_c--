#ifndef ORDEREDLIST_H_
#define ORDEREDLIST_H_

#include "../Lista/LinearList.h"

template<class T>
class OrderedList;

template<class T>
class _Node{
friend class OrderedList<T>;
private:
	T value;
	_Node<T>* next;
	_Node<T>* prev;
};


template<class T>
class OrderedList : public LinearList<T, _Node<T>*>{
public:
	typedef typename LinearList<T, _Node<T>*>::Position Position;
	typedef typename LinearList<T, _Node<T>*>::ValueType ValueType;

private:
	int d;
	_Node<T>* head;

	void pushFront(const ValueType &);
	void pushBack(const ValueType &);
	void insert(Position&, Position);
	void swap(Position, Position);
	bool appartiene(const ValueType&, Position p, int);//TODO
	Position search(const ValueType&, Position, int);

public:

	OrderedList();
	//~OrderedList();
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

	void insert(const ValueType& v);
	void erase(Position);

	int size() const;

	void popFront();
	void popBack();

	OrderedList<T>& operator=(const OrderedList<T>&);
	bool operator==(const OrderedList<T>&) const;

	void inverti();//una funzione in grado di invertire l'ordine di una lista senza utilizzare una lista di supporto
	bool appartiene(ValueType);//TODO

	OrderedList<T> merge(OrderedList<T>);

	Position search(const ValueType&);
};

template<class T>
OrderedList<T>::OrderedList(){
	create();
}

/*template<class T>
OrderedList<T>::~OrderedList(){
	clear();
}*/

template<class T>
void OrderedList<T>::create(){
	d = 0;
	head = new _Node<T>;
	head->next = head;
	head->prev = head;
}

template <class T>
void OrderedList<T>::clear(){
	if(!empty())
		while(!empty())
			erase(begin());
}

template<class T>
bool OrderedList<T>::empty() const{
	return d == 0;
}

template<class T>
void OrderedList<T>::write(Position p, const ValueType &v){
	erase(p);
	insert(v);
}

template<class T>
typename OrderedList<T>::ValueType OrderedList<T>::read(const Position &p) const{
	return p->value;
}

template<class T>
typename OrderedList<T>::Position OrderedList<T>::begin() const{
	return head->next;
}

template<class T>
typename OrderedList<T>::Position OrderedList<T>::last() const{
	return head->prev;
}

template<class T>
bool OrderedList<T>::end(Position p) const{
	return p == head;
}

template<class T>
typename OrderedList<T>::Position OrderedList<T>::next(Position p) const{
	return p->next;
}

template<class T>
typename OrderedList<T>::Position OrderedList<T>::previous(Position p) const{
	if(p == begin())
		return head->next;

	if(p != head)
		return p->prev;
}

template<class T>
void OrderedList<T>::insert(const ValueType& v){
	Position newNode = new _Node<T>;
	newNode->value = v;
	insert(head->next, newNode);
}

template<class T>
void OrderedList<T>::insert(Position& firstNode, Position newNode){
	if(d == 0 || newNode->value <= firstNode->value){
		newNode->next = firstNode;
		newNode->prev = head;
		firstNode->prev = newNode;
		firstNode = newNode;
	}
	else{
		Position current = firstNode;
		while(current->next != head && current->next->value < newNode->value){
			current = current->next;
		}

		newNode->next = current->next;
		newNode->prev = current;
		current->next->prev = newNode;
		current->next = newNode;
	}

	d++;
}

template<class T>
void OrderedList<T>::erase(Position p){
	p->prev->next = p->next;
	p->next->prev = p->prev;

	d--;
	delete p;
}

template<class T>
int OrderedList<T>::size() const{
	return d;
}

template<class T>
void OrderedList<T>::pushFront(const ValueType& v){
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
void OrderedList<T>::pushBack(const ValueType& v){
	Position last = head->prev;

	last->next = new _Node<T>;
	last->next->value = v;
	last->next->next = head;
	last->next->prev = last;

	head->prev = last->next;

	d++;
}

template<class T>
void OrderedList<T>::popFront(){
	if(!empty()){
		Position node = begin();

		node->next->prev = head->next->prev;
		head->next = node->next;

		d--;
		delete node;
	}
}

template<class T>
void OrderedList<T>::popBack(){
	if(!empty()){
		Position last = head->prev;

		head->prev = last->prev;
		last->prev->next = head;

		d--;
		delete last;
	}
}


template<class T>
OrderedList<T>& OrderedList<T>::operator=(const OrderedList<T>& l){
	this->clear();

	for(Position i = l.begin(); !l.end(i); i = l.next(i))
			this->pushBack(l.read(i));

	return *this;
}


template<class T>
bool OrderedList<T>::operator==(const OrderedList<T> &l) const{
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
void OrderedList<T>::swap(Position p1, Position p2){
	T temp = read(p1);

	p1->value = read(p2);
	p2->value = temp;
}

template<class T>
void OrderedList<T>::inverti(){
	if(!empty()){
		Position i = begin();
		Position j = last();

		for(int k = 0; k < d/2; k++, i = i->next, j = j->prev)
			swap(i, j);
	}
}

template<class T>
bool OrderedList<T>::appartiene(ValueType v){
	if(empty())
		return false;
	else return appartiene(v, begin(), size());
}

template<class T>
bool OrderedList<T>::appartiene(const ValueType& v, Position p, int dim){
	if(dim == 1){
		if(read(p) == v)
			return true;
		else
			return false;
	}
	else{
		int m = dim / 2;
		int i = 0;
		Position it;
		for(it = p; !end(it) && i < m; it = next(it), i++);

		if(v == read(it))
			return it;

		if(v > read(it))
			if(dim % 2 == 0)
				search(v, next(it), m - 1);
			else
				search(v, next(it), m);
		else
			appartiene(v, p, m);
	}
}

template<typename T>
OrderedList<T> OrderedList<T>::merge(OrderedList<T> l2){
	OrderedList<T> l3;
	Position p1 = begin();
	Position p2 = l2.begin();

	while(!end(p1) && !l2.end(p2)){
		T elem1 = read(p1);
		T elem2 = l2.read(p2);

		if(elem1 < elem2){
			l3.pushBack(elem1);
			p1 = next(p1);
		}
		else{
			l3.pushBack(elem2);
			p2 = l2.next(p2);
		}
	}

	while(!end(p1)){
		l3.pushBack(read(p1));
		p1 = next(p1);
	}

	while(!l2.end(p2)){
		l3.pushBack(read(p2));
		p2 = l2.next(p2);
	}

	return l3;
}

template<typename T>
typename OrderedList<T>::Position OrderedList<T>::search(const ValueType& v){
	if(empty())
		return NULL;
	else return search(v, begin(), size());
}

template<typename T>
typename OrderedList<T>::Position OrderedList<T>::search(const ValueType& v, Position p, int dim){
	if(dim == 1){
		if(read(p) == v)
			return p;
	}
	else{
		int m = dim / 2;
		int i = 0;
		Position it;
		for(it = p; !end(it) && i < m; it = next(it), i++);

		if(v == read(it))
			return it;

		if(v > read(it))
			if(dim % 2 == 0)
				search(v, next(it), m - 1);
			else
				search(v, next(it), m);
		else
			search(v, p, m);
	}
}

#endif /* ORDEREDLIST_H_ */
