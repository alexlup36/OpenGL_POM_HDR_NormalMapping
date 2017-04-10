#ifndef __CAMERA_H__
#define __CAMERA_H__

// ----------------------------------------------------------------------------

#include "Common.h"
#include <glm\gtc\matrix_transform.hpp>

#include "Input.h"

// ----------------------------------------------------------------------------

class Camera
{
public:

	// ----------------------------------------------------------------------------

	Camera(const char* cameraName);
	Camera(
		glm::vec3& position, 
		glm::vec3& target, 
		glm::vec3& up, 
		GLfloat near, 
		GLfloat far, 
		GLfloat fieldOfView,
		const char* cameraName);

	// ----------------------------------------------------------------------------

	// Initialize view matrix
	void SetView();
	// Initialize projection matrix
	void SetProjection(float fov, unsigned int width, unsigned int height, float near, float far);
	void UpdateProjection();
	void SetOrthoProjection(float left, float right, float bottom, float top, float near, float far);

	// ----------------------------------------------------------------------------
	// Getters
	const inline glm::mat4 ProjectionMatrix() const { return m_ProjectionMatrix; }
	const inline glm::mat4 ViewMatrix() const { return m_ViewMatrix; }
	const inline glm::mat4 ViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	const inline glm::vec3 GetCameraPosition() const { return m_vCameraPosition; }
	const inline glm::vec3 GetCameraTarget() const { return m_vCameraTarget; }
	const inline GLfloat GetCameraFOV() const { return m_fFOV; }

	// ----------------------------------------------------------------------------
	// Setters
	inline void SetPosition(const glm::vec3& pos) { m_vCameraPosition = pos; m_bChange = true; }
	inline void SetTarget(const glm::vec3& targ) { m_vCameraTarget = targ; m_bChange = true; }
	inline void SetCameraFOV(GLfloat fov) { m_fFOV = fov; }

	// ----------------------------------------------------------------------------

	void UpdateMatrices(float dt);
	void LoadIndentity();

	virtual ~Camera(void);

	// Camera name
	char* CameraName;

private:

	// Camera information
	GLfloat m_fNearClippingPlane;
	GLfloat m_fFarClippingPlane;
	GLfloat m_fFOV;

	glm::vec3 m_vCameraPosition;
	glm::vec3 m_vCameraTarget;
	glm::vec3 m_vCameraUp;

	// Transformation matrices
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ViewProjectionMatrix;

	// Camera orientation
	GLfloat m_fHorizontalAngle;
	GLfloat m_fVerticalAngle;

	// Time difference between two update calls
	GLfloat m_fDeltaTime;

	bool m_bChange;
};

#endif // __CAMERA_H__