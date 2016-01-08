/*
 * dictionary.h
 *
 *  Created on: 8.01.2016 г.
 *      Author: trifon
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <utility>
using namespace std;
#include "linked_list.cpp"

template <typename K, typename V>
class Dictionary {
public:
	// търсене
	virtual V* lookup(K const&) = 0;

	// вмъкване
	virtual bool add(K const&, V const&) = 0;

	// изтриване
	virtual bool remove(K const&) = 0;

	// списък от ключове
	virtual LinkedList<K> keys() = 0;

	// списък от стойности
	virtual LinkedList<V> values() = 0;

	virtual ~Dictionary() {}
};

template <typename K, typename V>
class KeyValuePair : public pair<K, V> {
public:
	KeyValuePair(K const& key = K(), V const& value = V())
		: pair<K,V>(key, value) {}

	K& key()   { return pair<K,V>::first; }
	V& value() { return pair<K,V>::second; }

	K const& key()   const { return pair<K,V>::first; }
	V const& value() const { return pair<K,V>::second; }

	bool operator==(KeyValuePair const& kvp) const {
		return key() == kvp.key();
	}

	bool operator!=(KeyValuePair const& kvp) const {
		return !(*this == kvp);
	}
};


#endif /* DICTIONARY_H_ */
