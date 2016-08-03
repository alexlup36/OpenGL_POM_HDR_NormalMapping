#include "MyEngine.h"
#include "Core.h"

//GLFWwindow* Core::Window = NULL;

int main(int argc, char* argv[])
{
	MyEngine* engine = new MyEngine();

	// Initialize the engine's window
	if (!engine->Initialize())
	{
		fprintf(stderr, "Failed to initialize GL\n");
		return 0;
	}
	// Set the properties of the engine's window
	engine->SetWindowProperties("TechDemo");

	do
	{
		static double lastTime = glfwGetTime();

		double currentTime = glfwGetTime();
		float dt = float(currentTime - lastTime);

		// Processing
		engine->Update(dt);
		engine->Draw(dt);

		lastTime = currentTime;
	} 
	while (!glfwWindowShouldClose(Core::Window));

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	delete engine;

	return 0;
}