/*
 * main.cpp
 *
 *  Created on: 14.01.2016 г.
 *      Author: trifon
 */

#include <fstream>
using namespace std;
#include "graph.hpp"
#include "lqueue.cpp"
#include "lstack.cpp"
#include "double_linked_list.cpp"

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

template <typename T>
bool isSymmetric(Graph<T>& g) {
	VL<T> vl = g.vertices();
	for(VI<T> it = vl.begin(); it; ++it)
		for(VI<T> sit = g.successors(*it); sit; ++sit)
			// обхождаме реброто (*it, *sit)
			if (!g.isEdge(*sit, *it))
				return false;
	return true;
}

IntGraph graph1() {
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
	return g;
}

IntGraph graph2(int n) {
	IntGraph g;
	for(int i = 1; i <= n; i++) {
		g.addVertex(i);
		for(int j = 1; j <= n; j++)
			if (i != j)
				g.addEdge(i, j);
	}
	return g;
}

void DFS1rec(IntGraph& g, unsigned u, IntSet& visited) {
	// обхождаме u
	cout << u << ' ';
	visited.insert(u);
	for(VI<unsigned> sit = g.successors(u); sit; ++sit)
		if (!visited.contains(*sit))
			DFS1rec(g, *sit, visited);
	visited.remove(u);
}

void DFS1(IntGraph& g, unsigned u) {
	IntSet visited;
	DFS1rec(g, u, visited);
}

void DFS2rec(IntGraph& g, unsigned u, IntSet& visited) {
	// обхождаме u
	cout << u << ' ';
	visited.insert(u);
	for(VI<unsigned> sit = g.successors(u); sit; ++sit)
		if (!visited.contains(*sit))
			DFS2rec(g, *sit, visited);
}

void DFS2(IntGraph& g, unsigned u) {
	IntSet visited;
	DFS2rec(g, u, visited);
}

void BFS(IntGraph& g, unsigned u) {
	LinkedQueue<unsigned> q;
	IntSet visited;
	q.enqueue(u);
	visited.insert(u);
	while (!q.empty()) {
		unsigned v = q.dequeue();
		// обхождаме v
		cout << v << ' ';
		for(VI<unsigned> sit = g.successors(v); sit; ++sit)
			if (!visited.contains(*sit)) {
				q.enqueue(*sit);
				visited.insert(*sit);
			}
	}
}

bool findPathDFSrec(IntGraph& g, unsigned u, unsigned v,
					IntSet& visited, LinkedStack<unsigned>& path) {
	// обхождаме u
	path.push(u);
	visited.insert(u);

	if (u == v)
		return true;

	for(VI<unsigned> sit = g.successors(u); sit; ++sit)
		// *sit == w, търсим път от w до v
		if (!visited.contains(*sit) &&
			findPathDFSrec(g, *sit, v, visited, path))
			return true;
	// отказваме се от u
	path.pop();
	// visited.remove(u);
	return false;
}


LinkedStack<unsigned> findPathDFS(IntGraph& g, unsigned u, unsigned v) {
	IntSet visited;
	LinkedStack<unsigned> path;

	findPathDFSrec(g, u, v, visited, path);
	return path;
}

template<typename T>
using Edge = pair<T, T>;

template <typename T>
ostream& operator<<(ostream& os, Edge<T> const& e) {
	return os << '(' << e.first << ',' << e.second << ')';
}

VL<unsigned> findPathBFS(IntGraph& g, unsigned u, unsigned v) {
	using E = Edge<unsigned>;
	using EI = DoubleLinkedListIterator<E>;

	DoubleLinkedList<E> q;
	IntSet visited;
	VL<unsigned> path;

	q.insertEnd(E(u,u));
	visited.insert(u);

	EI it = q.begin();

	while (it) {
		E e = *it;
		unsigned w = e.second; // v е краят на реброто
		// обхождаме v
		if (w == v) {
			cout << q << endl;
			// връщаме се назад по ребрата, за да конструираме списъка
			EI rit = it;
			path.insertEnd(e.second);
			while (--rit) {
				if ((*rit).second == e.first) {
					// ребро от пътя!
					path.insertBegin(e.first);
					e = *rit;
				}
			}
			return path;
		}
		for(VI<unsigned> sit = g.successors(w); sit; ++sit)
			if (!visited.contains(*sit)) {
				q.insertEnd(E(w,*sit));
				visited.insert(*sit);
			}
		++it;
	}
	return path;
}

void printAllPathsDFSrec(IntGraph& g, unsigned u, unsigned v,
					     IntSet& visited, LinkedStack<unsigned>& path) {
	// обхождаме u
	path.push(u);
	visited.insert(u);

	if (u == v) {
		// разглеждаме намерения път
		cout << path;
	} else
		for(VI<unsigned> sit = g.successors(u); sit; ++sit)
			// *sit == w, търсим път от w до v
			if (!visited.contains(*sit))
				printAllPathsDFSrec(g, *sit, v, visited, path);

	// отказваме се от u
	path.pop();
	visited.remove(u);
}


void printAllPathsDFS(IntGraph& g, unsigned u, unsigned v) {
	IntSet visited;
	LinkedStack<unsigned> path;

	printAllPathsDFSrec(g, u, v, visited, path);
}

/*
void printAllPathsBFS(IntGraph& g, unsigned u, unsigned v) {
	using E = Edge<unsigned>;
	using EI = DoubleLinkedListIterator<E>;

	DoubleLinkedList<E> q;
	IntIntSet visited;
	VL<unsigned> path;

	q.insertEnd(E(u,u));
	visited.insert(E(u,u));

	EI it = q.begin();

	while (it) {
		E e = *it;
		unsigned w = e.second; // v е краят на реброто
		// обхождаме v
		if (w == v) {
			cout << q << endl;
			// връщаме се назад по ребрата, за да конструираме списъка
			EI rit = it;
			path.insertEnd(e.second);
			while (--rit) {
				if ((*rit).second == e.first) {
					// ребро от пътя!
					path.insertBegin(e.first);
					e = *rit;
				}
			}
			// разглеждаме пътя
			cout << path;
		}
		for(VI<unsigned> sit = g.successors(w); sit; ++sit)
			if (!visited.contains(E(w,*sit))) {
				q.insertEnd(E(w,*sit));
				visited.insert(E(w,*sit));
			}
		++it;
	}
}
*/

bool findCycleDFSrec(IntGraph& g, unsigned u,
					IntSet& visited, LinkedStack<unsigned>& path) {
	// обхождаме u
	path.push(u);

	if (visited.contains(u))
		return true;

	visited.insert(u);

	for(VI<unsigned> sit = g.successors(u); sit; ++sit)
		// *sit == w, търсим път от w до v
		if (findCycleDFSrec(g, *sit, visited, path))
			return true;
	// отказваме се от u
	path.pop();
	// visited.remove(u);
	return false;
}


LinkedStack<unsigned> findCycleDFS(IntGraph& g, unsigned u) {
	IntSet visited;
	LinkedStack<unsigned> path;

	findCycleDFSrec(g, u, visited, path);
	return path;
}

void spanningTreeDFSrec(IntGraph& g, unsigned u,
					    IntSet& visited, IntGraph& tree) {
	// обхождаме u
	visited.insert(u);

	for(VI<unsigned> sit = g.successors(u); sit; ++sit)
		// *sit == w, търсим път от w до v
		if (!visited.contains(*sit)) {
			tree.addVertex(*sit);
			tree.addEdge(*sit, u);
			spanningTreeDFSrec(g, *sit, visited, tree);
		}
}


IntGraph spanningTreeDFS(IntGraph& g, unsigned u) {
	IntSet visited;
	IntGraph tree;

	spanningTreeDFSrec(g, u, visited, tree);
	return tree;
}


void testGraph() {
	IntGraph g = graph1();

	cout << *g.successors(1) << endl;
	ofstream of("graph.dot");
	g.printDOT(of);

	cout << noSuccessors(g) << endl;
	cout << predecessors(g, (unsigned)3) << endl;
	g.removeEdge(5, 3);
	cout << noSuccessors(g) << endl;
	cout << predecessors(g, (unsigned)3) << endl;

	cout << isSymmetric(g) << endl;

	const int N = 15;
	IntGraph g2 = graph2(N);
	cout << isSymmetric(g2) << endl;

	DFS1(g, 1);
	cout << endl;

	DFS2(g, 1);
	cout << endl;

	BFS(g, 1);
	cout << endl;

	cout << findPathDFS(g, 1, 6) << endl;
	cout << findPathBFS(g, 1, 6) << endl;

	cout << findPathDFS(g2, 1, N) << endl;
	cout << findPathBFS(g2, 1, N) << endl;

	g2.addVertex(N+1);
	cout << findPathDFS(g2, 1, N+1) << endl;
	cout << findPathBFS(g2, 1, N+1) << endl;

	printAllPathsDFS(g, 1, 6);
	// printAllPathsBFS(g, 1, 6);

	cout << "Cycle:\n";
	cout << findCycleDFS(g, 1);

	ofstream tf("tree.dot");
	spanningTreeDFS(g, 1).printDOT(tf);


	cout << "END\n";
}

int main() {
	testGraph();
	return 0;
}


