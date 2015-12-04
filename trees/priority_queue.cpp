/*
 * priority_queue.cpp
 *
 *  Created on: 4.12.2015 г.
 *      Author: trifon
 */

#include "bintree.cpp"

template <typename T>
class PriorityQueue : BinaryTree<T> {
private:
	using P = BinaryTreePosition<T>;

	void insertAndSiftUp(P pos, T const& x) {
		if (pos) {
			P newpos = (x % 2) ? -pos : +pos;
			insertAndSiftUp(newpos, x);
			// sift up
			if (*newpos > *pos)
				swap(*newpos, *pos);
		} else {
			// insert
			BinaryTree<T>::assignFrom(pos, BinaryTree<T>(x));
		}
	}

	P findLeaf(P pos) const {
		if (!pos || (!-pos && !+pos))
			return pos;
		if (!-pos)
			return findLeaf(+pos);
		if (!+pos)
			return findLeaf(-pos);
		return findLeaf((*pos % 2) ? -pos : +pos);
	}

	P maxChild(P pos) {
		if (!-pos)
			return +pos;
		if (!+pos)
			return -pos;
		return *-pos > *+pos ? -pos : +pos;

	}

	void siftDown(P pos) {
		if (pos) {
			P maxcpos = maxChild(pos);
			if (maxcpos && *pos < *maxcpos)
				swap(*maxcpos, *pos);
			siftDown(maxcpos);
		}
	}

public:
	bool empty() const { return BinaryTree<T>::empty(); }

	T head() { return *BinaryTree<T>::root(); }

	void enqueue_prioritized(T const& x) {
		insertAndSift(BinaryTree<T>::root(), x);
	}

	T dequeue_highest() {
		P rpos = BinaryTree<T>::root();
		T result = head();
		P pos = findLeaf(rpos);
		swap(*pos,*rpos);
		BinaryTree<T>::deleteAt(pos);
		siftDown(rpos);
		return result;
	}

	void printDOT(char const* filename) {
		::printDOT((BinaryTree<T>&)(*this), filename);
	}
};


