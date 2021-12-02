#ifndef TREE_H_
#define TREE_H_

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

template<class I, class N>
class Tree{
	public:
	typedef I item;
	typedef N node;

	virtual void create () = 0;
	virtual bool empty () const = 0;
	virtual void insRoot (item) = 0;
	virtual node root () const = 0;
	virtual node parent (node) const = 0;
	virtual bool leaf (node) const = 0;
	virtual node firstChild (node) const = 0;
	virtual bool lastSibling (node) const = 0;
	virtual node nextSibling (node) const = 0;

	/*virtual void insFirstSubTree (node, Tree) = 0;
	virtual void insSubTree (node, Tree) = 0;*/

	virtual void removeSubTree (node) = 0;
	virtual void writeNode (node, item) = 0;
	virtual item readNode (node) const = 0;

	//void BFS(node);
	virtual void preorder(node) = 0;
	virtual void postorder(node) = 0;
};


#endif /* TREE_H_ */
