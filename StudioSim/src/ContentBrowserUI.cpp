#include "ContentBrowserUI.h"
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

ContentBrowserUI::ContentBrowserUI(std::string name) : UIWindow(name)
{
	m_CurrentDirectory = m_ContentRoot;
}

ContentBrowserUI::~ContentBrowserUI()
{
	
}

void ContentBrowserUI::Render()
{
	//name of folder to use for content browser
	const std::string currentDir = m_CurrentDirectory;

	ImGui::Begin("Content Browser");

	//
	std::string current = "Current Path: " + m_CurrentDirectory;

	ImGui::Text(current.c_str());

	if (m_CurrentDirectory != m_ContentRoot)
	{
		if (ImGui::Button("Back"))
		{
			m_CurrentDirectory = fs::directory_entry(m_CurrentDirectory).path().parent_path().string();
		}
	}

	//loop through the directory in contentBrowser and show all directories
	//directory iterator goes through all subdirectories within the directory passed in
	//directory entry is each directory where the directory iterator is located
	for (fs::directory_entry directory : fs::directory_iterator(currentDir))
	{
		std::string path = directory.path().string();
		std::string directoryName = directory.path().stem().string();

		if (directory.is_directory())
		{
			if (ImGui::Button(directoryName.c_str()))
			{
				m_CurrentDirectory = path;
			}
		}
		if (directory.is_regular_file())
		{
			std::string file= directory.path().filename().string();
			ImGui::Text(file.c_str());
		}
	}

	

	ImGui::End();
}

void ContentBrowserUI::HandleInput(KeyEvent key)
{
}
