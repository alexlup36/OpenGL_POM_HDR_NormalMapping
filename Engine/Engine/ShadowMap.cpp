#include "ShadowMap.h"


ShadowMap::ShadowMap()
{
	m_uiDepthTexture = 0;
}


ShadowMap::~ShadowMap()
{
}

void ShadowMap::InitializeShadowMap()
{
	// Create a depth texture
	glGenTextures(1, &m_uiDepthTexture);
	glBindTexture(GL_TEXTURE_2D, m_uiDepthTexture);

	// Allocate storage for the texture data
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32)





}
