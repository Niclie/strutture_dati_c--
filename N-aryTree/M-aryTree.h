#ifndef M_ARYTREE_H_
#define M_ARYTREE_H_

#include "Tree.h"
#include "../Lista/List.h"
#include "../Queue/Queue.h"

template<typename T>
class NTree;


template<typename T>
class _TreeNode{
friend class NTree<T>;

private:
	T value;
	_TreeNode<T>* parent;
	List<_TreeNode<T>*> child;

public:
	_TreeNode(){
		parent = NULL;
		child = List<_TreeNode<T>*>();
	}

	_TreeNode(T etichetta){
		parent = NULL;
		child = List<_TreeNode<T>*>();
		value = etichetta;
	}
};


template<typename T>
class NTree : public Tree<T, _TreeNode<T>*>{
public:
	typedef typename Tree<T, _TreeNode<T>*>::item ValueType;
	typedef typename Tree<T, _TreeNode<T>*>::node TreeNode;

private:
	_TreeNode<T>* radice;
	int numNode;

	void printSubTree(_TreeNode<T>*);
	int depth(TreeNode);
	int width(TreeNode);


public:
	NTree();
	void create();
	//~NTree();//ATTENZIONE: in caso di strani problemi COMMENTARE
	void clear();

	bool empty() const;
	void insRoot (ValueType);
	TreeNode root() const;
	TreeNode parent(TreeNode) const;
	bool leaf(TreeNode) const;
	TreeNode firstChild(TreeNode) const;
	bool lastSibling(TreeNode) const;
	TreeNode nextSibling(TreeNode) const;

	void insFirstSubTree(TreeNode, NTree);
	void insSubTree(TreeNode, NTree);

	void removeSubTree (TreeNode);
	void writeNode (TreeNode, ValueType);
	ValueType readNode (TreeNode) const;

	void insFirstNode(TreeNode, ValueType);// inserisce un node come firstChild di n
	void insSibling(TreeNode, ValueType);// inserisce un node come frattello successivo di n

	NTree& operator=(const NTree&);
	TreeNode copy(TreeNode, TreeNode);

	void print();

	void preorder(TreeNode);
	void postorder(TreeNode);
	void inorder(TreeNode);
	void BFS(TreeNode);//esplora l'albero per livelli

	int depth();// ATTENZIONE profondità espressa in termini d nodi e non di archi (basta sottrarre -1)
	int width();

	NTree createFromList(List<TreeNode>);
};

template<typename T>
NTree<T>::NTree(){
	numNode = 0;
	create();
}

template<typename T>
void NTree<T>::create(){
	radice = NULL;
}

/*template<typename T>
NTree<T>::~NTree(){
	clear();
}*/

template<typename T>
void NTree<T>::clear(){
	removeSubTree(radice);
}

template<typename T>
bool NTree<T>::empty() const{
	return numNode == 0;
}

template<typename T>
void NTree<T>::insRoot (ValueType v){
	if(empty()){
		radice = new _TreeNode<T>(v);
		radice->parent = NULL;

		numNode++;
	}
}

template<typename T>
typename NTree<T>::TreeNode NTree<T>::root() const{
	if(!empty())
		return radice;
}

template<typename T>
typename NTree<T>::TreeNode NTree<T>::parent(TreeNode n) const{
	if(n != NULL && n != radice)
		return n->parent;
}

template<typename T>
bool NTree<T>::leaf(TreeNode n) const{
	if(n != NULL && !empty())
		return n->child.empty();
}

template<typename T>
typename NTree<T>::TreeNode NTree<T>::firstChild (TreeNode n) const{
	if(n != NULL && !leaf(n))
		return n->child.read(n->child.begin());
}

template<typename T>
bool NTree<T>::lastSibling(TreeNode n) const{
	if(n != NULL && n != radice){
		TreeNode parent = n->parent;
		return parent->child.read(parent->child.last()) == n;
	}
}

template<typename T>
typename NTree<T>::TreeNode NTree<T>::nextSibling(TreeNode n) const{
	if(n != NULL && n != radice && !lastSibling(n)){
		typename List<TreeNode>::Position it;
		for(it = n->parent->child.begin(); n->parent->child.read(it) != n; it = n->parent->child.next(it));

		return(n->parent->child.read(n->parent->child.next(it)));
	}
}

template<typename T>
void NTree<T>::insFirstSubTree(TreeNode n, NTree t){
	if(!empty() && !t.empty() && n != NULL){
		NTree newTree;
		newTree = t;
		newTree.radice->parent = n;

		n->child.pushFront(newTree.radice);

		numNode = numNode + t.numNode;
	}
}

template<typename T>
void NTree<T>::insSubTree(TreeNode n, NTree t){
	if(!empty() && !t.empty() && n != NULL && n != radice){
		typename List<TreeNode>::Position it;
		for(it = n->parent->child.begin(); n->parent->child.read(it) != n; it = n->parent->child.next(it));

		NTree newTree;
		newTree = t;
		newTree.radice->parent = n->parent;
		n->parent->child.insert(n->parent->child.next(it), newTree.radice);
		numNode = numNode + t.numNode;
	}
}

template<typename T>
void NTree<T>::removeSubTree(TreeNode n){
	if(empty())
		return;

	if(leaf(n)){
		if(n != radice)
			n->parent->child.popFront();
		else
			n = NULL;

		numNode--;
		delete n;
	}
	else{
		List<TreeNode> l;
		l = n->child;
		for(typename List<TreeNode>::Position it = l.begin(); !l.end(it); it = l.next(it))
			removeSubTree(l.read(it));

		n = NULL;
		numNode--;
		delete n;
	}
}


template<typename T>
void NTree<T>::writeNode(TreeNode n, ValueType v){
	n->value = v;
}

template<typename T>
typename NTree<T>::ValueType NTree<T>::readNode(TreeNode n) const{
	return n->value;
}

// inserisce un node come firstChild di n
template<typename T>
void NTree<T>::insFirstNode(TreeNode n, ValueType v){
	if(!empty() && n != NULL){
		TreeNode newNode = new _TreeNode<T>(v);
		newNode->parent = n;
		n->child.pushFront(newNode);

		numNode++;
	}
}

// inserisce un node come frattello successivo di n
template<typename T>
void NTree<T>::insSibling(TreeNode n, ValueType v){
	if(!empty() && n != NULL && n != radice){
		TreeNode p = n->parent;
		TreeNode newNode = new _TreeNode<T>(v);
		newNode->parent = p;
		p->child.pushBack(newNode);
		numNode++;
	}
}


template<typename T>
NTree<T>& NTree<T>::operator=(const NTree& tree){
	this->~NTree();

	radice = copy(tree.radice, NULL);
	this->numNode = tree.numNode;

	return *this;
}

template<typename T>
typename NTree<T>::TreeNode NTree<T>::copy(TreeNode n, TreeNode p){
	if(n == NULL)
		return NULL;

	TreeNode newRoot = new _TreeNode<T>;
	newRoot->value = n->value;
	newRoot->parent = p;
	p = newRoot;
	for(typename List<TreeNode>::Position it = n->child.begin(); !n->child.end(it); it = n->child.next(it))
		newRoot->child.pushBack(copy(n->child.read(it), p));

	return newRoot;
}

template<typename T>
void NTree<T>::preorder(TreeNode n){
	if(empty())
		return;

	cout<<n->value<<" ";
	if(!leaf(n)){
		TreeNode c = firstChild(n);
		while(!lastSibling(c)){
			preorder(c);
			c = nextSibling(c);
		}
		preorder(c);
	}
}

template<typename T>
void NTree<T>::postorder(TreeNode n){
	if(empty())
		return;

	if(!leaf(n)){
		TreeNode c = firstChild(n);
		while(!lastSibling(c)){
			postorder(c);
			c = nextSibling(c);
		}
		postorder(c);
	}
	cout<<n->value<<" ";
}

template<typename T>
void NTree<T>::inorder(TreeNode n){
	if(empty())
		return;

	if(leaf(n))
		cout<<n->value<<" ";
	else{
		TreeNode c = firstChild(n);
		inorder(c);
		cout<<n->value<<" ";
		while(!lastSibling(c)){
			c = nextSibling(c);
			inorder(c);
		}
	}
}

template<typename T>
void NTree<T>::print(){
	if(!empty())
		printSubTree(this->radice);
	else
		cout<<"[]";

	cout<<endl;
}

template<typename T>
void NTree<T>::printSubTree(_TreeNode<T>* n){
	cout<<"["<<n->value;

	if(!n->child.empty()){
		cout<<": ";
		for(typename List<_TreeNode<T>*>::Position it = n->child.begin(); !n->child.end(it); it = n->child.next(it))
			printSubTree(n->child.read(it));
	}

	cout<<"]";
}

template<typename T>
void NTree<T>::BFS(TreeNode n){
	if(n == NULL)
		return;

	Queue<TreeNode> q;
	q.inCoda(n);
	int i = 0;
	while(!q.empty()){
		cout<<"Level "<<i<<": ";
		int n = q.size();
		while(n > 0){
			TreeNode temp = q.leggiCoda();
			cout<<readNode(temp)<<" ";
			q.fuoriCoda();

			for(typename List<TreeNode>::Position it = temp->child.begin(); !temp->child.end(it); it = temp->child.next(it))
				q.inCoda(temp->child.read(it));

			n--;
		}
		i++;
		cout<<endl;
	}
}

template<typename T>
int NTree<T>::depth(){
	return depth(root());
}

int max(int x, int y){
	if(x > y)
		return x;

	return y;
}

template<typename T>
int NTree<T>::depth(TreeNode n){
	if(n == NULL)
		return 0;

	int maxDepth = 0;
	for(typename List<TreeNode>::Position it = n->child.begin(); !n->child.end(it); it = n->child.next(it))
		maxDepth = max(maxDepth, depth(n->child.read(it)));

	return maxDepth + 1;
}

template<typename T>
int NTree<T>::width(){
	return width(root());
}

template<typename T>
int NTree<T>::width(TreeNode n){
	if(n == NULL)
		return 0;

	int maxWidth = 0;

	Queue<TreeNode> q;
	q.inCoda(n);
	while(!q.empty()){
		int actualWidth = q.size();

		maxWidth = max(maxWidth, actualWidth);

		while(actualWidth > 0){
			TreeNode temp = q.leggiCoda();
			q.fuoriCoda();

			for(typename List<TreeNode>::Position it = temp->child.begin(); !temp->child.end(it); it = temp->child.next(it))
				q.inCoda(temp->child.read(it));

			actualWidth--;
		}
	}

	return maxWidth;
}

template<typename T>
NTree<T> NTree<T>::createFromList(List<TreeNode> l){
	NTree<T> t;
	int cont = 1;

	typename List<TreeNode>::Position j = l.next(l.begin());
	typename List<TreeNode>::Position i = l.begin();
	do{
		TreeNode temp = l.read(j);
		temp->parent = l.read(i);

		l.read(i)->child.pushBack(temp);

		cont++;
		i = l.next(l.next(i));
		j = l.next(l.next(j));
	}while(!l.end(i));

	t.radice = l.read(l.begin());
	t.numNode = cont;

	return t;
}



#endif /* M_ARYTREE_H_ */
