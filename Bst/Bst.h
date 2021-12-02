#ifndef BST_H_
#define BST_H_

#include "../BinaryTree/BinaryTree.h""

template<typename T>
class Bst{

private:
	BinaryTree<T> tree;

public:
	typedef typename BinaryTree<T>::ValueType ValueType;
	typedef typename BinaryTree<T>::Node Node;

	Bst();
	void create();
	bool empty();
	void insert(ValueType);
	void erase(ValueType);

	Node search(ValueType);
	Node search(Node, ValueType);

	Node minimum();
	Node maximum();
	Node minimum(Node);
	Node maximum(Node);

	Node predecessor(Node);
	Node successor(Node);

	ValueType read(Node);
	void write(Node, ValueType);

	void print();
	void printInOrder();
	void printInOrder(Node);

};

template<typename T>
Bst<T>::Bst(){
	create();
}

template<typename T>
void Bst<T>::create(){
	tree = BinaryTree<T>();
}

template<typename T>
bool Bst<T>::empty(){
	return tree.empty();
}

template<typename T>
void Bst<T>::insert(ValueType v){
	if(tree.empty())
		tree.insRoot(v);
	else{
		Node x = tree.root();
		bool found = true;
		while(found){
			if(v < tree.read(x) && !tree.sxEmpty(x)) x = tree.sx(x);
			else if(v > tree.read(x) && !tree.dxEmpty(x)) x = tree.dx(x);
			else found = false;
		}

		if(v < tree.read(x))
			tree.insSx(x, v);
		else
			tree.insDx(x, v);
	}
}

template<typename T>
void Bst<T>::erase(ValueType v){
	Node n = search(v);
	if(n == NULL) return;

	if(tree.isLeaf(n))
		tree.erase(n);

	else if ((tree.sxEmpty(n) && !tree.dxEmpty(n)) || (!tree.sxEmpty(n) && tree.dxEmpty(n))){
		Node f = new _Node<T>;
		if(!tree.sxEmpty(n))
			tree.copy(tree.sx(n), f);
		else
			tree.copy(tree.dx(n), f);

		Node p = tree.parent(n);
		if(tree.sx(p) == n){
			tree.erase(n);
			tree.insSx(p, f);
		}
		else{
			tree.erase(n);
			tree.insDx(p, f);
		}
	}
	else{
		Node succ = successor(n);
		erase(tree.read(succ));
		tree.write(n, tree.read(succ));
	}
}

template<typename T>
typename Bst<T>::Node Bst<T>::search(ValueType v){
	return search(tree.root(), v);
}

template<typename T>
typename Bst<T>::Node Bst<T>::search(Node n, ValueType v){
	if(tree.read(n) == v)
		return n;
	if(v < tree.read(n) && !tree.sxEmpty(n))
		return search(tree.sx(n), v);

	if(v > tree.read(n) && !tree.dxEmpty(n))
		return search(tree.dx(n), v);

	return NULL;
}

template<typename T>
typename Bst<T>::Node Bst<T>::minimum(){
	return minimum(tree.root());
}

template<typename T>
typename Bst<T>::Node Bst<T>::minimum(Node n){
	if(tree.sxEmpty(n))
		return n;

	return minimum(tree.sx(n));
}

template<typename T>
typename Bst<T>::Node Bst<T>::maximum(){
	return maximum(tree.root());
}

template<typename T>
typename Bst<T>::Node Bst<T>::maximum(Node n){
	if(tree.dxEmpty(n))
		return n;

	return maximum(tree.dx(n));
}

template<typename T>
typename Bst<T>::ValueType Bst<T>::read(Node n){
	if(n != NULL)
		return tree.read(n);
}

template<typename T>
void Bst<T>::write(Node n, ValueType v){
	if(n != NULL)
		tree.write(n, v);
}

template<typename T>
typename Bst<T>::Node Bst<T>::predecessor(Node n){
	if(!tree.sxEmpty(n))
		return maximum(tree.sx(n));

	if(tree.root( ) != n){
		Node p = tree.parent(n);
		while(tree.sx(p) == n){
			n = p;
			p = tree.parent(n);
		}

		return p;
	}

	return NULL;
}

template<typename T>
typename Bst<T>::Node Bst<T>::successor(Node n){
	if(!tree.dxEmpty(n))
		return minimum(tree.dx(n));

	if(tree.root() != n){
		Node p = tree.parent(n);
		while(tree.dx(p) == n){
			n = p;
			p = tree.parent(n);
		}

		return p;
	}

	return NULL;
}

template<typename T>
void Bst<T>::print(){
	cout<<tree;
}

template<typename T>
void Bst<T>::printInOrder(){
	printInOrder(tree.root());
	cout<<endl;
}

template<typename T>
void Bst<T>::printInOrder(Node n){
	if(!tree.sxEmpty(n))
		printInOrder(tree.sx(n));
	cout<<tree.read(n)<<" ";
	if(!tree.dxEmpty(n))
		printInOrder(tree.dx(n));

}

#endif /* BST_H_ */
