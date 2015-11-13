/*
 * main.cpp
 *
 *  Created on: 13.11.2015 г.
 *      Author: trifon
 */

#include "linked_list.cpp"

typedef LinkedList<int> TestList;

// O(n)
template <typename T, typename I>
void append(List<T, I>& l1, List<T, I> const& l2) {
	for(I it = l2.begin(); it; ++it)
		l1.insertEnd(*it);
}

// O(n)
template <typename T, typename I>
void reverse(List<T, I>& l) {
	I bit = l.begin();
	// bit е оригиналното начало на списъка
	T x;
	while (l.deleteAfter(x, bit)) // O(1)
		l.insertBegin(x); // O(1)
}

template <typename T, typename I>
void split(List<T, I> const& l, List<T, I>& l1, List<T, I>& l2) {
/*	bool first = true;
	for(I it = l.begin(); it; ++it) {
		if (first)
			l1.insertEnd(*it);
		else
			l2.insertEnd(*it);
		first = !first;
	}*/
	List<T, I> *first = &l1, *second = &l2;
	for(I it = l.begin(); it; ++it) {
		first->insertEnd(*it);
		swap(first, second);
	}
}

template <typename T, typename I>
void merge(List<T, I> const& l1, List<T, I> const& l2, List<T, I>& l) {
	I i1 = l1.begin(), i2 = l2.begin();
	while (i1 && i2) {
		if (*i1 < *i2)
			l.insertEnd(*(i1++));
		else
			l.insertEnd(*(i2++));
	}
	// !i1 || !i2
	while (i1)
		l.insertEnd(*i1++);
	while (i2)
		l.insertEnd(*i2++);
}

TestList sort(TestList const& l) {
	if (!++l.begin())
		return l;
	// 1. разделяме
	TestList l1, l2;
	split(l, l1, l2);

	// 2. рекурсивно сортираме
	// 3. сливаме сортираните списъци
	TestList result;
	merge(sort(l1), sort(l2), result);
	return result;
}

template <typename T, typename I>
T foldr(T (*op)(T, T), T nv, I it) {
	if (!it)
		return nv;
	T x = *it++;
	return op(x, foldr(op, nv, it));
}

int myplus(int x, int y) {
	return x + y;
}


void testList() {
	TestList l;
	for(int i = 1; i <= 10; i++)
		if (i % 2 == 0)
			l.insertEnd(i);
		else
			l.insertBegin(i);
	cout << l;
	TestList* l2 = new TestList(l);
	l2->insertEnd(100);
	cout << l << *l2 << endl;

	// append(l, *l2);
	l.append(*l2);
	cout << *l2 << endl;
	delete l2;
	cout << l << endl;
	reverse(l);
	cout << l << endl;
	TestList l3, l4;
	//split(l, l3, l4);
	//cout << l3 << endl << l4 << endl;
	for(int i = 1; i <= 10; i++)
		if (i % 3 == 0)
			l3.insertEnd(i);
		else
			l4.insertEnd(i);
	cout << l3 << endl << l4 << endl;
	TestList l5;
	merge(l3, l4, l5);
	cout << l5 << endl;
	//LinkedListIterator<int> it = l.begin();
	//cout << *it << ' ';
	//it++;
	//cout << *it << ' ';
	cout << sort(l) << endl;
	cout << foldr(myplus, 0, l.begin()) << endl;
}



int main() {
	testList();
	return 0;
}


