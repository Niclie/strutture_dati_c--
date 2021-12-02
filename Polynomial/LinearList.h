#ifndef LINEARLIST_H_
#define LINEARLIST_H_


#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::ostream;

template<class T, class P >
class LinearList{
 public:
	typedef T ValueType;   // the type of object, T, stored in the list
	typedef P Position;

	// operators
	virtual void create() = 0;
	virtual void clear() = 0; // erases all the elements
	virtual bool empty() const = 0; // true if the list's size is 0
	virtual void write(Position p, const ValueType& x) = 0; // write x at position p
	virtual ValueType read(const Position&) const = 0;
	virtual Position begin() const = 0;  // returns a position pointing to the beginning of the list
	virtual bool end(Position) const = 0; // true with a position pointing to the end of the list
	virtual Position next(Position) const = 0; // returns the next position
	virtual Position previous(Position) const = 0; // return the previous position
	virtual void insert(Position, const ValueType& ) = 0; // insert an element
	virtual void erase(Position) = 0; // ersaes the element at position pos

	/* Altre funzioni di servizio implementabili */

	virtual int size() const = 0;  // returns the size of the list
	virtual void pushFront(const ValueType &) = 0; // insert a new element at the beginning
	virtual void pushBack(const ValueType &) = 0; // insert a new element at the end
	virtual void popFront() = 0; // removes the first element
	virtual void popBack() = 0; // removes the last element

	// funzioni di servizio
	/* sovraccarica <<. Attenzione se il tipo restituito da read non � primitivo, allora
	 * anche per questo tipo bisogna sovraccaricare l'operatore <<
	 */
	friend ostream& operator<< (ostream& os, const LinearList<T,P>& l){
		typename LinearList<T,P>::Position p;
		p = l.begin();
		os << "[";
		while (!l.end(p)){
			if (p != l.begin())
				os << ", " << l.read(p);
			else
				os << l.read(p);
			p = l.next(p);
		}
		os << "]" << std::endl;
		return os;
	}

};

#endif /* LINEARLIST_H_ */
