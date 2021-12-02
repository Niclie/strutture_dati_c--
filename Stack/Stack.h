#ifndef STACK_H_
#define STACK_H_

#include "../Lista/List.h"

template<class T>
class Stack{
private:
	List<T> stack;

public:
	typedef T ValueType;

	Stack();
	bool empty() const;
	~Stack();
	ValueType leggiPila() const;
	void fuoriPila();
	void inpila(const ValueType&);

	void print();
};

template<class T>
Stack<T>::Stack(){

}

template<class T>
Stack<T>::~Stack(){
	stack.~List();
}

template<class T>
bool Stack<T>::empty() const{
	return stack.empty();
}

template<class T>
typename Stack<T>::ValueType Stack<T>::leggiPila() const{
	return stack.read(stack.begin());
}

template<class T>
void Stack<T>::fuoriPila(){
	stack.pop_front();
}

template<class T>
void Stack<T>::inpila(const ValueType& v){
	stack.pushFront(v);
}

template<class T>
void Stack<T>::print(){
	cout<<stack;
}


#endif /* STACK_H_ */
