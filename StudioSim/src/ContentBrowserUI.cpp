#include "ContentBrowserUI.h"
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

ContentBrowserUI::ContentBrowserUI(std::string name) : UIWindow(name)
{
	m_CurrentDirectory = m_ContentRoot;

	m_thumbnailPadding = 0.0f;
	m_thumbnailSize = 0.0f;
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

	ImGui::Columns(4, 0, false);



	//loop through the directory in contentBrowser and show all directories
	//directory iterator goes through all subdirectories within the directory passed in
	//directory entry is each directory where the directory iterator is located
	for (fs::directory_entry directory : fs::directory_iterator(currentDir))
	{
		std::string path = directory.path().string();
		std::string directoryName = directory.path().stem().string();

		if (directory.is_directory())
		{
			if (ImGui::Button(directoryName.c_str(), { 128, 128}))
			{
				m_CurrentDirectory = path;
			}
			ImGui::Text(directoryName.c_str());
		}
		if (directory.is_regular_file())
		{
			std::string file= directory.path().filename().string();
			if (ImGui::Button(file.c_str()))
			{
				
			}

		}
		ImGui::NextColumn();
	}

	

	ImGui::End();
}

void ContentBrowserUI::HandleInput(KeyEvent key)
{
}
