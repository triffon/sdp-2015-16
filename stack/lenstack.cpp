/*
 * lenstack.cpp
 *
 *  Created on: 7.05.2015 г.
 *      Author: trifon
 */

#include "lstack.cpp"

template <typename T>
class LengthStack : public LinkedStack<T> {
private:
	int length;
public:
	LengthStack() : // LinkedStack<T>(),
					length(0) {}

	/* !!!
	~LengthStack() {
		~LinkedStack<T>();
	} 	!!! 	*/

	int getLength() const { return length; }

	/*
	bool empty() const { return length == 0; }
	*/

	void push(T const& x) {
		LinkedStack<T>::push(x);
		length++;
	}

	T pop() {
		if (!LinkedStack<T>::empty())
			length--;
		return LinkedStack<T>::pop();
	}
};


