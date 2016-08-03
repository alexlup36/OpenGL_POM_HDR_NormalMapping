#ifndef __SHADOWMAP_H__
#define __SHADOWMAP_H__

#include "Common.h"

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();

	void InitializeShadowMap();

private:

	GLuint m_uiDepthTexture;

	//GLuint m_
};

#endif // __SHADOWMAP_H__