#include "TextMan.h"


TextMan::TextMan(void)
{
}


TextMan::~TextMan(void)
{
	// Delete buffers
	glDeleteBuffers(1, &m_Text2DVertexBufferID);
	glDeleteBuffers(1, &m_Text2DUVBufferID);

	// Delete texture
	GLuint textureID = m_pTextTexture->GetHandler();
	glDeleteTextures(1, &textureID);

	// Delete shader
	glDeleteProgram(m_pTextShader->ProgramID());
}

void 
TextMan::Initialize(const char* sFontTexturePath)
{
	m_pTextShader = new Engine::Shader(".\\Shaders\\text.vert", ".\\Shaders\\text.frag");

	m_pTextShader->Enable();

	// Initialize texture
	m_pTextTexture = new Engine::Texture(sFontTexturePath, TextureType::Diffuse, true, false);

	// Create the vertex buffer and UV buffer
	glGenBuffers(1, &m_Text2DVertexBufferID);
	glGenBuffers(1, &m_Text2DUVBufferID);

	m_pTextShader->Disable();
}

void 
TextMan::PrintText(const char* sText, int x, int y, int size)
{
	size_t length = strlen(sText);

	// Fill buffers
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> UVs;

	for (unsigned int i = 0 ; i < length ; i++)
	{	
		glm::vec2 vertex_up_left    = glm::vec2(x + i * size, y + size);
		glm::vec2 vertex_up_right   = glm::vec2(x + i * size + size, y + size);
		glm::vec2 vertex_down_right = glm::vec2(x + i * size + size, y);
		glm::vec2 vertex_down_left  = glm::vec2(x + i * size, y);

		vertices.push_back(vertex_up_left);
		vertices.push_back(vertex_down_left);
		vertices.push_back(vertex_up_right);

		vertices.push_back(vertex_down_right);
		vertices.push_back(vertex_up_right);
		vertices.push_back(vertex_down_left);

		char character = sText[i];
		float uv_x = (character % 16) / 16.0f;
		float uv_y = (character / 16) / 16.0f;

		glm::vec2 uv_up_left    = glm::vec2( uv_x           , uv_y );
		glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, uv_y );
		glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, (uv_y + 1.0f/16.0f) );
		glm::vec2 uv_down_left  = glm::vec2( uv_x           , (uv_y + 1.0f/16.0f) );
		UVs.push_back(uv_up_left   );
		UVs.push_back(uv_down_left );
		UVs.push_back(uv_up_right  );

		UVs.push_back(uv_down_right);
		UVs.push_back(uv_up_right);
		UVs.push_back(uv_down_left);
	}

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_Text2DVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_Text2DUVBufferID);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

	// Enable the text shader
	m_pTextShader->Enable();

	// Bind texture
	m_pTextTexture->Bind(0, m_pTextShader->ProgramID());

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_Text2DVertexBufferID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_Text2DUVBufferID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw call
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size() );

	glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindVertexArray(0);

	// Disable the text shader
	m_pTextShader->Disable();
}