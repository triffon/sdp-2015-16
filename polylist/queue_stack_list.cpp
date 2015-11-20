/*
 * queue_stack_list.cpp
 *
 *  Created on: 20.11.2015 г.
 *      Author: trifon
 */

#include <iostream>
using namespace std;
#include "linked_list.cpp"
#include "lqueue.cpp"
#include "lstack.cpp"

template <typename T>
class Object {
public:
	// включване
	virtual bool insert(T const&) = 0;

	// изключване
	virtual bool remove(T&) = 0;

	// извеждане
	virtual void print(ostream& os) const = 0;

	virtual ~Object() {}
};

template <typename T>
class StackObject : public Object<T>, private LinkedStack<T> {
public:
	// включване
	bool insert(T const& x) {
		LinkedStack<T>::push(x);
		return true;
	}

	// изключване
	bool remove(T& x) {
		if (LinkedStack<T>::empty())
			return false;
		x = LinkedStack<T>::pop();
		return true;
	}

	// извеждане
	void print(ostream& os) const {
		os << *this;
	}
};

template <typename T>
class QueueObject : public Object<T>, private LinkedQueue<T> {
public:
	// включване
	bool insert(T const& x) {
		LinkedQueue<T>::enqueue(x);
		return true;
	}

	// изключване
	bool remove(T& x) {
		if (LinkedQueue<T>::empty())
			return false;
		x = LinkedQueue<T>::dequeue();
		return true;
	}

	// извеждане
	void print(ostream& os) const {
		os << *this;
	}
};

template <typename T>
//using QueueStackList = LinkedList<Object<T>*>;
class QueueStackList : public LinkedList<Object<T>*> {
public:
	~QueueStackList() {
		for(LinkedListIterator<Object<T>*> it = this->begin(); it; ++it)
			delete *it;
	}
};

/*
template <typename T>
ostream& operator<<(ostream& os, QueueStackList<T> const& qsl) {
	for(LinkedListIterator<Object<T>*> it = qsl.begin(); it; ++it)
		(*it)->print(os);
	return os << endl;

}
*/

template <typename T>
ostream& operator<<(ostream& os, Object<T>* o) {
	o->print(os);
	return os;
}
