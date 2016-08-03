#ifndef HDRLIGHTINGTECHNIQUE_H
#define HDRLIGHTINGTECHNIQUE_H

// ----------------------------------------------------------------------------

#include "Common.h"
#include "Shader.h"

// ----------------------------------------------------------------------------

class HDRLightingTechnique
{
public:
	HDRLightingTechnique(Engine::Shader* shader);
	~HDRLightingTechnique();

	void SetExposure(GLfloat exposure);
	void SetHDREnabled(GLboolean hdrEnabled);
	void SetGamma(GLfloat gamma);

private:

	// Current shader instance
	Engine::Shader* m_pCurrentShaderInstance;

	// Shader locations
	GLint m_iExposureLocation;
	GLint m_iHDREnabledLocation;
	GLint m_iGammaLocation;
};

// ----------------------------------------------------------------------------

#endif // HDRLIGHTINGTECHNIQUE_H