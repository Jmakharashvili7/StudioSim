#include "UIWindow.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

UIWindow::UIWindow(std::string name) : m_name(name), m_position(0,0)
{
}

UIWindow::~UIWindow()
{
}

void UIWindow::Init()
{
}

void UIWindow::Render()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin(m_name.c_str());
	ImGui::PopStyleVar();
}
