/*
 * bitwise.h
 *
 *  Created on: 9.10.2015 г.
 *      Author: trifon
 */

#ifndef BITWISE_H_
#define BITWISE_H_

#include <iostream>
using namespace std;

typedef unsigned long bits;
const int BITS_IN_BYTE = 8;

class Bitwise {
	bits b;

public:
	Bitwise(int _b = 0) : b(_b) {}

	int length() const { return sizeof(bits) * BITS_IN_BYTE; }

	// Мутатори
	void set(int i);
	void reset(int i);

	// Селектор
	bool get(int i) const;


};

ostream& operator<<(ostream&, Bitwise const&);

#endif /* BITWISE_H_ */
