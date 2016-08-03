#ifndef RENDERTOTEXTURE_H
#define RENDERTOTEXTURE_H

#include "Common.h"

class RenderToTexture
{
public:
	RenderToTexture();
	~RenderToTexture();

	// Setup quad geometry
	void SetupQuadGeometry();

	// Render to quad
	void RenderToQuad();

	// Used to setup the color and depth buffers and attach them to the framebuffer
	void SetupFramebuffer(GLint colorBufferFormat, GLenum dataType, bool colorBuffer, bool depthBuffer);

	// Before rendering bind the framebuffer
	inline void BindFramebuffer() { glBindFramebuffer(GL_FRAMEBUFFER, m_uiFrameBuffer); }
	inline void BindFramebuffer(GLuint frameBuffer) { glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer); }
	// Once the rendering is done unbind the framebuffer
	inline void UnbindFramebuffer() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

	inline GLuint GetColorBuffer() { return m_uiColorBuffer; }

private:

	// Floating point framebuffer
	GLuint m_uiFrameBuffer;

	// Color buffer
	GLuint m_uiColorBuffer;

	// Depth buffer
	GLuint m_uiDepthBuffer;

	// Vertex array object
	GLuint m_uiQuadVAO;

	// Vertex buffer object
	GLuint m_uiQuadVBO;
};

#endif // RENDERTOTEXTURE_H