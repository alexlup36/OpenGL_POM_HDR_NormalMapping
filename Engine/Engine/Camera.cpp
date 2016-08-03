#include "Camera.h"
#include "Core.h"

#include <iostream>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>



//***Default camera***
// Position 0.0f, 0.0f, 0.0f
// Target   1.0f, 0.0f, 1.0f
// Up		0.0f, 1.0f, 0.0f
// NearClip 0.1f
// FarClip  3000.0f
// WindowWidth Default
// WindowHeight Default
Camera::Camera(const char* cameraName)
	: m_vCameraPosition(0.0f, 0.0f, -5.0f),
	m_vCameraTarget(1.0f, 0.0f, 0.0f),
	m_vCameraUp(0.0f, 1.0f, 0.0f),
	m_fNearClippingPlane(0.1f),
	m_fFarClippingPlane(3000.0f),
	m_fFOV(45.0f)
{
	m_fHorizontalAngle = 0.0f;
	m_fVerticalAngle = 0.0f;

	CameraName = new char[strlen(cameraName) + 1];
	strcpy_s(CameraName, strlen(cameraName) + 1, cameraName);

	// Debug
	std::cout<<CameraName<<std::endl;

	SetView();
	SetProjection(m_fFOV, WINDOW_WIDTH, WINDOW_HEIGHT, m_fNearClippingPlane, m_fFarClippingPlane);

	// Set mouse position to the center of the screen
	glfwSetCursorPos(Core::Window, (double)WINDOW_WIDTH / 2, (double)WINDOW_HEIGHT / 2);
}

Camera::Camera(
		glm::vec3& position, 
		glm::vec3& target, 
		glm::vec3& up, 
		GLfloat near, 
		GLfloat far, 
		GLfloat fieldOfView,
		unsigned int windowWidth, 
		unsigned int windowHeight,
		const char* cameraName)
	: m_vCameraPosition(position),
	m_vCameraTarget(target),
	m_vCameraUp(up),
	m_fNearClippingPlane(near),
	m_fFarClippingPlane(far),
	m_fFOV(fieldOfView)
{
	m_fHorizontalAngle = 0.0f;
	m_fVerticalAngle = 0.0f;

	CameraName = new char[strlen(cameraName) + 1];
	strcpy_s(CameraName, strlen(cameraName) + 1, cameraName);

	// Debug
	std::cout<<CameraName<<std::endl;

	SetView();
	SetProjection(m_fFOV, WINDOW_WIDTH, WINDOW_HEIGHT, m_fNearClippingPlane, m_fFarClippingPlane);

	// Set mouse position to the center of the screen
	glfwSetCursorPos(Core::Window, (double)WINDOW_WIDTH / 2, (double)WINDOW_HEIGHT / 2);
}

Camera::~Camera(void)
{
	delete CameraName;
}


// Initialize view matrix
void Camera::SetView()
{
	m_ViewMatrix = glm::lookAt(this->m_vCameraPosition, this->m_vCameraTarget, this->m_vCameraUp);
}
	
// Initialize projection matrix
void Camera::SetProjection(float fov, unsigned int width, unsigned int height, float near, float far)
{
	this->m_fFOV = fov;
	this->m_fNearClippingPlane = near;
	this->m_fFarClippingPlane = far;

	// Update the projection matrix
	m_ProjectionMatrix = glm::perspective(this->m_fFOV, (float)WINDOW_WIDTH / WINDOW_HEIGHT, m_fNearClippingPlane, m_fFarClippingPlane);
}

void Camera::SetOrthoProjection(float left, float right, float bottom, float top, float near, float far)
{
	m_ProjectionMatrix = glm::ortho(left, right, bottom, top, near, far);
}

// Getters
glm::mat4 Camera::ProjectionMatrix()
{
	return m_ProjectionMatrix;
}

glm::mat4 Camera::ViewMatrix()
{
	return m_ViewMatrix;
}

glm::vec3 Camera::GetCameraPosition()
{
	return m_vCameraPosition;
}

glm::vec3 Camera::GetCameraTarget()
{
	return m_vCameraTarget;
}
	
glm::vec3 Camera::GetCameraUp()
{
	return m_vCameraUp;
}

	
// Setters
void Camera::SetPosition(const glm::vec3& pos)
{
	m_vCameraPosition = pos;
	m_bChange = true;
}
	
void Camera::SetTarget(const glm::vec3& targ)
{
	m_vCameraTarget = targ;
	m_bChange = true;
}
	
void Camera:: SetUp(const glm::vec3& up)
{
	m_vCameraUp = up;
	m_bChange = true;
}

void Camera::UpdateMatrices(float dt)
{
	// Update the mouse cursor position
	glfwGetCursorPos(Core::Window, &Input::X_MOUSEPOS, &Input::Y_MOUSEPOS);

	// Update the camera angles
	m_fHorizontalAngle += Core::MouseSpeed * dt * float(WINDOW_WIDTH / 2 - Input::X_MOUSEPOS);
	m_fVerticalAngle += Core::MouseSpeed * dt * float(WINDOW_HEIGHT / 2 - Input::Y_MOUSEPOS);

	// Debug - display camera angles
	//std::cout<<m_fHorizontalAngle<<std::endl;
	//std::cout<<m_fVerticalAngle<<std::endl;

	// Calculate the new direction, right and up vectors
	glm::vec3 direction(
		cos(m_fVerticalAngle) * sin(m_fHorizontalAngle),
		sin(m_fVerticalAngle),
		cos(m_fVerticalAngle) * cos(m_fHorizontalAngle));

	glm::vec3 right(
		sin(m_fHorizontalAngle - M_PI / 2),
		0.0f,
		cos(m_fHorizontalAngle - M_PI / 2));

	glm::vec3 up(glm::cross(right, direction));

	// Input update
	Input::Update(dt, m_vCameraPosition, direction, right);

	// Update the projection matrix
	SetProjection(m_fFOV, WINDOW_WIDTH, WINDOW_HEIGHT, m_fNearClippingPlane, m_fFarClippingPlane);

	// Update the view matrix
	m_vCameraTarget = m_vCameraPosition + direction;
	m_vCameraUp = up;

	if (m_fHorizontalAngle != 0.0f || m_fVerticalAngle != 0.0f || m_bChange)
	{
		SetView();

		m_bChange = false;
	}
}

void Camera::LoadIndentity()
{
	m_ProjectionMatrix = glm::mat4(1.0f);
	m_ViewMatrix = glm::mat4(1.0f);
}