#pragma once
#include <iostream>

template <class Type>
class vec2
{
public:
	Type magnitude;
	Type x, y;

public:
	vec2() :
		x(0), y(0), magnitude(-1)
	{}

	vec2(Type _x, Type _y)
		: x(_x), y(_y)
	{
		Magnitude();
	}

	vec2(const vec2& other)
	{
		x = other.x;
		y = other.y;
		magnitude = other.magnitude;
	}

	vec2 operator + (const vec2& other) const
	{
		return vec2(x + other.x, y + other.y);
	}

	vec2 operator - (const vec2& other) const
	{
		return vec2(x - other.x, y - other.y);
	}

	vec2 operator * (const float scalar) const
	{
		return vec2(x * scalar, y * scalar);
	}

	vec2 operator / (const float scalar) const
	{
		return this * (1 / scalar);
	}

	void operator += (const vec2& other)
	{
		x = x + other.x;
		y = y + other.y;
	}

	void operator -= (const vec2& other)
	{
		x = x - other.x;
		y = y - other.y;
	}

	void operator *= (const float scalar)
	{
		x = x * scalar;
		y = y * scalar;
	}

	void operator /= (const float scalar)
	{
		float invS = 1 / scalar;
		x = x * invS;
		y = y * invS;
	}

	bool operator == (const vec2& other)
	{
		return (x == other.x && y == other.y);
	}

	bool operator < (const vec2& other)
	{
		return (x < other.x && y < other.y);
	}

	bool operator > (const vec2& other)
	{
		return (x > other.x&& y > other.y);
	}

	bool operator <= (const vec2& other)
	{
		return (x <= other.x&& y <= other.y);
	}

	bool operator >= (const vec2& other)
	{
		return (x >= other.x && y >= other.y);
	}

	float Dot(const vec2& other)
	{
		return (x * other.x + y * other.y);
	}

	vec2 Normalized() const
	{
		if (magnitude == -1)
			Magnitude();

		if(magnitude == 0)
			return 0;

		return this / magnitude;
	}

	void Normalize()
	{
		if (magnitude == -1)
			Magnitude();

		if (magnitude == 0)
			return;

		this /= magnitude;
	}

	/*
	If the value is +ve
	e0 is right of the e1

	if the value is -ve
	e0 is left of e1

	if the value is 0
	the e0 and e1 are the same
	*/

	static float EdgeFunction(const vec2& e0, const vec2& e1)
	{
		return (e0.x * e1.y - e0.y * e1.x);
	}
	

	/*
		If the return value
		+ P is right of edge a,b
		- P is left of edge a, b
		0 P is on edge a, b
	*/

	static float EdgeFunction(const vec2& a, const vec2& b, const vec2& p)
	{
		vec2 e0 = p - a;
		vec2 e1 = b - a;

		return EdgeFunction(e0, e1);
	}

	friend std::ostream& operator <<(std::ostream& os, const vec2<Type>& v)
	{
		os << "(" << v.x << "," << v.y << ")" << std::endl;
		return os;
	}

	void Magnitude()
	{
		magnitude = (Type)sqrt(x * x + y * y);
	}

	static const vec2 ZERO;
};