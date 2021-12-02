#ifndef _DIZIONARIO_H
#define _DIZIONARIO_H

#include <iostream>
using std::string;
using std::cout;
using std::endl;

template<class K, class E>
struct Pair {
  // data member
  K key;
  E value;

  // methods
  Pair(){}
  Pair(Pair<K,E>& the_pair){
	  key = the_pair.key;
	  value = the_pair.value;
  }
};


template <class K, class E>
class Dizionario{
public:

	virtual ~Dizionario() {}
  
	virtual void create() = 0;
	//create an empty dictionary
	virtual void clear() = 0;

	virtual bool empty() const = 0;
	  // return true if the dictionary is empty
	virtual int size() const = 0;
	  // return the number of pairs in the dictionary
	virtual Pair<K, E>* find(const K& k) const = 0;
	  // return the pair with key k
	virtual void insert(Pair<K, E>& p) = 0;
	  // insert the pair p into the dictionary
	virtual void erase(const K& k) = 0;
	  // delete the pair with key k
	virtual void modify(const K& k, const E& e) = 0;
	  // modify the value of the pair with key k to e
};

#endif
