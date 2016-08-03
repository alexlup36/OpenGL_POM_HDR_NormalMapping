#include "HDRLightingTechnique.h"

// ----------------------------------------------------------------------------

HDRLightingTechnique::HDRLightingTechnique(Engine::Shader* shader)
{
	m_pCurrentShaderInstance = shader;

	m_iExposureLocation = -1;
	m_iHDREnabledLocation = -1;
	m_iGammaLocation = -1;
}

// ----------------------------------------------------------------------------

HDRLightingTechnique::~HDRLightingTechnique()
{
}

// ----------------------------------------------------------------------------

void HDRLightingTechnique::SetExposure(GLfloat exposure)
{
	m_pCurrentShaderInstance->Enable();

	if (m_iExposureLocation != -1)
	{
		glUniform1f(m_iExposureLocation, exposure);
	}
	else
	{
		m_iExposureLocation = glGetUniformLocation(m_pCurrentShaderInstance->ProgramID(), "exposure");
		if (m_iExposureLocation != -1)
		{
			glUniform1f(m_iExposureLocation, exposure);
		}
		else
		{
			std::cout << "Failed to get the location of the exposure uniform." << std::endl;
		}
	}

	m_pCurrentShaderInstance->Disable();
}

// ----------------------------------------------------------------------------

void HDRLightingTechnique::SetHDREnabled(GLboolean hdrEnabled)
{
	m_pCurrentShaderInstance->Enable();

	if (m_iHDREnabledLocation != -1)
	{
		glUniform1i(m_iHDREnabledLocation, hdrEnabled);
	}
	else
	{
		m_iHDREnabledLocation = glGetUniformLocation(m_pCurrentShaderInstance->ProgramID(), "hdrEnabled");
		if (m_iHDREnabledLocation != -1)
		{
			glUniform1i(m_iHDREnabledLocation, hdrEnabled);
		}
		else
		{
			std::cout << "Failed to get the location of the hdr enabled uniform." << std::endl;
		}
	}

	m_pCurrentShaderInstance->Disable();
}

// ----------------------------------------------------------------------------

void HDRLightingTechnique::SetGamma(GLfloat gamma)
{
	m_pCurrentShaderInstance->Enable();

	if (m_iGammaLocation != -1)
	{
		glUniform1f(m_iGammaLocation, gamma);
	}
	else
	{
		m_iGammaLocation = glGetUniformLocation(m_pCurrentShaderInstance->ProgramID(), "gamma");
		if (m_iGammaLocation != -1)
		{
			glUniform1f(m_iGammaLocation, gamma);
		}
		else
		{
			std::cout << "Failed to get the location of the gamma uniform." << std::endl;
		}
	}

	m_pCurrentShaderInstance->Disable();
}

// ----------------------------------------------------------------------------