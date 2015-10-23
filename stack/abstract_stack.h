/*
 * abstract_stack.h
 *
 *  Created on: 28.05.2015 г.
 *      Author: trifon
 */

#ifndef ABSTRACT_STACK_H_
#define ABSTRACT_STACK_H_

template <typename T>
class AbstractStack {
public:
	// селектори

	// проверка дали стек е празен
	virtual bool empty() const = 0;

	// намиране на елемента на върха на стека
	virtual T peek() const = 0;

	// мутатори

	// включване на елемент
	virtual void push(T const&) = 0;

	// изключване на елемент
	virtual T pop() = 0;

	virtual ~AbstractStack() {}
};



#endif /* ABSTRACT_STACK_H_ */
