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

	bool remove(T const& x) {
		P pos = findPosition(x);
		if (!pos)
			return false;
		BinarySearchTree<T> dyingThief;
		if (!-pos) {
			// крадецът краде x и детето му
			dyingThief.assignFrom(dyingThief.root(), pos);
			// родителят на x си връща дясното дете на x
			BinaryTree<T>::assignFrom(pos, +dyingThief.root());
		} else
		if (!+pos) {
			// крадецът краде x и детето му
			dyingThief.assignFrom(dyingThief.root(), pos);
			// родителят на x си връща лявото дете на x
			BinaryTree<T>::assignFrom(pos, -dyingThief.root());
		} else {
			// има и двете поддървета
			// трябва да заменим корена с M
			// където M е най-малкият (най-левият) елемент
			// в дясното поддърво
			P m = +pos;
			// вървим наляво докато можем
			while (-m) m = -m;
			// Като не можем повече (!-m), тогава сме на най-малкия елемент

			// 1. числото в m отива на мястото на корена
			*pos = *m;
			// 2. крадецът открадва m и детето му
			dyingThief.assignFrom(dyingThief.root(), m);
			// 3. родителят на m си връща дясното дете на m
			BinaryTree<T>::assignFrom(m, +dyingThief.root());
		}

		// dyingThief умира и завлича със себе си откраднатия възел
		// но само него, без децата му
		return true;
	}

	void printDOT(char const* filename) {
		::printDOT((BinaryTree<T>&)(*this), filename);
	}

};

#endif


