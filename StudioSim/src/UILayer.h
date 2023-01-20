#pragma once
#include "Layer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "UIWindow.h"
#include "ViewportUI.h"


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
	inline ViewportUI* GetViewport() { return m_viewport; }
	static void SetPos(glm::vec3 pos);
private:
	void EnableDocking();
private:
	float m_time;
	glm::vec4 m_color;
	ViewportUI* m_viewport;
	static glm::vec3 vectorPos;
	static glm::vec3 vectorRot;
	static glm::vec3 vectorScale;
};

