#ifndef QUEUE_H_
#define QUEUE_H_

#include"List.h"

template<class T>
class Queue{
private:
	List<T> queue;

public:
	typedef T ValueType;

	Queue();
	~Queue();
	bool empty();
	ValueType leggiCoda() const;
	void fuoriCoda();
	void inCoda(const ValueType&);
	bool appartiene(ValueType);
	int size(){
		return queue.size();
	}

	void print();
};

template<class T>
Queue<T>::Queue(){

}

template<class T>
Queue<T>::~Queue(){
	queue.~List();
}

template<class T>
bool Queue<T>::empty(){
	return queue.empty();
}

template<class T>
typename Queue<T>::ValueType Queue<T>::leggiCoda() const{
	return queue.read(queue.begin());
}

template<class T>
void Queue<T>::fuoriCoda(){
	queue.popFront();
}

template<class T>
void Queue<T>::inCoda(const ValueType& v){
	queue.pushBack(v);
}

template<typename T>
bool Queue<T>::appartiene(ValueType v){
	for(typename List<T>::Position i = queue.begin(); !queue.end(i); i = queue.next(i)){
		if(queue.read(i) == v)
			return true;
	}

	return false;
}


template<class T>
void Queue<T>::print(){
	cout<<queue;
}


#endif /* QUEUE_H_ */
