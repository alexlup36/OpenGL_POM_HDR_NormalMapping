#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#define GLM_FORCE_RADIANS 1

#include "Common.h"

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
		: m_vPosition( pos ), m_vRotation( rot ), m_vScale( scale ) {}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMatrix = glm::translate( m_vPosition );

		glm::mat4 rotMatrix = glm::rotate(m_vRotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::rotate(m_vRotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::rotate(m_vRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

		glm::mat4 scaleMatrix = glm::scale( m_vScale );

		return posMatrix * rotMatrix * scaleMatrix;
	}

	inline glm::vec3& GetPos()		{ return m_vPosition; }
	inline glm::vec3& GetRotation() { return m_vRotation; }
	inline glm::vec3& GetScale()	{ return m_vScale; }

	inline void SetPos( const glm::vec3& pos )		{ m_vPosition = pos; }
	inline void SetRotation( const glm::vec3& rot )	{ m_vRotation = rot; }
	inline void SetScale( const glm::vec3& scale )	{ m_vScale = scale; }
		
	inline void SetPos( GLfloat x, GLfloat y, GLfloat z )		
	{
		m_vPosition.x = x; 
		m_vPosition.y = y; 
		m_vPosition.z = z; 
	}
	inline void SetRotation( GLfloat x, GLfloat y, GLfloat z )	
	{ 
		m_vRotation.x = x;
		m_vRotation.y = y;
		m_vRotation.z = z; 
	}
	inline void SetScale( GLfloat x, GLfloat y, GLfloat z )	
	{ 
		m_vScale.x = x; 
		m_vScale.y = y; 
		m_vScale.z = z; 
	}
protected:

private:
	glm::vec3 m_vPosition;
	glm::vec3 m_vRotation;
	glm::vec3 m_vScale;

};


#endif