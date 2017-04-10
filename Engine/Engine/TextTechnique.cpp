#include "TextTechnique.h"

// ----------------------------------------------------------------------------

TextTechnique::TextTechnique()
{
}

// ----------------------------------------------------------------------------

TextTechnique::~TextTechnique()
{
}

// ----------------------------------------------------------------------------

bool TextTechnique::init()
{
	// Initialize base
	if (BaseTechnique::init() == false)
	{
		std::cout << "Failed to initialize base technique - TextTechnique. \n";
		return false;
	}

	// Add shaders
	if (addShader(GL_VERTEX_SHADER, ".\\Shaders\\text.vert") == false)
	{
		std::cout << "Failed to add vertex shader - TextTechnique. \n";
		return false;
	}
	if (addShader(GL_FRAGMENT_SHADER, ".\\Shaders\\text.frag") == false)
	{
		std::cout << "Failed to add fragment shader - TextTechnique. \n";
		return false;
	}

	// Link program
	if (finalize() == false)
	{
		std::cout << "Failed to link the program - TextTechnique. \n";
		return false;
	}

	// Success
	return true;
}

// ----------------------------------------------------------------------------

void TextTechnique::update()
{

}

// ----------------------------------------------------------------------------