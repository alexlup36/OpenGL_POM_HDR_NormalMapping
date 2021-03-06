#include "Core.h"

#include "Common.h"
//#include "ShaderMan.h"
#include "CameraMan.h"
#include "GfxStats.h"

GLFWwindow* Core::Window = nullptr;
float Core::MouseSpeed = 0.08f;
float Core::KeyboardSpeed = 15.0f;

// ----------------------------------------------------------------------------------------------
Core::Core() 
{
	Log("Core", "Constructor called");
}


Core::~Core()
{
	Log("Core", "Destructor called");
}

int Core::Initialize()
{
	Log("Core", "Initialize called");

	// Failed to initialize GL
	if ( InitializeGL() == 0 )
	{
		return 0;
	}

	//SetupScene();

	return 1;
}

int Core::InitializeGL()
{
	Log("Core", "InitializeGL called");

	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return 0;
	}

	// Set OpenGL version
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_SAMPLES, 0);
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// Full screen or window 
#if X_FULLSCREEN
	{
		// Open a full screen window and set the OpenGL context
		Window = glfwCreateWindow( 
			WINDOW_WIDTH, 
			WINDOW_HEIGHT, 
			"GL Demo", 
			glfwGetPrimaryMonitor(), 
			nullptr);
	}
#else
	{
		// Open a window and set the OpenGL context
		Window = glfwCreateWindow( 
			WINDOW_WIDTH, 
			WINDOW_HEIGHT, 
			"GL Demo", 
			nullptr, 
			nullptr);
	}
#endif // X_FULLSCREEN
	

	if (Window == nullptr)
	{
		glfwTerminate();
		fprintf( stderr, "Failed to open GLFW window.\n" );
		return 0;
	}

	glfwMakeContextCurrent(Window);

	glewExperimental = true;

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return 0;
	}

	SetGLState();

	return 1;
}

void Core::SetWindowProperties(const char* windowTitle)
{
	Log("Core", "SetWindowProperties called");

	glfwSetWindowTitle(Window, windowTitle);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(Window, GLFW_STICKY_KEYS, GL_TRUE);

	// Hide the mouse cursor
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse scroll callback
	glfwSetScrollCallback(Window, Input::scrollCallback);
}

void Core::SetGLState()
{
	Log("Core", "SetGLState called");

	// Dark blue background
	glClearColor(0.01f, 0.01f, 0.01f, 1.0f);

	// Disable vsync
	glfwSwapInterval(0);

	//glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Core::Update(float dt)
{
	glfwPollEvents();

	// Update calls
	CameraMan::Instance().Update(dt);
}

void Core::Draw(float dt)
{
	// Draw
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Core::SetupScene()
{

}