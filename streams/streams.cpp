/*
 * streams.cpp
 *
 *  Created on: 9.10.2015 г.
 *      Author: trifon
 */

#include <iomanip>

#include <iostream>
using namespace std;

void recover() {
	int a = 0;
	cin >> a;
	while (!cin) {
		cout << a << ' ' << cin.rdstate() << endl;
		if (!cin) {
			cin.clear();
			cin.ignore();
			cin >> a;
		}
	}

	cout << a << ' ' << cin.rdstate() << endl;
}

void manipulators() {
	cout << hex << showbase << internal << setw(10) << setfill('.') << 123 << endl;
	cout << scientific << 1.23;
}

int main() {
	// recover();
	manipulators();
	return 0;
}

