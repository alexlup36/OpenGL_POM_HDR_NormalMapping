#ifndef CAMERA2_H
#define CAMERA2_H

// ----------------------------------------------------------------------------

#include "Common.h"
#include <glm\gtc\matrix_transform.hpp>

#include "Input.h"

// ----------------------------------------------------------------------------

class Camera2
{
public:

	// ----------------------------------------------------------------------------

	Camera2(const char* cameraName);
	Camera2(
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
	const inline glm::mat4 OrthoProjectionMatrix() const { return m_orthoProjectionMatrix; }
	const inline glm::mat4 ViewMatrix() const { return m_ViewMatrix; }
	const inline glm::mat4 ViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	const inline glm::vec3 GetCameraPosition() const { return m_vCameraPosition; }
	const inline glm::vec3 GetCameraDirection() const { return m_vCameraDirection; }
	const inline GLfloat GetCameraFOV() const { return m_fFOV; }

	// ----------------------------------------------------------------------------
	// Setters
	inline void SetPosition(const glm::vec3& pos) { m_vCameraPosition = pos; m_bChange = true; }
	inline void SetDirection(const glm::vec3& targ) { m_vCameraDirection = targ; m_bChange = true; }
	inline void SetCameraFOV(GLfloat fov) { m_fFOV = fov; }
	inline void NeedViewUpdate() { m_bChange = true; }

	// ----------------------------------------------------------------------------

	void UpdateMatrices(float dt);
	void LoadIndentity();

	virtual ~Camera2(void);

	// Camera name
	char* CameraName;

private:

	// Camera information
	GLfloat m_fNearClippingPlane;
	GLfloat m_fFarClippingPlane;
	GLfloat m_fFOV;

	glm::vec3 m_vCameraPosition;
	glm::vec3 m_vCameraDirection;
	glm::vec3 m_vCameraUp;

	// Transformation matrices
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_orthoProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ViewProjectionMatrix;

	// Camera orientation
	GLfloat m_fYaw;
	GLfloat m_fPitch;

	// Time difference between two update calls
	GLfloat m_fDeltaTime;

	bool m_bChange;
	bool m_bFirstUpdate;
};

#endif // CAMERA2_H