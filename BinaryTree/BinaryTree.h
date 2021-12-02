#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include "BinTree.h"
#include "../Lista/List.h"

template<typename T>
class BinaryTree;

template<typename T>
class _Node{
public:
	//friend class BinaryTree<T>;

	_Node(){
		parent = NULL;
		sx = NULL;
		dx = NULL;
		subTreeNodes = 0;
	}

//private:
	T value;
	_Node<T>* parent;
	_Node<T>* sx;
	_Node<T>* dx;
	int subTreeNodes;
};

template<typename T>
class BinaryTree : public Bin_tree<T, _Node<T>*>{

	typedef typename Bin_tree<T, _Node<T>*>::value_type ValueType;
	typedef typename Bin_tree<T, _Node<T>*>::Nodo Node;

private:
	_Node<T>* radice;

	void stampaLivello(Node, int);
	void mediaLivello(Node, int, float&, float&, int&);
	void sommaLivello(Node, int, float&);
	void numNodiLivello(Node, int, int&);
	void nLeaf(Node, int&);
	bool isHeightBalanced(Node, int&);
	void completeNodes(Node, bool&);

	void updateSubTreeNumberNodes(Node n){
		if(n == NULL)
			return;

		n->subTreeNodes = contaNodi(n);
		updateSubTreeNumberNodes(n->parent);
	}


public:
	//Costruttori e distruttori
	BinaryTree();
	void create();
	//~BinaryTree();
	void clear();

	int numberNodes();
	bool empty() const;
	Node root() const ;
	Node parent(Node) const;
	Node sx(Node) const;
	Node dx(Node) const;
	bool sxEmpty(Node) const;
	bool dxEmpty(Node) const;

	BinaryTree<T> costr(BinaryTree<T>, ValueType);// Costruisce un nuovo albero che ha come figlio sinistro this e come figlio desto t2
	void erase(Node);

	ValueType read(Node) const;
	void write(Node, ValueType);

	void insRoot(ValueType);
	void insSx(Node, ValueType);
	void insDx(Node, ValueType);
	void insSx(Node, Node);
	void insDx(Node, Node);

	BinaryTree<T>& operator=(const BinaryTree<T>&);
	void copy(Node, Node);

	void previsit(Node);
	void invisita(Node);
	void postvisit(Node);

	int height(Node);//Calcola il numero di nodi lungo il percorso pi� lungo dal nodo in input fino al nodo foglia pi� lontano. Basta sottrarre -1 per ottenere il numero di archi.
	int depth(Node);//Calcola il numero di archi lungo il percorso pi� lungo dal nodo radice fino al nodo in input.

	bool isLeaf(Node);
	int contaNodi(Node);

	void stampaLivello(int);
	List<float> mediaLivelli();
	float mediaLivello(int);
	float sommaLivello(int);
	int numNodiLivello(int);

	int nLeaf();// restituisce il numero di foglie dell'albero

	bool isHeightBalanced();
	bool completeNodes();

	int subTreeNodes(Node n) const{
		return n->subTreeNodes;
	}

	void mutation(BinaryTree&, Node, BinaryTree&, Node);//scambia i sottoalberi con radice u e v.
};

template<typename T>
BinaryTree<T>::BinaryTree(){
	create();
}

template<typename T>
void BinaryTree<T>::create(){
	radice = NULL;
}

/*template<typename T>
BinaryTree<T>::~BinaryTree(){
	clear();
}*/

template<typename T>
void BinaryTree<T>::clear(){
	erase(radice);
}

template<typename T>
int BinaryTree<T>::numberNodes(){
	if(empty())
		return 0;

	return radice->subTreeNodes;
}

template<typename T>
bool BinaryTree<T>::empty() const{
	return radice == NULL;
}

template<typename T>
typename BinaryTree<T>::Node BinaryTree<T>::root() const{
	if(!empty())
		return radice;
}

template<typename T>
typename BinaryTree<T>::Node BinaryTree<T>::parent(Node n) const{
	if(n != root() && n != NULL)
		return n->parent;
}

template<typename T>
typename BinaryTree<T>::Node BinaryTree<T>::sx(Node n) const{
	if(n != NULL && !sxEmpty(n))
		return n->sx;
}

template<typename T>
typename BinaryTree<T>::Node BinaryTree<T>::dx(Node n) const{
	if(n != NULL && !dxEmpty(n))
		return n->dx;
}

template<typename T>
bool BinaryTree<T>::sxEmpty(Node n) const{
	return n->sx == NULL;
}

template<typename T>
bool BinaryTree<T>::dxEmpty(Node n) const{
	return n->dx == NULL;
}

template<typename T>
BinaryTree<T> BinaryTree<T>::costr(BinaryTree<T> t2, ValueType v){
	BinaryTree<T> t3;

	t3.insRoot(v);
	if(!this->empty()){
		t3.radice->sx = new _Node<T>;
		t3.radice->sx->parent = t3.radice;
		copy(radice, t3.radice->sx);
	}

	if(!t2.empty()){
		t3.radice->dx = new _Node<T>;
		t3.radice->dx->parent = t3.radice;
		copy(t2.radice, t3.radice->dx);
	}

	int dim = this->numberNodes() + t2.numberNodes();
	t3.radice->subTreeNodes = dim + 1;

	return t3;
}

template<typename T>
void BinaryTree<T>::erase(Node n){
	if(n != NULL){
		if(!sxEmpty(n))
			erase(n->sx);

		if(!dxEmpty(n))
			erase(n->dx);

		if(n != radice){
			Node p = n->parent;

			if(p->sx == n)
				p->sx = NULL;
			else
				p->dx = NULL;
		}
		else
			radice = NULL;
		updateSubTreeNumberNodes(n->parent);
	}
}

template<typename T>
typename BinaryTree<T>::ValueType BinaryTree<T>::read(Node n) const{
	return n->value;
}

template<typename T>
void BinaryTree<T>::write(Node n, ValueType v){
	if(n != NULL)
		n->value = v;
}

template<typename T>
void BinaryTree<T>::insRoot(ValueType v){
	if(radice == NULL){
		radice = new _Node<T>;
		radice->value = v;
		radice->parent = NULL;
		radice->sx = NULL;
		radice->dx = NULL;
		radice->subTreeNodes = 0;
	}
}

template<typename T>
void BinaryTree<T>::insSx(Node n, ValueType v){
	if(radice == NULL)
		cout<<"ERRORE: radice inesistente"<<endl;
	else if(n == NULL)
		cout<<"ERRORE: il nodo inserito ha valore null"<<endl;
	else if(n->sx != NULL)
		cout<<"ERRORE: un nodo e' gia' stato aggiunto"<<endl;
	else{
		n->sx = new _Node<T>;
		n->sx->value = v;
		n->sx->sx = NULL;
		n->sx->dx = NULL;
		n->sx->parent = n;
		updateSubTreeNumberNodes(n->sx);
	}
}

template<typename T>
void BinaryTree<T>::insDx(Node n, ValueType v){
	if(radice == NULL)
		cout<<"ERRORE: radice inesistente"<<endl;
	else if(n == NULL)
		cout<<"ERRORE: il nodo inserito ha valore null"<<endl;
	else if(n->dx != NULL)
		cout<<"ERRORE: un nodo e' gia' stato aggiunto"<<endl;
	else{
		n->dx = new _Node<T>;
		n->dx->value = v;
		n->dx->sx = NULL;
		n->dx->dx = NULL;
		n->dx->parent = n;
		updateSubTreeNumberNodes(n->dx);
	}
}

template<typename T>
void BinaryTree<T>::insSx(Node n, Node nsx){
	if(radice == NULL)
		cout<<"ERRORE: radice inesistente"<<endl;
	else if(n == NULL)
		cout<<"ERRORE: il nodo inserito ha valore null"<<endl;
	else if(n->sx != NULL)
		cout<<"ERRORE: un nodo e' gia' stato aggiunto"<<endl;
	else{
		n->sx = new _Node<T>;
		nsx->parent = n;
		n->sx = nsx;
		updateSubTreeNumberNodes(nsx);
	}
}

template<typename T>
void BinaryTree<T>::insDx(Node n, Node ndx){
	if(radice == NULL)
		cout<<"ERRORE: radice inesistente"<<endl;
	else if(n == NULL)
		cout<<"ERRORE: il nodo inserito ha valore null"<<endl;
	else if(n->dx != NULL)
		cout<<"ERRORE: un nodo e' gia' stato aggiunto"<<endl;
	else{
		n->dx = new _Node<T>;
		ndx->parent = n;
		n->dx = ndx;
		updateSubTreeNumberNodes(ndx);
	}
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& t1){
	this->clear();
	this->radice = new _Node<T>;
	this->radice->parent = NULL;

	copy(t1.radice, this->radice);

	return *this;
}

template<typename T>
void BinaryTree<T>::copy(Node r, Node nr){
	if(r != NULL){
		nr->value = r->value;
		nr->subTreeNodes = r->subTreeNodes;

		if(r->sx != NULL){
			nr->sx = new _Node<T>;
			nr->sx->parent = nr;
		}
		else
			nr->sx = NULL;

		if(r->dx != NULL){
			nr->dx = new _Node<T>;
			nr->dx->parent = nr;
		}
		else
			nr->dx = NULL;

		copy(r->sx, nr->sx);
		copy(r->dx, nr->dx);
	}
}

template<typename T>
void BinaryTree<T>::previsit(Node start){
	if (start == NULL) return;

	cout<<start->value<<" ";
	previsit(start->sx);
	previsit(start->dx);
}

template<typename T>
void BinaryTree<T>::invisita(Node start){
	if (start == NULL) return;

	invisita(start->sx);
	cout<<start->value<<" ";
	invisita(start->dx);
}

template<typename T>
void BinaryTree<T>::postvisit(Node start){
	if (start == NULL) return;

	postvisit(start->sx);
	postvisit(start->dx);
	cout<<start->value<<" ";
}

template<typename T>
int BinaryTree<T>::height(Node n){
	if(n == NULL)
		return 0;

	int hSx = height(n->sx);
	int hDx = height(n->dx);

	if(hSx >= hDx)
		return hSx + 1;
	else
		return hDx + 1;
}

template<typename T>
int BinaryTree<T>::depth(Node n){
	if(n == radice)
		return 0;

	int dep = depth(n->parent);

	return dep + 1;
}

template<typename T>
bool BinaryTree<T>::isLeaf(Node n){
	if(n != NULL)
		return n->sx == NULL && n->dx == NULL;

}

template<typename T>
int BinaryTree<T>::contaNodi(Node n){
	int i = 0;
	if (n == NULL) return 0;
	else i = i + 1;

	i = i + contaNodi(n->sx) + contaNodi(n->dx);

	return i;
}

template<typename T>
void BinaryTree<T>::stampaLivello(int l){
	stampaLivello(root(), l);
	cout<<endl;
}


template<typename T>
void BinaryTree<T>::stampaLivello(Node n, int l){
	if(n == NULL)
		return;

	if(l == 0)
		cout<<n->value<<" ";
	else{
		stampaLivello(n->sx, l - 1);
		stampaLivello(n->dx, l - 1);
	}
}

template<>
void BinaryTree<float>::sommaLivello(Node n, int l, float& sum){
	if(n == NULL)
		return;

	if(l == 0)
		sum = sum + n->value;
	else{
		sommaLivello(n->sx, l - 1, sum);
		sommaLivello(n->dx, l - 1, sum);
	}
}

template<>
void BinaryTree<float>::mediaLivello(Node n, int l, float& sum, float& med, int& numNodi){
	if(n == NULL)
		return;

	if(l == 0){
		sum = sum + n->value;
		numNodi++;
		med = sum / numNodi;
	}
	else{
		mediaLivello(n->sx, l - 1, sum, med, numNodi);
		mediaLivello(n->dx, l - 1, sum, med, numNodi);
	}
}

template<>
float BinaryTree<float>::mediaLivello(int l){
	if(l < 0 || l >= height(root()))
		return 0;

	float med = 0;
	float sum = 0;
	int numNodi = 0;
	mediaLivello(root(), l, sum, med, numNodi);

	return med;
}

template<>
List<float> BinaryTree<float>::mediaLivelli(){
	int h = height(root());
	List<float> med;

	for(int i = 0; i < h; i++)
		med.pushBack(mediaLivello(i));

	return med;
}

template<>
float BinaryTree<float>::sommaLivello(int l){
	if(l < 0 || l >= height(root()))
		return 0;

	float sum = 0;
	sommaLivello(root(), l, sum);

	return sum;
}

template<typename T>
int BinaryTree<T>::numNodiLivello(int l){
	if(l < 0 || l >= height(root()))
		return 0;

	int numNodi = 0;
	numNodiLivello(root(), l, numNodi);

	return numNodi;
}

template<typename T>
void BinaryTree<T>::numNodiLivello(Node n, int l, int& cont){
	if(n == NULL)
		return;

	if(l == 0)
		cont++;
	else{
		numNodiLivello(n->sx, l - 1, cont);
		numNodiLivello(n->dx, l - 1, cont);
	}
}

template<typename T>
int BinaryTree<T>::nLeaf(){
	int n = 0;

	nLeaf(root(), n);

	return n;
}

template<typename T>
void BinaryTree<T>::nLeaf(Node n, int& cont){
	if(n == NULL)
		return;

	if(isLeaf(n))
		cont++;

	nLeaf(n->sx, cont);
	nLeaf(n->dx, cont);
}

template<typename T>
bool BinaryTree<T>::isHeightBalanced(){
	int h = 0;

	return isHeightBalanced(root(), h);
}

template<typename T>
bool BinaryTree<T>::isHeightBalanced(Node n, int& height){
    int lh = 0, rh = 0;

    int l = 0, r = 0;

    if (n == NULL) {
        height = 0;
        return 1;
    }

    l = isHeightBalanced(n->sx, lh);
    r = isHeightBalanced(n->dx, rh);

    height = (lh > rh ? lh : rh) + 1;

    if (abs(lh - rh) >= 2)
        return 0;

    else
        return l && r;
}

template<typename T>
bool BinaryTree<T>::completeNodes(){
	if(empty() || isLeaf(root()))
		return false;

	bool cond = true;

	completeNodes(root(), cond);

	return cond;
}

template<typename T>
void BinaryTree<T>::completeNodes(Node n, bool& c){
	if(n == NULL || isLeaf(n) || !c)
		return;

	if(sxEmpty(n) || dxEmpty(n))
		c = false;

	completeNodes(n->sx, c);
	completeNodes(n->dx, c);
}

template<typename T>
void BinaryTree<T>::mutation(BinaryTree& t1, Node n1, BinaryTree& t2, Node n2){
	if(n1 == t1.root() && n2 == t2.root()){
		t1.radice = n2;
		t2.radice = n1;

		return;
	}

	if(n1 == t1.root() || n2 == t2.root()){
		if(n1 == t1.root()){
			Node n2p = n2->parent;

			t1.radice->parent = n2p;
			if(n2p->sx == n2){
				n2p->sx = t1.radice;
			}
			else{
				n2p->dx = t1.radice;
			}

			n2->parent = NULL;
			t1.radice = n2;
		}
		else if(n2 == t2.root()){
			Node n1p = n1->parent;

			t2.radice->parent = n1p;
			if(n1p->sx == n1){
				n1p->sx = t2.radice;
			}
			else{
				n1p->dx = t2.radice;
			}

			n1->parent = NULL;
			t2.radice = n1;
		}

		return;
	}

	Node n1p = n1->parent;
	Node n2p = n2->parent;

	n2->parent = n1p;
	if(n1p->sx == n1)
		n1p->sx = n2;
	else if(n1p->dx == n1)
		n1p->dx = n2;

	n1->parent = n2p;
	if(n2p->sx == n2)
		n2p->sx = n1;
	else if(n2p->dx == n2)
		n2p->dx = n1;
}


#endif /* BINARYTREE_H_ */