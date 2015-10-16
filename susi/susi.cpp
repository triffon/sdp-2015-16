/*
 * susi.cpp
 *
 *  Created on: 16.10.2015 г.
 *      Author: trifon
 */

#include "student.h"
#include <fstream>

const int MAX = 100;

Student* readStudents(int& n) {
	cout << "n = ";  cin >> n;
	Student* s = new Student[n];
	for(int i = 0; i < n; i++)
		cin >> s[i];
	return s;
}

void writeStudents(Student* s, int n) {
	ofstream fo("students.txt");
	fo << n << endl;
	for(int i = 0; i < n; i++)
		fo << s[i];
}

void toMainBook() {
	ifstream fi("students.txt");
	ofstream fo("main.bk", ios::out | ios::binary);
	int n;
	fi >> n;
	Student s;

	while (fi >> s)
		if (s.getGrade() >= 3)
			fo.write((char const*)&s, sizeof(Student));
}

void raiseGrade(int fn) {
	fstream fo("main.bk", ios::in | ios::out | ios::binary);
	Student s;
	while (fo.read((char*)&s, sizeof(Student))) {
		if (s.getFN() == fn) {
			s.setGrade(s.getGrade() + 1);
			fo.seekp(-sizeof(Student), ios::cur);
			fo.write((char const*)&s, sizeof(Student));
		}
	}
}

int main() {
	int n;
	//Student* s = readStudents(n);
	//writeStudents(s, n);
	toMainBook();
	raiseGrade(80005);
	return 0;
}
