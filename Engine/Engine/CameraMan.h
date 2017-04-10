#ifndef __CAMERAMAN_H__
#define __CAMERAMAN_H__

#include "Camera2.h"

#include <vector>

class CameraMan
{
private:
	CameraMan(void);
	~CameraMan(void);
public:
	
	// Static access function
	static CameraMan& Instance()
	{
		static CameraMan refInstance;

		return refInstance;
	}
	
	// Override -----------------------------------------------
	void Update(float dt);

	// Specific -----------------------------------------------
	void UpdateCamera(float dt, const char* camName);
	void UpdateCamera(float dt, int index);

	// Create camera
	Camera2* CreateCamera(const char* camName, float fFOV, float fNearPlane, float fFarPlane);
	// Set the active camera
	void SetActiveCamera(Camera2* newCamera);
	// Get the active camera
	Camera2* GetActiveCamera();
	// Get camera
	Camera2* GetCamera(const char* camName);
	Camera2* GetCamera(int index);

private:
	Camera2* m_pActiveCamera;

	std::vector<Camera2*> m_pCameraList;
};

#endif // _CAMERAMAN_H__