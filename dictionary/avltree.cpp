/*
 * avltree.cpp
 *
 *  Created on: 18.12.2015 г.
 *      Author: trifon
 */

#ifndef _AVLTREE_CPP
#define _AVLTREE_CPP

#include "binsearchtree.cpp"

template <typename T>
class AVLElement {
	//  : public pair<T, int> {
private:
	T x;
	int b;
public:
	AVLElement(T const& _data = T(), int _balance = 0)
	   : x(_data), b(_balance) {}

	T& data() { return x; }
	int& balance() { return b; }

	bool operator<(AVLElement const& avle) const {
		return x < avle.x;
	}

	bool operator==(AVLElement const& avle) const {
		return x == avle.x;
	}

	bool operator!=(AVLElement const& avle) const {
		return !(*this == avle);
	}

	bool operator>=(AVLElement const& avle) const {
		return !(*this < avle);
	}

	bool operator<=(AVLElement const& avle) const {
		return *this < avle || *this == avle;
	}

	bool operator>(AVLElement const& avle) const {
		return !(*this <= avle);
	}
};

template <typename T>
ostream& operator<<(ostream& os, AVLElement<T> avle) {
	return os << avle.data();
}

template <typename T>
class AVLTree : protected BinarySearchTree<AVLElement<T>> {
private:

	using AVL = AVLElement<T>;
	using BT = BinaryTree<AVL>;
	using BST = BinarySearchTree<AVL>;
	using P = BinaryTreePosition<AVL>;

	void rotateLeft(P x) { // zag
		BT tmp;
		P y = tmp.root();
		BT::assignFrom(y, +x);

		int& bx = (*x).balance();
		int& by = (*y).balance();

		BT::assignFrom(+x, -y);
		BT::assignFrom(-y, x);
		BT::assignFrom(x, y);

		if (by <= 0)
			bx--;
		else
			bx -= by + 1;

		if (bx >= 0)
			by--;
		else
			by += bx - 1;

	}

	void rotateRight(P y) { // zig
		BT tmp;
		P x = tmp.root();
		BT::assignFrom(x, -y);

		int& bx = (*x).balance();
		int& by = (*y).balance();

		BT::assignFrom(-y, +x);
		BT::assignFrom(+x, y);
		BT::assignFrom(y, x);

		if (bx >= 0)
			by++;
		else
			by -= bx - 1;

		if (by <= 0)
			bx++;
		else
			bx += by + 1;
	}

	// -1 --- неуспешно включване, елементът вече го има
	// 0  --- успешно включване, но няма промяна във височината
	// 1  --- успешно включване и има увеличение на височината с 1
	int insertAt(P p, T const& x) {
		if (!p) {
			// дъно
			BinaryTree<AVL>::assignFrom(p, AVL(x));
			return 1;
		}
		// p --- валидна позиция
		if ((*p).data() == x)
			// Грешка! x вече го има
			return -1;
		// p && *p != x
		int result;
		if (x < (*p).data()) {
			// вмъкваме наляво
			result = insertAt(-p, x);
			if (result == 1) {
				(*p).balance()--;
				if ((*p).balance() == -2) {
					if ((*-p).balance() == 1)
						rotateLeft(-p);
					rotateRight(p);
					result = 0;
				}
			}
		} else {
			// вмъкваме надясно
			result = insertAt(+p, x);
			if (result == 1) {
				(*p).balance()++;
				if ((*p).balance() == 2) {
					if ((*+p).balance() == -1)
						rotateRight(+p);
					rotateLeft(p);
					result = 0;
				}
			}
		}
		// ако сме вмъкнали успешно и балансът се е получил 0
		// значи нямаме промяна във височината
		if (result >= 0 && (*p).balance() == 0)
			result = 0;
		return result;
	}

public:
	T* search(T const& x) {
		return &(BST::search(x)->data());
	}

	bool insert(T const& x) {
		return insertAt(BST::root(), x) >= 0;
	}

	bool remove(T const& x) {
		return false;
	}

	void printDOT(char const* filename) {
		::printDOT((BST&)(*this), filename);
	}

};

#endif


