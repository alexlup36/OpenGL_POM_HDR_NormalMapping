#include "Input.h"
#include "Core.h"

#include "Camera.h"
#include "CameraMan.h"


// Mouse position
double Input::X_MOUSEPOS		= WINDOW_WIDTH / 2.0f;
double Input::Y_MOUSEPOS		= WINDOW_HEIGHT / 2.0f;

double Input::X_PREVIOUSPOS = WINDOW_WIDTH / 2.0f;
double Input::Y_PREVIOUSPOS = WINDOW_HEIGHT / 2.0f;

Input::Input(void)
{
}

Input::~Input(void)
{
}

void Input::Update(float dt, glm::vec3& newPosition, const glm::vec3& direction, const glm::vec3& right)
{
	glfwGetCursorPos(Core::Window, &X_MOUSEPOS, &Y_MOUSEPOS);

	// Set mouse position to the center of the screen
	glfwSetCursorPos(Core::Window, (double)WINDOW_WIDTH / 2, (double)WINDOW_HEIGHT / 2);

	// Move forward
	if (glfwGetKey(Core::Window, GLFW_KEY_UP) == GLFW_PRESS ||
		glfwGetKey(Core::Window, GLFW_KEY_W) == GLFW_PRESS)
	{
		newPosition += direction * dt * Core::KeyboardSpeed;
	}
	// Move backward
	if (glfwGetKey(Core::Window, GLFW_KEY_DOWN) == GLFW_PRESS ||
		glfwGetKey(Core::Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		newPosition -= direction * dt * Core::KeyboardSpeed;
	}
	// Strafe right
	if (glfwGetKey(Core::Window, GLFW_KEY_RIGHT) == GLFW_PRESS ||
		glfwGetKey(Core::Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		newPosition += right * dt * Core::KeyboardSpeed;
	}
	// Strafe left
	if (glfwGetKey(Core::Window, GLFW_KEY_LEFT) == GLFW_PRESS ||
		glfwGetKey(Core::Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		newPosition -= right * dt * Core::KeyboardSpeed;
	}

	// Quit the app
	if (glfwGetKey(Core::Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(Core::Window, 1);
	}

	// Camera position snapshot
	if (glfwGetKey(Core::Window, GLFW_KEY_C) == GLFW_PRESS)
	{
		Camera* camera = CameraMan::Instance().GetActiveCamera();

		glm::vec3 camPos = camera->GetCameraPosition();
		std::cout << "Camera position: " << camPos.x << ", " << camPos.y << ", " << camPos.z << std::endl;
		glm::vec3 camTarget = camera->GetCameraTarget();
		std::cout << "Camera target: " << camTarget.x << ", " << camTarget.y << ", " << camTarget.z << std::endl;
		glm::vec3 camUp = camera->GetCameraUp();
		std::cout << "Camera up: " << camUp.x << ", " << camUp.y << ", " << camUp.z << std::endl;
	}
}