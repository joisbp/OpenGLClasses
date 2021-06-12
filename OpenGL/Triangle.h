#pragma once
#include <array>
#include "Vector.h"

class Triangle
{	
public:
	std::array<vec4f, 3> vertices;
	std::array<vec3f, 3> colors;

public:
	Triangle()
	{}

	Triangle(vec4f v0, vec4f v1, vec4f v2)
	{
		vertices = { v0, v1, v2 };
		colors = { vec3f(1,0,0), vec3f(0,1,0), vec3f(0,0,1) };
	}

	Triangle(vec4f v0, vec4f v1, vec4f v2, vec3f c0, vec3f c1, vec3f c2)
	{
		vertices = { v0, v1, v2 };
		colors = { c0, c1, c2 };
	}
};

