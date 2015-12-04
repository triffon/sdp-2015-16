/*
 * arithmetic.cpp
 *
 *  Created on: 23.10.2015 г.
 *      Author: trifon
 */

#include <iostream>
using namespace std;

#include "lstack.cpp"
#include "bintree.cpp"

const int MAX = 100;

double valueof(char c) {
	return c - '0';
}

void apply(char op, LinkedStack<double>& stack) {
	double rarg = stack.pop();
	double larg = stack.pop();
	switch (op) {
	case '+': stack.push(larg + rarg);break;
	case '-': stack.push(larg - rarg);break;
	case '*': stack.push(larg * rarg);break;
	case '/': stack.push(larg / rarg);break;
	default : stack.push(0);
	}
}

double calculate_rpn(char const* rpn) {
	char const* p = rpn;
	LinkedStack<double> results;

	while (*p != '\0') {
		if (isdigit(*p))
			results.push(valueof(*p));
		else
			apply(*p, results);
		p++;
	}
	return results.pop();
}

bool isop(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}

int priority(char op) {
	switch (op) {
	case '+':
	case '-':return 1;
	case '*':
	case '/':return 2;
	default: return 0;
	}
}

char* to_rpn(char const* expr, char* rpn) {
	char const* p = expr;
	char* q = rpn;
	LinkedStack<char> ops;

	while (*p != '\0') {
		if (*p == '(')
			ops.push(*p);
		else if (isop(*p)) {
			while (!ops.empty() &&
				   priority(ops.peek()) >= priority(*p))
				*q++ = ops.pop();
			ops.push(*p);
		}
		else if (isdigit(*p))
				*q++ = *p;
		else if (*p == ')') {
				while(ops.peek() != '(')
					*q++ = ops.pop();
				// махаме и (
				ops.pop();
		}
		p++;
	}
	// изпразваме стека
	while (!ops.empty())
		*q++ = ops.pop();
	return rpn;
}

double calculate_expr(char const* expr) {
	char const* p = expr;
	LinkedStack<char> ops;
	LinkedStack<double> results;

	while (*p != '\0') {
		if (*p == '(')
			ops.push(*p);
		else if (isop(*p)) {
			while (!ops.empty() &&
				   priority(ops.peek()) >= priority(*p))
				apply(ops.pop(), results);
			ops.push(*p);
		}
		else if (isdigit(*p))
				results.push(valueof(*p));
		else if (*p == ')') {
				while(ops.peek() != '(')
					apply(ops.pop(), results);
				// махаме и (
				ops.pop();
		}
		p++;
	}
	// изпразваме стека
	while (!ops.empty())
		apply(ops.pop(), results);
	return results.pop();
}

using ExprTree = BinaryTree<char>;

void applyTree(char op, LinkedStack<ExprTree>& stack) {
	ExprTree rarg = stack.pop();
	ExprTree larg = stack.pop();
	stack.push(ExprTree(op, ExprTree(larg), ExprTree(rarg)));
}

ExprTree build_expr_tree(char const* expr) {
	char const* p = expr;
	LinkedStack<char> ops;
	LinkedStack<ExprTree> results;

	while (*p != '\0') {
		if (*p == '(')
			ops.push(*p);
		else if (isop(*p)) {
			while (!ops.empty() &&
				   priority(ops.peek()) >= priority(*p))
				applyTree(ops.pop(), results);
			ops.push(*p);
		}
		else if (isdigit(*p))
				results.push(ExprTree(*p));
		else if (*p == ')') {
				while(ops.peek() != '(')
					applyTree(ops.pop(), results);
				// махаме и (
				ops.pop();
		}
		p++;
	}
	// изпразваме стека
	while (!ops.empty())
		applyTree(ops.pop(), results);
	return results.pop();
}

double calc_expr_tree(BinaryTreePosition<char> pos) {
	if (!pos)
		return 0;
	if (isdigit(*pos))
		return valueof(*pos);
	double l = calc_expr_tree(-pos);
	double r = calc_expr_tree(+pos);
	switch (*pos) {
	case '+': return l + r;
	case '-': return l - r;
	case '*': return l * r;
	case '/': return l / r;
	}
}

int main() {
	char expr[MAX] = "";
	char rpn[MAX] = "";
	cin.getline(expr, MAX);
	to_rpn(expr, rpn);
	cout << rpn << endl;
	cout << calculate_rpn(rpn) << endl;
	cout << calculate_expr(expr) << endl;
	ExprTree et = build_expr_tree(expr);
	printDOT(ExprTree(et), "tree.dot");
	cout << calc_expr_tree(et.root()) << endl;
}
