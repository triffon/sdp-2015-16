/*
 * main.cpp
 *
 *  Created on: 27.11.2015 г.
 *      Author: trifon
 */


#include "tree.cpp"
#include "bintree.cpp"

using TestTree = Tree<int>;
using TestBinaryTree = BinaryTree<int>;

template <typename I>
int length(I it) {
	int result = 0;
	while (it++)
		result++;
	return result;
}

template <typename T>
int breadth(Tree<T> const& t) {
	int result = length(t.subtrees());
	for(typename Tree<T>::I it = t.subtrees();it;++it) {
		int l = breadth(*it);
		if (l > result)
			result = l;
	}
	return result;
}

void testTree() {
	TestTree t1(1);
	t1.addChild(TestTree(2)
				.addChild(TestTree(3))
				.addChild(TestTree(4)
						  .addChild(TestTree(5))
						  .addChild(TestTree(6)))
			    .addChild(TestTree(7))
			    .addChild(TestTree(8)))
	  .addChild(TestTree(9))
	  .addChild(TestTree(10));
	cout << t1 << endl;
	cout << breadth(t1) << endl;
}

void testBinaryTree() {
	TestBinaryTree e;
	TestBinaryTree t(1,
                         TestBinaryTree(2, e, e),
                         TestBinaryTree(3,
                                        TestBinaryTree(4, e, e),
                                        TestBinaryTree(5, e, e)));
	cout << t;
}

int main() {
	// testTree();
	testBinaryTree();
	return 0;
}

