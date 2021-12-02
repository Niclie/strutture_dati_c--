#ifndef BINTREE_H_
#define BINTREE_H_

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

template <class T, class N>
class Bin_tree {

public:
	// tipi
	typedef T value_type;
	typedef N Nodo;

	// operatori
	virtual void create() = 0;
	virtual bool empty() const =  0;

	virtual Nodo root() const = 0;
	virtual Nodo parent(Nodo) const =  0;
	virtual Nodo sx(Nodo) const = 0;
	virtual Nodo dx(Nodo) const = 0;
	virtual bool sxEmpty(Nodo) const = 0;
	virtual bool dxEmpty(Nodo) const = 0;

	virtual void erase(Nodo) = 0;

	virtual T read(Nodo) const = 0;
	virtual void write(Nodo, value_type) = 0;

	virtual void insRoot(T) = 0;
	virtual void insSx(Nodo, T) = 0;
	virtual void insDx(Nodo, T) = 0;

	virtual int subTreeNodes(Nodo n) const = 0;

	// funzioni di servizio da implementare qui
	//virtual void previsit(Nodo);
	//virtual void invisita(Nodo);
	//virtual void postvisit(Nodo);

	virtual void print() const;

private:
    virtual void printSubTree(const Nodo) const;


  };

template <class T, class N>
void Bin_tree<T,N>::print() const{
	if (!empty())
		printSubTree(root());
	else
		std::cout << "[]" << std::endl;
	std::cout << std::endl;
}

template <class T, class N>
void Bin_tree<T,N>::printSubTree(const Nodo n) const{
	std::cout << "[" << read(n) <<"("<<subTreeNodes(n)<<")"<< ", ";
	if (!sxEmpty(n))
		printSubTree(sx(n));
	else std::cout << "NIL";
	std::cout << ", ";
	if (!dxEmpty(n))
		printSubTree(dx(n));
	else std::cout << "NIL";
	std::cout << " ]";
}

template<class T, class N>
std::ostream& operator<<(std::ostream& out, const Bin_tree<T, N>& t) {
    t.print();
    return out;
}

#endif /* BINTREE_H_ */
