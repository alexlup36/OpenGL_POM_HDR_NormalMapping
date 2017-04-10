#ifndef LIGHTUTIL_H
#define LIGHTUTIL_H

// -------------------------------------------------------------------------

#include "Common.h"

#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "Object.h"

// -------------------------------------------------------------------------

struct DirectionalLight
{
	size_t lightIndex;

	glm::vec3 Position;
	glm::vec3 AmbientLight; 
	glm::vec3 DiffuseLight;
	glm::vec3 SpecularLight;
	GL::Object* lightObject;

	DirectionalLight()
	{
		Position = glm::vec3(0.0f);
		AmbientLight = glm::vec3(1.0f);
		DiffuseLight = glm::vec3(1.0f);
		SpecularLight = glm::vec3(1.0f);
		lightObject = nullptr;
	}

	DirectionalLight(const glm::vec3& vDir,
		const glm::vec3& vAmbientLight,
		const glm::vec3& vDiffuseLight,
		const glm::vec3& vSpecularLight)
	{
		Position = glm::normalize(vDir);
		AmbientLight = vAmbientLight;
		DiffuseLight = vDiffuseLight;
		SpecularLight = vSpecularLight;
		lightObject = nullptr;
	}
};

// -------------------------------------------------------------------------

struct PointLight : public DirectionalLight
{
	glm::vec3 Attenuation;

	PointLight()
		: DirectionalLight()
	{
		Attenuation = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	PointLight(const glm::vec3& vPos,
		const glm::vec3& vAmbientLight,
		const glm::vec3& vDiffuseLight,
		const glm::vec3& vSpecularLight,
		const glm::vec3& vAttenuation)
		: DirectionalLight(vPos, vAmbientLight, vDiffuseLight, vSpecularLight) 
	{ 
		Attenuation = vAttenuation;
	}
};

// -------------------------------------------------------------------------

struct SpotLight : public PointLight
{
	glm::vec3 SpotLightDirection;
	float SpotLightExponent;
	float SpotLightCutoff;
	float SpotLightCosCutoff;

	SpotLight()
		: PointLight()
	{
		SpotLightDirection = glm::vec3(1.0f, 1.0f, 1.0f);
		SpotLightExponent = 0.0f;
		SpotLightCutoff = 0.0f;
		SpotLightCosCutoff = 0.0f;
	}

	SpotLight(const glm::vec3& vPos,
		const glm::vec3& vHalfVector,
		const glm::vec3& vAmbientLight,
		const glm::vec3& vDiffuseLight,
		const glm::vec3& vSpecularLight,
		const glm::vec3& vAttenuation,
		const glm::vec3& vSpotLightDirection,
		const float fSpotLightExponent,
		const float fSpotLightCutoff,
		const float fSpotLightCosCutoff)
		: PointLight(vPos, vAmbientLight, vDiffuseLight, vSpecularLight, vAttenuation)
	{
		SpotLightDirection = glm::normalize(vSpotLightDirection);
		SpotLightExponent = fSpotLightExponent;
		SpotLightCutoff = fSpotLightCutoff;
		SpotLightCosCutoff = fSpotLightCosCutoff;
	}
};

// ------------------------------------------------------------------------

struct DirectionalLightLocation
{
	GLuint DirectionLocation;
	GLuint AmbientColorLocation;
	GLuint DiffuseColorLocation;
	GLuint SpecularColorLocation;
};

struct PointLightLocation
{
	GLuint PositionLocation;
	GLuint AmbientColorLocation;
	GLuint DiffuseColorLocation;
	GLuint SpecularColorLocation;
	GLuint AttenuationLocation;
};

struct SpotLightLocation
{
	GLuint PositionLocation;
	GLuint AmbientColorLocation;
	GLuint DiffuseColorLocation;
	GLuint SpecularColorLocation;
	GLuint AttenuationLocation;
	GLuint SpotLightDirectionLocation;
	GLuint SpotLightExponentLocation;
	GLuint SpotLightCutoffLocation;
	GLuint SpotLightCosCutoffLocation;
};

// -------------------------------------------------------------------------

#endif // LIGHTUTIL_H
