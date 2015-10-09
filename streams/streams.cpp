/*
 * streams.cpp
 *
 *  Created on: 9.10.2015 г.
 *      Author: trifon
 */


#include <iostream>
using namespace std;

int main() {
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
	return 0;
}

