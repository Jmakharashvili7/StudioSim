#include "ViewportUI.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

ViewportUI::ViewportUI(std::string name, FrameBuffer* frameBuffer) : UIWindow(name), m_frameBuffer(frameBuffer)
{
}

ViewportUI::~ViewportUI()
{
}

void ViewportUI::Init()
{
}

void ViewportUI::Render()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin(m_name.c_str());

	// Check if the size of the window changed
	// *((glm::vec2*)& is used to compare imvec2 and glm vec2 and it works due to their layouts both being two floats
	ImVec2 viewportPos = ImGui::GetWindowPos();
	if (m_position != *((glm::vec2*)&viewportPos))
	{
		m_position = {viewportPos.x, viewportPos.y };
	}

	// Check if the size of the window changed
	// *((glm::vec2*)& is used to compare imvec2 and glm vec2 and it works due to their layouts both being two floats
	ImVec2 viewportSize = ImGui::GetContentRegionAvail();
	if (m_size != *((glm::vec2*)&viewportSize))
	{
		m_size = { viewportSize.x, viewportSize.y };
		m_frameBuffer->Resize(m_size.x, m_size.y);
	}

	m_isFocused = ImGui::IsWindowFocused();
	ImGui::Image((void*)m_frameBuffer->GetID(), ImVec2(m_size.x, m_size.y), ImVec2(0, 1), ImVec2(1, 0));
	ImGui::End();
}

void ViewportUI::HandleInput(KeyEvent key)
{
}
