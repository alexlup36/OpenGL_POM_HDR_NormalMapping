#ifndef __RENDERINGENGINE_H__
#define __RENDERINGENGINE_H__

#include "Core.h"

//#include "TextMan.h"
#include "CameraMan.h"
//#include "ShaderMan.h"

class BaseGLApp : public Core
{
public:
	BaseGLApp(void);
	virtual ~BaseGLApp(void);

	void Run();

// Override
protected:
	virtual void Update(float dt);
	virtual void Draw(float dt);

	virtual int Initialize();
	virtual void SetupScene();

	// Member variables
};

#endif // __RENDERINGENGINE_H__

