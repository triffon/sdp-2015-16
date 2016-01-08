/*
 * avl_dictionary.cpp
 *
 *  Created on: 8.01.2016 г.
 *      Author: trifon
 */

#ifndef _AVL_DICTIONARY
#define _AVL_DICTIONARY

#include "dictionary.h"
#include "avltree.cpp"

template <typename K, typename V>
class AVLDictionary : AVLTree<KeyValuePair<K,V> >,
					  public Dictionary<K,V> {
private:

	using KVP = KeyValuePair<K, V>;
	using AKVP = AVLElement<KVP>;

	void collectKeys(BinaryTreePosition<AKVP> pos, LinkedList<K>& keys) {
		if (pos) {
			collectKeys(-pos, keys);
			keys.insertEnd((*pos).data().key());
			collectKeys(+pos, keys);
		}
	}

	void collectValues(BinaryTreePosition<AKVP> pos, LinkedList<V>& values) {
		if (pos) {
			collectValues(-pos, values);
			values.insertEnd((*pos).data().value());
			collectValues(+pos, values);
		}
	}


public:

	// търсене
	V* lookup(K const& key) {
		KVP* result = AVLTree<KVP>::search(key);
		if (result == NULL)
			return NULL;
		return &result->value();
	}

	// вмъкване
	bool add(K const& key, V const& value) {
		return AVLTree<KVP>::insert(KVP(key, value));
	}

	// изтриване
	bool remove(K const& key) {
		return AVLTree<KVP>::remove(key);
	}

	// списък от ключове
	LinkedList<K> keys() {
		LinkedList<K> result;
		collectKeys(BinaryTree<AKVP>::root(), result);
		return result;
	}

	// списък от стойности
	LinkedList<V> values() {
		LinkedList<V> result;
		collectValues(BinaryTree<AKVP>::root(), result);
		return result;
	}

};

#endif


