/*
 * stack.cpp
 *
 *  Created on: 19.03.2015 г.
 *      Author: trifon
 */

#include <iostream>
using namespace std;

#include "stack.h"

int const EMPTY_STACK = -1; // отбелязваме празен стек

Stack::Stack() {
	top = EMPTY_STACK;
}

bool Stack::empty() const {
	return top == EMPTY_STACK;
}

int Stack::peek() const {
	if (empty()) {
		cout << "Грешка: опит за поглеждане в празен стек!\n";
		return 0;
	}

	return a[top];
}

void Stack::push(int const& x) {
	if (full()) {
		cout << "Грешка: опит за включване в пълен стек!\n";
	} else
		a[++top] = x;
}

bool Stack::full() const {
	return top == MAX - 1;
}

int Stack::pop() {
	if (empty()) {
		cout << "Грешка: опит за изключване от празен стек!\n";
		return 0;
	}
	return a[top--];
}



