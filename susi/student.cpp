/*
 * student.cpp
 *
 *  Created on: 16.10.2015 г.
 *      Author: trifon
 */

#include <cstring>
#include <iomanip>
#include "student.h"

Student::Student(char const* _name, int _fn, double _grade)
 : fn(_fn), grade(_grade) {
	strncpy(name, _name, MAX_NAME);
	name[MAX_NAME] = '\0';
}

istream& operator>>(istream& is, Student& s) {
	return (is >> s.fn >> s.grade).getline(s.name, MAX_NAME);
}

ostream& operator<<(ostream& os, Student const& s) {
	return os << setw(8) << s.fn
			  << fixed << setprecision(2) << setw(8) << s.grade
			  << ' ' << s.name << endl;

}
