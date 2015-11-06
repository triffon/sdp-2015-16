/*
 * lqueue.cpp
 *
 *  Created on: 30.10.2015 г.
 *      Author: trifon
 */


#include <iostream>
using namespace std;

template <typename T>
struct QueueElement {
	T data;
	QueueElement* next;

	QueueElement(T const& _data = T(), QueueElement* _next = NULL) :
		data(_data), next(_next) {}
};

template <typename T>
class LinkedQueue {
	QueueElement<T> *front, *back;

	void copy(LinkedQueue<T> const& q) {
		for(QueueElement<T>* p = q.front;p != NULL;p = p->next)
			enqueue(p->data);
	}

	void clean() {
		while (!empty())
			dequeue();
	}

public:

	LinkedQueue() : front(NULL), back(NULL) {}

	LinkedQueue(LinkedQueue const& q) : front(NULL), back(NULL) {
		copy(q);
	}

	LinkedQueue& operator=(LinkedQueue const& q) {
		if (this != &q) {
			clean();
			copy(q);
		}
		return *this;
	}

	~LinkedQueue() {
		clean();
	}

	bool empty() const {
		return back == NULL;
	}

	void enqueue(T const& x) {
		QueueElement<T>* p = new QueueElement<T>(x);
		if (!empty()) {
			back->next = p;
		} else
			front = p;
		back = p;
	}

	T dequeue() {
		if (empty()) {
			cerr << "Опит за изключване от празна опашка!\n";
			return T();
		}
		QueueElement<T>* p = front;
		front = front->next;
		if (front == NULL)
			back = NULL;
		T x = p->data;
		delete p;
		return x;
	}

	T head() const {
		if (empty()) {
			cerr << "Опит за поглеждане в празна опашка!\n";
			return T();
		}
		return front->data;
	}
};

template <typename T>
ostream& operator<<(ostream& os, LinkedQueue<T> q) {
	while (!q.empty())
		os << q.dequeue() << ' ';
	return os << endl;
}
