#include "M-aryTree.h"

int main() {
	/*NTree<char> t;

	t.insRoot('a');
	t.insFirstNode(t.root(), 'c');
	t.insSibling(t.firstChild(t.root()), 'k');
	t.insSibling(t.nextSibling(t.firstChild(t.root())), 'h');
	t.insFirstNode(t.firstChild(t.root()), 'j');
	t.insSibling(t.firstChild(t.firstChild(t.root())), 'b');
	t.insFirstNode(t.nextSibling(t.firstChild(t.firstChild(t.root()))), 'e');
	t.insFirstNode(t.nextSibling(t.nextSibling(t.firstChild(t.root()))), 'f');
	t.insSibling(t.firstChild(t.nextSibling(t.nextSibling(t.firstChild(t.root())))), 'd');
	t.insSibling(t.nextSibling(t.firstChild(t.nextSibling(t.nextSibling(t.firstChild(t.root()))))), 'g');
	t.insSibling(t.nextSibling(t.nextSibling(t.firstChild(t.nextSibling(t.nextSibling(t.firstChild(t.root())))))), 'i');

	t.print();
	cout<<t.depth()<<endl;
	cout<<t.width()<<endl;

	List<_TreeNode<char>*> l;

	_TreeNode<char>* na = new _TreeNode<char>('a');
	_TreeNode<char>* nc = new _TreeNode<char>('c');
	_TreeNode<char>* nk = new _TreeNode<char>('k');
	_TreeNode<char>* nh = new _TreeNode<char>('h');
	_TreeNode<char>* nj = new _TreeNode<char>('j');
	_TreeNode<char>* nb = new _TreeNode<char>('b');
	_TreeNode<char>* ne = new _TreeNode<char>('e');
	_TreeNode<char>* nf = new _TreeNode<char>('f');
	_TreeNode<char>* nd = new _TreeNode<char>('d');
	_TreeNode<char>* ng = new _TreeNode<char>('g');
	_TreeNode<char>* ni = new _TreeNode<char>('i');

	l.pushBack(na);
	l.pushBack(nc);

	l.pushBack(na);
	l.pushBack(nk);

	l.pushBack(na);
	l.pushBack(nh);

	l.pushBack(nc);
	l.pushBack(nj);

	l.pushBack(nc);
	l.pushBack(nb);

	l.pushBack(nb);
	l.pushBack(ne);

	l.pushBack(nh);
	l.pushBack(nf);

	l.pushBack(nh);
	l.pushBack(nd);

	l.pushBack(nh);
	l.pushBack(ng);

	l.pushBack(nh);
	l.pushBack(ni);

	t.createFromList(l).print();*/

	NTree<int> t;
	NTree<int> t2;
	NTree<int> t3;

	t.insRoot(1);
	t.insFirstNode(t.root(), 2);
	t.insFirstNode(t.root(), 3);
	t.insFirstNode(t.root(), 4);
	t.print();

	t2 = t;
	t3 = t;

	t2.print();
	t3.print();


	t.insRoot(1);
	t.insFirstNode(t.root(), 2);
	t.insFirstNode(t.root(), 3);
	t.insFirstNode(t.root(), 4);
	t.print();

	t2.insRoot(100);
	t2.insFirstNode(t2.root(), 200);
	t2.insFirstSubTree(t2.root(), t);
	t2.print();

	t2.insSubTree(t2.firstChild(t2.root()), t);
	t2.print();

	/*t2.preorder(t2.root());
	cout<<endl;
	t2.postorder(t2.root());
	cout<<endl;
	t2.inorder(t2.root());
	cout<<endl;

	t2.clear();

	t2.insRoot(100);
	t2.print();
	t2.BFS(t2.root());*/

	cin.get();
	return 0;
}
