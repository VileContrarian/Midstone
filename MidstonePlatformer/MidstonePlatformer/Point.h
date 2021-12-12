#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
public:
	float x, y;

private:
	Point(float x=0, float y=0) : x(x), y(y) {}

	// addition +
	inline Point operator+(const Point& p2) const {
		return Point(x + p2.x, y + p2.y);
	}

	// addition +=
	inline friend Point operator+=(Point & p1, const Point & p2) {
		p1.x += p2.x;
		p1.y += p2.y;
		return p1;
	}

	// subtraction -
	inline Point operator-(const Point& p2) const {
		return Point(x - p2.x, y - p2.y);
	}

	// subtraction -=
	inline friend Point operator-=(Point& p1, const Point& p2) {
		p1.x -= p2.x;
		p1.y -= p2.y;
		return p1;
	}

	// multiplication *
	inline Point operator*(const float scalar) const {
		return Point(x * scalar, y * scalar);
	}

	void Log(std::string msg = "") {
		std::cout << msg << "(x y) = (" << x << " " << y << ")" << std::endl;
	}
};

#endif // POINT_H
