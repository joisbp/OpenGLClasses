#pragma once
#include <iostream>

template <class Type>
class vec3
{
public:
	Type magnitude;
	Type x, y, z;

public:
	vec3() :
		x(0), y(0), z(0), magnitude(-1)
	{
		
	}

	vec3(Type _x, Type _y, Type _z)
		: x(_x), y(_y), z(_z)
	{
		Magnitude();
	}

	vec3(const vec3& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		magnitude = other.magnitude;
	}

	// Adding 2 vectors
	vec3 operator + (const vec3& other) const
	{
		return vec3(x + other.x, y + other.y, z + other.z);
	}

	//Subtracting 2 vectors
	vec3 operator - (const vec3& other) const
	{
		return vec3(x - other.x, y - other.y, z - other.z);
	}

	//Scalar multiplication of a vector
	vec3 operator * (const float scalar) const
	{
		return vec3(x * scalar, y * scalar, z * scalar);
	}

	//Scalar division
	vec3 operator / (const float scalar) const
	{
		float invScalar = 1 / scalar;
		return *this * invScalar;
	}

	void operator += (const vec3& other)
	{
		x = x + other.x;
		y = y + other.y;
		z = z + other.z;
	}

	void operator -= (const vec3& other)
	{
		x = x - other.x;
		y = y - other.y;
		z = z - other.z;
	}

	void operator *= (const float scalar)
	{
		x = x * scalar;
		y = y * scalar;
		z = z * scalar;
	}

	void operator /= (const float scalar)
	{
		float invS = 1 / scalar;
		x = x * invS;
		y = y * invS;
		z = z * invS;
	}

	// Equals
	bool operator ==(const vec3& other) const
	{
		return (x == other.x && y == other.y && z == other.z);
	}

	//Less than
	bool operator < (const vec3& other) const
	{
		return (x < other.x && y < other.y && z < other.z);
	}

	//Greater than
	bool operator >(const vec3 other) const
	{
		return (other < this);
	}

	bool operator <= (const vec3& other) const
	{
		return (x <= other.x && y <= other.y && z <= other.z);
	}

	//Greater than
	bool operator >=(const vec3 other) const
	{
		return (other <= this);
	}

	//Dot
	float Dot(const vec3& other)
	{
		return (x * other.x + y * other.y + z * other.z);
	}

	//Length
	void Magnitude()
	{
		magnitude = (Type)sqrt(x * x + y * y + z * z);
	}

	//return a new Normalized vector to unit length
	vec3 Normalized() const 
	{
		if (magnitude == -1)
			Magnitude();

		if (magnitude == 0)
			return ZERO;

		return this / magnitude;
	}

	// Normalize the vector to unit length
	void Normalize()
	{
		if (magnitude == -1)
			Magnitude();

		if (magnitude == 0)
			return;

		this /= magnitude;
	}

	// Accessor for x, y, z
	Type operator [] (const int index) const
	{
		if (index == 0)
			return x;
		if (index == 1)
			return y;
		if (index == 2)
			return z;
	}

	// construct a vector 2 from x and y components
	vec2<Type> GetXY() const
	{
		return vec2<Type>(x, y);
	}

	// to print out
	friend std::ostream& operator <<(std::ostream& os, const vec3<Type>& v)
	{
		os << "(" << v.x << "," << v.y << "," << v.z << ")" << std::endl;
		return os;
	};


	// Static Dot
	static float Dot(const vec3& v1, const vec3& v2)
	{
		return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
	}

	// Angle between 2 vectors
	static float Angle(const vec3& from, const vec3& target)
	{
		return acos(Dot(from, target) / (from.magnitude * target.magnitude));
	}

	//Static Cross product
	static vec3 Cross(const vec3& v1, const vec3& v2)
	{
		vec3 result;
		//	i	j	k
		//	v1x	v1y	v1z
		//	v2x	v2y	v2z	
		result.x = v1.y * v2.z - v1.z * v2.y;
		result.y = v1.x * v2.z - v2.x * v1.z;
		result.z = v1.x * v2.y - v1.y * v2.x;

		return result;
	}

	static float Distance(const vec3& v1, const vec3& v2)
	{
		vec3 v = v1 - v2;
		return v.magnitude;
	}

	static const vec3 ZERO;
};
