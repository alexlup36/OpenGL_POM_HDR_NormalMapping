#include "CameraMan.h"

#include <iostream>

CameraMan::CameraMan(void)
{
	m_pActiveCamera = nullptr;
}


CameraMan::~CameraMan(void)
{
	//std::cout << "CameraMan destructor" << std::endl;
}

// Create camera
Camera2* 
CameraMan::CreateCamera(const char* camName, float fFOV, float fNearPlane, float fFarPlane)
{
	// Create a new default camera
	Camera2* newCamera = new Camera2(camName);

	// Set the projection matrix for the camera
	newCamera->SetProjection(fFOV, WINDOW_WIDTH, WINDOW_HEIGHT, fNearPlane, fFarPlane);
	newCamera->SetOrthoProjection(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 5.0f);

	// If no active camera set it to the new created camera
	if (!m_pActiveCamera)
	{
		m_pActiveCamera = newCamera;
	}

	// Add the new created camera to the camera list
	m_pCameraList.push_back(newCamera);

	// Camera created
	std::cout << "Camera: " << camName << " created" << std::endl;

	// Return the newly created camera
	return newCamera;
}

// Set the active camera
void 
CameraMan::SetActiveCamera(Camera2* newCamera)
{
	assert(newCamera != nullptr);
	m_pActiveCamera = newCamera;
}

// Get the active camera
Camera2* 
CameraMan::GetActiveCamera()
{
	assert(m_pActiveCamera != nullptr);
	return m_pActiveCamera;
}

// Get camera
Camera2* 
CameraMan::GetCamera(const char* camName)
{
	// Iterator for the list of cameras
	std::vector<Camera2*>::const_iterator camIterator = m_pCameraList.begin();

	while (camIterator != m_pCameraList.end())
	{
		if (strcmp((*camIterator)->CameraName, camName) == 0)
		{
			return *camIterator;
		}

		camIterator++;
	}

	std::cout << "Camera " << camName << "not found." << std::endl;
	return nullptr;
}

Camera2* 
CameraMan::GetCamera(int index)
{
	return m_pCameraList[index];
}

// Update the camera
void 
CameraMan::Update(float dt)
{
	if (m_pActiveCamera)
	m_pActiveCamera->UpdateMatrices(dt);
}

void 
CameraMan::UpdateCamera(float dt, const char* camName)
{
	Camera2* temp = GetCamera(camName);

	if (temp != nullptr)
	{
		temp->UpdateMatrices(dt);
	}
}

void 
CameraMan::UpdateCamera(float dt, int index)
{
	Camera2* temp = GetCamera(index);

	if (temp != nullptr)
	{
		temp->UpdateMatrices(dt);
	}
}
