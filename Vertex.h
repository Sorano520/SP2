#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "Vector3.h"

//Represent positions and colors with structs.
struct Position
{
	float x, y, z;
	Position(float x = 0, float y = 0, float z = 0) { Set(x, y, z); }
	void Set(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
};

//Create a struct Vertex to store all information related to each vertex
struct Color
{
	float r, g, b;
	Color(float r = 1, float g = 1, float b = 1) { Set(r, g, b); }
	void Set(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }
};

struct TexCoord
{
	float u, v;
	TexCoord(float u = 0, float v = 0) { Set(u, v); }
	void Set(float u, float v) { this->u = u; this->v = v; }
};

//Previously our vertex buffer contains PPP and color buffer contains CCC.
//However it makes sense to combine color buffer into vertex buffer such that it
//contains PCPCPC.
struct Vertex
{
	Position pos;
	Color color;
	Vector3 normal;
	TexCoord texCoord;
};


#endif