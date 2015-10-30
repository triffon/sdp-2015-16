/*
 * squeue.cpp
 *
 *  Created on: 30.10.2015 г.
 *      Author: trifon
 */

#include <iostream>
using namespace std;

const int MAX = 100;

template <typename T>
class StaticQueue {
	T a[MAX];
	int front, back;

	bool full() const {
		return back == MAX - 1;
	}

public:
	StaticQueue() : front(0), back(-1) {}

	bool empty() const {
		return front > back;
	}

	void enqueue(T const& x) {
		if (full())
			cerr << "Опит за включване в пълна опашка!\n";
		else
			a[++back] = x;
	}

	T dequeue() {
		if (empty()) {
			cerr << "Опит за изключване от празна опашка!\n";
			return T();
		} else
			return a[front++];
	}

	T head() const {
		if (empty()) {
			cerr << "Опит за поглеждане в празна опашка!\n";
			return T();
		}
		return a[front];
	}
};


