#include "BaseGLApp.h"

#include "Common.h"
#include "Core.h"
#include "TextMan.h"
#include "CameraMan.h"

BaseGLApp::BaseGLApp(void)
{
	Log("BaseGLApp", "Constructor called");
}


BaseGLApp::~BaseGLApp(void)
{
	Log("BaseGLApp", "Destructor called");
}

int 
BaseGLApp::Initialize()
{
	Log("BaseGLApp", "InitializeGL called");

	// Call parent function
	Core::Initialize();

	// Initialize the text renderer
	TextMan::Instance().Initialize(".\\Assets\\Holstein.tga");

	// Success
	return 1;
}

void 
BaseGLApp::SetupScene()
{
	Log("BaseGLApp", "SetupScene called");

	// Call parent function
	Core::SetupScene();
}

void 
BaseGLApp::Update(float dt)
{
	// Call parent function
	Core::Update(dt);
}

void 
BaseGLApp::Draw(float dt)
{
	// Call parent function
	Core::Draw(dt);
}

void 
BaseGLApp::Run()
{
	
}