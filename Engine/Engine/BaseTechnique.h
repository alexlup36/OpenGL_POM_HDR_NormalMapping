#ifndef TECHNIQUE_H
#define TECHNIQUE_H

// ----------------------------------------------------------------------------

#include "Common.h"
#include <list>

// ----------------------------------------------------------------------------

class BaseTechnique
{
public:
	BaseTechnique();
	virtual ~BaseTechnique();

	virtual bool init();
	virtual void update();
	
	const void enable() const;

	const inline GLuint getProgramID() const { return m_uiProgramID; }

protected:
	bool addShader(GLenum shaderType, const char* shaderFilePath);
	bool finalize();
	GLuint getUniformLocation(const char* uniformName);
	
	GLuint m_uiProgramID;

private:
	std::list<GLuint> m_lShaderObjects;

private:
	bool readShaderFromFile(std::string& shaderCode, const char* shaderPath);
	bool compileShader(GLuint shaderObject, std::string& shaderCode, const char* shaderFile);

};

// ----------------------------------------------------------------------------

#endif // TECHNIQUE_H