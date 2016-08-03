#include "CameraMan.h"

#include <iostream>

CameraMan::CameraMan(void)
{
	m_pActiveCamera = NULL;
}


CameraMan::~CameraMan(void)
{
	//std::cout << "CameraMan destructor" << std::endl;
}

// Create camera
Camera* 
CameraMan::CreateCamera(const char* camName, float fFOV, float fNearPlane, float fFarPlane)
{
	// Create a new default camera
	Camera* newCamera = new Camera(camName);

	// Set the projection matrix for the camera
	newCamera->SetProjection(fFOV, WINDOW_WIDTH, WINDOW_HEIGHT, fNearPlane, fFarPlane);

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
CameraMan::SetActiveCamera(Camera* newCamera)
{
	m_pActiveCamera = newCamera;
}

// Get the active camera
Camera* 
CameraMan::GetActiveCamera()
{
	return m_pActiveCamera;
}

// Get camera
Camera* 
CameraMan::GetCamera(const char* camName)
{
	// Iterator for the list of cameras
	std::vector<Camera*>::const_iterator camIterator = m_pCameraList.begin();

	while (camIterator != m_pCameraList.end())
	{
		if (strcmp((*camIterator)->CameraName, camName) == 0)
		{
			return *camIterator;
		}

		camIterator++;
	}

	std::cout << "Camera " << camName << "not found." << std::endl;
	return NULL;
}

Camera* 
CameraMan::GetCamera(int index)
{
	return m_pCameraList[index];
}

// Update the camera
void 
CameraMan::Update(float dt)
{
	m_pActiveCamera->UpdateMatrices(dt);
}

void 
CameraMan::UpdateCamera(float dt, const char* camName)
{
	Camera* temp = GetCamera(camName);

	if (temp != NULL)
	{
		temp->UpdateMatrices(dt);
	}
}

void 
CameraMan::UpdateCamera(float dt, int index)
{
	Camera* temp = GetCamera(index);

	if (temp != NULL)
	{
		temp->UpdateMatrices(dt);
	}
}
