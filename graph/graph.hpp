/*
 * graph.cpp
 *
 *  Created on: 14.01.2016 г.
 *      Author: trifon
 */

#ifndef __GRAPH_CPP
#define __GRAPH_CPP

#include <iostream>
using namespace std;

#include "hashtable.hpp"
#include "linked_list.cpp"

template <typename T>
class Graph {
protected:
	LinkedHashTable<T, LinkedList<T> > g;
public:

	using VI = LinkedListIterator<T>;

	LinkedList<T> vertices() {
		return g.keys();
	}

	VI successors(T const& u) {
		return g[u].begin();
	}

	bool isEdge(T const& u, T const& v) {
		VI it = successors(u);
		while(it && *it != v)
			++it;
		return it;
	}

	void addVertex(T const& u) {
		g.add(u, LinkedList<T>());
	}

	void removeVertex(T const& u) {
		for(VI it = vertices().begin();it; ++it)
			removeEdge(*it, u);
		g.remove(u);
	}

	void addEdge(T const& u, T const& v) {
		g[u].insertEnd(v);
	}

	void removeEdge(T const& u, T const& v) {
		LinkedList<T>& su = g[u];
		T tmp;
		for(VI it = su.begin(); it; ++it)
			if (*it == v)
				su.deleteAt(tmp, it);
	}

	void printDOT(ostream& os = cout) {
		os << "digraph g {\n";
		// всички ребра:
		// за всеки връх в графа:
		LinkedList<T> v = vertices();
		for(VI it = v.begin(); it; ++it)
			// обхождаме всеки негов наследник
			for(VI sit = successors(*it); sit; ++sit)
				os << "\"" << *it << "\" -> \"" << *sit << "\";\n";
		os << "}\n";
	}
};

int inthash(unsigned const& x, int MAX) {
	return x % MAX;
}

class IntGraph : public Graph<unsigned> {
public:
	IntGraph() {
		g.setHashFunction(inthash);
	}

	using Graph<unsigned>::addVertex;
	using Graph<unsigned>::removeVertex;
	using Graph<unsigned>::addEdge;
	using Graph<unsigned>::removeEdge;
	using Graph<unsigned>::isEdge;
	using Graph<unsigned>::vertices;
	using Graph<unsigned>::successors;
	using Graph<unsigned>::printDOT;
};

#endif
