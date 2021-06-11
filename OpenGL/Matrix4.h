#pragma once
#include <array>
#include "Vector.h"

template <class Type>
class Matrix4
{
private:
	std::array<Type, 16> elements;

public:

	Matrix4()
		: elements({ 0 })
	{}

	Matrix4(Type _00, Type _01, Type _02, Type _03,
		Type _10, Type _11, Type _12, Type _13,
		Type _20, Type _21, Type _22, Type _23,
		Type _30, Type _31, Type _32, Type _33)
		: elements({ _00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33 })
	{}

	Matrix4(vec4<Type> r0, vec4<Type> r1, vec4<Type> r2, vec4<Type> r3)
		: elements({ r0.x, r0.y, r0.z, r0.w, r1.x, r1.y, r1.z, r1.w, r2.x, r2.y, r2.z, r2.w, r3.x, r3.y, r3.z, r3.w })
	{}

	Matrix4(const Matrix4& other)
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

	/*

	r0	|	0	1	2	3	|
	r1	|	4	5	6	7	|
	r2	|	8	9	10	11	|
	r3	|	12	13	14	15	|

	*/

	vec4<Type> GetRow(const int index) const
	{
		if (index >= 0 && index < 4)
		{
			return vec4<Type>(elements[(index * 4) + 0],
				elements[(index * 4) + 1],
				elements[(index * 4) + 2],
				elements[(index * 4) + 3]);
		}

		return vec4<Type>();
	}

	/*
				c0	c1	c2	c3
		r0	|	0	1	2	3	|
		r1	|	4	5	6	7	|
		r2	|	8	9	10	11	|
		r3	|	12	13	14	15	|

	*/
	vec4<Type> GetCol(const int index) const
	{
		if (index >= 0 && index < 4)
		{
			return vec4<Type>(elements[index],
				elements[index + 4],
				elements[index + 8],
				elements[index + 12]);
		}

		return vec4<Type>();
	}

	Matrix4 operator + (const Matrix4& other)
	{
		Matrix4 result;
		for (int i = 0; i < 16; ++i)
		{
			result[i] = elements[i] + other[i];
		}

		return result;
	}

	Matrix4 operator - (const Matrix4& other)
	{
		Matrix4 result;
		for (int i = 0; i < 16; ++i)
		{
			result[i] = elements[i] - other[i];
		}
		return result;
	}

	Matrix4 operator * (const Type scalar)
	{
		Matrix4 result;
		for (int i = 0; i < 16; ++i)
		{
			result[i] = elements[i] * scalar;
		}

		return result;
	}

	Matrix4 operator / (const Type scalar)
	{
		Matrix4 result;
		Type invS = 1 / scalar;

		for (int i = 0; i < 16; ++i)
		{
			result[i] = elements[i] * invS;
		}

		return result;
	}

	Matrix4 operator * (const Matrix4& other)
	{
		Matrix4 result;

		vec4<Type> r0 = GetRow(0);
		vec4<Type> r1 = GetRow(1);
		vec4<Type> r2 = GetRow(2);
		vec4<Type> r3 = GetRow(3);

		vec4<Type> c0 = other.GetCol(0);
		vec4<Type> c1 = other.GetCol(1);
		vec4<Type> c2 = other.GetCol(2);
		vec4<Type> c3 = other.GetCol(3);

		result[0] = r0.Dot(c0);
		result[1] = r0.Dot(c1);
		result[2] = r0.Dot(c2);
		result[3] = r0.Dot(c3);

		result[4] = r1.Dot(c0);
		result[5] = r1.Dot(c1);
		result[6] = r1.Dot(c2);
		result[7] = r1.Dot(c3);
		
		result[8] = r2.Dot(c0);
		result[9] = r2.Dot(c1);
		result[10] = r2.Dot(c2);
		result[11] = r2.Dot(c3);
		
		result[12] = r3.Dot(c0);
		result[13] = r3.Dot(c1);
		result[14] = r3.Dot(c2);
		result[15] = r3.Dot(c3);

		return result;
	}

	vec4<Type> operator * (const vec4<Type>& vector) const 
	{
		vec4<Type> result;
		   
		vec4<Type> col0 = this->GetCol(0);
		vec4<Type> col1 = this->GetCol(1);
		vec4<Type> col2 = this->GetCol(2);
		vec4<Type> col3 = this->GetCol(3);

		result.x = vector.Dot(col0);
		result.y = vector.Dot(col1);
		result.z = vector.Dot(col2);
		result.w = vector.Dot(col3);

		return result;
	}

	Matrix4 Transpose()
	{
		Matrix4 transpose;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				transpose[j * 4 + i] = elements[i * 4 + j];
			}
		}

		return transpose;
	}

	Matrix4 Inverse()
	{
		Type determinant = Determinant();

		if (determinant == 0)
			return ZERO;

		Type invDeterminant = 1 / determinant;

		Matrix4 adjoint = Adjoint();

		return adjoint * invDeterminant;
	}

	/*
				c0	c1	c2	c3
		r0	|	0	1	2	3	|	|	a11	a12	a13	a14	|
		r1	|	4	5	6	7	|	|	a21	a22	a23	a24	|
		r2	|	8	9	10	11	|	|	a31	a32	a33	a34	|
		r3	|	12	13	14	15	|	|	a41	a42	a43	a44	|

		https://semath.info/src/inverse-cofactor-ex4.html

		

	*/

	Type Determinant()
	{
		Type determinant =
			elements[0] * elements[5] * elements[10] * elements[11]
			+ elements[0] * elements[6] * elements[11] * elements[13]
			+ elements[0] * elements[7] * elements[9] * elements[14]
			- elements[0] * elements[7] * elements[10] * elements[13]
			- elements[0] * elements[6] * elements[9] * elements[15]
			- elements[0] * elements[5] * elements[11] * elements[14]
			- elements[1] * elements[4] * elements[10] * elements[15]
			- elements[2] * elements[4] * elements[11] * elements[13]
			- elements[3] * elements[4] * elements[9] * elements[14]
			+ elements[3] * elements[4] * elements[10] * elements[13]
			+ elements[2] * elements[4] * elements[9] * elements[15]
			+ elements[1] * elements[4] * elements[11] * elements[14]
			+ elements[1] * elements[6] * elements[8] * elements[15]
			+ elements[2] * elements[7] * elements[8] * elements[13]
			+ elements[3] * elements[5] * elements[8] * elements[14]
			- elements[3] * elements[6] * elements[8] * elements[13]
			- elements[2] * elements[5] * elements[8] * elements[15]
			- elements[1] * elements[7] * elements[8] * elements[14]
			- elements[1] * elements[6] * elements[11] * elements[12]
			- elements[2] * elements[7] * elements[9] * elements[12]
			- elements[3] * elements[5] * elements[10] * elements[12]
			+ elements[3] * elements[6] * elements[9] * elements[12]
			+ elements[2] * elements[5] * elements[11] * elements[12]
			+ elements[1] * elements[7] * elements[10] * elements[12];


		return determinant;
	}

	/*
				c0	c1	c2	c3
		r0	|	0	1	2	3	|	|	a11	a12	a13	a14	|
		r1	|	4	5	6	7	|	|	a21	a22	a23	a24	|
		r2	|	8	9	10	11	|	|	a31	a32	a33	a34	|
		r3	|	12	13	14	15	|	|	a41	a42	a43	a44	|

		https://semath.info/src/inverse-cofactor-ex4.html



	*/

	Matrix4 Adjoint()
	{
		Matrix4 adjoint;
		adjoint[0] = +(elements[5] * elements[10] * elements[15]
					+ elements[6] * elements[11] * elements[13]
					+ elements[7] * elements[9] * elements[14]
					- elements[7] * elements[10] * elements[13]
					- elements[6] * elements[9] * elements[15]
					- elements[5] * elements[11] * elements[14]);

		adjoint[1] = -(elements[4] * elements[10] * elements[15]
					+ elements[6] * elements[11] * elements[12]
					+ elements[7] * elements[8] * elements[14]
					- elements[7] * elements[10] * elements[12]
					- elements[6] * elements[8] * elements[15]
					- elements[4] * elements[11] * elements[14]);

		adjoint[2] = +(elements[4] * elements[9] * elements[15]
					+ elements[5] * elements[11] * elements[12]
					+ elements[7] * elements[8] * elements[13]
					- elements[7] * elements[9] * elements[12]
					- elements[5] * elements[8] * elements[15]
					- elements[4] * elements[11] * elements[13]);

		adjoint[3] = -(elements[4] * elements[9] * elements[14]
					+ elements[5] * elements[10] * elements[12]
					+ elements[6] * elements[8] * elements[13]
					- elements[6] * elements[9] * elements[12]
					- elements[5] * elements[8] * elements[14]
					- elements[4] * elements[10] * elements[13]);

		adjoint[4] = -(elements[1] * elements[10] * elements[15]
					+ elements[2] * elements[11] * elements[13]
					+ elements[3] * elements[9] * elements[14]
					- elements[3] * elements[10] * elements[13]
					- elements[2] * elements[9] * elements[15]
					- elements[1] * elements[11] * elements[14]);

		adjoint[5] = +(elements[0] * elements[10] * elements[15]
					+ elements[2] * elements[11] * elements[12]
					+ elements[3] * elements[8] * elements[14]
					- elements[3] * elements[10] * elements[12]
					- elements[2] * elements[8] * elements[15]
					- elements[0] * elements[11] * elements[14]);

		adjoint[6] = -(elements[0] * elements[9] * elements[15]
					+ elements[1] * elements[11] * elements[12]
					+ elements[3] * elements[8] * elements[13]
					- elements[3] * elements[9] * elements[12]
					- elements[1] * elements[8] * elements[15]
					- elements[0] * elements[11] * elements[13]);

		adjoint[7] = +(elements[0] * elements[9] * elements[14]
					+ elements[1] * elements[10] * elements[12]
					+ elements[2] * elements[8] * elements[13]
					- elements[2] * elements[9] * elements[12]
					- elements[1] * elements[8] * elements[14]
					- elements[0] * elements[10] * elements[13]);


		/*
					c0	c1	c2	c3
			r0	|	0	1	2	3	|	|	a11	a12	a13	a14	|
			r1	|	4	5	6	7	|	|	a21	a22	a23	a24	|
			r2	|	8	9	10	11	|	|	a31	a32	a33	a34	|
			r3	|	12	13	14	15	|	|	a41	a42	a43	a44	|

			https://semath.info/src/inverse-cofactor-ex4.html



		*/

		adjoint[8] = +(elements[1] * elements[6] * elements[15]
					+ elements[2] * elements[7] * elements[13]
					+ elements[3] * elements[5] * elements[14]
					- elements[3] * elements[6] * elements[13]
					- elements[2] * elements[5] * elements[15]
					- elements[1] * elements[7] * elements[14]);

		adjoint[9] = -(elements[0] * elements[6] * elements[15]
					+ elements[2] * elements[7] * elements[12]
					+ elements[3] * elements[4] * elements[14]
					- elements[3] * elements[6] * elements[12]
					- elements[2] * elements[4] * elements[15]
					- elements[0] * elements[7] * elements[14]);

		adjoint[10] = +(elements[0] * elements[5] * elements[15]
					+ elements[1] * elements[7] * elements[12]
					+ elements[3] * elements[4] * elements[13]
					- elements[3] * elements[5] * elements[12]
					- elements[1] * elements[4] * elements[15]
					- elements[0] * elements[7] * elements[13]);

		adjoint[11] = -(elements[0] * elements[5] * elements[14]
					+ elements[1] * elements[6] * elements[12]
					+ elements[2] * elements[4] * elements[13]
					- elements[2] * elements[5] * elements[12]
					- elements[1] * elements[4] * elements[14]
					- elements[0] * elements[6] * elements[13]);

		adjoint[12] = -(elements[1] * elements[6] * elements[11]
					+ elements[2] * elements[7] * elements[9]
					+ elements[3] * elements[5] * elements[10]
					- elements[3] * elements[6] * elements[9]
					- elements[2] * elements[5] * elements[11]
					- elements[1] * elements[7] * elements[10]);

		adjoint[13] = +(elements[0] * elements[6] * elements[11]
					+ elements[2] * elements[7] * elements[8]
					+ elements[3] * elements[4] * elements[10]
					- elements[3] * elements[6] * elements[8]
					- elements[2] * elements[4] * elements[11]
					- elements[0] * elements[7] * elements[10]);

		adjoint[14] = -(elements[0] * elements[5] * elements[11]
					+ elements[1] * elements[7] * elements[8]
					+ elements[3] * elements[4] * elements[9]
					- elements[3] * elements[5] * elements[8]
					- elements[1] * elements[4] * elements[11]
					- elements[0] * elements[7] * elements[9]);

		adjoint[15] = +(elements[0] * elements[5] * elements[10]
					+ elements[1] * elements[6] * elements[8]
					+ elements[2] * elements[4] * elements[9]
					- elements[2] * elements[5] * elements[8]
					- elements[1] * elements[4] * elements[10]
					- elements[0] * elements[6] * elements[9]);


		return adjoint.Transpose();
	}

	static const Matrix4 ZERO;
	static const Matrix4 IDENTITY;
};

