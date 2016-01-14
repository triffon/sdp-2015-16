/*
 * main.cpp
 *
 *  Created on: 14.01.2016 г.
 *      Author: trifon
 */

#include <fstream>
using namespace std;
#include "graph.hpp"

/*
 * (1, 2), (2, 3), (3, 6), (1, 3), (4, 1), (3, 4), (5, 3), (6, 5), (4, 5), (2, 6)
 */

template <typename T>
using VI = LinkedListIterator<T>;

template <typename T>
using VL = LinkedList<T>;

template <typename T>
VL<T> noSuccessors(Graph<T>& g) {
	VL<T> result;
	VL<T> v = g.vertices();
	for(VI<T> it = v.begin(); it; ++it)
		if (!g.successors(*it))
			result.insertEnd(*it);
	return result;
}

template <typename T>
VL<T> predecessors(Graph<T>& g, T const& v) {
	VL<T> result;
	VL<T> vl = g.vertices();
	for(VI<T> it = vl.begin(); it; ++it)
		if (g.isEdge(*it, v))
			result.insertEnd(*it);
	return result;
}


void testGraph() {
	IntGraph g;
	for(int i = 1; i <= 6; i++)
		g.addVertex(i);
	cout << g.vertices() << endl;
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(3, 6);
	g.addEdge(1, 3);
	g.addEdge(4, 1);
	g.addEdge(3, 4);
	g.addEdge(5, 3);
	g.addEdge(6, 5);
	g.addEdge(4, 5);
	g.addEdge(2, 6);

	cout << *g.successors(1) << endl;
	ofstream of("graph.dot");
	g.printDOT(of);

	cout << noSuccessors(g) << endl;
	cout << predecessors(g, (unsigned)3) << endl;
	g.removeEdge(5, 3);
	cout << noSuccessors(g) << endl;
	cout << predecessors(g, (unsigned)3) << endl;
}

int main() {
	testGraph();
	return 0;
}


