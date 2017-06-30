#pragma once

#include <math.h>

struct Point
{
	float x;
	float y;
	float z;

	Point() : x(0.0f), y(0.0f), z(0.0f) {}

	Point(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	static float distance(const Point& p1, Point& p2)
	{
		return sqrtf(
			(p1.x - p2.x) * (p1.x - p2.x) +
			(p1.y - p2.y) * (p1.y - p2.y) +
			(p1.z - p2.z) * (p1.z - p2.z));
	}

	Point& operator+=(const Point& p)
	{
		x += p.x;
		y += p.y;
		z += p.z;
		return *this;
	}

	Point& operator-=(const Point& p)
	{
		x -= p.x;
		y -= p.y;
		z -= p.z;
		return *this;
	}
	
	Point& operator*=(const float f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	Point& operator/=(const float f)
	{
		x /= f;
		y /= f;
		z /= f;
		return *this;
	}

	Point& operator=(const Point& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
		return *this;
	}
};

Point operator+(Point p1, const Point& p2);
Point operator-(Point p1, const Point& p2);
Point operator*(Point p1, const float f);
Point operator/(Point p1, const float f);


