#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include "../BinaryTree/BinaryTree.h"

template<typename T>
class PriorityQueue{
private:
	BinaryTree<T> tree;
	_Node<T>* last;

public:
	typedef typename BinaryTree<T>::Node Node;
	typedef typename BinaryTree<T>::ValueType ValueType;

	PriorityQueue();
	void inserisci(ValueType);
	ValueType min();
	void cancellaMin();
	Node minPrioritySon(Node);
	void print();
};

template<typename T>
PriorityQueue<T>::PriorityQueue(){
	last = NULL;
}

template<typename T>
void PriorityQueue<T>::inserisci(ValueType v){
	if(tree.empty()){
		tree.insRoot(v);
		last = tree.root();

		return;
	}
	else if(tree.numberNodes() == 1){
		tree.insSx(tree.root(), v);
		last = tree.sx(tree.root());
	}
	else if(tree.sx(tree.parent(last)) == last){
		tree.insDx(tree.parent(last), v);
		last = tree.dx(tree.parent(last));
	}
	else{
		while(tree.dx(tree.parent(last)) == last)
			last = tree.parent(last);

		if(last != tree.root())
			last = tree.dx(tree.parent(last));

		while(!tree.sxEmpty(last) && !tree.dxEmpty(last))
			last = tree.sx(last);

		tree.insSx(last, v);
		last = tree.sx(last);
	}

	for(Node n = last; n != tree.root() && tree.read(n) < tree.read(tree.parent(n)); n = tree.parent(n)){
		ValueType temp = tree.read(n);
		tree.write(n, tree.read(tree.parent(n)));
		tree.write(tree.parent(n), temp);
	}
}

template<typename T>
typename PriorityQueue<T>::ValueType PriorityQueue<T>::min(){
	if(!tree.empty())
		return tree.read(tree.root());
}


template<typename T>
void PriorityQueue<T>::cancellaMin(){
	if(!tree.empty()){
		if(tree.numberNodes() == 1){
			tree.erase(tree.root());
			last = NULL;
		}
		else{
			Node deleteMe = last;

			tree.write(tree.root(), tree.read(last));

			if(last == tree.dx(tree.parent(last)))
				last = tree.sx(tree.parent(last));
			else{
				while(last != tree.root() && last == tree.sx(tree.parent(last)))
					last = tree.parent(last);

				if(last != tree.root())
					last = tree.sx(tree.parent(last));

				while(tree.sx(last) != NULL || tree.dx(last) != NULL)
					last = tree.dx(last);
			}
			tree.erase(deleteMe);

			Node attuale = tree.root();
			Node min = minPrioritySon(attuale);
			while((!tree.isLeaf(attuale)) && (tree.read(attuale) > tree.read(min))){

				ValueType temp = tree.read(attuale);
				tree.write(attuale, tree.read(min));
				tree.write(min, temp);
				attuale = min;
				min = minPrioritySon(attuale);
			}
		}
	}
}

template<typename T>
typename PriorityQueue<T>::Node PriorityQueue<T>::minPrioritySon(Node n){
	if(!tree.isLeaf(n)){
		if(!tree.sxEmpty(n) && !tree.dxEmpty(n)){
			if(tree.read(tree.sx(n)) < tree.read(tree.dx(n)))
				return tree.sx(n);
			else
				return tree.dx(n);
		}
		else
			return tree.sx(n);
	}
}


template<typename T>
void PriorityQueue<T>::print(){
	cout<<tree;
}


#endif /* PRIORITYQUEUE_H_ */
