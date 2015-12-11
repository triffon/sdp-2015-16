/*
 * binsearchtree.cpp
 *
 *  Created on: 11.12.2015 г.
 *      Author: trifon
 */

#ifndef _BINSEARCHTREE_CPP
#define _BINSEARCHTREE_CPP

#include "bintree.cpp"

template <typename T>
class BinarySearchTree : BinaryTree<T> {
public:
	using typename BinaryTree<T>::P;

private:

	P findPosition(T const& x) {
		P pos = BinaryTree<T>::root();
		while (pos && *pos != x)
			if (x < *pos)
				pos = -pos;
			else
				pos = +pos;
		// *pos == x -- намерихме!
		// !pos --- няма го
		return pos;
	}

public:

	T* search(T const& x) {
		P pos = findPosition(x);
		if (pos)
			return &*pos;
		return NULL;
	}

	bool insert(T const& x) {
		P pos = findPosition(x);
		if (!pos) {
			BinaryTree<T>::assignFrom(pos, x);
			return true;
		}
		return false;
	}

	void printDOT(char const* filename) {
		::printDOT((BinaryTree<T>&)(*this), filename);
	}

};

#endif


