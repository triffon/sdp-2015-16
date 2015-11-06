/*
 * main.cpp
 *
 *  Created on: 30.10.2015 г.
 *      Author: trifon
 */

#include <iostream>
#include <cmath>
using namespace std;

#include "squeue.cpp"
#include "lqueue.cpp"

typedef LinkedQueue<int> TestQueue;

void test1() {
	TestQueue q;
	for(int i = 0; i < 105; i++)
		q.enqueue(i);
	TestQueue q2 = q;
	q2.enqueue(-1);
	while (!q2.empty())
		cout << q2.dequeue() << ' ';
	cout << endl;
}

void test2() {
	TestQueue q;
	for(int i = 0; i < 105; i++) {
		q.enqueue(i);
		cout << q.dequeue() << ' ';
		// cout << q.head() << ' ';
	}
}

// O(log n)
bool isHamming(int n) {
	for(int d = 2; d <= 5; d++)
		while (n % d == 0)
			n /= d;
	return n == 1;
}

// O(n(log n))
void firstHamming(int n) {
	int counter = 0;
	int i = 1;
	while (counter < n) {
		if (isHamming(i)) {
			cout << i << ' ';
			counter++;
		}
		i++;
	}
	cout << endl;
}

template <typename T>
LinkedQueue<T>& minQ(LinkedQueue<T>& q1, LinkedQueue<T>& q2) {
	return (q1.head() < q2.head()) ? q1 : q2;
}

template <typename T>
void dequeueIf(LinkedQueue<T>& q, T const& x) {
	if (q.head() == x)
		q.dequeue();
}

void firstHammingQueue(int n) {
	LinkedQueue<int> q2, q3, q5;
	cout << 1 << ' ';
	q2.enqueue(2);
	q3.enqueue(3);
	q5.enqueue(5);
	for(int counter = 1;counter < n; counter++) {
		// намираме опашката с най-малкото число
		// LinkedQueue<int>& minq = minQ(minQ(q2, q3), q5);

		// намираме и извеждаме най-малкото число
		// int x = minq.head();
		int x = min(q2.head(), min(q3.head(), q5.head()));
		cout << x << ' ';

		// изваждаме числото x от ВСИЧКИ опашки, които го
		// съдържат
		dequeueIf(q2, x);
		dequeueIf(q3, x);
		dequeueIf(q5, x);

		// добавяме в q2, q3, q5 числата 2*x, 3*x, 5*x
		q2.enqueue(2*x);
		q3.enqueue(3*x);
		q5.enqueue(5*x);
	}
	cout << endl;
}

template <typename T>
ostream& operator<<(ostream& os, LinkedQueue<T>& q) {
	while (!q.empty())
		os << q.dequeue() << ' ';
	return os << endl;
}

template <typename T>
T dequeueMin(LinkedQueue<T>& q) {
	T min = q.dequeue();
	T sentinel;
	q.enqueue(sentinel);
	while (q.head() != sentinel) {
		T x = q.dequeue();
		if (x < min) {
			q.enqueue(min);
			min = x;
		} else
			q.enqueue(x);
	}
	// махаме сентинела
	q.dequeue();
	return min;
}

void testDequeueMin() {
	LinkedQueue<int> q;
	for (int i = 1; i < 20; i++)
		q.enqueue(i * 101 % 37);
	LinkedQueue<int> q2 = q;
	cout << q2;
	cout << "min: " << dequeueMin(q) << endl;
	cout << q;
}

int main() {
	// test1();
	// test2();
	//const int N = 100;
	//firstHamming(N);
	//firstHammingQueue(N);
	testDequeueMin();
	return 0;
}


