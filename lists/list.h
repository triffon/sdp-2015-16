/*
 * list.h
 *
 *  Created on: 6.11.2015 г.
 *      Author: trifon
 */

#ifndef LIST_H_
#define LIST_H_

template <typename T, typename P>
class List {
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
};

template <typename T>
class Iterator {
	// Iterator it = l.begin();
	// it++; --> връща старата позиция (rvalue)
	// ++it; --> връща новата позиция (lvalue)
	// x = *it;
	// *it = 5;
	// if (!it) --> невалиден
	// if (it) --> валиден

	// придвижва итератора напред и връща старата позиция
	virtual Iterator operator++(int) = 0;

	// придвижва итератора напред и връща новата позиция
	virtual Iterator& operator++() = 0;

	// придвижва итератора назад и връща старата позиция
	virtual Iterator operator--(int) = 0;

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
};


#endif /* LIST_H_ */
