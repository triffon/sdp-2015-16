/*
 * bitwise.cpp
 *
 *  Created on: 9.10.2015 г.
 *      Author: trifon
 */

#include "bitwise.h"

void Bitwise::set(int i) {
	bits mask = 1L << i;
	b |= mask;
}

void Bitwise::reset(int i) {
	bits mask = ~(1L << i);
	b &= mask;
}

bool Bitwise::get(int i) const {
	bits mask = 1L << i;
	return b & mask;
}

ostream& operator <<(ostream& os, const Bitwise& bw) {
	for(int i = 0; i < bw.length(); i++)
		os << bw.get(i);
	return os;
}
