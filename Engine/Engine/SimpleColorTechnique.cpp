#include "SimpleColorTechnique.h"

// ----------------------------------------------------------------------------

SimpleColorTechnique::SimpleColorTechnique()
{
}

// ----------------------------------------------------------------------------

SimpleColorTechnique::~SimpleColorTechnique()
{
}

// ----------------------------------------------------------------------------

bool SimpleColorTechnique::init()
{
	// Initialize base
	if (BaseTechnique::init() == false)
	{
		std::cout << "Failed to initialize base technique - SimpleColorTechnique. \n";
		return false;
	}

	// Add shaders
	if (addShader(GL_VERTEX_SHADER, ".\\Shaders\\colour.vert") == false)
	{
		std::cout << "Failed to add vertex shader - SimpleColorTechnique. \n";
		return false;
	}
	if (addShader(GL_FRAGMENT_SHADER, ".\\Shaders\\colour.frag") == false)
	{
		std::cout << "Failed to add fragment shader - SimpleColorTechnique. \n";
		return false;
	}

	// Link program
	if (finalize() == false)
	{
		std::cout << "Failed to link the program - SimpleColorTechnique. \n";
		return false;
	}

	// Initialize the base class - transform
	if (TransformTechnique::init() == false)
	{
		std::cout << "Failed to initialize transform technique - SimpleColorTechnique. \n";
		return false;
	}

	// Success
	return true;
}

// ----------------------------------------------------------------------------

void SimpleColorTechnique::update()
{

}

// ----------------------------------------------------------------------------