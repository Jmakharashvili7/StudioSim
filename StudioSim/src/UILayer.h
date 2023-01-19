#pragma once
#include "Layer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class UILayer : public Layer
{
public:
	UILayer();
	~UILayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate() override;
	void OnEvent() override;

	inline glm::vec4& GetColor() { return m_color; }
	inline glm::vec2& GetViewportSize() { return m_viewportSize; }
private:
	void EnableDocking();
private:
	float m_time;
	glm::vec4 m_color;
	glm::vec2 m_viewportSize;
};

