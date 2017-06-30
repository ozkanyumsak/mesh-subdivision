#pragma once

#include "Point.h"

Point operator+(Point p1, const Point& p2) { return p1 += p2; }
Point operator-(Point p1, const Point& p2) { return p1 += p2; }
Point operator*(Point p1, const float f) { return p1 *= f; }
Point operator/(Point p1, const float f) { return p1 /= f; }
