#include "RenderToTexture.h"

// ---------------------------------------------------------------------------

RenderToTexture::RenderToTexture()
{
	m_uiColorBuffer = 0;
	m_uiDepthBuffer = 0;

	m_uiFrameBuffer = 0;

	m_uiQuadVAO = 0;
	m_uiQuadVBO = 0;
}

// ---------------------------------------------------------------------------

RenderToTexture::~RenderToTexture()
{
}

// ---------------------------------------------------------------------------

void RenderToTexture::SetupFramebuffer(GLint colorBufferFormat, 
	GLenum dataType, 
	bool colorBuffer, 
	bool depthBuffer)
{
	// ---------------------------------------------------------------------------
	// Setup a framebuffer

	// Generate a framebuffer object
	glGenFramebuffers(1, &m_uiFrameBuffer);

	if (colorBuffer)
	{
		// ---------------------------------------------------------------------------
		// Create a color buffer object
		glGenTextures(1, &m_uiColorBuffer);
		// Bind the color buffer
		glBindTexture(GL_TEXTURE_2D, m_uiColorBuffer);
		// Generate a texture image on the currently bound texture object
		glTexImage2D(GL_TEXTURE_2D, 0, colorBufferFormat, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, dataType, nullptr);
		// Set textures parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Unbind the color buffer
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	if (depthBuffer)
	{
		// ---------------------------------------------------------------------------
		// Create a depth buffer
		glGenRenderbuffers(1, &m_uiDepthBuffer);
		// Bind the depth buffer
		glBindRenderbuffer(GL_RENDERBUFFER, m_uiDepthBuffer);
		// Allocate memory for the texture
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WINDOW_WIDTH, WINDOW_HEIGHT);
		// Set depth texture parameters
		glTexParameteri(GL_RENDERBUFFER, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_RENDERBUFFER, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_RENDERBUFFER, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_RENDERBUFFER, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// Unbind the depth buffer
		glBindTexture(GL_RENDERBUFFER, 0);
	}

	// ---------------------------------------------------------------------------
	// Attach the color buffer and the depth buffer to the framebuffer

	// Bind the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_uiFrameBuffer);
	if (colorBuffer)
	{
		// Attach the color buffer to the framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_uiColorBuffer, 0);
	}
	if (depthBuffer)
	{
		// Attach the depth buffer to the framebuffer
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_uiDepthBuffer);
	}
	
	// ---------------------------------------------------------------------------
	// Error check
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Framebuffer error." << std::endl;
	}

	// ---------------------------------------------------------------------------
	// Unbind the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// ---------------------------------------------------------------------------
}

// ---------------------------------------------------------------------------

void RenderToTexture::SetupQuadGeometry()
{
	// If the vertex array object hasn't been initialized
	if (m_uiQuadVAO == 0)
	{
		GLfloat quadVertices[] = 
		{
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};

		// Setup the vertex array object
		glGenVertexArrays(1, &m_uiQuadVAO);
		// Bind the vertex array object
		glBindVertexArray(m_uiQuadVAO);

		// Generate the vertex buffer object
		glGenBuffers(1, &m_uiQuadVBO);
		// Bind the vertex buffer object
		glBindBuffer(GL_ARRAY_BUFFER, m_uiQuadVBO);
		// Set the vertex buffer data - allocates memory and sets the data
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), (GLvoid*)&quadVertices, GL_STATIC_DRAW);

		// Enable vertex attrib pointer 0 
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);

		// Enable vertex attrib pointer 1
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	}
}

// ---------------------------------------------------------------------------

void RenderToTexture::RenderToQuad()
{
	// Bind vertex array object
	glBindVertexArray(m_uiQuadVAO);

	// Render the geometry
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// Unbind vertex array object
	glBindVertexArray(0);
}

// ---------------------------------------------------------------------------