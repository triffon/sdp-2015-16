/*
 * rstack.h
 *
 *  Created on: 26.03.2015 г.
 *      Author: trifon
 */

#ifndef RSTACK_H_
#define RSTACK_H_

#include "abstract_stack.h"

class ResizingStack : public AbstractStack<int> {
private:
	int* a; // елементите на стека
	int top; // индекс на последния елемент
	int capacity; // капацитет на стека

	// проверка дали стекът е пълен
	bool full() const;

	// разширяване на стека
	void resize();

	void copy(ResizingStack const&);
	void erase();

public:

	// създаване на празен стек
	ResizingStack();

	// конструктор за копиране
	ResizingStack(ResizingStack const&);

	// операция за присвояване
	ResizingStack& operator=(ResizingStack const&);

	// селектори

	// проверка дали стек е празен
	bool empty() const;

	// намиране на елемента на върха на стека
	int peek() const;

	// мутатори

	// включване на елемент
	void push(int const&);

	// изключване на елемент
	int pop();

	// деструктор
	~ResizingStack();

};



#endif /* RSTACK_H_ */
