#pragma once
#include "Layer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "UIWindow.h"


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
	inline UIWindow* GetViewport() { return m_viewport; }
private:
	void EnableDocking();
private:
	float m_time;
	glm::vec4 m_color;
	UIWindow* m_viewport;
};

