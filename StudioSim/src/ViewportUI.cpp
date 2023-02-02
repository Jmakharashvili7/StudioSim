#include "pch.h"

#include "ViewportUI.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Quack.h"
#include "OrthographicCamera.h"
#include "MouseClass.h"

ViewportUI::ViewportUI(std::string name) : UIWindow(name)
{
	startViewportX = 0;
	startViewportY = 0;
}

ViewportUI::~ViewportUI()
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
		m_position = { viewportPos.x, viewportPos.y };
	}

	// Check if the size of the window changed
	// *((glm::vec2*)& is used to compare imvec2 and glm vec2 and it works due to their layouts both being two floats
	ImVec2 viewportSize = ImGui::GetContentRegionAvail();
	if (m_size != *((glm::vec2*)&viewportSize))
	{
		m_size = { viewportSize.x, viewportSize.y };
		Quack::GetFrameBuffer()->Resize(m_size.x, m_size.y);

		float aspect = m_size.x / m_size.y;

		if (Quack::GetOrthoCam())
		{
			Quack::GetOrthoCam()->RecalculateProjection(-Quack::GetOrthoCam()->GetZoom() * aspect, Quack::GetOrthoCam()->GetZoom() * aspect, -Quack::GetOrthoCam()->GetZoom(), Quack::GetOrthoCam()->GetZoom());
		}

	}

	startViewportX = ImGui::GetCursorScreenPos().x;
	startViewportY = ImGui::GetCursorScreenPos().y;
	m_isFocused = ImGui::IsWindowFocused();
	ImGui::Image((void*)Quack::GetFrameBuffer()->GetID(), ImVec2(m_size.x, m_size.y), ImVec2(0, 1), ImVec2(1, 0));
	ImGui::End();
}

void ViewportUI::HandleKeyboardInput(KeyEvent key)
{
	
}

void ViewportUI::HandleMouseInput(MouseEvent e)
{
	if (Quack::GetOrthoCam())
	{
		if (Quack::GetOrthoCam()->GetCanZoom())
		{
			float newZoom = Quack::GetOrthoCam()->GetZoom();
			float aspect = m_size.x / m_size.y;

			if (e.GetType() == MouseEvent::EventType::SCROLL_DOWN)
			{
				newZoom += (float)e.GetType() * Quack::GetOrthoCam()->GetZoomSpeed();
			}

			if (e.GetType() == MouseEvent::EventType::SCROLL_UP)
			{
				newZoom -= (float)e.GetType() * Quack::GetOrthoCam()->GetZoomSpeed();
			}

			newZoom = newZoom <= 1.0f ? 1.0f : newZoom;
			Quack::GetOrthoCam()->SetZoom(newZoom);

			Quack::GetOrthoCam()->RecalculateProjection(-Quack::GetOrthoCam()->GetZoom() * aspect, Quack::GetOrthoCam()->GetZoom() * aspect, -Quack::GetOrthoCam()->GetZoom(), Quack::GetOrthoCam()->GetZoom());
			
		}

	}

}
