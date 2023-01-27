#include "ContentBrowserUI.h"

ContentBrowserUI::ContentBrowserUI(std::string name) : UIWindow(name)
{
}

ContentBrowserUI::~ContentBrowserUI()
{
	
}

void ContentBrowserUI::Render()
{
	//name of folder to use for content browser
	std::string contentBrowserDirectory = "res";

	ImGui::Begin("Content Browser");

	//loop through the directory in contentBrowser and show all directories
	for (auto& directory : std::filesystem::directory_iterator(contentBrowserDirectory))
	{
		ImGui::Text("%s", directory.path().c_str());
	}

	ImGui::End();
}

void ContentBrowserUI::HandleInput(KeyEvent key)
{
}
