#ifndef __LIGHTTECHNIQUE_H__
#define  __LIGHTTECHNIQUE_H__

#include <vector>

#include "Common.h"

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

#define MAX_POINT_LIGHTS 2
#define MAX_SPOT_LIGHT 1

// -------------------------------------------------------------------------

struct DirectionalLight
{
	glm::vec3 Position;
	glm::vec3 AmbientLight;
	glm::vec3 DiffuseLight;
	glm::vec3 SpecularLight;
	float SpecularIntensity;

	DirectionalLight()
	{
		Position = glm::vec3(0.0f);
		AmbientLight = glm::vec3(1.0f);
		DiffuseLight = glm::vec3(1.0f);
		SpecularLight = glm::vec3(1.0f);
		SpecularIntensity = 1.0f;
	}

	DirectionalLight(const glm::vec3& vPos,
		const glm::vec3& vAmbientLight,
		const glm::vec3& vDiffuseLight,
		const glm::vec3& vSpecularLight,
		float specIntensity)
	{
		Position		= vPos;
		AmbientLight	= vAmbientLight;
		DiffuseLight	= vDiffuseLight;
		SpecularLight	= vSpecularLight;

		SpecularIntensity = specIntensity;
	}
};

// -------------------------------------------------------------------------

struct PointLight : public DirectionalLight
{
};

// -------------------------------------------------------------------------

struct SpotLight : public PointLight
{
	glm::vec3 SpotLightDirection;
	float SpotLightExponent;
	float SpotLightCutoff;
	float SpotLightCosCutoff;

	SpotLight()
	{
		SpotLightDirection	= glm::vec3(1.0f, 1.0f, 1.0f);
		SpotLightExponent	= 0.0f;
		SpotLightCutoff		= 0.0f;
		SpotLightCosCutoff	= 0.0f;
	}

	SpotLight(const glm::vec3& vPos,
		const glm::vec3& vHalfVector,
		const glm::vec3& vAmbientLight,
		const glm::vec3& vDiffuseLight,
		const glm::vec3& vSpecularLight,
		const float fConstantAttenuation,
		const float fLinearAttenuation,
		const float fQuadraticAttenuation,
		const glm::vec3& vSpotLightDirection,
		const float fSpotLightExponent,
		const float fSpotLightCutoff,
		const float fSpotLightCosCutoff)
	{
		// Call point light constructor
		/*PointLight::PointLight(vPos,
			vHalfVector,
			vAmbientLight,
			vDiffuseLight,
			vSpecularLight,
			fConstantAttenuation,
			fLinearAttenuation,
			fQuadraticAttenuation);
*/
		SpotLightDirection	= vSpotLightDirection;
		SpotLightExponent	= fSpotLightExponent;
		SpotLightCutoff		= fSpotLightCutoff;
		SpotLightCosCutoff	= fSpotLightCosCutoff;
	}
};

// -------------------------------------------------------------------------

struct Material
{
	glm::vec3 Emission;
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	float Shineness;

	Material()
	{
		Emission = glm::vec3(1.0f);
		Ambient = glm::vec3(1.0f);
		Diffuse = glm::vec3(1.0f);
		Specular = glm::vec3(1.0f);
		Shineness = 10.0f;
	}

	Material(const glm::vec3& vEmission,
		const glm::vec3& vAmbient,
		const glm::vec3 vDiffuse,
		const glm::vec3 vSpecular,
		const float fShineness)
	{
		Emission = vEmission;
		Ambient = vAmbient;
		Diffuse = vDiffuse;
		Specular = vSpecular;
		Shineness = fShineness;
	}
};

// -------------------------------------------------------------------------

struct PointLightLocation
{
	GLint PositionLocation;
	GLint AmbientColorLocation;
	GLint DiffuseColorLocation;
	GLint SpecularColorLocation;
	GLint SpecularIntensityLocation;
};

// -------------------------------------------------------------------------

class LightTechnique
{
public:
	LightTechnique(/*Shader* pShader*/);
	~LightTechnique();

	// Methods
	void SetDirectionalLight(const DirectionalLight& Light);
	void AddPointLight(const PointLight& Light);
	void AddSpotLight(const SpotLight& Light);

	void SetMaterial(const Material& material);

	void SetCubeMap(GLuint cubeMapTextureHandle);

	void SetGamma(float fGamma);
	void SetDisplacementMapProperties(float displacementMapScale);
	void SetEyePosWorld(const glm::vec3& eyePositionWorld);

private:
	//Shader* m_pShaderInstance;

	float m_fGamma;
	float m_fDisplacementMapScale;
	float m_fDisplacementMapOffset;

	// Directional light
	DirectionalLight m_directionalLight;

	// Point lights
	std::vector<PointLight> m_pointLights;
	std::vector<PointLightLocation> m_pointLightsLocations;

	SpotLight m_spotLights[MAX_SPOT_LIGHT];
	unsigned int m_uiSpotLightCount;
};

#endif // __LIGHTTECHNIQUE_H__