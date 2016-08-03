#include "AbstractEngine.h"

#include "Common.h"
#include "Core.h"
#include "TextMan.h"
#include "CameraMan.h"

AbstractEngine::AbstractEngine(void)
{
	Log("AbstractEngine", "Constructor called");
}


AbstractEngine::~AbstractEngine(void)
{
	Log("AbstractEngine", "Destructor called");
}

int 
AbstractEngine::Initialize()
{
	Log("AbstractEngine", "InitializeGL called");

	// Call parent function
	Core::Initialize();

	// Initialize the text renderer
	TextMan::Instance().Initialize(".\\Assets\\Holstein.tga");

	// Success
	return 1;
}

void 
AbstractEngine::SetupScene()
{
	Log("AbstractEngine", "SetupScene called");

	// Call parent function
	Core::SetupScene();
}

void 
AbstractEngine::Update(float dt)
{
	// Call parent function
	Core::Update(dt);
}

void 
AbstractEngine::Draw(float dt)
{
	// Call parent function
	Core::Draw(dt);
}

void 
AbstractEngine::Run()
{
	
}