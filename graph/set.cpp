
/*
 * set.cpp
 *
 *  Created on: 14.01.2016 г.
 *      Author: trifon
 */

#include "linked_list.cpp"
#include "dictionary.h"

template <typename T, template<typename, typename> class D>
class Set {
private:
	using DT = D<T, bool>;
	DT dict;
public:
	// проверка за празнота
	bool empty() const {
		return dict.keys().empty();
	}

	// включване на елемент
	bool insert(T const& x) {
		return dict.add(x, false);
	}

	// изключване на елемент
	bool remove(T const& x) {
		return dict.remove(x);
	}

	// проверка за съдържане
	bool contains(T const& x) {
		return dict.lookup(x) != NULL;
	}

	// списък от елементи
	LinkedList<T> elements() {
		return dict.keys();
	}

	template <typename K>
	using HashFunction = int (*)(K const&, int);

	void setHashFunction(HashFunction<T> hf) {
		dict.setHashFunction(hf);
	}
};

// Set<int, AVLDictionary>
// Set<string, HashTable>
// template <typename T> using HashSet = Set<T, HashTable>
// HashSet<int>
// template <typename T> using AVLSet = Set<T, AVLDictionary>
// AVLSet<string>
