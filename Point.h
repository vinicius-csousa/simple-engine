#pragma once

#include <string>
#include <iostream>

class Point {

public:
	float X, Y;
	Point(float x = 0, float y = 0) : X(x), Y(y) {}

	// Overriding + operator
	inline Point operator+(const Point& p2) const {
		return Point(X + p2.X, Y + p2.Y);
	}

	// Overriding - operator
	inline Point operator-(const Point& p2) const {
		return Point(X - p2.X, Y - p2.Y);
	}

	// Overriding * (scalar multiplication) operator
	inline Point operator*(const float scalar) const {
		return Point(X * scalar, Y * scalar);
	}

	inline friend Point operator+=(Point& p1, const Point& p2) {
		p1.X += p2.X;
		p1.Y += p2.Y;
		return p1;
	}

	inline friend Point operator-=(Point& p1, const Point& p2) {
		p1.X -= p2.X;
		p1.Y -= p2.Y;
		return p1;
	}

	inline void Log(std::string msg = "") {
		std::cout << "(X, Y) = (" << X << ", " << Y << " )" << std::endl;
	}
};