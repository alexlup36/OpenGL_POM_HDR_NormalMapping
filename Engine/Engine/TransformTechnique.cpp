#include "TransformTechnique.h"

// ----------------------------------------------------------------------------

TransformTechnique::TransformTechnique()
{
}

// ----------------------------------------------------------------------------

TransformTechnique::~TransformTechnique()
{
}

// ----------------------------------------------------------------------------

bool TransformTechnique::init()
{
	// World - view - projection matrix
	m_uiWVPMatLocation = getUniformLocation("wvpMatrix");
	if (m_uiWVPMatLocation == -1)
	{
		return false;
	}

	// View matrix
	m_uiViewMatLocation = getUniformLocation("vMatrix");

	// Projection matrix
	m_uiProjectionMatLocation = getUniformLocation("pMatrix");

	// World matrix
	m_uiWMatLocation = getUniformLocation("wMatrix");

	// Normal matrix
	m_uiNMatLocation = getUniformLocation("nMatrix");

	return true;
}

// ----------------------------------------------------------------------------

void TransformTechnique::update()
{

}

// ----------------------------------------------------------------------------