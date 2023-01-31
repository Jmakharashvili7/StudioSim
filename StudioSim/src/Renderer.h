#pragma once
#include "BasicIncludes.h"
#include "VertexArray.h"
#include "Shader.h"
#include "OrthographicCamera.h"

class Renderer
{
public:
	static void Init();
	static void DrawLine(glm::vec3 p0, glm::vec3 p1, glm::vec3 color);
	static void DrawDebugLines(OrthographicCamera* camera);
private:
	static std::vector<VertexArray*> m_objects;
	static Shader* m_shader;
};

