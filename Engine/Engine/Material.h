#ifndef MATERIAL_H
#define MATERIAL_H

// ------------------------------------------------------------------------

#include <glm/glm.hpp>
#include "Common.h"

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

// ------------------------------------------------------------------------

struct PBRMaterial
{
	glm::vec3 albedo;
	float metallic;
	float roughness;
	float ao;

	PBRMaterial()
	{
		albedo = glm::vec3(1.0f, 0.0f, 0.0f);
		metallic = 0.0f;
		roughness = 0.0f;
		ao = 0.0f;
	}

	PBRMaterial(const glm::vec3& vAlbedo,
		float metal,
		float rough,
		float ambientoc)
	{
		albedo = vAlbedo;
		metallic = metal;
		roughness = rough;
		ao = ambientoc;
	}
};

struct PBRTexMaterial
{
	Texture* albedoTexture;
	Texture* pbrTexture;
	Texture* normalTexture;
	Texture* displacementTexture;
	float displacementMapScale;

	PBRTexMaterial()
		: albedoTexture(nullptr),
		pbrTexture(nullptr),
		normalTexture(nullptr),
		displacementTexture(nullptr),
		displacementMapScale(1.0f) {}

	PBRTexMaterial(Texture* albedo, 
		Texture* pbr,
		Texture* normal, 
		Texture* displacement,
		float dispScale)
		: albedoTexture(albedo),
		pbrTexture(pbr),
		normalTexture(normal),
		displacementTexture(displacement),
		displacementMapScale(dispScale) {}

};

// ------------------------------------------------------------------------

#endif // MATERIAL_H
