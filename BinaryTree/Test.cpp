#include "BinaryTree.h"

int main() {
	BinaryTree<char> t1;
	BinaryTree<char> t2;

	t1.insRoot('a');
	t1.insSx(t1.root(), 'b');
	t1.insDx(t1.root(), 'c');
	t1.insSx(t1.sx(t1.root()), 'd');
	t1.insDx(t1.sx(t1.root()), 'e');

	t2.insRoot('f');
	t2.insSx(t2.root(), 'g');
	t2.insDx(t2.root(), 'h');
	t2.insSx(t2.dx(t2.root()), 'i');
	t2.insDx(t2.dx(t2.root()), 'j');

	t1.print();
	t2.print();

	cout<<endl;
	t1.mutation(t1, t1.sx(t1.root()), t2, t2.root());
	t1.print();
	t2.print();


	/*BinaryTree<float> t;
	BinaryTree<float> t1;

	t.insRoot(0.3);
	t.insSx(t.root(), 2.1);
	t.insDx(t.root(), 3.4);
	t.insSx(t.sx(t.root()), 8.2);
	t.insDx(t.sx(t.root()), 4.7);
	t.insSx(t.dx(t.root()), 1.9);
	t.insDx(t.dx(t.root()), 2.4);

	/*t.insSx(t.sx(t.sx(t.root())), 1.0);
	t.insDx(t.sx(t.sx(t.root())), 2.0);

	t.insSx(t.dx(t.sx(t.root())), 3.0);
	t.insDx(t.dx(t.sx(t.root())), 4.0);

	t.insSx(t.sx(t.dx(t.root())), 5.0);
	t.insDx(t.sx(t.dx(t.root())), 6.0);

	t.insSx(t.dx(t.dx(t.root())), 7.0);
	t.insDx(t.dx(t.dx(t.root())), 8.0);*/

	/*t1 = t;

	t1.print();
	t1.previsit(t1.root());
	cout<<endl;
	t1.invisita(t1.root());
	cout<<endl;
	t1.postvisit(t1.root());
	cout<<endl;

	cout<<endl;
	t1.stampaLivello(2);
	cout<<t1.nLeaf()<<endl;
	cout<<t1.sommaLivello(2)<<endl;
	cout<<t1.numNodiLivello(2)<<endl;
	cout<<t1.mediaLivello(2)<<endl;
	cout<<t1.mediaLivelli();
	cout<<"Height: "<<t1.height(t1.root())<<endl;
	cout<<"Depth: "<<t1.depth(t1.dx(t1.sx(t1.root())))<<endl;
	cout<<t1.isHeightBalanced()<<endl;
	cout<<t1.completeNodes()<<endl;




	//cout<<t.nLeaf()<<endl;
	//cout<<t.mediaLivello(3);
	//cout<<t.mediaLivelli()<<endl;


	/*BinaryTree<char> t1;
	BinaryTree<char> t2;

	t1.insRoot('a');
	t1.insSx(t1.root(), 'b');
	t1.insDx(t1.root(), 'c');
	cout<<t1;

	t2.insRoot('d');
	t2.insSx(t2.root(), 'e');
	t2.insDx(t2.root(), 'f');
	cout<<t2;

	BinaryTree<char> t3;
	t3 = t1.costr(t2, 'z');
	cout<<t3;
	cout<<"Height: "<<t1.height(t1.root())<<endl;
	cout<<"Depth: "<<t1.depth(t1.sx(t1.root()))<<endl;

	cout<<t3.contaNodi(t3.root());

	//cout<<t3.numberNodes()<<endl;

	/*t3.previsit(t3.root());
	cout<<endl;
	t3.invisita(t3.root());
	cout<<endl;
	t3.postvisit(t3.root());
	cout<<endl;*/

	//t1.costr(t2, 'z');
	//cout<<t1;

	//BinaryTree<char> t3;
	/*t1.costr(t2, 'z');
	//cout<<t3;
	cout<<t1<<endl;


	/*tree.insRoot('a');
	tree.insSx(tree.root(), 'b');
	tree.insDx(tree.root(), 'c');
	tree.insSx(tree.sx(tree.root()), 'g');
	tree.insDx(tree.sx(tree.root()), 'd');
	tree.insSx(tree.dx(tree.root()), 'e');
	tree.insDx(tree.dx(tree.root()), 'f');

	cout<<tree;
	cout<<tree.dxEmpty(tree.sx(tree.sx(tree.root())))<<endl;
	cout<<"OK"<<endl;

	tree.erase(tree.sx(tree.root()));
	cout<<tree;

	cout<<"OK"<<endl;
	cout<<tree.numberNodes()<<endl;
	cout<<tree.empty()<<endl;*/

	cin.get();
	return 0;
}
