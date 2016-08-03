#include "LightTechnique.h"


LightTechnique::LightTechnique(Engine::Shader* pShader)
{
	m_pShaderInstance = pShader;

	m_pointLights.reserve(MAX_POINT_LIGHTS);
	m_pointLightsLocations.reserve(MAX_POINT_LIGHTS);
}

// -------------------------------------------------------------------------

LightTechnique::~LightTechnique(void)
{
}

// -------------------------------------------------------------------------

void 
LightTechnique::SetDirectionalLight(const DirectionalLight& Light)
{
	m_pShaderInstance->Enable();

	GLint lightDirectionLoc = glGetUniformLocation(m_pShaderInstance->ProgramID(), "dirLight.lightDirection");
	GLint lightAmbientLoc = glGetUniformLocation(m_pShaderInstance->ProgramID(), "dirLight.ambientLight");
	GLint lightDiffuseLoc = glGetUniformLocation(m_pShaderInstance->ProgramID(), "dirLight.diffuseLight");
	GLint lightSpecularLoc = glGetUniformLocation(m_pShaderInstance->ProgramID(), "dirLight.specularLight");
	GLint lightSpecularIntensityLoc = glGetUniformLocation(m_pShaderInstance->ProgramID(), "dirLight.specularIntensity");

	glUniform3f(lightDirectionLoc, Light.Position.x, Light.Position.y, Light.Position.z);
	glUniform3f(lightAmbientLoc, Light.AmbientLight.x, Light.AmbientLight.y, Light.AmbientLight.z);
	glUniform3f(lightDiffuseLoc, Light.DiffuseLight.x, Light.DiffuseLight.y, Light.DiffuseLight.z);
	glUniform3f(lightSpecularLoc, Light.SpecularLight.x, Light.SpecularLight.y, Light.SpecularLight.z);
	glUniform1f(lightSpecularIntensityLoc, Light.SpecularIntensity);

	m_pShaderInstance->Disable();
}

// -------------------------------------------------------------------------

void 
LightTechnique::AddPointLight(const PointLight& Light)
{
	// Add the new light structure to the list of lights
	m_pointLights.push_back(Light);

	m_pShaderInstance->Enable();

	// Get the location for the current Light instance
	GLuint lightCount = (GLuint)(m_pointLights.size() - 1);
	std::string sLightIndex = std::to_string(lightCount);
	std::string sTemp = "pointLight[" + sLightIndex + "].";
	std::string sShaderLocation;
	
	PointLightLocation pointLightLocation;
	sShaderLocation = sTemp + "lightPosition";
	pointLightLocation.PositionLocation = glGetUniformLocation(m_pShaderInstance->ProgramID(), sShaderLocation.c_str());
	sShaderLocation = sTemp + "ambientLight";
	pointLightLocation.AmbientColorLocation = glGetUniformLocation(m_pShaderInstance->ProgramID(), sShaderLocation.c_str());
	sShaderLocation = sTemp + "diffuseLight";
	pointLightLocation.DiffuseColorLocation = glGetUniformLocation(m_pShaderInstance->ProgramID(), sShaderLocation.c_str());
	sShaderLocation = sTemp + "specularLight";
	pointLightLocation.SpecularColorLocation = glGetUniformLocation(m_pShaderInstance->ProgramID(), sShaderLocation.c_str());
	sShaderLocation = sTemp + "specularIntensity";
	pointLightLocation.SpecularIntensityLocation = glGetUniformLocation(m_pShaderInstance->ProgramID(), sShaderLocation.c_str());
	m_pointLightsLocations.push_back(pointLightLocation);

	// Send the point light parameters to the GPU
	glUniform3f(pointLightLocation.PositionLocation, Light.Position.x, Light.Position.y, Light.Position.z);
	glUniform3f(pointLightLocation.AmbientColorLocation, Light.AmbientLight.x, Light.AmbientLight.y, Light.AmbientLight.z);
	glUniform3f(pointLightLocation.DiffuseColorLocation, Light.DiffuseLight.x, Light.DiffuseLight.y, Light.DiffuseLight.z);
	glUniform3f(pointLightLocation.SpecularColorLocation, Light.SpecularLight.x, Light.SpecularLight.y, Light.SpecularLight.z);
	glUniform1f(pointLightLocation.SpecularIntensityLocation, Light.SpecularIntensity);

	m_pShaderInstance->Disable();
}

// -------------------------------------------------------------------------

void 
LightTechnique::AddSpotLight(const SpotLight& Light)
{
	m_spotLights[m_uiSpotLightCount++] = Light;

	// Set the light properties
	GLuint bindingPoint = 1;
	GLuint buffer;
	GLuint blockIndex;

	// Get the block index from the shader
	blockIndex= glGetUniformBlockIndex(m_pShaderInstance->ProgramID(),
		"SpotLight");

	// Bind the block to the binding point
	glUniformBlockBinding(m_pShaderInstance->ProgramID(), blockIndex, bindingPoint);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, buffer);

	// Set the data in the GL buffer
	glBufferData(GL_UNIFORM_BUFFER, sizeof(SpotLight), &Light, GL_DYNAMIC_DRAW);

	// Bind the GL buffer to the binding point
	glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, buffer);
}

// -------------------------------------------------------------------------

void 
LightTechnique::SetMaterial(const Material& material)
{
	m_pShaderInstance->Enable();

	// Set the material
	GLint matEmissionLoc = glGetUniformLocation(m_pShaderInstance->ProgramID(), "material.vMatEmission");
	GLint matAmbientLoc = glGetUniformLocation(m_pShaderInstance->ProgramID(), "material.vMatAmbient");
	GLint matDiffuseLoc = glGetUniformLocation(m_pShaderInstance->ProgramID(), "material.vMatDiffuse");
	GLint matSpecularLoc = glGetUniformLocation(m_pShaderInstance->ProgramID(), "material.vMatSpecular");
	GLint matShineLoc = glGetUniformLocation(m_pShaderInstance->ProgramID(), "material.fMatShineness");

	glUniform3f(matAmbientLoc, material.Ambient.x, material.Ambient.y, material.Ambient.z);
	glUniform3f(matDiffuseLoc, material.Diffuse.x, material.Diffuse.y, material.Diffuse.z);
	glUniform3f(matSpecularLoc, material.Specular.x, material.Specular.y, material.Specular.z);
	glUniform1f(matShineLoc, material.Shineness);

	m_pShaderInstance->Disable();
}

// -------------------------------------------------------------------------

void
LightTechnique::SetCubeMap(GLuint cubeMapTextureHandle)
{
	m_pShaderInstance->Enable();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureHandle);

	GLuint uiUniformCubeMapHandle = glGetUniformLocation(m_pShaderInstance->ProgramID(), "cubeMap");
	glUniform1i(uiUniformCubeMapHandle, 0);

	m_pShaderInstance->Disable();
}

// -------------------------------------------------------------------------

void LightTechnique::SetGamma(float fGamma)
{
	m_pShaderInstance->Enable();

	GLuint uiGammaLocation = glGetUniformLocation(m_pShaderInstance->ProgramID(), "gamma");
	glUniform1f(uiGammaLocation, fGamma);

	m_pShaderInstance->Disable();
}

// -------------------------------------------------------------------------

void LightTechnique::SetDisplacementMapProperties(float displacementMapScale)
{
	m_pShaderInstance->Enable();

	GLuint uiDisplacementMapScaleLocation = glGetUniformLocation(m_pShaderInstance->ProgramID(), "dispMapScale");
	glUniform1f(uiDisplacementMapScaleLocation, displacementMapScale);

	m_pShaderInstance->Disable();
}

// -------------------------------------------------------------------------

void LightTechnique::SetEyePosWorld(const glm::vec3& eyePositionWorld)
{
	m_pShaderInstance->Enable();

	GLuint uiEyePosWorldLocation = glGetUniformLocation(m_pShaderInstance->ProgramID(), "eyePosW");
	glUniform3fv(uiEyePosWorldLocation, 1, &eyePositionWorld[0]);

	m_pShaderInstance->Disable();
}

// -------------------------------------------------------------------------