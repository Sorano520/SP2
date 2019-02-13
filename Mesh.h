#ifndef MESH_H
#define MESH_H

#include <string>
#include "Vertex.h"
#include "Material.h"
#include <math.h>
/******************************************************************************/
/*!
		Class Mesh:
\brief	To store VBO (vertex & color buffer) and IBO (index buffer)
*/
/******************************************************************************/
class Mesh
{
public:
	enum DRAW_MODE
	{
		DRAW_TRIANGLES, //default mode
		DRAW_TRIANGLE_STRIP,
		DRAW_LINES,
		DRAW_MODE_LAST,
	};
	Mesh(const std::string &meshName);
	~Mesh();
	void Render();
	void Render(unsigned offset, unsigned count);
	void setValues(float XCoord[2], float YCoord[2], float ZCoord[2]);
	const std::string name;
	DRAW_MODE mode;
	Material material;
	unsigned vertexBuffer;
	unsigned colorBuffer;
	unsigned indexBuffer;
	unsigned indexSize;
	unsigned textureID;
	float XCoord[2];
	float YCoord[2];
	float ZCoord[2];
};

#endif