/*
 * main.cpp
 *
 *  Created on: 27.11.2015 г.
 *      Author: trifon
 */

#include <cmath>

#include "tree.cpp"
#include "bintree.cpp"
#include "priority_queue.cpp"

using TestTree = Tree<int>;
using TestBinaryTree = BinaryTree<int>;

template <typename I>
int length(I it) {
	int result = 0;
	while (it++)
		result++;
	return result;
}

template <typename T>
int breadth(Tree<T> const& t) {
	int result = length(t.subtrees());
	for(typename Tree<T>::I it = t.subtrees();it;++it) {
		int l = breadth(*it);
		if (l > result)
			result = l;
	}
	return result;
}

void testTree() {
	TestTree t1(1);
	t1.addChild(TestTree(2)
				.addChild(TestTree(3))
				.addChild(TestTree(4)
						  .addChild(TestTree(5))
						  .addChild(TestTree(6)))
			    .addChild(TestTree(7))
			    .addChild(TestTree(8)))
	  .addChild(TestTree(9))
	  .addChild(TestTree(10));
	cout << t1 << endl;
	cout << breadth(t1) << endl;
}

template <typename T>
int depth(BinaryTreePosition<T> pos) {
	if (!pos)
		return 0;
	return 1 + max(depth(-pos), depth(+pos));
}

template <typename T>
bool operator==(BinaryTreePosition<T> p1, BinaryTreePosition<T> p2) {
	return  (!p1 && !p2) ||
			p1 && p2 && *p1 == *p2 && -p1 == -p2 && +p1 == +p2;
}

void testBinaryTree() {
	TestBinaryTree e;
	TestBinaryTree t(1, 2, TestBinaryTree(3, 4, 5));
	//TestBinaryTree t2(0, t, t);
	cout << "-----\n";
	//cout << t2;
	cout << t.root() << endl;
	t.assignFrom(-+t.root(), TestBinaryTree(6,7,8));
	printDOT(t, "tree.dot");
	cout << "Дълбочина: " << depth(t.root()) << endl;
	cout << t.root() << endl;
	t.deleteAt(-+t.root());
	cout << t.root() << endl;
	cout << "Проверка за равенство: " <<
			(TestBinaryTree(1, 2, TestBinaryTree(3, TestBinaryTree(), 6)).root()
			 ==
			t.root()) << endl;
	BinaryTreePosition<int> pos = t.root();
	pos = +pos;
	BinaryTreePosition<int> newpos = +pos;
}

void testPriorityQueue() {
	PriorityQueue<int> pq;
	pq.enqueue_prioritized(5);
	pq.enqueue_prioritized(6);
	pq.enqueue_prioritized(3);
	pq.enqueue_prioritized(4);
	pq.enqueue_prioritized(2);
	pq.enqueue_prioritized(1);
	cout << pq.dequeue_highest() << endl;
	cout << pq.dequeue_highest() << endl;
	pq.printDOT("heap.dot");
}

int main() {
	// testTree();
	// testBinaryTree();
	testPriorityQueue();
	return 0;
}

