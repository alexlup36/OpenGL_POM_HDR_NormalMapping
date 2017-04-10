#ifndef HDRLIGHTINGTECHNIQUE_H
#define HDRLIGHTINGTECHNIQUE_H

// ----------------------------------------------------------------------------

#include "Common.h"

// ----------------------------------------------------------------------------

class HDRLightingTechnique
{
public:
	HDRLightingTechnique();
	~HDRLightingTechnique();

	void SetExposure(GLfloat exposure);
	void SetHDREnabled(GLboolean hdrEnabled);
	void SetGamma(GLfloat gamma);

private:

	// Shader locations
	GLint m_iExposureLocation;
	GLint m_iHDREnabledLocation;
	GLint m_iGammaLocation;
};

// ----------------------------------------------------------------------------

#endif // HDRLIGHTINGTECHNIQUE_H