#pragma once
#include "BasicIncludes.h"

namespace QuackEngine {

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void window_size_callback(GLFWwindow* window, int width, int height);
	void window_close_callback(GLFWwindow* window);
} // quack engine namespace

