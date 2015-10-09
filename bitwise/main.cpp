/*
 * main.cpp
 *
 *  Created on: 9.10.2015 г.
 *      Author: trifon
 */

#include "bitwise.h"

int main() {
	Bitwise b(65);
	cout << b << endl;
	b.set(15);
	b.reset(6);
	//for(int i = 0; i < 1000; i++)
		cout << b << endl;
	//clog << "Край!\n";
	//cerr << "Край!\n";
	for(int i = 0; i < 10000; i++) {
		if (i == 1000)
			cerr << "Test";
		cout << "Проба";
	}
	return 0;
}


