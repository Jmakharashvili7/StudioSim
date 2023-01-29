#pragma once
#include "BasicIncludes.h"
#include "VertexArray.h"

class Renderer
{
public:
	static void DrawLine(glm::vec3 p0, glm::vec3 p1, glm::vec3 color);
	static void DrawDebugLines();
private:
	static std::vector<VertexArray*> m_objects;
};

