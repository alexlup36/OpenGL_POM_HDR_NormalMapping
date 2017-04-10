#include "Mesh.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

// ----------------------------------------------------------------------------------------------

// Constructor
Mesh::Mesh(const Vertex* vertexData, size_t vertexCount, const GLushort* indexData, size_t indexCount)
{
	m_uiVertexCount = 0;

	Initialize(vertexData, vertexCount, indexData, indexCount, true);
}

// ----------------------------------------------------------------------------

// Destructor
Mesh::~Mesh()
{
	// Delete the GL buffers
	glDeleteBuffers( keNumOfBuffers, m_uiVertexArrayBuffer );

	// Delete the vertex array object
	glDeleteVertexArrays( 1, &m_uiVertexArrayObject );
}

// ----------------------------------------------------------------------------

// Create the vertex and index buffers and initialize them
void Mesh::Initialize(const Vertex* vertexData, size_t vertexCount, const GLushort* indexData, size_t indexCount, bool bCalcNormals)
{
	m_uiVertexCount = vertexCount;

	// Generate the buffers -------------------------------------------------------------------------

	// Generate the vertex array
	glGenVertexArrays( 1, &m_uiVertexArrayObject );
	glBindVertexArray( m_uiVertexArrayObject );

	// Generate the buffers and bind them
	glGenBuffers( keNumOfBuffers, m_uiVertexArrayBuffer );
	glGenBuffers( 1, &uiIndexBuffer );
	
	glBindBuffer( GL_ARRAY_BUFFER, m_uiVertexArrayBuffer[keVertexPosition] );
	glBindBuffer( GL_ARRAY_BUFFER, m_uiVertexArrayBuffer[keVertexTextureCoord] );
	glBindBuffer( GL_ARRAY_BUFFER, m_uiVertexArrayBuffer[keVertexNormal] );
	glBindBuffer( GL_ARRAY_BUFFER, m_uiVertexArrayBuffer[keVertexTangent] );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, uiIndexBuffer );

	// Initialize the data in the buffers ------------------------------------------------------------

	// Vertices
	glBufferData( GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, vertexData, GL_STATIC_DRAW );
	// Indices
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indexCount, indexData, GL_STATIC_DRAW );

	// Setup the attributes --------------------------------------------------------------------------
	glEnableVertexAttribArray(0); // Enable vertex position
	glEnableVertexAttribArray(1); // Enable vertex texture
	glEnableVertexAttribArray(2); // Enable vertex normal
	glEnableVertexAttribArray(3); // Enable vertex tangent

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); // Position
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(float) * 3)); // Texture
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(float) * 5)); // Normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(float) * 8)); // Tangent

	// -----------------------------------------------------------------------------------------------
	glBindVertexArray( 0 );
}

// ----------------------------------------------------------------------------

// Compute mesh normals
void Mesh::CalcNormals(Vertex* vertexData, size_t vertexCount, GLushort* indexData, size_t indexCount)
{
	for(size_t i = 0; i < indexCount; i += 3)
	{
		int i0 = indexData[i];
		int i1 = indexData[i + 1];
		int i2 = indexData[i + 2];

		glm::vec3 v1 = vertexData[i1].position - vertexData[i0].position;
		glm::vec3 v2 = vertexData[i2].position - vertexData[i0].position;

		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		vertexData[i0].normal += normal;
		vertexData[i1].normal += normal;
		vertexData[i2].normal += normal;
	}

	for(size_t i = 0; i < vertexCount; i++)
	{
		vertexData[i].normal = glm::normalize(vertexData[i].normal);
	}
}

// ----------------------------------------------------------------------------

// Render Mesh
void Mesh::Render() const
{
	GLClearErrors();

	// Bind the vertex array object
	glBindVertexArray( m_uiVertexArrayObject );

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Draw call
	glDrawElements(GL_TRIANGLES, (GLsizei)m_uiVertexCount, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray( 0 );

	GLErrorCheck("MeshRender");
}

// ----------------------------------------------------------------------------