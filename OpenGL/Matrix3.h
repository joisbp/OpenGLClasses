#pragma once
#include <array>
#include "Vector.h"

template <class Type>
class Matrix3
{
private:
	std::array<Type, 9> elements;

public:
	Matrix3()
		: elements({ 0 })
	{}

	Matrix3(Type _00, Type _01, Type _02,
			Type _10, Type _11, Type _12,
			Type _20, Type _21, Type _22)
		: elements({_00, _01, _02, _10, _11, _12, _20, _21, _22})
	{}

	Matrix3(const vec3<Type>& r1, const vec3<Type>& r2, const vec3<Type>& r3)
		: elements({r1.x, r1.y, r1.z, r2.x, r2.y, r2.z, r3.x, r3.y, r3.z})
	{
	}

	Matrix3(const Matrix3& other)
	{
		elements = other.elements;
	}

	Type operator [] (const int index) const
	{
		return elements[index];
	}

	Type& operator [] (const int index)
	{
		return elements[index];
	}

	vec3<Type> GetRow(const int index) const
	{
		if (index >= 0 && index < 3)
		{
			return vec3<Type>(elements[(index * 3) + 0],
				elements[(index * 3) + 1],
				elements[(index * 3) + 2]);
		}

		return vec3<Type>();
	}

	vec3<Type> GetCol(const int index) const
	{
		if (index >= 0 && index < 3)
		{
			return vec3<Type>(elements[index],
				elements[index + 3],
				elements[index + 6]);
		}
		
		return vec3<Type>();
	}

	Matrix3 operator + (const Matrix3 & other)
	{
		Matrix3 result;
		for (int i = 0; i < 9; ++i)
		{
			result[i] = elements[i] + other[i];
		}

		return result;
	}

	Matrix3 operator - (const Matrix3& other)
	{
		Matrix3 result;
		for (int i = 0; i < 9; ++i)
		{
			result[i] = elements[i] - other[i];
		}
		return result;
	}

	Matrix3 operator * (const Type scalar)
	{
		Matrix3 result;
		for (int i = 0; i < 9; ++i)
		{
			result[i] = elements[i] * scalar;
		}

		return result;
	}

	Matrix3 operator / (const Type scalar)
	{
		Matrix3 result;
		Type invS = 1 / scalar;

		for (int i = 0; i < 9; ++i)
		{
			result[i] = elements[i] * invS;
		}

		return result;
	}

	Matrix3 operator * (const Matrix3& other)
	{
		Matrix3 result;

		vec3<Type> r0 = GetRow(0);
		vec3<Type> r1 = GetRow(1);
		vec3<Type> r2 = GetRow(2);

		vec3<Type> c0 = other.GetCol(0);
		vec3<Type> c1 = other.GetCol(1);
		vec3<Type> c2 = other.GetCol(2);

		result[0] = r0.Dot(c0);
		result[1] = r0.Dot(c1);
		result[2] = r0.Dot(c2);
		result[3] = r1.Dot(c0);
		result[4] = r1.Dot(c1);
		result[5] = r1.Dot(c2);
		result[6] = r2.Dot(c0);
		result[7] = r2.Dot(c1);
		result[8] = r2.Dot(c2);

		return result;
	}


	static void Multiply (const Matrix3& left, const Matrix3& right, Matrix3& result)
	{

		vec3<Type> r0 = left.GetRow(0);
		vec3<Type> r1 = left.GetRow(1);
		vec3<Type> r2 = left.GetRow(2);

		vec3<Type> c0 = right.GetCol(0);
		vec3<Type> c1 = right.GetCol(1);
		vec3<Type> c2 = right.GetCol(2);

		result[0] = r0.Dot(c0);
		result[1] = r0.Dot(c1);
		result[2] = r0.Dot(c2);
		result[3] = r1.Dot(c0);
		result[4] = r1.Dot(c1);
		result[5] = r1.Dot(c2);
		result[6] = r2.Dot(c0);
		result[7] = r2.Dot(c1);
		result[8] = r2.Dot(c2);

	}

	vec3<Type> operator * (const vec3<Type>& vector)
	{
		vec3<Type> result;

		vec3<Type> col0 = this->GetCol(0);
		vec3<Type> col1 = this->GetCol(1);
		vec3<Type> col2 = this->GetCol(2);

		result.x = vector.Dot(col0);
		result.y = vector.Dot(col1);
		result.z = vector.Dot(col2);

		return result;
	}

	static void Multiply (const Matrix3& matrix, const vec3<Type>& vector, vec3<Type>& result)
	{
		vec3<Type> col0 = matrix.GetCol(0);
		vec3<Type> col1 = matrix.GetCol(1);
		vec3<Type> col2 = matrix.GetCol(2);

		result.x = vector.Dot(col0);
		result.y = vector.Dot(col1);
		result.z = vector.Dot(col2);
	}

	Matrix3 Inverse()
	{
		Type determinant = Determinant();
		if (determinant == 0.0f)
		{
			return ZERO;
		}
		Type invDeterminant = 1 / determinant;
		Matrix3 adjoint = Adjoint();

		Matrix3 inverse = adjoint * invDeterminant;
		return inverse;
	}

	/*
	|	0	1	2	|
	|	3	4	5	|
	|	6	7	8	|
	
	*/

	Type Determinant()
	{
		Type determinant =
			elements[0] * (elements[4] * elements[8] - elements[5] * elements[7])
			- elements[1] * (elements[3] * elements[8] - elements[6] * elements[5])
			+ elements[2] * (elements[3] * elements[7] - elements[6] * elements[4]);

		return determinant;
	}

	/*
		|	0	1	2	|
		|	3	4	5	|
		|	6	7	8	|

		|	+	-	+	|
		|	-	+	-	|
		|	=	-	+	|


	*/

	Matrix3 Adjoint()
	{
		Matrix3 adjoint;

		adjoint[0] = +(elements[4] * elements[8] - elements[5] * elements[7]);
		adjoint[1] = -(elements[3] * elements[8] - elements[5] * elements[6]);
		adjoint[2] = +(elements[3] * elements[7] - elements[6] * elements[4]);
		adjoint[3] = -(elements[1] * elements[8] - elements[2] * elements[7]);
		adjoint[4] = +(elements[0] * elements[8] - elements[6] * elements[2]);
		adjoint[5] = -(elements[0] * elements[7] - elements[1] * elements[6]);
		adjoint[6] = +(elements[1] * elements[5] - elements[4] * elements[2]);
		adjoint[7] = -(elements[0] * elements[5] - elements[3] * elements[2]);
		adjoint[8] = +(elements[4] * elements[0] - elements[1] * elements[3]);

		return adjoint.Transpose();
	}

	Matrix3 Transpose()
	{
		Matrix3 transpose;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				transpose[j * 3 + i] = elements[i * 3 + j];
			}
		}

		return transpose;
	}

	static const Matrix3 IDENTITY;
	static const Matrix3 ZERO;
};