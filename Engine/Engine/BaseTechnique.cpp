#include "BaseTechnique.h"

#include <string>
#include <fstream>
#include <vector>

// ----------------------------------------------------------------------------

BaseTechnique::BaseTechnique()
	: m_uiProgramID(-1)
{
}

// ----------------------------------------------------------------------------

BaseTechnique::~BaseTechnique()
{
	// Delete all the shader objects
	for (auto shaderObject : m_lShaderObjects)
	{
		glDeleteShader(shaderObject);
	}
	// Delete the shader program
	if (m_uiProgramID != 0)
	{
		glDeleteProgram(m_uiProgramID);
		m_uiProgramID = 0;
	}
}

// ----------------------------------------------------------------------------

bool BaseTechnique::init()
{
	// Create shader program
	m_uiProgramID = glCreateProgram();
	if (m_uiProgramID == 0)
	{
		std::cout << "Failed to create GL program. \n";
		return false;
	}

	return true;
}

// ----------------------------------------------------------------------------

void BaseTechnique::update()
{

}

// ----------------------------------------------------------------------------

const void BaseTechnique::enable() const
{
	glUseProgram(m_uiProgramID);
}

// ----------------------------------------------------------------------------

bool BaseTechnique::addShader(GLenum shaderType, const char* shaderFilePath)
{
	// Read the shader source from the file
	std::string shaderSource;
	if (readShaderFromFile(shaderSource, shaderFilePath) == true)
	{
		// Create shader object
		GLuint shaderObject = glCreateShader(shaderType);

		// Add shader object to the shader object list
		m_lShaderObjects.push_back(shaderObject);

		assert(shaderObject != 0);

		// Compile shader
		compileShader(shaderObject, shaderSource, shaderFilePath);

		// Attach the shader to the program
		glAttachShader(m_uiProgramID, shaderObject);
	}
	else
	{
		std::cout << "Failed to read shader source: " << shaderFilePath << "\n";
		return false;
	}

	return true;
}

// ----------------------------------------------------------------------------
	
bool BaseTechnique::finalize()
{
	GLint result = GL_FALSE;
	int infoLogLength;

	glLinkProgram(m_uiProgramID);

	// Check the program
	glGetProgramiv(m_uiProgramID, GL_LINK_STATUS, &result);
	glGetProgramiv(m_uiProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 1)
	{
		std::vector<char> programErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(m_uiProgramID, infoLogLength, nullptr, &programErrorMessage[0]);
		printf("%s\n", &programErrorMessage[0]);
	}
	printf("\n");

	// Delete all the shader objects
	for (auto shaderObject : m_lShaderObjects)
	{
		glDeleteShader(shaderObject);
	}

	return (result == GL_TRUE) ? true : false;
}

// ----------------------------------------------------------------------------
	
GLuint BaseTechnique::getUniformLocation(const char* uniformName)
{
	GLuint location = glGetUniformLocation(m_uiProgramID, uniformName);

	if (location == -1) 
	{
		std::cout << "Unable to get the location of uniform: " << uniformName << "\n";
		return -1;
	}

	return location;
}

// ----------------------------------------------------------------------------

bool BaseTechnique::readShaderFromFile(std::string& shaderCode, const char* shaderPath)
{
	std::ifstream vertexShaderStream(shaderPath, std::ios::in);

	if (vertexShaderStream.is_open())
	{
		std::string line = "";
		while (getline(vertexShaderStream, line))
			shaderCode += "\n" + line;
		vertexShaderStream.close();
	}
	else
	{
		std::cout << "Failed to open %s." << shaderPath << std::endl;
		return false;
	}

	return true;
}

// ----------------------------------------------------------------------------

bool BaseTechnique::compileShader(GLuint shaderObject, std::string& shaderCode, const char* shaderFile)
{
	GLint result = GL_FALSE;
	int infoLogLength;

	// Compile Shader
	std::cout << "Compiling shader :" << shaderFile << ".\n";
	char const* src = shaderCode.c_str();
	glShaderSource(shaderObject, 1, &src, nullptr);
	glCompileShader(shaderObject);

	// Check Shader
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 1)
	{
		std::vector<char> shaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(shaderObject, infoLogLength, nullptr, &shaderErrorMessage[0]);
		printf("%s\n", &shaderErrorMessage[0]);
	}

	return (result == GL_TRUE) ? true : false;
}

// ----------------------------------------------------------------------------