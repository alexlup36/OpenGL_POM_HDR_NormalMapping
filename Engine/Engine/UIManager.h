#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "Common.h"

// -------------------------------------------------------------

class UIManager
{
public:
	static UIManager& Instance()
	{
		static UIManager refInstance;
		return refInstance;
	}

	void init(GLFWwindow* pWindow);
	void render();

private:
	UIManager();
	~UIManager();

	UIManager(const UIManager& rhs) = delete;
	void operator=(const UIManager& rhs) = delete;

private:

	// App main window
	GLFWwindow* m_pWindow;

	int m_iTestValue;

	// Methods
	static void windowResize(GLFWwindow* window, int width, int height);
	static void cursorPosCallback(GLFWwindow* window, double x, double y);
	static void mouseButtonCallback(GLFWwindow *, int button, int action, int modifiers);
	static void keyCallback(GLFWwindow *, int key, int scancode, int action, int mods);
	static void charCallback(GLFWwindow *, unsigned int codepoint);
	static void dropCallback(GLFWwindow *, int count, const char **filenames);
	static void scrollCallback(GLFWwindow *, double x, double y);
	static void framebufferSizeCallback(GLFWwindow *, int width, int heigh);

	void setCallbacks();
};

// ----------------------------------------------------------------------------

#endif // UIMANAGER_H