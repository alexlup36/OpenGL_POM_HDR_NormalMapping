#ifndef __Core_H__
#define __Core_H__

#include "Shader.h"
#include "Texture.h"
#include "Transform.h"

class Core
{
public:
	Core();
	virtual ~Core();

	int Initialize();
	void SetWindowProperties(const char* windowTitle);

	static GLFWwindow* Window;
	static float KeyboardSpeed;
	static float MouseSpeed;

// Overwrite
protected:
	virtual void Update(float dt);
	virtual void Draw(float dt);

	virtual int InitializeGL();
	virtual void SetupScene();

private:
	void SetGLState();
};

#endif // __Core_H__