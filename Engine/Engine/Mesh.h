#ifndef __MESH_H__
#define __MESH_H__

#include <glm\vec3.hpp>
#include <glm\vec2.hpp>
#include <string>

#include "Common.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec2 textureCoord;
	glm::vec3 normal;
	glm::vec3 tangent;
	
	Vertex(const glm::vec3& pos = glm::vec3(),
		const glm::vec2& tex = glm::vec2(),
		const glm::vec3& norm = glm::vec3(),
		const glm::vec3& tan = glm::vec3())
		: position(pos), textureCoord(tex), normal(norm), tangent(tan)
	{

	}
};

class Mesh
{
public:
	// Constructor
	Mesh(const Vertex* vertexData, size_t vertexCount, const GLushort* indexData, size_t indexCount);

	// Destructor
	virtual ~Mesh();

	// Methods ----------------------------------------------------------------
	void Render() const;

private:

	// Methods ----------------------------------------------------------------
	void Initialize(const Vertex* vertexData, size_t vertexCount, const GLushort* indexData, size_t indexCount, bool bCalcNormals = true);
	void CalcNormals(Vertex* vertexData, size_t vertexCount, GLushort* indexData, size_t indexCount);

	// Data --------------------------------------------------------------------
	enum 
	{
		keVertexPosition,
		keVertexTextureCoord,
		keVertexNormal,
		keVertexTangent,

		keNumOfBuffers,
	};

	// Vertex count
	size_t m_uiVertexCount;

	// Vertex array object
	GLuint m_uiVertexArrayObject;

	GLuint uiIndexBuffer;

	// Array of buffers
	GLuint m_uiVertexArrayBuffer[ keNumOfBuffers ];
};

#endif // __MESH_H__
