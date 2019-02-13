#include "MeshBuilder.h"
#include <GL\glew.h>


/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	v.pos.Set(-1000, 0, 0);
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(1000, 0, 0); 
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, -1000, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, 1000, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, 0, -1000);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, 0, 1000);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	
	index_buffer_data.push_back(0); 
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3); 
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, float lengthX, float lengthY)
{
	Vertex v;

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	v.pos.Set(0.5, 0, 0.5);
	v.color = color;
	v.normal.Set(0.0, 1, 0.0);
	//v.texCoord.Set(0, 0);
	v.texCoord.Set(1, 0);
	//v.texCoord.Set(1, 1);
	//v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5, 0, -0.5);
	v.color = color;
	v.normal.Set(0.0, 1, 0.0);
	//v.texCoord.Set(0, 0);
	//v.texCoord.Set(1, 0);
	v.texCoord.Set(1, 1);
	//v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5, 0, -0.5);
	v.color = color;
	v.normal.Set(0.0, 1, 0.0);
	//v.texCoord.Set(0, 0);
	//v.texCoord.Set(1, 0);
	//v.texCoord.Set(1, 1);
	v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5, 0, 0.5);
	v.color = color;
	v.normal.Set(0.0, 1, 0.0);
	v.texCoord.Set(0, 0);
	//v.texCoord.Set(1, 0);
	//v.texCoord.Set(1, 1);
	//v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0);

	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ); // Index 0
	v.color = color;
	v.normal.Set(0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ); // Index 0
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ); // Index 1
	v.color = color;
	v.normal.Set(-0.5f * lengthX, 0.5f * lengthY, 0.5f * lengthZ); // Index 1
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ); // Index 2
	v.color = color;
	v.normal.Set(-0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ); // Index 2
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ); // Index 3
	v.color = color;
	v.normal.Set(0.5f * lengthX, -0.5f * lengthY, 0.5f * lengthZ); // Index 3
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * lengthX, 0.5f * lengthY, -0.5f * lengthZ); // Index 4
	v.color = color;
	v.normal.Set(0.5f * lengthX, 0.5f * lengthY, -0.5f * lengthZ); // Index 4
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); // Index 5
	v.color = color;
	v.normal.Set(0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); // Index 5
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * lengthX, 0.5f * lengthY, -0.5f * lengthZ); // Index 6
	v.color = color;
	v.normal.Set(-0.5f * lengthX, 0.5f * lengthY, -0.5f * lengthZ); // Index 6
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); // Index 7
	v.color = color;
	v.normal.Set(-0.5f * lengthX, -0.5f * lengthY, -0.5f * lengthZ); // Index 7
	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0); // Triangle 0
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);

	index_buffer_data.push_back(0); // Triangle 1
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);

	index_buffer_data.push_back(4); // Triangle 2
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(3);

	index_buffer_data.push_back(4); // Triangle 3
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(5);

	index_buffer_data.push_back(6); // Triangle 4
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	index_buffer_data.push_back(6); // Triangle 5
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(7);

	index_buffer_data.push_back(1); // Triangle 6
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(7);

	index_buffer_data.push_back(1); // Triangle 7
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(2);

	index_buffer_data.push_back(4); // Triangle 8
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(1);

	index_buffer_data.push_back(4); // Triangle 9
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(0);

	index_buffer_data.push_back(3); // Triangle 10
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(7);

	index_buffer_data.push_back(3); // Triangle 11
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(5);

	
	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateFeet(const std::string &meshName, Color color, float TallerHeight, float ShorterHeight)
{
	Vertex v;

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	for (int Num = 0; Num < 2; Num++)
	{
		float YCoord;
		if (Num == 0)
		{
			YCoord = 0.0;
		}
		else
		{
			YCoord = ShorterHeight;
		}
		v.pos.Set(0.5f * ShorterHeight, YCoord, 0.3f * ShorterHeight); // Index 0, 4
		v.color = color;
		v.normal.Set(0.5f * ShorterHeight, YCoord, 0.3f * ShorterHeight); // Index 0, 4
		vertex_buffer_data.push_back(v);

		v.pos.Set(0.5f * ShorterHeight, YCoord, -0.3f * ShorterHeight); // Index 1, 5
		v.color = color;
		v.normal.Set(0.5f * ShorterHeight, YCoord, -0.3f * ShorterHeight); // Index 1, 5
		vertex_buffer_data.push_back(v);

		v.pos.Set(-0.5f * ShorterHeight, YCoord, -0.5f * ShorterHeight); // Index 2, 6
		v.color = color;
		v.normal.Set(-0.5f * ShorterHeight, YCoord, -0.5f * ShorterHeight); // Index 2, 6
		vertex_buffer_data.push_back(v);

		v.pos.Set(-0.5f * ShorterHeight, YCoord, 0.5f * ShorterHeight); // Index 3, 7
		v.color = color;
		v.normal.Set(-0.5f * ShorterHeight, YCoord, 0.5f * ShorterHeight); // Index 3, 7
		vertex_buffer_data.push_back(v);
	}
	v.pos.Set(-0.5f * ShorterHeight, TallerHeight, -0.5f * ShorterHeight); // Index 8
	v.color = color;
	v.normal.Set(-0.5f * ShorterHeight, TallerHeight, -0.5f * ShorterHeight); // Index 8
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * ShorterHeight, TallerHeight, 0.5f * ShorterHeight); // Index 9
	v.color = color;
	v.normal.Set(-0.5f * ShorterHeight, TallerHeight, 0.5f * ShorterHeight); // Index 9
	vertex_buffer_data.push_back(v);

	// Surface
	index_buffer_data.push_back(0); 
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0);

	// Height
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(7);

	index_buffer_data.push_back(1);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(4);

	index_buffer_data.push_back(2);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(5);

	index_buffer_data.push_back(3);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(6);

	//Top
	index_buffer_data.push_back(4); // Front
	index_buffer_data.push_back(9);
	index_buffer_data.push_back(7);

	index_buffer_data.push_back(5); // Back
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(8);

	index_buffer_data.push_back(4); // Diagonal
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(9);
	index_buffer_data.push_back(8);
	index_buffer_data.push_back(9);
	index_buffer_data.push_back(5);

	index_buffer_data.push_back(6); // Straight
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(8);
	index_buffer_data.push_back(9);
	index_buffer_data.push_back(8);
	index_buffer_data.push_back(7);

	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateCircle(const std::string &meshName, Color color, float Radius, unsigned NumSlice)
{
	Vertex v;
	const double pi = 3.14159;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	for (int slice = 0; slice < (int)NumSlice; slice++)
	{
		v.pos.Set(float(sin((slice * 10.0f) / 180.0f * pi) * Radius), 0.0f * Radius, float(cos((slice * 10.0f) / 180.0f * pi)) * Radius); // Index 0 - 35
		v.color = color;
		v.normal.Set(float(sin((slice * 10.0f) / 180.0f * pi) * Radius), 0.0f * Radius, float(cos((slice * 10.0f) / 180.0f * pi)) * Radius); // Index 0 - 35
		vertex_buffer_data.push_back(v);
	}
	v.pos.Set(0.0f, 0.0f, 0.0f);
	v.color = color;
	v.normal.Set(0.0f, 0.0f, 0.0f);
	vertex_buffer_data.push_back(v);

	for (int Num = 0; Num < (int)NumSlice; Num++)
	{
		if (Num == (int)NumSlice - 1)
		{
			index_buffer_data.push_back(35);
			index_buffer_data.push_back(0);
			index_buffer_data.push_back(36);
		}
		else
		{
			index_buffer_data.push_back(Num);
			index_buffer_data.push_back(Num + 1);
			index_buffer_data.push_back(36);
		}
	}
	
	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateCylinder(const std::string &meshName, Color color, float RadiusTop, float RadiusBottom, unsigned NumSlice, float height)
{
	Vertex v;
	const double pi = 3.14159;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	for (int slice = 0; slice < (int)NumSlice; slice++)
	{
		v.pos.Set(float(sin((slice * 10.0f) / 180.0f * pi) * RadiusTop), 0.0f * RadiusTop, float(cos((slice * 10.0f) / 180.0f * pi)) * RadiusTop); // Index 0 - 35
		v.color = color;
		v.normal.Set(float(sin((slice * 10.0f) / 180.0f * pi) * RadiusTop), 0.0f * RadiusTop, float(cos((slice * 10.0f) / 180.0f * pi)) * RadiusTop); // Index 0 - 35
		vertex_buffer_data.push_back(v);
	}
	v.pos.Set(0.0f, 0.0f, 0.0f); // Index 36
	v.color = color;
	v.normal.Set(0.0f, 0.0f, 0.0f); // Index 36
	vertex_buffer_data.push_back(v);
	for (int slice = 0; slice < (int)NumSlice; slice++)
	{
		v.pos.Set(float(sin((slice * 10.0f) / 180.0f * pi) * RadiusBottom), 0.0f * RadiusBottom + height, float(cos((slice * 10.0f) / 180.0f * pi)) * RadiusBottom); // Index 37 - 72
		v.color = color;
		v.normal.Set(float(sin((slice * 10.0f) / 180.0f * pi) * RadiusBottom), 0.0f * RadiusBottom + height, float(cos((slice * 10.0f) / 180.0f * pi)) * RadiusBottom); // Index 37 - 72
		vertex_buffer_data.push_back(v);
	}
	v.pos.Set(0.0f, 0.0f + height, 0.0f); // Index 73
	v.color = color;
	v.normal.Set(0.0f, 0.0f + height, 0.0f); // Index 73
	vertex_buffer_data.push_back(v);
	for (int Num = 0; Num < (int)NumSlice; Num++)
	{
		if (Num == (int)NumSlice - 1)
		{
			index_buffer_data.push_back(35);
			index_buffer_data.push_back(36);
			index_buffer_data.push_back(0);
		}
		else
		{
			index_buffer_data.push_back(Num);
			index_buffer_data.push_back(36);
			index_buffer_data.push_back(Num + 1);
		}
	}
	for (int Num = (int)NumSlice + 1; Num < (int)NumSlice * 2; Num++)
	{
		if (Num == (int)NumSlice* 2 - 1)
		{
			index_buffer_data.push_back(Num);
			index_buffer_data.push_back(37);
			index_buffer_data.push_back((int)NumSlice * 2 + 1);
		}
		else
		{
			index_buffer_data.push_back(Num);
			index_buffer_data.push_back(Num + 1);
			index_buffer_data.push_back((int)NumSlice * 2 + 1);
		}
	}
	for (int Num = 0; Num < (int)NumSlice; Num++)
	{
		if (Num == (int)NumSlice - 1)
		{
			index_buffer_data.push_back(Num);
			index_buffer_data.push_back(0);
			index_buffer_data.push_back(Num + (int)NumSlice + 1);
		}
		else
		{
			index_buffer_data.push_back(Num);
			index_buffer_data.push_back(Num + 1);
			index_buffer_data.push_back(Num + (int)NumSlice + 1);
		}
	}
	for (int Num = 0; Num < (int)NumSlice; Num++)
	{
		if (Num == (int)NumSlice - 1)
		{
			index_buffer_data.push_back(Num + (int)NumSlice + 1);
			index_buffer_data.push_back(0);
			index_buffer_data.push_back(37);
		}
		else
		{
			index_buffer_data.push_back(Num + (int)NumSlice + 1);
			index_buffer_data.push_back(Num + 1);
			index_buffer_data.push_back(Num + (int)NumSlice + 2);
		}
	}
	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateMask(const std::string &meshName, Color color, float Radius, unsigned NumSlice, float height)
{
	// It's an open incomplete cylinder 
	Vertex v;
	const double pi = 3.14159;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	for (int slice = 0; slice < (int)NumSlice; slice++)
	{
		v.pos.Set(float(sin((slice * 10.0f) / 180.0f * pi) * Radius), 0.0f * Radius, float(cos((slice * 10.0f) / 180.0f * pi)) * Radius); // Index 0 - 35
		v.color = color;
		v.normal.Set(float(sin((slice * 10.0f) / 180.0f * pi) * Radius), 0.0f * Radius, float(cos((slice * 10.0f) / 180.0f * pi)) * Radius); // Index 0 - 35
		vertex_buffer_data.push_back(v);
	}
	v.pos.Set(0.0f, 0.0f, 0.0f); // Index 36
	v.color = color;
	v.normal.Set(0.0f, 0.0f, 0.0f); // Index 36
	vertex_buffer_data.push_back(v);
	for (int slice = 0; slice < (int)NumSlice; slice++)
	{
		v.pos.Set(float(sin((slice * 10.0f) / 180.0f * pi) * Radius), 0.0f * Radius + height, float(cos((slice * 10.0f) / 180.0f * pi)) * Radius); // Index 37 - 72
		v.color = color;
		v.normal.Set(float(sin((slice * 10.0f) / 180.0f * pi) * Radius), 0.0f * Radius + height, float(cos((slice * 10.0f) / 180.0f * pi)) * Radius); // Index 37 - 72
		vertex_buffer_data.push_back(v);
	}
	v.pos.Set(0.0f, 0.0f + height, 0.0f); // Index 73
	v.color = color;
	vertex_buffer_data.push_back(v);

	// Special Vertex
	int Mask = (int)NumSlice - 5;
	for (int slice = 5; slice > 0; slice--)
	{
		v.pos.Set(float(sin((slice * 10.0f) / 180.0f * pi) * Radius), 0.0f * Radius + 0.2f * height, float(cos((slice * 10.0f) / 180.0f * pi)) * Radius); // Index 74 - 78
		v.color = color;
		v.normal.Set(float(sin((slice * 10.0f) / 180.0f * pi) * Radius), 0.0f * Radius + 0.2f * height, float(cos((slice * 10.0f) / 180.0f * pi)) * Radius); // Index 74 - 78
		vertex_buffer_data.push_back(v);
	}
	int Numoftimes = 4;
	for (int IDK = 0; IDK < 5; IDK++, Numoftimes--)
	{
		for (int Num = 5; Num > Numoftimes; Num--)
		{
			v.pos.Set(float(sin((Num * 10.0f) / 180.0f * pi) * Radius), 0.0f * Radius + (0.2f + 0.02f * (Numoftimes + 1)) * height, float(cos((Num * 10.0f) / 180.0f * pi)) * Radius); // Index 79 - 93
			v.color = color;
			v.normal.Set(float(sin((Num * 10.0f) / 180.0f * pi) * Radius), 0.0f * Radius + (0.2f + 0.02f * (Numoftimes + 1)) * height, float(cos((Num * 10.0f) / 180.0f * pi)) * Radius); // Index 79 - 93
			vertex_buffer_data.push_back(v);
		}
	}
	for (int slice = Mask; slice < Mask + 5; slice++)
	{
		v.pos.Set(float(sin((slice * 10.0f) / 180.0f * pi) * Radius), 0.0f * Radius + 0.2f * height, float(cos((slice * 10.0f) / 180.0f * pi)) * Radius); // Index 94 - 98
		v.color = color;
		v.normal.Set(float(sin((slice * 10.0f) / 180.0f * pi) * Radius), 0.0f * Radius + 0.2f * height, float(cos((slice * 10.0f) / 180.0f * pi)) * Radius); // Index 94 - 98
		vertex_buffer_data.push_back(v);
	}
	Numoftimes = 4;
	for (int IDK = 0; IDK < 5; IDK++, Numoftimes--)
	{
		for (int Num = 0; Num < 5 - Numoftimes; Num++)
		{
			v.pos.Set(float(sin(((Num + Mask) * 10.0f) / 180.0f * pi) * Radius), 0.0f * Radius + (0.2f + 0.02f * (Numoftimes + 1)) * height, float(cos(((Num + Mask) * 10.0f) / 180.0f * pi)) * Radius); // Index 99 - 113
			v.color = color;
			v.normal.Set(float(sin(((Num + Mask) * 10.0f) / 180.0f * pi) * Radius), 0.0f * Radius + (0.2f + 0.02f * (Numoftimes + 1)) * height, float(cos(((Num + Mask) * 10.0f) / 180.0f * pi)) * Radius); // Index 99 - 113
			vertex_buffer_data.push_back(v);
		}
	}

	for (int Num = 5; Num < Mask; Num++)
	{
		index_buffer_data.push_back(Num);
		index_buffer_data.push_back(Num + 1);
		index_buffer_data.push_back(Num + (int)NumSlice + 1);
	}
	for (int Num = 5; Num < Mask; Num++)
	{
		index_buffer_data.push_back(Num + (int)NumSlice + 1);
		index_buffer_data.push_back(Num + 1);
		index_buffer_data.push_back(Num + (int)NumSlice + 2);
	}

	// Special Index
	for (int Num = 1; Num < 5; Num++)
	{
		index_buffer_data.push_back(Num);
		index_buffer_data.push_back(Num + 1);
		index_buffer_data.push_back(79 - Num);
	}
	for (int Num = 1; Num < 5; Num++)
	{
		index_buffer_data.push_back(79 - Num);
		index_buffer_data.push_back(Num + 1);
		index_buffer_data.push_back(79 - Num - 1);
	}
	for (int Num = 0; Num < 10; Num++)
	{
		if (Num == 0)
		{
			index_buffer_data.push_back(Num + 79);
			index_buffer_data.push_back(Num + 79 + 2);
			index_buffer_data.push_back(Num + 79 + 1);
		}
		else if (Num < 3)
		{
			index_buffer_data.push_back(Num + 79);
			index_buffer_data.push_back(Num + 79 + 3);
			index_buffer_data.push_back(Num + 79 + 2);
		}
		else if (Num < 6)
		{
			index_buffer_data.push_back(Num + 79);
			index_buffer_data.push_back(Num + 79 + 4);
			index_buffer_data.push_back(Num + 79 + 3);
		}
		else
		{
			index_buffer_data.push_back(Num + 79);
			index_buffer_data.push_back(Num + 68 + 1);
			index_buffer_data.push_back(Num + 68);
		}
	}

	index_buffer_data.push_back(81);
	index_buffer_data.push_back(83);
	index_buffer_data.push_back(80);

	index_buffer_data.push_back(83);
	index_buffer_data.push_back(86);
	index_buffer_data.push_back(82);

	index_buffer_data.push_back(86);
	index_buffer_data.push_back(75);
	index_buffer_data.push_back(85);

	index_buffer_data.push_back(84);
	index_buffer_data.push_back(87);
	index_buffer_data.push_back(83);

	index_buffer_data.push_back(87);
	index_buffer_data.push_back(76);
	index_buffer_data.push_back(86);

	index_buffer_data.push_back(88);
	index_buffer_data.push_back(77);
	index_buffer_data.push_back(87);

	for (int Num = 31; Num < Mask + 4; Num++)
	{
		index_buffer_data.push_back(Num);
		index_buffer_data.push_back(Num + 1);
		index_buffer_data.push_back(93 + Num - 30);
	}
	for (int Num = 31; Num < Mask + 4; Num++)
	{
		index_buffer_data.push_back(93 + Num - 30);
		index_buffer_data.push_back(Num + 1);
		index_buffer_data.push_back(93 + Num - 29);
	}
	for (int Num = 0; Num < 10; Num++)
	{
		if (Num == 0)
		{
			index_buffer_data.push_back(Num + 99);
			index_buffer_data.push_back(Num + 99 + 1);
			index_buffer_data.push_back(Num + 99 + 2);
		}
		else if (Num < 3)
		{
			index_buffer_data.push_back(Num + 99);
			index_buffer_data.push_back(Num + 99 + 2);
			index_buffer_data.push_back(Num + 99 + 3);
		}
		else if (Num < 6)
		{
			index_buffer_data.push_back(Num + 99);
			index_buffer_data.push_back(Num + 99 + 3);
			index_buffer_data.push_back(Num + 99 + 4);
		}
		else
		{
			index_buffer_data.push_back(Num + 99);
			index_buffer_data.push_back(Num + 88);
			index_buffer_data.push_back(Num + 88 + 1);
		}
	}

	index_buffer_data.push_back(100);
	index_buffer_data.push_back(103);
	index_buffer_data.push_back(101);

	index_buffer_data.push_back(102);
	index_buffer_data.push_back(106);
	index_buffer_data.push_back(103);

	index_buffer_data.push_back(105);
	index_buffer_data.push_back(95);
	index_buffer_data.push_back(106);

	index_buffer_data.push_back(103);
	index_buffer_data.push_back(107);
	index_buffer_data.push_back(104);

	index_buffer_data.push_back(106);
	index_buffer_data.push_back(96);
	index_buffer_data.push_back(107);

	index_buffer_data.push_back(107);
	index_buffer_data.push_back(97);
	index_buffer_data.push_back(108);

	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateRing(const std::string &meshName, Color color, float RadiusBig, float RadiusSmall, unsigned NumSlice)
{
	Vertex v;
	const double pi = 3.14159;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	for (int slice = 0; slice < (int)NumSlice; slice++)
	{
		v.pos.Set(float(sin((slice * 10.0f) / 180.0f * pi) * RadiusSmall), 0.0f * RadiusSmall, float(cos((slice * 10.0f) / 180.0f * pi) * RadiusSmall)); // Index 0 - 35
		v.color = color;
		//v.normal.Set(0.0, 1, 0.0);
		v.normal.Set(float(sin((slice * 10.0f) / 180.0f * pi) * RadiusSmall), 0.0f * RadiusSmall, float(cos((slice * 10.0f) / 180.0f * pi) * RadiusSmall)); // Index 0 - 35
		vertex_buffer_data.push_back(v);
	}
	for (int slice = 0; slice < (int)NumSlice; slice++)
	{
		v.pos.Set(float(sin((slice * 10.0f) / 180.0f * pi) * RadiusBig), 0.0f * RadiusBig, float(cos((slice * 10.0f) / 180.0f * pi) * RadiusBig)); // Index 36 - 72
		v.color = color;
		v.normal.Set(0.0, 1, 0.0);
		v.normal.Set(float(sin((slice * 10.0f) / 180.0f * pi) * RadiusBig), 0.0f * RadiusBig, float(cos((slice * 10.0f) / 180.0f * pi) * RadiusBig)); // Index 36 - 72
		vertex_buffer_data.push_back(v);
	}
	for (int Num = 0; Num < (int)NumSlice; Num++)
	{
		if (Num == (int)NumSlice - 1)
		{
			index_buffer_data.push_back(Num);
			index_buffer_data.push_back(Num + (int)NumSlice);
			index_buffer_data.push_back(0);
		}
		else
		{
			index_buffer_data.push_back(Num);
			index_buffer_data.push_back(Num + (int)NumSlice);
			index_buffer_data.push_back(Num + 1);
		}
	}
	for (int Num = 0; Num < (int)NumSlice; Num++)
	{
		if (Num == (int)NumSlice - 1)
		{
			index_buffer_data.push_back(Num + (int)NumSlice);
			index_buffer_data.push_back(0);
			index_buffer_data.push_back((int)NumSlice);
		}
		else
		{
			index_buffer_data.push_back(Num + (int)NumSlice);
			index_buffer_data.push_back(Num + 1);
			index_buffer_data.push_back(Num + (int)NumSlice + 1);
		}
	}
	for (int Num = 0; Num < (int)NumSlice; Num++)
	{
		if (Num == (int)NumSlice - 1)
		{
			index_buffer_data.push_back(Num);
			index_buffer_data.push_back(0);
			index_buffer_data.push_back(Num + (int)NumSlice);
		}
		else
		{
			index_buffer_data.push_back(Num);
			index_buffer_data.push_back(Num + 1);
			index_buffer_data.push_back(Num + (int)NumSlice);
		}
	}
	for (int Num = 0; Num < (int)NumSlice; Num++)
	{
		if (Num == (int)NumSlice - 1)
		{
			index_buffer_data.push_back(Num + (int)NumSlice);
			index_buffer_data.push_back((int)NumSlice);
			index_buffer_data.push_back(0);
		}
		else
		{
			index_buffer_data.push_back(Num + (int)NumSlice);
			index_buffer_data.push_back(Num + (int)NumSlice + 1);
			index_buffer_data.push_back(Num + 1);
		}
	}
	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color, float Radius, unsigned NumSlice, unsigned NumStack)
{
	Vertex v;
	const double pi = 3.14159;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	for (int stack = 0; stack < (int)NumStack; stack++) // phi
	{
		for (int slice = 0; slice < (int)NumSlice; slice++) // theta
		{
			v.pos.Set(float(cos((stack * 10.0f) / 180.0f * pi) * cos((slice * 10.0f) / 180.0f * pi) * Radius), float(sin((stack * 10.0f) / 180.0f * pi) * Radius), float(cos((stack * 10.0f) / 180.0f * pi) * sin((slice * 10.0f) / 180.0f * pi) * Radius)); // Index 0 - 647
			v.color = color;
			v.normal.Set(float(cos((stack * 10.0f) / 180.0f * pi) * cos((slice * 10.0f) / 180.0f * pi) * Radius), float(sin((stack * 10.0f) / 180.0f * pi) * Radius), float(cos((stack * 10.0f) / 180.0f * pi) * sin((slice * 10.0f) / 180.0f * pi) * Radius)); // Index 0 - 647
			vertex_buffer_data.push_back(v);
		}
	}
	for (int stack = 0; stack < (int)NumStack; stack++) // phi
	{
		for (int slice = 0; slice < (int)NumSlice; slice++) // theta
		{
			v.pos.Set(float(cos((stack * 10.0f) / 180.0f * pi) * cos((slice * 10.0f) / 180.0f * pi) * -Radius), float(sin((stack * 10.0f) / 180.0f * pi) * -Radius), float(cos((stack * 10.0f) / 180.0f * pi) * sin((slice * 10.0f) / 180.0f * pi) * -Radius)); // Index 648 - 1296
			v.color = color;
			v.normal.Set(float(cos((stack * 10.0f) / 180.0f * pi) * cos((slice * 10.0f) / 180.0f * pi) * -Radius), float(sin((stack * 10.0f) / 180.0f * pi) * -Radius), float(cos((stack * 10.0f) / 180.0f * pi) * sin((slice * 10.0f) / 180.0f * pi) * -Radius)); // Index 648 - 1296
			vertex_buffer_data.push_back(v);
		}
	}
	v.pos.Set(0.0f * Radius, Radius, 0.0f * Radius); // Index 1300
	v.color = (0.f, 0.f, 0.f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.0f * -Radius, -Radius, 0.0f * -Radius); // Index 1301
	v.color = (0.f, 0.f, 0.f);
	vertex_buffer_data.push_back(v);
	for (int Num = 0; Num < (int)NumSlice * (int)NumStack / 2; Num++) // 1st top
	{
		if ((Num + 1) % (int)NumSlice == 0)
		{
			index_buffer_data.push_back(Num);
			index_buffer_data.push_back(Num + (int)NumSlice);
			index_buffer_data.push_back(Num + 1 - (int)NumSlice);
		}
		else
		{
			index_buffer_data.push_back(Num);
			index_buffer_data.push_back(Num + (int)NumSlice);
			index_buffer_data.push_back(Num + 1);
		}
	}
	for (int Num = 0; Num < (int)NumSlice * (int)NumStack / 2; Num++) // 2nd top
	{
		if ((Num + 1) % (int)NumSlice == 0)
		{
			index_buffer_data.push_back(Num + (int)NumSlice);
			index_buffer_data.push_back(Num + (int)NumSlice + 1);
			index_buffer_data.push_back(Num + 1 - (int)NumSlice);
		}
		else
		{
			index_buffer_data.push_back(Num + (int)NumSlice);
			index_buffer_data.push_back(Num + (int)NumSlice + 1);
			index_buffer_data.push_back(Num + 1);
		}
	}
	for (int Num = 0; Num < (int)NumSlice * (int)NumStack / 2; Num++) // 1st bottom
	{
		if ((Num + 1) % (int)NumSlice == 0)
		{
			index_buffer_data.push_back(Num + (int)NumSlice * (int)NumStack);
			index_buffer_data.push_back(Num + 1 - (int)NumSlice + (int)NumSlice * (int)NumStack);
			index_buffer_data.push_back(Num + (int)NumSlice + (int)NumSlice * (int)NumStack);
		}
		else
		{
			index_buffer_data.push_back(Num + (int)NumSlice * (int)NumStack);
			index_buffer_data.push_back(Num + 1 + (int)NumSlice * (int)NumStack);
			index_buffer_data.push_back(Num + (int)NumSlice + (int)NumSlice * (int)NumStack);
		}
	}
	for (int Num = 0; Num < (int)NumSlice * (int)NumStack / 2; Num++) // 2nd bottom
	{
		if ((Num + 1) % (int)NumSlice == 0)
		{
			index_buffer_data.push_back(Num + (int)NumSlice + (int)NumSlice * (int)NumStack);
			index_buffer_data.push_back(Num + 1 - (int)NumSlice + (int)NumSlice * (int)NumStack);
			index_buffer_data.push_back(Num + (int)NumSlice + 1 + (int)NumSlice * (int)NumStack);
		}
		else
		{
			index_buffer_data.push_back(Num + (int)NumSlice + (int)NumSlice * (int)NumStack);
			index_buffer_data.push_back(Num + 1 + (int)NumSlice * (int)NumStack);
			index_buffer_data.push_back(Num + (int)NumSlice + 1 + (int)NumSlice * (int)NumStack);
		}
	}
	for (int Num = 611; Num < (int)NumSlice * (int)NumStack / 2; Num++) // 2nd bottom
	{
		index_buffer_data.push_back(Num);
		index_buffer_data.push_back(Num + 1);
		index_buffer_data.push_back(1300);
	}
	
	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateHemisphere(const std::string &meshName, Color color, float Radius, unsigned NumSlice, unsigned NumStack)
{
	Vertex v;
	const double pi = 3.14159;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	for (int stack = 0; stack < (int)NumStack; stack++) // phi
	{
		for (int slice = 0; slice < (int)NumSlice; slice++) // theta
		{
			v.pos.Set(float(cos((stack * 10.0f) / 180.0f * pi) * cos((slice * 10.0f) / 180.0f * pi) * Radius), float(sin((stack * 10.0f) / 180.0f * pi) * Radius), float(cos((stack * 10.0f) / 180.0f * pi) * sin((slice * 10.0f) / 180.0f * pi) * Radius)); // Index 0 - 647
			v.color = color;
			v.normal.Set(float(cos((stack * 10.0f) / 180.0f * pi) * cos((slice * 10.0f) / 180.0f * pi) * Radius), float(sin((stack * 10.0f) / 180.0f * pi) * Radius), float(cos((stack * 10.0f) / 180.0f * pi) * sin((slice * 10.0f) / 180.0f * pi) * Radius)); // Index 0 - 647
			vertex_buffer_data.push_back(v);
		}
	}
	for (int Num = 0; Num < (int)NumSlice * (int)NumStack / 2; Num++) // 1st top
	{
		if ((Num + 1) % (int)NumSlice == 0)
		{
			index_buffer_data.push_back(Num);
			index_buffer_data.push_back(Num + (int)NumSlice);
			index_buffer_data.push_back(Num + 1 - (int)NumSlice);
		}
		else
		{
			index_buffer_data.push_back(Num);
			index_buffer_data.push_back(Num + (int)NumSlice);
			index_buffer_data.push_back(Num + 1);
		}
	}
	for (int Num = 0; Num < (int)NumSlice * (int)NumStack / 2; Num++) // 2nd top
	{
		if ((Num + 1) % (int)NumSlice == 0)
		{
			index_buffer_data.push_back(Num + (int)NumSlice);
			index_buffer_data.push_back(Num + (int)NumSlice + 1);
			index_buffer_data.push_back(Num + 1 - (int)NumSlice);
		}
		else
		{
			index_buffer_data.push_back(Num + (int)NumSlice);
			index_buffer_data.push_back(Num + (int)NumSlice + 1);
			index_buffer_data.push_back(Num + 1);
		}
	}
	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateOBJ(const std::string &meshName, const std::string &file_path) 
{
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	float tempX[2] = { 0.f, 0.f };
	float tempY[2] = { 0.f, 0.f };
	float tempZ[2] = { 0.f, 0.f };
	bool success = LoadOBJ(file_path.c_str(), vertices,
		uvs, normals, tempX, tempY, tempZ);
	if (!success)
		return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
	//Create the mesh and call glBindBuffer, glBufferData
	//Use triangle list and remember to set index size
	Mesh *mesh = new Mesh(meshName);
	mesh->setValues(tempX, tempY, tempZ);
	std::cout << meshName << std::endl;
	std::cout << "XSmall: " << mesh->XCoord[0] << " " << "XBig: " << mesh->XCoord[1] << std::endl;
	std::cout << "YSmall: " << mesh->YCoord[0] << " " << "YBig: " << mesh->YCoord[1] << std::endl;
	std::cout << "ZSmall: " << mesh->ZCoord[0] << " " << "ZBig: " << mesh->ZCoord[1] << std::endl;
	mesh->mode = Mesh::DRAW_TRIANGLES;
	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol)
{
	Vertex v;

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	float width = 1.f / numCol;
	float height = 1.f / numRow;
	int offset = 0;
	for (unsigned i = 0; i < numRow; ++i)
	{
		for (unsigned j = 0; j < numCol; ++j)
		{
			float u1 = j * width;
			float v1 = 1.f - height - i * height;

			v.pos.Set(-0.5f,-0.5f, 0);
			v.texCoord.Set(u1, v1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f, -0.5f, 0);
			v.texCoord.Set(u1 + width, v1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f, 0.5f, 0);
			v.texCoord.Set(u1 + width, v1 + height);
			vertex_buffer_data.push_back(v);

			v.pos.Set(-0.5f, 0.5f, 0);
			v.texCoord.Set(u1, v1 + height);
			vertex_buffer_data.push_back(v);

			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 3);
			offset += 4;
		}
	}
	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}