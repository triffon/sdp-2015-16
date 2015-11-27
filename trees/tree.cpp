/*
 * tree.cpp
 *
 *  Created on: 27.11.2015 г.
 *      Author: trifon
 */


#include <iostream>
using namespace std;
#include "linked_list.cpp"

template <typename T>
class Tree {
private:
	T data;
	LinkedList<Tree<T>> children;
	// !!! Tree t;
	// Tree* t;

public:

	using I = LinkedListIterator<Tree<T>>;

	Tree(T const& _data = T()) : data(_data) {}

	Tree<T>& addChild(Tree<T> const& c) {
		children.insertEnd(c);
		return *this;
	}

	T root() const {
		return data;
	}

	I subtrees() const {
		return children.begin();
	}
};

template <typename T>
ostream& operator<<(ostream& os, Tree<T> const& t) {
	os << '(';
	for(typename Tree<T>::I it = t.subtrees();it;++it)
		os << *it << ' ';
	return os << t.root() << ')';
}

