/*
 * bintree.cpp
 *
 *  Created on: 27.11.2015 г.
 *      Author: trifon
 */

#ifndef _BINTREE_CPP
#define _BINTREE_CPP

#include <iostream>
#include <fstream>
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
class BinaryTree;

template <typename T>
class BinaryTreePosition {
private:
	TreeNode<T>*& p;
public:
	BinaryTreePosition(TreeNode<T>*& _p) : p(_p) {}

	operator bool() const {
		return p != NULL;
	}

	bool operator!() const {
		return p == NULL;
	}

	T& operator*() const {
		return p->data;
	}

	BinaryTreePosition operator+() const {
		if (p == NULL)
			return *this;
		return BinaryTreePosition(p->right);
	}

	BinaryTreePosition operator-() const {
		if (p == NULL)
			return *this;
		return BinaryTreePosition(p->left);
	}

	friend class BinaryTree<T>;

};

template <typename T>
class BinaryTree {
private:
	TreeNode<T>* r;

	TreeNode<T>* copyNode(TreeNode<T>* n) {
		if (n == NULL)
			return n;
		cout << "Copying tree" << endl;
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

	void assignFrom(TreeNode<T>*& to, TreeNode<T>*& from) {
		eraseNode(to);
		to = from;
		from = NULL;
	}

public:

	using P = BinaryTreePosition<T>;

	BinaryTree() : r(NULL) {}
	BinaryTree(T const& x, BinaryTree<T>&& lt = BinaryTree<T>(),
			               BinaryTree<T>&& rt = BinaryTree<T>()) {
		r = new TreeNode<T>(x);
		assignFrom(r->left,  lt.r);
		assignFrom(r->right, rt.r);
	}

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

	void assignFrom(P pos, BinaryTree<T>&& t) {
		assignFrom(pos.p, t.r);
	}

	void deleteAt(P pos) {
		TreeNode<T>* tmp = NULL;
		assignFrom(pos.p, tmp);
	}

	/*
	T root() const {
		if (r == NULL)
			return T();
		return r->data;
	}
	*/
	P root() {
		return P(r);
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
	return os << '(' << *bt.root() << ' ' << bt.leftTree()
			                       << ' ' << bt.rightTree() << ')';
}


template <typename T>
ostream& operator<<(ostream& os, BinaryTreePosition<T> pos) {
	if (!pos)
		return os << '.';
	return os << '(' << *pos << ' ' << -pos
			                 << ' ' << +pos << ')';
}

template <typename T>
void printDOT(ofstream&, BinaryTreePosition<T>);

template <typename T>
void printEdge(ofstream& dot, BinaryTreePosition<T> from,
								BinaryTreePosition<T> to) {
	if (to) {
		dot << *from << " -> " << *to << ";\n";
		printDOT(dot, to);
	}
}

template <typename T>
void printDOT(ofstream& dot, BinaryTreePosition<T> pos) {
	if (pos) {
		printEdge(dot, pos, -pos);
		printEdge(dot, pos, +pos);
	}
}

template <typename T>
void printDOT(BinaryTree<T>& t, char const* filename) {
	ofstream dot(filename);
	dot << "digraph tree { ";
	printDOT(dot, t.root());
	dot << "}";
}

#endif
