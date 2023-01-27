#pragma once
#include "Layer.h"
#include "UIWindow.h"
#include "ViewportUI.h"
#include "EditorUI.h"

class UILayer : public Layer
{
public:
	UILayer();
	~UILayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate() override;
	void OnEvent() override;
	void InitWindows();

	inline glm::vec4& GetColor() { return m_color; }
	inline ViewportUI* GetViewport() { return m_viewportUI; }
	inline EditorUI* GetEditorUI() { return m_editorUI; }

private:
	void EnableDocking();
private:
	float m_time;
	glm::vec4 m_color;
	ViewportUI* m_viewportUI;	
	EditorUI* m_editorUI;
};

