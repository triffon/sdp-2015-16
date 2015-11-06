/*
 * linked_list.cpp
 *
 *  Created on: 6.11.2015 г.
 *      Author: trifon
 */

#include <iostream>
using namespace std;

#include "list.h"

template <typename T>
struct LinkedListElement {
	T data;
	LinkedListElement* next;

	LinkedListElement(T _data = T(), LinkedListElement* _next = NULL)
		: data(_data), next(_next) {}
};

template <typename T>
class LinkedListIterator : public Iterator<T> {
	LinkedListElement<T>* p;
public:

	LinkedListIterator(LinkedListElement<T>* _p = NULL) : p(_p) {}

	// придвижва итератора напред и връща старата позиция
	Iterator<T> operator++(int) {
		LinkedListIterator copy = *this;
		operator++();
		return copy;
	}

	// придвижва итератора напред и връща новата позиция
	Iterator<T>& operator++() {
		if (p != NULL)
			p = p->next;
		return *this;
	}

	// придвижва итератора назад и връща старата позиция
	Iterator<T> operator--(int) {
		// не можем да се връщаме назад!!!
		return LinkedListIterator();
	}

	// придвижва итератора назад и връща новата позиция
	Iterator<T>& operator--() {
		// не можем да се връщаме назад!!!
		return *this;
	}

	// достъп до елемент
	T& operator*() const {
		// ВНИМАНИЕ: итераторът трябва да е валиден!
		return p->data;
	}

	// проверка за валидност
	operator bool() const {
		return p != NULL;
	}

};

