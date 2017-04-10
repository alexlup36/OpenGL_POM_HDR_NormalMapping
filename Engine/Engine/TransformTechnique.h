#ifndef TRANSFORMTECHNIQUE_H
#define TRANSFORMTECHNIQUE_H

// ----------------------------------------------------------------------------

#include "BaseTechnique.h"
#include "Transform.h"

// ----------------------------------------------------------------------------

class TransformTechnique : public BaseTechnique
{
public:
	TransformTechnique();
	virtual ~TransformTechnique();

	virtual bool init() override;
	virtual void update() override;

	// Set uniforms
	const inline void setWVPMatrix(const glm::mat4& wvp) 
	{ 
		glUniformMatrix4fv(m_uiWVPMatLocation, 1, GL_FALSE, &wvp[0][0]);
	}
	const inline void setWMatrix(const glm::mat4& w)
	{
		glUniformMatrix4fv(m_uiWMatLocation, 1, GL_FALSE, &w[0][0]);
	}
	const inline void setViewMatrix(const glm::mat4& v)
	{
		glUniformMatrix4fv(m_uiViewMatLocation, 1, GL_FALSE, &v[0][0]);
	}
	const inline void setProjectionMatrix(const glm::mat4& p)
	{
		glUniformMatrix4fv(m_uiProjectionMatLocation, 1, GL_FALSE, &p[0][0]);
	}
	const inline void setNMatrix(const glm::mat4& n)
	{
		glUniformMatrix4fv(m_uiNMatLocation, 1, GL_FALSE, &n[0][0]);
	}

	// ----------------------------------------------------------------------------

private:
	GLuint m_uiWVPMatLocation;
	GLuint m_uiViewMatLocation;
	GLuint m_uiProjectionMatLocation;
	GLuint m_uiWMatLocation;
	GLuint m_uiNMatLocation;

	// ----------------------------------------------------------------------------
};

#endif // TRANSFORMTECHNIQUE_H