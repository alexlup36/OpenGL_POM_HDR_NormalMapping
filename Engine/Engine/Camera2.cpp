#include "Camera2.h"
#include "Core.h"

#include <iostream>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

// ----------------------------------------------------------------------------

//***Default camera***
// Position 0.0f, 0.0f, 0.0f
// Target   1.0f, 0.0f, 1.0f
// Up		0.0f, 1.0f, 0.0f
// NearClip 0.1f
// FarClip  3000.0f
// WindowWidth Default
// WindowHeight Default
Camera2::Camera2(const char* cameraName)
	: m_vCameraPosition(0.0f, 0.0f, 50.0f),
	m_vCameraDirection(0.0f, 0.0f, -1.0f),
	m_vCameraUp(0.0f, 1.0f, 0.0f),
	m_fNearClippingPlane(0.1f),
	m_fFarClippingPlane(3000.0f),
	m_fFOV(45.0f)
{
	m_bFirstUpdate = true;

	m_fYaw = -90.0f;
	m_fPitch = 0.0f;

	CameraName = new char[strlen(cameraName) + 1];
	strcpy_s(CameraName, strlen(cameraName) + 1, cameraName);

	LoadIndentity();
	SetProjection(m_fFOV, WINDOW_WIDTH, WINDOW_HEIGHT, m_fNearClippingPlane, m_fFarClippingPlane);
	SetOrthoProjection(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
}

// ----------------------------------------------------------------------------

Camera2::Camera2(
	glm::vec3& position,
	glm::vec3& target,
	glm::vec3& up,
	GLfloat near,
	GLfloat far,
	GLfloat fieldOfView,
	const char* cameraName)
	: m_vCameraPosition(position),
	m_vCameraDirection(target),
	m_vCameraUp(up),
	m_fNearClippingPlane(near),
	m_fFarClippingPlane(far),
	m_fFOV(fieldOfView)
{
	m_bFirstUpdate = true;

	m_fYaw = -90.0f;
	m_fPitch = 0.0f;

	CameraName = new char[strlen(cameraName) + 1];
	strcpy_s(CameraName, strlen(cameraName) + 1, cameraName);

	LoadIndentity();
	SetProjection(m_fFOV, WINDOW_WIDTH, WINDOW_HEIGHT, m_fNearClippingPlane, m_fFarClippingPlane);
	SetOrthoProjection(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
}

// ----------------------------------------------------------------------------

Camera2::~Camera2(void)
{
	delete CameraName;
}

// ----------------------------------------------------------------------------

// Initialize view matrix
void Camera2::SetView()
{
	m_ViewMatrix = glm::lookAt(this->m_vCameraPosition, 
		this->m_vCameraDirection + this->m_vCameraPosition, 
		this->m_vCameraUp);
}

// ----------------------------------------------------------------------------

// Initialize projection matrix
void Camera2::SetProjection(float fov, unsigned int width, unsigned int height, float near, float far)
{
	this->m_fFOV = fov;
	this->m_fNearClippingPlane = near;
	this->m_fFarClippingPlane = far;
	UpdateProjection();
}

// ----------------------------------------------------------------------------

void Camera2::UpdateProjection()
{
	m_ProjectionMatrix = glm::perspective(glm::radians(this->m_fFOV), (float)WINDOW_WIDTH / WINDOW_HEIGHT, m_fNearClippingPlane, m_fFarClippingPlane);
}

// ----------------------------------------------------------------------------

void Camera2::SetOrthoProjection(float left, float right, float bottom, float top, float near, float far)
{
	m_orthoProjectionMatrix = glm::ortho(left, right, bottom, top, near, far);
}

// ----------------------------------------------------------------------------

void Camera2::UpdateMatrices(float dt)
{
	// Update the mouse cursor position
	glfwGetCursorPos(Core::Window, &Input::X_MOUSEPOS, &Input::Y_MOUSEPOS);

	// Get current mouse position
	float fMousePosX = static_cast<float>(Input::X_MOUSEPOS);
	float fMousePosY = static_cast<float>(Input::Y_MOUSEPOS);
	// Calculate horizontal and vertical offset
	float xOffset = fMousePosX - WINDOW_WIDTH * 0.5f;
	float yOffset = WINDOW_HEIGHT * 0.5f - fMousePosY;
	// Scale offset by mouse sensitivity
	xOffset *= Core::MouseSpeed;
	yOffset *= Core::MouseSpeed;
	// Update the camera angles
	m_fYaw += xOffset;
	m_fPitch += yOffset;
	// Limit the angles
	if (m_fPitch > 89.0f) m_fPitch = 89.0f;
	if (m_fPitch < -89.0f) m_fPitch = -89.0f;

	// Calculate the new direction, right and up vectors
	m_vCameraDirection = glm::normalize(glm::vec3(
		cos(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch)),
		sin(glm::radians(m_fPitch)),
		sin(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch))));

	// Camera right vector
	glm::vec3 right = glm::normalize(glm::cross(m_vCameraDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
	// Camera up vector
	m_vCameraUp = glm::normalize(glm::cross(right, m_vCameraDirection));

	// Input update
	Input::Update(dt, m_vCameraPosition, m_vCameraDirection, right);

	if (xOffset != 0.0f || yOffset != 0.0f || m_bChange)
	{
		SetView();
		m_bChange = false;

		// Update view-projection matrix
		m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
	}

	// ------------------------------------------------------------------------
	// Debug

	/*static int updateCount = 0;
	updateCount++;
	if (updateCount > 100)
	{
		std::cout << "Cursor position x: " << fMousePosX << "; Cursor position y: " << fMousePosY << "\n";
		std::cout << "Mouse offset x: " << xOffset << "; Mouse offset y: " << yOffset << "\n";
		std::cout << "Camera position: " << m_vCameraPosition.x << ", " << m_vCameraPosition.y << ", " << m_vCameraPosition.z << std::endl;
		std::cout << "Camera direction: " << m_vCameraDirection.x << ", " << m_vCameraDirection.y << ", " << m_vCameraDirection.z << std::endl;
		std::cout << "Camera up: " << m_vCameraUp.x << ", " << m_vCameraUp.y << ", " << m_vCameraUp.z << std::endl;
		std::cout << "Yaw: " << m_fYaw << "; Pitch: " << m_fPitch << "\n";
		std::cout << "\n";
		
		updateCount = 0;
	}*/

	// ------------------------------------------------------------------------
}

// ----------------------------------------------------------------------------

void Camera2::LoadIndentity()
{
	m_ProjectionMatrix = glm::mat4(1.0f);
	m_ViewMatrix = glm::mat4(1.0f);
	m_orthoProjectionMatrix = glm::mat4(1.0f);
}

// ----------------------------------------------------------------------------