/*
 * hashtable.cpp
 *
 *  Created on: 8.01.2016 г.
 *      Author: trifon
 */

#ifndef _HASHTABLE_CPP
#define _HASHTABLE_CPP

#include <string>
#include "dictionary.h"
#include "linked_list.cpp"

using namespace std;

int myhash(string const& s, int max) {
	//return s.length() % max;
	//return s[0] % max;
	int sum = 0;
	int coef = 2;
	for(unsigned i = 0; i < s.length(); i++) {
		(sum += s[i] * coef) %= max;
		(++(coef *= coef)) %= max;
	}
	return sum;
}

const int MAX = 101;

template <typename K>
using HashFunction = int (*)(K const&, int);

template <typename K, typename V>
class LinkedHashTable : public Dictionary<K, V> {
private:
	using KVP = KeyValuePair<K, V>;
	using Bucket = LinkedList<KVP>;
	using BI = typename Bucket::I;

	Bucket table[MAX];
	HashFunction<K> hashFunction;

	BI search(Bucket const& bucket, K const& key) {
		BI it = bucket.begin();
		while (it && (*it).key() != key)
			++it;
		return it;
	}

public:
	LinkedHashTable(HashFunction<K> hf) : hashFunction(hf) {}

	// търсене
	V* lookup(K const& key) {
		int index = hashFunction(key, MAX);
		BI it = search(table[index], key);
		if (!it)
			return NULL;
		return &(*it).value();
	}

	// вмъкване
	bool add(K const& key, V const& value) {
		int index = hashFunction(key, MAX);
		if (search(table[index], key))
			// грешка, ключа вече го има
			return false;
		table[index].insertEnd(KVP(key, value));
		return true;
	}

	// изтриване
	bool remove(K const& key) {
		int index = hashFunction(key, MAX);
		BI it = search(table[index], key);
		if (!it)
			return false;
		KVP tmp;
		table[index].deleteAt(tmp, it);
		return true;
	}

	// списък от ключове
	LinkedList<K> keys() {
		LinkedList<K> result;
		for(int i = 0; i < MAX; i++)
			for(BI it = table[i].begin(); it; ++it)
				result.insertEnd((*it).key());
		return result;
	}

	// списък от стойности
	LinkedList<V> values() {
		LinkedList<V> result;
		for(int i = 0; i < MAX; i++)
			for(BI it = table[i].begin(); it; ++it)
				result.insertEnd((*it).value());
		return result;
	}
};

#endif
