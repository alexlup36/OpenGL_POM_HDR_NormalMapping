#ifndef PBRTEXTECHNIQUE_H
#define PBRTEXTECHNIQUE_H

// ----------------------------------------------------------------------------

#include "LightUtil.h"
#include "TransformTechnique.h"
#include "SimpleColorTechnique.h"

#include <vector>

// ----------------------------------------------------------------------------

class PBRTexTechnique : public TransformTechnique
{
public:
	PBRTexTechnique();
	virtual ~PBRTexTechnique();

	// ------------------------------------------------------------------------

	virtual bool init() override;
	virtual void update() override;

	// ------------------------------------------------------------------------

	// Add light sources
	void addDirectionalLight(DirectionalLight& Light);
	void addPointLight(PointLight& Light);
	void addSpotLight(SpotLight& Light);

	// Set light sources
	void setDirectionalLight(const DirectionalLight& dirLight);
	void setPointLight(const PointLight& pointLight);
	void setSpotLight(const SpotLight& spotLight);

private:

	// ------------------------------------------------------------------------
	// Constants
	static const unsigned int MAX_POINT_LIGHTS = 10;
	static const unsigned int MAX_DIRECTIONAL_LIGHTS = 10;
	static const unsigned int MAX_SPOT_LIGHTS = 10;

	// ------------------------------------------------------------------------
	// Light data
	std::vector<DirectionalLight> m_vDirLights;
	std::vector<PointLight> m_vPointLights;
	std::vector<SpotLight> m_vSpotLights;

	unsigned int m_uiDirLightCount;
	unsigned int m_uiPointLightCount;
	unsigned int m_uiSpotLightCount;

	// ------------------------------------------------------------------------
	// Uniform locations
	std::vector<DirectionalLightLocation> m_vDirLightsLoc;
	std::vector<PointLightLocation> m_vPointLightsLoc;
	std::vector<SpotLightLocation> m_vSpotLightsLoc;

	GLuint m_uiEyePosWVecLoc;
	GLuint m_uiDirLightCountLoc;
	GLuint m_uiPointLightCountLoc;
	GLuint m_uiSpotLightCountLoc;

	// ------------------------------------------------------------------------
	// Mesh
	void addLightSourceMesh(PointLight* lightSource);
	SimpleColorTechnique* m_pSimpleColorTechnique;
	Material m_mat;

	// ------------------------------------------------------------------------

	// ------------------------------------------------------------------------
};

#endif // PBRTEXTECHNIQUE_H

