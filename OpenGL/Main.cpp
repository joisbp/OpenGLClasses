#include <iostream>
#include "Vector.h"
#include "Matrix.h"

using namespace std;
int main()
{
	vec3f fv;
	vec3i iv;

	vec2f f2v0(2, 3);
	vec2f f2v1(3, 3);

	f2v0 += f2v1;

	std::cout << fv;

	mat3f mat(1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 4.0f, 5.0f, 6.0f, 0.0f);
	mat3f inv = mat.Inverse();

	mat3f mul = mat * inv;

	mat4f mat4(1, 1, 1, -1, 1, 1, -1, 1, 1, -1, 1, 1, -1, 1, 1, 1);
	mat4f inv4 = mat4.Inverse();

	mat4f mul4 = mat4 * inv4;

	int a;
	std::cin >> a;
	return 0;
}