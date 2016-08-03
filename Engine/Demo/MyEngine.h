#ifndef __ABSTRACTENGINE_H__
#define __ABSTRACTENGINE_H__

#include "AbstractEngine.h"
#include "LightTechnique.h"
#include "Skybox.h"
#include "HDRLightingTechnique.h"
#include "RenderToTexture.h"

class MyEngine : public AbstractEngine
{
public:
	MyEngine(void);
	virtual ~MyEngine(void);

	// Overrides
	virtual void Update(float dt);
	virtual void Draw(float dt);

	virtual int Initialize();

private:

	virtual void SetupScene();

	// Private methods
	void LoadShaders();

	// Private members

	Skybox* m_pSkybox;

	// Shaders
	Engine::Shader* m_pBlinnPhongShader;
	Engine::Shader* m_pReflectionShader;
	Engine::Shader* m_pQuadShader;
	Engine::Shader* m_pNormalShader;
	Engine::Shader* m_pHDRShader;
	Engine::Shader* m_pGBufferShader;
	Engine::Shader* m_pLightingPassShader;

	// Light technique
	LightTechnique* pDirectionalLightTechnique;
	LightTechnique* pGBufferTechnique;
	LightTechnique* pNormalMappingTechnique;
	LightTechnique* pBlinnPhongSolidTechnique;
	LightTechnique* pReflectionTechnique;
	HDRLightingTechnique* pHDRLightTechnique;

	// Render to texture for hdr
	RenderToTexture* m_pHDRRenderToTexture;
	// Render to texture for shadow mapping
	RenderToTexture* m_pShadowMappingRenderToTexture;

	GLuint uiFBO;
	GLuint uiRenderTexture;
	GLuint uiDepthTexture;

	// Temp gbuffer
	GLuint gBuffer;
	// Temp attachments
	GLuint gPosition, gNormal, gAlbedoSpec;
};

#endif // __ABSTRACTENGINE_H__