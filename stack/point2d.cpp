/*
 * point2d.cpp
 *
 *  Created on: 12.03.2015 г.
 *      Author: trifon
 */

#ifndef POINT2D_CPP_
#define POINT2D_CPP_

#include <iostream>
#include <cmath>
using namespace std;

template <typename T>
class Point2D {
	T x, y;

public:

	// конструктори
	Point2D(T = 0, T = 0);

	// селектори
	T getX() const { return x; }
	T getY() const { return y; }
	void print() const;
	double vectorLength() const;
	double distance(Point2D) const;
	// a.distance(b);
	// distance(a, b); - ако е външна функция

	// мутатори
	void setX(T _x) { x = _x; }
	void setY(T _y) { y = _y; }
	void translate(Point2D);
	// a.translate(b);
	// премести точката a с вектор, който е
	// определен от точката b
	void reflect();

	friend istream& operator>>(istream& is, Point2D& p) {
		return is >> p.x >> p.y;
	}
};

template <typename T>
Point2D<T>::Point2D(T _x, T _y) {
	x = _x;
	y = _y;
}

template <typename T>
void Point2D<T>::print() const {
	cout << '(' << x << ", " << y << endl;
}

template <typename T>
double Point2D<T>::vectorLength() const {
	return sqrt(x*x + y*y);
}

template <typename T>
double Point2D<T>::distance(Point2D<T> p) const {
	/*
	return sqrt((x-p.x)*(x-p.x) +
				(y-p.y)*(y-p.y));
	*/
	/*
	return sqrt((getX()-p.getX())*(getX()-p.getX()) +
				(getY()-p.getY())*(getY()-p.getY()));
	*/
	Point2D v = *this;
	v.reflect();
	p.translate(v);
	return p.vectorLength();
}

template <typename T>
void Point2D<T>::translate(Point2D<T> p) {
	/*
	x += p.x;
	y += p.y;
	*/
	setX(getX() + p.getX());
	setY(getY() + p.getY());
}

template <typename T>
void Point2D<T>::reflect() {
	/*
	x = -x;
	y = -y;
	*/
	setX(-getX());
	setY(-getY());
}


#endif
