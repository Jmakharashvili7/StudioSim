#include "ContentBrowserUI.h"

ContentBrowserUI::ContentBrowserUI(std::string name) : UIWindow(name)
{
}

ContentBrowserUI::~ContentBrowserUI()
{
}

void ContentBrowserUI::Render()
{
	ImGui::Begin("Content Browser");
	ImGui::End();
}

void ContentBrowserUI::HandleInput(KeyEvent key)
{
}
