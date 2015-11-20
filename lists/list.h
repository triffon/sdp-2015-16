/*
 * list.h
 *
 *  Created on: 6.11.2015 г.
 *      Author: trifon
 */

#ifndef LIST_H_
#define LIST_H_

#include <iostream>
using namespace std;

template <typename T, typename P>
class List {
protected:

	// O(n)
	void copy(List<T, P> const& l) {
		for(P it = l.begin(); it; ++it)
			insertEnd(*it);
	}

	// O(n)
	void clean() {
		T tmp;
		while (deleteEnd(tmp));
	}

public:
	// проверка за празнота
	virtual bool empty() const = 0;

	// включване преди позиция
	virtual bool insertBefore(T const&, P const&) = 0;

	// включване след позиция
	virtual bool insertAfter(T const&, P const&) = 0;

	// изключване преди позиция
	virtual bool deleteBefore(T&, P const&) = 0;

	// изключване на позиция
	virtual bool deleteAt(T&, P const&) = 0;

	// изключване след позиция
	virtual bool deleteAfter(T&, P const&) = 0;

	// достъп до елемент на позиция
	virtual T& elementAt(P const&) = 0;

	// връща позицията "начало на списъка"
	virtual P begin() const = 0;

	// връща позицията "край на списъка"
	virtual P end() const = 0;

	// O(1)
	bool insertBegin(T const& x) {
		return insertBefore(x, begin());
	}

	// O(1)
	bool insertEnd(T const& x) {
		return insertAfter(x, end());
	}

	// O(1)
	bool deleteBegin(T& x) {
		return deleteAt(x, begin());
	}

	// O(1)
	bool deleteEnd(T& x) {
		return deleteAt(x, end());
	}

	virtual ~List() {}

};

template <typename T, typename ConcreteIterator>
class Iterator {
public:
	// Iterator it = l.begin();
	// it++; --> връща старата позиция (rvalue)
	// ++it; --> връща новата позиция (lvalue)
	// x = *it;
	// *it = 5;
	// if (!it) --> невалиден
	// if (it) --> валиден

	// придвижва итератора напред и връща старата позиция
	ConcreteIterator operator++(int) {
		ConcreteIterator copy = (ConcreteIterator&)*this;
		operator++();
		return copy;
	}

	// придвижва итератора напред и връща новата позиция
	virtual Iterator& operator++() = 0;

	// придвижва итератора назад и връща старата позиция
	ConcreteIterator operator--(int) {
		ConcreteIterator copy = (ConcreteIterator&)*this;
		operator--();
		return copy;
	}

	// придвижва итератора назад и връща новата позиция
	virtual Iterator& operator--() = 0;

	// достъп до елемент
	virtual T& operator*() const = 0;

	// проверка за валидност
	virtual operator bool() const = 0;

	// проверка за невалидност
	bool operator!() const {
		return !operator bool();
	}

	// сравнение

	virtual bool operator==(Iterator const&) const = 0;

	bool operator!=(Iterator const& it) const {
		return !(*this == it);
	}

	virtual ~Iterator() {}
};

template<typename T, typename P>
ostream& operator<<(ostream& os, List<T, P> const& l) {
	for(P it = l.begin(); it; ++it)
		os << *it << ' ';
	return os << endl;
}


#endif /* LIST_H_ */
