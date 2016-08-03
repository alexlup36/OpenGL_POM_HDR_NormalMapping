#ifndef __CAMERAMAN_H__
#define __CAMERAMAN_H__

#include "Camera.h"
#include "GameComponent.h"

#include <vector>

class CameraMan : public GameComponent
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
	Camera* CreateCamera(const char* camName, float fFOV, float fNearPlane, float fFarPlane);
	// Set the active camera
	void SetActiveCamera(Camera* newCamera);
	// Get the active camera
	Camera* GetActiveCamera();
	// Get camera
	Camera* GetCamera(const char* camName);
	Camera* GetCamera(int index);

private:
	Camera* m_pActiveCamera;

	std::vector<Camera*> m_pCameraList;
};

#endif // _CAMERAMAN_H__