/*
 * main.cpp
 *
 *  Created on: 30.10.2015 г.
 *      Author: trifon
 */

#include <iostream>
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
int main() {
	test1();
	test2();
	return 0;
}


