/*
 * student.h
 *
 *  Created on: 16.10.2015 г.
 *      Author: trifon
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>
using namespace std;

const int MAX_NAME = 100;

class Student {
	char name[MAX_NAME];
	int fn;
	double grade;

public:
	Student(char const* = "<анонимен>", int = 0, double = 2);
	char const* getName() const { return name; }
	int getFN() const { return fn; }
	int getGrade() const { return grade; }
	void setGrade(double _grade) { grade = _grade; }

	friend istream& operator>>(istream&,Student&);
	friend ostream& operator<<(ostream&,Student const&);
};



#endif /* STUDENT_H_ */
