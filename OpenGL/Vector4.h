#pragma once

template<class Type>
class vec4
{
public:
	Type x, y, z, w;
	Type magnitude;

public:

	vec4() :
		x(0), y(0), z(0), w(0), magnitude(-1)
	{}

	vec4(Type _x, Type _y, Type _z, Type _w)
		: x(_x), y(_y), z(_z), w(_w)
	{
		Magnitude();
	}

	vec4(const vec4& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;

		magnitude = other.magnitude;
	}

	// Adding 2 vectors
	vec4 operator + (const vec4& other)
	{
		return vec4(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	//Subtracting 2 vectors
	vec4 operator - (const vec4& other)
	{
		return vec4(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	//Scalar multiplication of a vector
	vec4 operator *(const float scalar)
	{
		return vec4(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	//Scalar division
	vec4 operator /(const float scalar)
	{
		return this * 1 / scalar;
	}

	void operator += (const vec4& other)
	{
		x = x + other.x;
		y = y + other.y;
		z = z + other.z;
		w = w + other.w;
	}

	void operator -= (const vec4& other)
	{
		x = x - other.x;
		y = y - other.y;
		z = z - other.z;
		w = w - other.w;
	}

	void operator *= (const float scalar)
	{
		x = x * scalar;
		y = y * scalar;
		z = z * scalar;
		w = w * scalar;

	}

	void operator /= (const float scalar)
	{
		float invS = 1 / scalar;
		x = x * invS;
		y = y * invS;
		z = z * invS;
		w = w * invS;
	}

	// Equals
	bool operator ==(const vec4& other)
	{
		return (x == other.x && y == other.y && z == other.z && w == other.w);
	}

	//Less than
	bool operator < (const vec4& other)
	{
		return (x < other.x&& y < other.y&& z < other.z&& w < other.w);
	}

	//Greater than
	bool operator >(const vec4& other)
	{
		return (other < this);
	}

	bool operator <= (const vec4& other)
	{
		return (x <= other.x && y <= other.y && z <= other.z && w <= other.w);
	}

	//Greater than
	bool operator >=(const vec4& other)
	{
		return (other <= this);
	}

	vec3<Type> GetVec3()
	{
		return vec3<Type>(x, y, z);
	}

	void Magnitude()
	{
		magnitude = (Type)sqrt(x * x + y * y + z * z + w* w);
	}

	float Dot(const vec4& other)
	{
		return (x * other.x + y * other.y + z * other.z + w * other.w);
	}

	//return a new Normalized vector to unit length
	vec4 Normalized() const
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

	static const vec4 ZERO;
};