#include "PBRTexTechnique.h"
#include "CameraMan.h"
#include "TechniqueMan.h"
#include "ObjectMan.h"

#include <string>

// ----------------------------------------------------------------------------

PBRTexTechnique::PBRTexTechnique()
	: m_uiDirLightCount(0), m_uiPointLightCount(0), m_uiSpotLightCount(0)
{
	// Allocate space for the light data and light data uniform locations
	m_vDirLights.reserve(MAX_DIRECTIONAL_LIGHTS);
	m_vPointLights.reserve(MAX_POINT_LIGHTS);
	m_vSpotLights.reserve(MAX_SPOT_LIGHTS);

	m_vDirLightsLoc.reserve(MAX_DIRECTIONAL_LIGHTS);
	m_vPointLightsLoc.reserve(MAX_POINT_LIGHTS);
	m_vSpotLights.reserve(MAX_SPOT_LIGHTS);
}

// ----------------------------------------------------------------------------

PBRTexTechnique::~PBRTexTechnique()
{
}

// ----------------------------------------------------------------------------

bool PBRTexTechnique::init()
{
	// Initialize base
	if (BaseTechnique::init() == false)
	{
		std::cout << "Failed to initialize base technique - PBRTexTechnique. \n";
		return false;
	}

	// Add shaders
	if (addShader(GL_VERTEX_SHADER, ".\\Shaders\\pbrTex.vert") == false)
	{
		std::cout << "Failed to add vertex shader - PBRTexTechnique. \n";
		return false;
	}
	if (addShader(GL_FRAGMENT_SHADER, ".\\Shaders\\pbrTex.frag") == false)
	{
		std::cout << "Failed to add fragment shader - PBRTexTechnique. \n";
		return false;
	}

	// Link program
	if (finalize() == false)
	{
		std::cout << "Failed to link the program - PBRTexTechnique. \n";
		return false;
	}

	// Get uniform locations
	m_uiEyePosWVecLoc = getUniformLocation("eyePosW");
	m_uiDirLightCountLoc = getUniformLocation("dirLightCount");
	m_uiPointLightCountLoc = getUniformLocation("pointLightCount");
	m_uiSpotLightCountLoc = getUniformLocation("spotLightCount");

	// Initialize the base class - transform
	if (TransformTechnique::init() == false)
	{
		std::cout << "Failed to initialize transform technique - PBRTexTechnique. \n";
		return false;
	}

	m_pSimpleColorTechnique = new SimpleColorTechnique();
	if (m_pSimpleColorTechnique->init() == false)
	{
		std::cout << "Failed to init SimpleColorTechnique from PBRTexTechnique. \n";
		return false;
	}
	else
	{
		// Add technique to the tech manager
		TechniqueMan::Instance().registerTechnique(m_pSimpleColorTechnique);
	}

	// Success
	return true;
}

// ----------------------------------------------------------------------------

void PBRTexTechnique::update()
{
	// Get active camera
	Camera2* activeCamera = CameraMan::Instance().GetActiveCamera();
	// Update camera position
	glm::vec3 cameraPosition = activeCamera->GetCameraPosition();
	glUniform3f(m_uiEyePosWVecLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);
}

// ----------------------------------------------------------------------------

void PBRTexTechnique::addDirectionalLight(DirectionalLight& dirLight)
{
	// Add light source to dir light vector list
	m_vDirLights.push_back(dirLight);
	++m_uiDirLightCount;

	// Enable shader program
	enable();

	// Get the location for the current light uniform
	GLuint lightCount = (GLuint)(m_vDirLights.size() - 1);
	std::string sLightIndex = std::to_string(lightCount);
	std::string sTemp = "dirLight[" + sLightIndex + "].";
	std::string sShaderLocation;

	// Init dir light location structure
	DirectionalLightLocation directionalLightLocation;
	memset(&directionalLightLocation, 0, sizeof(DirectionalLightLocation));

	sShaderLocation = sTemp + "lightDirection";
	directionalLightLocation.DirectionLocation = getUniformLocation(sShaderLocation.c_str());
	sShaderLocation = sTemp + "ambientLight";
	directionalLightLocation.AmbientColorLocation = getUniformLocation(sShaderLocation.c_str());
	sShaderLocation = sTemp + "diffuseLight";
	directionalLightLocation.DiffuseColorLocation = getUniformLocation(sShaderLocation.c_str());
	sShaderLocation = sTemp + "specularLight";
	directionalLightLocation.SpecularColorLocation = getUniformLocation(sShaderLocation.c_str());

	// Store directional light uniform location
	m_vDirLightsLoc.push_back(directionalLightLocation);

	// Update dir light count
	glUniform1i(m_uiDirLightCountLoc, m_uiDirLightCount);

	// Set light index
	dirLight.lightIndex = lightCount;

	// Set uniform directional light
	setDirectionalLight(dirLight);
}

// ----------------------------------------------------------------------------

void PBRTexTechnique::addPointLight(PointLight& pointLight)
{
	// Add light source to point light vector list
	m_vPointLights.push_back(pointLight);
	++m_uiPointLightCount;

	// Enable shader program
	enable();

	// Get the location for the current light uniform
	GLuint lightCount = (GLuint)(m_vPointLights.size() - 1);
	std::string sLightIndex = std::to_string(lightCount);
	std::string sTemp = "pointLight[" + sLightIndex + "].";
	std::string sShaderLocation;

	// Init dir light location structure
	PointLightLocation pointLightLocation;
	memset(&pointLightLocation, 0, sizeof(PointLightLocation));

	sShaderLocation = sTemp + "lightPosition";
	pointLightLocation.PositionLocation = getUniformLocation(sShaderLocation.c_str());
	sShaderLocation = sTemp + "ambientLight";
	pointLightLocation.AmbientColorLocation = getUniformLocation(sShaderLocation.c_str());
	sShaderLocation = sTemp + "diffuseLight";
	pointLightLocation.DiffuseColorLocation = getUniformLocation(sShaderLocation.c_str());
	sShaderLocation = sTemp + "specularLight";
	pointLightLocation.SpecularColorLocation = getUniformLocation(sShaderLocation.c_str());
	sShaderLocation = sTemp + "attenuation";
	pointLightLocation.AttenuationLocation = getUniformLocation(sShaderLocation.c_str());

	// Store point light uniform location
	m_vPointLightsLoc.push_back(pointLightLocation);

	// Update point light count
	glUniform1i(m_uiPointLightCountLoc, m_uiPointLightCount);

	// Set light index
	pointLight.lightIndex = lightCount;

	// Set uniform point light
	setPointLight(pointLight);

	// Create mesh representation of the light source
	addLightSourceMesh(&pointLight);

	// Transform the mesh
	pointLight.lightObject->Translate(pointLight.Position.x,
		pointLight.Position.y,
		pointLight.Position.z);
}

// ----------------------------------------------------------------------------

void PBRTexTechnique::addSpotLight(SpotLight& spotLight)
{
	// Add light source to point light vector list
	m_vSpotLights.push_back(spotLight);
	++m_uiSpotLightCount;

	// Enable shader program
	enable();

	// Get the location for the current light uniform
	GLuint lightCount = (GLuint)(m_vSpotLights.size() - 1);
	GLuint lightIndex = lightCount + 1;
	std::string sLightIndex = std::to_string(lightCount);
	std::string sTemp = "spotLight[" + sLightIndex + "].";
	std::string sShaderLocation;

	// Init dir light location structure
	SpotLightLocation spotLightLocation;
	memset(&spotLightLocation, 0, sizeof(SpotLightLocation));

	sShaderLocation = sTemp + "lightPosition";
	spotLightLocation.PositionLocation = getUniformLocation(sShaderLocation.c_str());
	sShaderLocation = sTemp + "ambientLight";
	spotLightLocation.AmbientColorLocation = getUniformLocation(sShaderLocation.c_str());
	sShaderLocation = sTemp + "diffuseLight";
	spotLightLocation.DiffuseColorLocation = getUniformLocation(sShaderLocation.c_str());
	sShaderLocation = sTemp + "specularLight";
	spotLightLocation.SpecularColorLocation = getUniformLocation(sShaderLocation.c_str());
	sShaderLocation = sTemp + "spotLightDirection";
	spotLightLocation.SpotLightDirectionLocation = getUniformLocation(sShaderLocation.c_str());
	sShaderLocation = sTemp + "spotLightExponent";
	spotLightLocation.SpotLightExponentLocation = getUniformLocation(sShaderLocation.c_str());
	sShaderLocation = sTemp + "spotLightCutoff";
	spotLightLocation.SpotLightCutoffLocation = getUniformLocation(sShaderLocation.c_str());
	sShaderLocation = sTemp + "spotLightCosCutoff";
	spotLightLocation.SpotLightCosCutoffLocation = getUniformLocation(sShaderLocation.c_str());

	// Store spot light uniform location
	m_vSpotLightsLoc.push_back(spotLightLocation);

	// Update spot light count
	glUniform1i(m_uiSpotLightCountLoc, m_uiSpotLightCount);

	// Set light index
	spotLight.lightIndex = lightIndex;

	// Set uniform spot light
	setSpotLight(spotLight);
}

// ----------------------------------------------------------------------------

void PBRTexTechnique::setDirectionalLight(const DirectionalLight& dirLight)
{
	assert(dirLight.lightIndex < m_vDirLights.size());

	// Enable shader program
	enable();

	// Update light source inside vector
	m_vDirLights[dirLight.lightIndex] = dirLight;

	// Get uniform location
	DirectionalLightLocation& dirLightLocation = m_vDirLightsLoc[dirLight.lightIndex];

	// Set uniform directional light
	glUniform3f(dirLightLocation.DirectionLocation, dirLight.Position.x, dirLight.Position.y, dirLight.Position.z);
	glUniform3f(dirLightLocation.AmbientColorLocation, dirLight.AmbientLight.x, dirLight.AmbientLight.y, dirLight.AmbientLight.z);
	glUniform3f(dirLightLocation.DiffuseColorLocation, dirLight.DiffuseLight.x, dirLight.DiffuseLight.y, dirLight.DiffuseLight.z);
	glUniform3f(dirLightLocation.SpecularColorLocation, dirLight.SpecularLight.x, dirLight.SpecularLight.y, dirLight.SpecularLight.z);

	// Transform directional light mesh (direction)
	if (dirLight.lightObject != nullptr)
	{
		dirLight.lightObject->Translate(dirLight.Position.x,
			dirLight.Position.y,
			dirLight.Position.z);
	}
}

// ----------------------------------------------------------------------------

void PBRTexTechnique::setPointLight(const PointLight& pointLight)
{
	assert(pointLight.lightIndex < m_vPointLightsLoc.size());

	// Enable shader program
	enable();

	// Update light source inside vector
	m_vPointLights[pointLight.lightIndex] = pointLight;

	// Get uniform location
	PointLightLocation& pointLightLocation = m_vPointLightsLoc[pointLight.lightIndex];

	// Set uniform point light
	glUniform3f(pointLightLocation.PositionLocation, pointLight.Position.x, pointLight.Position.y, pointLight.Position.z);
	glUniform3f(pointLightLocation.AmbientColorLocation, pointLight.AmbientLight.x, pointLight.AmbientLight.y, pointLight.AmbientLight.z);
	glUniform3f(pointLightLocation.DiffuseColorLocation, pointLight.DiffuseLight.x, pointLight.DiffuseLight.y, pointLight.DiffuseLight.z);
	glUniform3f(pointLightLocation.SpecularColorLocation, pointLight.SpecularLight.x, pointLight.SpecularLight.y, pointLight.SpecularLight.z);
	glUniform3f(pointLightLocation.AttenuationLocation, pointLight.Attenuation.x, pointLight.Attenuation.y, pointLight.Attenuation.z);

	// Transform point light mesh
	if (pointLight.lightObject != nullptr)
	{
		pointLight.lightObject->Translate(pointLight.Position.x,
			pointLight.Position.y,
			pointLight.Position.z);
	}
}

// ----------------------------------------------------------------------------

void PBRTexTechnique::setSpotLight(const SpotLight& spotLight)
{
	assert(spotLight.lightIndex < m_vSpotLightsLoc.size());

	// Enable shader program
	enable();

	// Update light source inside vector
	m_vSpotLights[spotLight.lightIndex] = spotLight;

	// Get uniform location
	SpotLightLocation& spotLightLocation = m_vSpotLightsLoc[spotLight.lightIndex];

	// Set uniform spot light
	glUniform3f(spotLightLocation.PositionLocation, spotLight.Position.x, spotLight.Position.y, spotLight.Position.z);
	glUniform3f(spotLightLocation.AmbientColorLocation, spotLight.AmbientLight.x, spotLight.AmbientLight.y, spotLight.AmbientLight.z);
	glUniform3f(spotLightLocation.DiffuseColorLocation, spotLight.DiffuseLight.x, spotLight.DiffuseLight.y, spotLight.DiffuseLight.z);
	glUniform3f(spotLightLocation.SpecularColorLocation, spotLight.SpecularLight.x, spotLight.SpecularLight.y, spotLight.SpecularLight.z);
	glUniform3f(spotLightLocation.SpotLightDirectionLocation, spotLight.SpotLightDirection.x, spotLight.SpotLightDirection.y, spotLight.SpotLightDirection.z);
	glUniform1f(spotLightLocation.SpotLightExponentLocation, spotLight.SpotLightExponent);
	glUniform1f(spotLightLocation.SpotLightCutoffLocation, spotLight.SpotLightCutoff);
	glUniform1f(spotLightLocation.SpotLightCosCutoffLocation, spotLight.SpotLightCosCutoff);

	// Transform the spot light mesh
	if (spotLight.lightObject != nullptr)
	{
		spotLight.lightObject->Translate(spotLight.Position.x,
			spotLight.Position.y,
			spotLight.Position.z);
	}
}

// ----------------------------------------------------------------------------

void PBRTexTechnique::addLightSourceMesh(PointLight* lightSource)
{
	// Build point light object name
	GLuint lightCount = (GLuint)(m_vPointLights.size() - 1);
	std::string sPointLightObjectName = "pointLightPBRMesh" + std::to_string(lightCount);

	// Create object
	GL::Object* pointLightObject = new GL::Object(sPointLightObjectName,
		".\\Assets\\planet.obj",
		m_pSimpleColorTechnique,
		&m_mat);
	pointLightObject->Translate(lightSource->Position.x,
		lightSource->Position.y,
		lightSource->Position.z);

	lightSource->lightObject = pointLightObject;

	// Add object to scene
	ObjectMan::GetInstance().addObject(pointLightObject);
}

// ----------------------------------------------------------------------------