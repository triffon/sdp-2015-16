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
#include "binsearchtree.cpp"
#include "avltree.cpp"

using TestTree = Tree<int>;
using TestBinaryTree = BinaryTree<int>;
using TestBST = BinarySearchTree<int>;
using TestAVL = AVLTree<int>;

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

template <typename T>
void printArray(T a[], int n) {
	for(int i = 0; i < n; i++)
		cout << a[i] << ' ';
	cout << endl;
}

inline int left(int i) {
	return 2 * i + 1;
}

inline int right(int i) {
	return 2 * i + 2;
}


// пресяваме възела с индекс i надолу
template <typename T>
void siftDown(T a[], int i, int n) {
	// докато има дете, от което a[i] е по-малко
	while (left(i)  < n && a[i] < a[left(i)] ||
		   right(i) < n && a[i] < a[right(i)]) {
		// кое е по-голямото дете
		// Може би е лявото
		int newi = left(i);
		// А дали не е дясното?
		if (right(i) < n && a[right(i)] > a[left(i)])
			newi = right(i);
		swap(a[i], a[newi]);
		i = newi;
	}
	// (left(i) >= n || a[i] >= a[left(i)]) &&
    // (right(i) >= n || a[i] >= a[right(i)])
}

template <typename T>
void buildHeap(T a[], int n) {
	for(int i = n / 2 - 1; i >= 0; i--)
		siftDown(a, i, n);
}

template <typename T>
void disassembleHeap(T a[], int n) {
	for(int i = n - 1; i >= 1; i--) {
		swap(a[0], a[i]);
		siftDown(a, 0, i);
	}
}

template <typename T>
void heapSort(T a[], int n) {
	printArray(a, n);
	// 1. построяваме пирамида
	buildHeap(a, n);
	printArray(a, n);

	// 2. разглобяваме пирамидата
	disassembleHeap(a, n);
	printArray(a, n);
}

void testHeapSort() {
	int a[] = { 5, 1, 7, 2, 8, 4, 6, 10, 3, 8, 7 };
	const int N = sizeof(a) / sizeof(a[0]);
	heapSort(a, N);
}

void testBST() {
	TestAVL t;
	t.insert(5);
	t.insert(10);
	t.insert(15);
	t.insert(15);
	t.insert(18);
	t.insert(19);
	t.insert(20);
	t.insert(35);
	cout << (bool)t.search(20) << endl;
	cout << (bool)t.search(2) << endl;
	t.printDOT("bst.dot");
	t.remove(10);
	t.printDOT("bst2.dot");
	t.remove(15);
	t.printDOT("bst3.dot");
	t.remove(20);
	t.remove(20);
	t.printDOT("bst4.dot");
}

template <typename T>
BinaryTree<T> buildPBT(T a[], int n) {
	if (n == 0)
		return BinaryTree<T>();
	int mid = n / 2;
	return BinaryTree<T>(a[mid], buildPBT(a, mid),
								 buildPBT(a + mid + 1, n - mid - 1));
}

void testBuildPBT() {
	const int N = 20;
	int a[N];
	for(int i = 0; i < N; i++)
		a[i] = i + 1;
	TestBinaryTree&& bt = buildPBT(a, N);
	cout << depth(bt.root()) << endl;
	printDOT(bt,"pbt.dot");
}


int main() {
	// testTree();
	// testBinaryTree();
	// testPriorityQueue();
	// testHeapSort();
	testBST();
	// testBuildPBT();
	return 0;
}

