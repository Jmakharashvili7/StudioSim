#include "QuackCallbacks.h"
#include "KeyboardClass.h"
#include "Quack.h"

namespace QuackEngine {
	// Input callback
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		switch (action)
		{
		case GLFW_PRESS:
			KeyboardClass::OnKeyPressed(key);
			break;
		case GLFW_RELEASE:
			KeyboardClass::OnKeyReleased(key);
			break;
		}
	}

	// windw close callback
	void window_close_callback(GLFWwindow* window)
	{
		Quack::s_running = false;
	}
}