#include "ContentBrowserUI.h"
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

ContentBrowserUI::ContentBrowserUI(std::string name) : UIWindow(name)
{
	m_CurrentDirectory = m_ContentRoot;

	m_thumbnailPadding = 24.0f;
	m_thumbnailSize = 128.0f;

	m_folderThumbnail = new Texture(TextureData("engine res/icons/duck folder icon.png"));
	m_fileThumbnail = new Texture(TextureData("engine res/icons/big boi.jpg"));
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

	//Gets number of columns based off current window size
	int numberOfColumns = ImGui::GetContentRegionAvail().x / (m_thumbnailSize + m_thumbnailPadding);

	ImGui::Columns(numberOfColumns, 0, false);

	//loop through the directory in contentBrowser and show all directories
	//directory iterator goes through all subdirectories within the directory passed in
	//directory entry is each directory where the directory iterator is located
	for (fs::directory_entry directory : fs::directory_iterator(currentDir))
	{
		std::string path = directory.path().string();
		std::string directoryName = directory.path().stem().string();

		//for folders
		if (directory.is_directory())
		{
			if (ImGui::ImageButton((ImTextureID)m_folderThumbnail->GetRendererID(), ImVec2(m_thumbnailSize, m_thumbnailSize), ImVec2(0, 1), ImVec2(1, 0)))
			{
				m_CurrentDirectory = path;
			}


			ImGui::Text(directoryName.c_str());
		}



		//for files
		if (directory.is_regular_file())
		{
			std::string file= directory.path().filename().string();

			if(ImGui::ImageButton((ImTextureID)m_fileThumbnail->GetRendererID(), ImVec2(m_thumbnailSize, m_thumbnailSize), ImVec2(0, 1), ImVec2(1, 0)))
			{
				std::cout << " I'M SEXY AND I KNOW IT" << std::endl;
			}

			ImGui::Text(file.c_str());
		}

		ImGui::NextColumn();
	}

	ImGui::Columns(1);
	

	ImGui::End();
}

void ContentBrowserUI::HandleInput(KeyEvent key)
{
}
