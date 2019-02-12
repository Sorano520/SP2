#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"
#include "LoadOBJ.h"
/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, Color color, float lengthX, float lengthY);
	static Mesh* GenerateCube(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateFeet(const std::string &meshName, Color color, float TallerHeight, float ShorterHeight);
	static Mesh* GenerateCircle(const std::string &meshName, Color color, float Radius, unsigned NumSlice);
	static Mesh* GenerateRing(const std::string &meshName, Color color, float RadiusBig, float RadiusSmall, unsigned NumSlice);
	static Mesh* GenerateCylinder(const std::string &meshName, Color color, float RadiusTop, float RadiusBottom, unsigned NumSlice, float height);
	static Mesh* GenerateMask(const std::string &meshName, Color color, float Radius, unsigned NumSlice, float height);
	static Mesh* GenerateHemisphere(const std::string &meshName, Color color, float Radius, unsigned NumSlice, unsigned NumStack);
	static Mesh* GenerateSphere(const std::string &meshName, Color color, float Radius, unsigned NumSlice, unsigned NumStack);
	static Mesh* GenerateOBJ(const std::string &meshName, const std::string &file_path);
	static Mesh* GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol);
};

#endif