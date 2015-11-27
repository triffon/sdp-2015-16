/*
 * slist.cpp
 *
 *  Created on: 27.11.2015 г.
 *      Author: trifon
 */

#include <iostream>
using namespace std;

#include "linked_list.cpp"

class Element {
public:
	// извеждане
	virtual void print(ostream&) const = 0;

	// събиране на атоми
	virtual void collectInts(LinkedList<int>&) const = 0;

	virtual ~Element() {}
};

class IntElement : public Element {
private:
	int x;
public:
	IntElement(int _x = 0) : x(_x) {}

	void print(ostream& os) const {
		os << x;
	}

	void collectInts(LinkedList<int>& l) const {
		l.insertEnd(x);
	}
};

class ListElement : public Element, public LinkedList<Element*> {
public:
	void print(ostream& os) const {
		os << '(';
		for(LinkedListIterator<Element*> it = this->begin(); it; ++it) {
			if (it != this->begin())
				os << ' ';
			(*it)->print(os);
		}
		os << ')';
	}

	void collectInts(LinkedList<int>& l) const {
		for(LinkedListIterator<Element*> it = this->begin(); it; ++it)
			(*it)->collectInts(l);
	}

	~ListElement() {
		for(LinkedListIterator<Element*> it = this->begin(); it; ++it) {
			/*
			cout << "Ще изтрием: ";
			(*it)->print(cout);
			cout << endl;
			*/
			delete *it;
		}

	}
};

using SList = ListElement;
/*
ostream& operator<<(ostream& os, LinkedList<Element*>const& sl) {
	for(LinkedListIterator<Element*> it = sl.begin(); it; ++it)
		(*it)->print(os);
	return os;
}
*/
