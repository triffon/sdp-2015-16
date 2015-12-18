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
class BinarySearchTree : protected BinaryTree<T> {
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
		if (+pos && -pos) {
			// има и двете поддървета
			// трябва да заменим корена с M
			// където M е най-малкият (най-левият) елемент
			// в дясното поддърво
			P m = +pos;
			// вървим наляво докато можем
			while (-m) m = -m;
			// Като не можем повече (!-m), тогава сме на най-малкия елемент

			// числото в m отива на мястото на корена
			*pos = *m;
			// сведохме задачата до случая, когато нямаме ляво поддърво
			pos = m;
		}
		// тук сме сигурни, че !-pos || !+pos
		if (!-pos)
			// закачаме дясното дете на мястото на родителя
			BinaryTree<T>::assignFrom(pos, +pos);
		else
			// !+pos
			// закачаме лявото дете на мястото на родителя
			BinaryTree<T>::assignFrom(pos, -pos);

		return true;
	}

	void printDOT(char const* filename) {
		::printDOT((BinaryTree<T>&)(*this), filename);
	}

};

#endif


