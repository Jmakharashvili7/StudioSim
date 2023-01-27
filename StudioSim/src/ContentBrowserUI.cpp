#include "ContentBrowserUI.h"
#include <filesystem>
#include <string>

using namespace std::filesystem;

ContentBrowserUI::ContentBrowserUI(std::string name) : UIWindow(name)
{
}

ContentBrowserUI::~ContentBrowserUI()
{
	
}

void ContentBrowserUI::Render()
{
	//name of folder to use for content browser
	const std::string rootBrowserDirectory = "res";

	ImGui::Begin("Content Browser");

	//loop through the directory in contentBrowser and show all directories
	//directory iterator goes through all subdirectories within the directory passed in
	//directory entry is each directory where the directory iterator is located
	for (directory_entry directory : directory_iterator(rootBrowserDirectory))
	{
		std::string path = directory.path().string();
		ImGui::Text("%s", path.c_str());
	}
	ImGui::End();
}

void ContentBrowserUI::HandleInput(KeyEvent key)
{
}
