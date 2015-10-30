/*
 * horse.cpp
 *
 *  Created on: 30.10.2015 г.
 *      Author: trifon
 */

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <fstream>
using namespace std;

#include "lstack.cpp"

vector<vector<bool> > board;

void initBoard(int n) {
	board.clear();
	for(int i = 0; i < n; i++)
		board.push_back(vector<bool>(n));
}

void printBoard() {
	for(int i = 0; i < board.size(); i++) {
		for(int j = 0; j < board.size(); j++)
			cout << (board[i][j]?'X':'.');
		cout << endl;
	}
}

typedef pair<int, int> Point;

ostream& operator<<(ostream& os, Point const& p) {
	return os << '(' << p.first << ',' << p.second << ')';
}

bool inside_board(Point p) {
	return p.first >= 0 && p.first < board.size() &&
		   p.second >= 0 && p.second < board.size();
}

void printPath(LinkedStack<Point>& path, ostream& os = cout) {
	if (!path.empty()) {
		Point x = path.pop();
		printPath(path, os);
		os << x << endl;
	}
}

void printHistory(LinkedStack<LinkedStack<Point> >& history, ostream& os = cout) {
	if (!history.empty()) {
		Point x = history.pop().peek();
		printHistory(history);
		os << x << endl;
	}
}

bool horse_rec(Point start, Point end,
			LinkedStack<Point>& path) {
	if (start == end) {
		path.push(end);
		cout << "Успех!" << endl;
		printPath(path);
		return true;
	}
	if (board[start.first][start.second])
		return false;
	board[start.first][start.second] = true;
	path.push(start);
	// !!! cout << start << endl;
	for(int dx = -2; dx <= 2; dx++)
		if (dx != 0)
			for(int sign = -1; sign <= 1; sign += 2) {
				int dy = sign * (3 - abs(dx));
				Point newstart(start.first + dx,
						       start.second + dy);
				if (inside_board(newstart) &&
					horse_rec(newstart, end, path))
					return true;

			}
	path.pop();
	return false;
}

void horse_stack(Point start, Point end) {
	LinkedStack<LinkedStack<Point> > history;
	LinkedStack<Point> startStack;
	// ofstream clog("log.txt");
	startStack.push(start);
	history.push(startStack);
	while (!history.empty() &&
			(history.peek().empty() || history.peek().peek() != end)) {
		if (history.peek().empty()) {
			// Стъпка назад
			history.pop();
			if (!history.empty())
				history.peek().pop();
			clog << "Стъпка назад" << endl;
		}
		else {
			// стъпка напред
			Point current = history.peek().peek();
			clog << "Стъпка напред: " << current << endl;
			LinkedStack<Point> possibleMoves;
			board[current.first][current.second] = true;
			for(int dx = -2; dx <= 2; dx++)
				if (dx != 0)
					for(int sign = -1; sign <= 1; sign += 2) {
						int dy = sign * (3 - abs(dx));
						Point newstart(current.first + dx,
									   current.second + dy);
						if (inside_board(newstart)
							&&
							!board[newstart.first][newstart.second])
							possibleMoves.push(newstart);
					}
			LinkedStack<Point> pm(possibleMoves);
			clog << "---\n";
			printPath(pm,clog);
			clog << endl << "---\n";
			history.push(possibleMoves);
		}
	}
	if (!history.empty() && !history.peek().empty()) {
		cout << "Успех:\n";
		printHistory(history);
	}
}

int main() {
	initBoard(4);
	printBoard();
	LinkedStack<Point> path;
	// horse_rec(Point(0,0), Point(3,3), path);
	horse_stack(Point(0,0), Point(1,1));
	return 0;
}
