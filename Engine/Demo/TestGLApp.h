#ifndef __ABSTRACTENGINE_H__
#define __ABSTRACTENGINE_H__

#include <memory>

#include "BaseGLApp.h"
//#include "LightTechnique.h"
//#include "Skybox.h"
//#include "HDRLightingTechnique.h"
//#include "RenderToTexture.h"

// Rendering techniques
#include "PhongLightTechnique.h"
#include "PBRLightTechnique.h"

class TestGLApp : public BaseGLApp
{
public:
	TestGLApp(void);
	virtual ~TestGLApp(void);

	// Overrides
	virtual void Update(float dt);
	virtual void Draw(float dt);

	virtual int Initialize();

private:

	virtual void SetupScene();

	// Private methods
	void LoadShaders();

	// Private members

	//Skybox* m_pSkybox;

	// Shaders
	//Engine::Shader* m_pBlinnPhongShader;
	//Engine::Shader* m_pReflectionShader;
	//Engine::Shader* m_pQuadShader;
	//Engine::Shader* m_pNormalShader;
	//Engine::Shader* m_pParallaxShader;
	//Engine::Shader* m_pHDRShader;
	//Engine::Shader* m_pGBufferShaderNormal;
	//Engine::Shader* m_pGBufferShaderParallax;
	//Engine::Shader* m_pLightingPassShader;

	// Light technique
	//LightTechnique* pDirectionalLightTechnique;
	//LightTechnique* pGBufferTechniqueNormal;
	//LightTechnique* pGBufferTechniqueParallax;
	//LightTechnique* pNormalMappingTechnique;
	//LightTechnique* pParallaxMappingTechnique;
	//LightTechnique* pBlinnPhongSolidTechnique;
	//LightTechnique* pReflectionTechnique;
	//HDRLightingTechnique* pHDRLightTechnique;

	// Rendering techniques
	PhongLightTechnique* m_pPhongTechnique;
	PBRLightTechnique* m_pPBRTechnique;

	PBRMaterial m_pbrMaterial;
	PointLight m_pointLightStruct1;
	PointLight m_pointLightStruct2;

	// Render to texture for hdr
	//RenderToTexture* m_pHDRRenderToTexture;
	// Render to texture for shadow mapping
	//RenderToTexture* m_pShadowMappingRenderToTexture;

	GLuint uiFBO;
	GLuint uiRenderTexture;
	GLuint uiDepthTexture;

	// Temp gbuffer
	GLuint gBuffer;
	// Temp attachments
	GLuint gPosition, gNormal, gNormal2, gAlbedoSpec, gAlbedoSpec2;
};

#endif // __ABSTRACTENGINE_H__