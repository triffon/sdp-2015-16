/*
 * bintree.cpp
 *
 *  Created on: 27.11.2015 г.
 *      Author: trifon
 */

#include <iostream>
using namespace std;

template <typename T>
struct TreeNode {
	T data;
	TreeNode *left, *right;

	TreeNode(T const& _data = T(),
			 TreeNode* _left = NULL,
			 TreeNode* _right = NULL)
			: data(_data), left(_left), right(_right) {}
};

template <typename T>
class BinaryTree {
private:
	TreeNode<T>* r;

	TreeNode<T>* copyNode(TreeNode<T>* n) {
		if (n == NULL)
			return n;
		cerr << "Copying tree" << endl;
		return new TreeNode<T>(n->data, copyNode(n->left),
				                        copyNode(n->right));
	}

	void eraseNode(TreeNode<T>* n) {
		if (n != NULL) {
			eraseNode(n->left);
			eraseNode(n->right);
			delete n;
		}
	}

	BinaryTree(TreeNode<T>* p) : r(copyNode(p)) {}

public:

	BinaryTree() : r(NULL) {}
	BinaryTree(T const& x, BinaryTree<T> const& lt,
			               BinaryTree<T> const& rt)
	: r(new TreeNode<T>(x, copyNode(lt.r), copyNode(rt.r))) {}


	BinaryTree(BinaryTree const& bt) : r(copyNode(bt.r)) {
	}

	BinaryTree& operator=(BinaryTree const& bt) {
		if (this != &bt) {
			eraseNode(r);
			r = copyNode(bt.r);
		}
		return *this;
	}

	~BinaryTree() {
		eraseNode(r);
	}

	T root() const {
		if (r == NULL)
			return T();
		return r->data;
	}

	BinaryTree leftTree() const {
		return BinaryTree(r->left);
	}

	BinaryTree rightTree() const {
		return BinaryTree(r->right);
	}

	bool empty() const {
		return r == NULL;
	}

};

template <typename T>
ostream& operator<<(ostream& os, BinaryTree<T> const& bt) {
	if (bt.empty())
		return os << '.';
	return os << '(' << bt.root() << ' ' << bt.leftTree()
			                      << ' ' << bt.rightTree() << ')';
}
