/*
 * main.cpp
 *
 *  Created on: 8.01.2016 г.
 *      Author: trifon
 */

#include <iostream>
#include "avl_dictionary.cpp"
#include "hashtable.hpp"

using namespace std;

// using TestDictionary = AVLDictionary<string, string>;
using TestDictionary = LinkedHashTable<string, string>;

void testDictionary() {
	TestDictionary dict(myhash);
	string keys[] = { "Todor", "Ivan", "Maria",
				"Vasil", "Ani", "Robert", "Bozhidar", "Yordan", "Plamena"
	};
	string values[] = { "Mihailov", "Petrov", "Georgieva",
				"Vasilev", "Nikolova", "Petrov", "Georgiev", "Yordanov", "Vandeva"
	};
	const int N = sizeof(keys) / sizeof(keys[0]);
	for(int i = 0; i < N; i++) {
		dict.add(keys[i], values[i]);
		cout << myhash(keys[i], MAX) << endl;
	}

	string* name = dict.lookup("Plamena");
	if (name != NULL)
		cout << *name << endl;
	else
		cout << "Няма фамилия!\n";
	cout << dict["Plamena"] << endl;
	cout << dict.keys();
	cout << dict.values();
}

void testHashFunction() {
	string keys[] = { "Todor", "Ivan", "Maria",
				"Vasil", "Ani", "Robert", "Bozhidar", "Yordan", "Plamena"
	};
	const int N = sizeof(keys) / sizeof(keys[0]);
	int MAX = 41;
	for(int i = 0; i < N; i++)
		cout << keys[i] << " -> " << myhash(keys[i], MAX) << endl;
}

int main() {
	testDictionary();
	// testHashFunction();
	return 0;
}

