#include "UIManager.h"

//Screen* UIManager::m_pScreen = nullptr;

// ----------------------------------------------------------------------------

UIManager::UIManager()
{
}

// ----------------------------------------------------------------------------

UIManager::~UIManager()
{
	//TwTerminate();
}

// ----------------------------------------------------------------------------

void UIManager::init(GLFWwindow* pWindow)
{
	assert(pWindow != nullptr);
	m_pWindow = pWindow;

	setCallbacks();
}

// ----------------------------------------------------------------------------

void UIManager::render()
{
	GLErrorCheck("UIManager::Render");

	GLClearErrors();

	GLErrorCheck("UIManager::Render");
}

// ----------------------------------------------------------------------------

void UIManager::windowResize(GLFWwindow* window, int width, int height)
{
}

// ----------------------------------------------------------------------------

void UIManager::cursorPosCallback(GLFWwindow* window, double x, double y)
{
	//m_pScreen->cursorPosCallbackEvent(x, y);
}

// ----------------------------------------------------------------------------

void UIManager::mouseButtonCallback(GLFWwindow*, int button, int action, int modifiers)
{
	//m_pScreen->mouseButtonCallbackEvent(button, action, modifiers);
}

// ----------------------------------------------------------------------------

void UIManager::keyCallback(GLFWwindow*, int key, int scancode, int action, int mods)
{
	//m_pScreen->keyCallbackEvent(key, scancode, action, mods);
}

// ----------------------------------------------------------------------------

void UIManager::charCallback(GLFWwindow*, unsigned int codepoint)
{
	//m_pScreen->charCallbackEvent(codepoint);
}

// ----------------------------------------------------------------------------

void UIManager::dropCallback(GLFWwindow*, int count, const char **filenames)
{
	//m_pScreen->dropCallbackEvent(count, filenames);
}

// ----------------------------------------------------------------------------

void UIManager::scrollCallback(GLFWwindow*, double x, double y)
{
	//m_pScreen->scrollCallbackEvent(x, y);
}

// ----------------------------------------------------------------------------

void UIManager::framebufferSizeCallback(GLFWwindow*, int width, int height)
{
	//m_pScreen->resizeCallbackEvent(width, height);
}

// ----------------------------------------------------------------------------

void UIManager::setCallbacks()
{
	// nanogui
	/*glfwSetCursorPosCallback(m_pWindow, UIManager::cursorPosCallback);
	glfwSetMouseButtonCallback(m_pWindow, UIManager::mouseButtonCallback);
	glfwSetKeyCallback(m_pWindow, UIManager::keyCallback);
	glfwSetCharCallback(m_pWindow, UIManager::charCallback);
	glfwSetDropCallback(m_pWindow, UIManager::dropCallback);
	glfwSetScrollCallback(m_pWindow, UIManager::scrollCallback);
	glfwSetFramebufferSizeCallback(m_pWindow, UIManager::framebufferSizeCallback);*/
}

// ----------------------------------------------------------------------------