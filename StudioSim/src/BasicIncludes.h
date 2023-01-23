#pragma once

// Include all the basic includes needed for most files here

#include <GL/glew.h> // must be included before GLFW
#include <GLFW\glfw3.h>
#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <glm\glm.hpp>
#include "imgui_impl_glfw.h"
#include <glm/ext/scalar_constants.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>
#include <map>
#include "json.h"
#include "Log.h"
#include "KeyEvent.h"
#include "CustomMaths.h"

using namespace std;

//#define _3D_SHADER
#define _2D_SHADER