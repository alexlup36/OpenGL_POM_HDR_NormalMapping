#include "TestGLApp.h"
#include "Core.h"
#include "MappedProperties.h"

#include <thread>

void watchdog()
{
	MappedProperties::GetInstance().watchDir(".\\data\\test.txt", "C:\\disk\\programming\\opengl\\OpenglRenderingFramework2\\Engine\\Demo\\data");
}

int main(int argc, char* argv[])
{
	TestGLApp* app = new TestGLApp();
	
	std::thread watchdogThread(watchdog);

	// Initialize the engine
	if (!app->Initialize())
	{
		std::cout << "Failed to initialize GL.\n";
		return 0;
	}

	do
	{
		static double lastTime = glfwGetTime();

		double currentTime = glfwGetTime();
		float dt = float(currentTime - lastTime);

		// Processing
		app->Update(dt);
		app->Draw(dt);

		lastTime = currentTime;
	} 
	while (!glfwWindowShouldClose(Core::Window));

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	watchdogThread.join();
	delete app;

	return 0;
}