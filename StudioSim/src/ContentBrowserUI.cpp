#include "ContentBrowserUI.h"
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

ContentBrowserUI::ContentBrowserUI(std::string name) : UIWindow(name)
{
	m_CurrentDirectory = m_ContentRoot;

	m_ThumbnailPadding = 24.0f;
	m_ThumbnailSize = 128.0f;

	m_FolderThumbnail = new Texture(TextureData("engine res/icons/duck folder icon.png"));
	m_FileThumbnail = new Texture(TextureData("engine res/icons/rubber-duck.jpg"));

	m_ButtonHighlighted = false;
}

ContentBrowserUI::~ContentBrowserUI()
{
	delete m_FolderThumbnail;
	m_FolderThumbnail = nullptr;

	delete m_FileThumbnail;
	m_FolderThumbnail = nullptr;
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
	int numberOfColumns = ImGui::GetContentRegionAvail().x / (m_ThumbnailSize + m_ThumbnailPadding);

	ImGui::Columns(numberOfColumns, 0, false);

	//loop through the directory in contentBrowser and show all directories
	//directory iterator goes through all subdirectories within the directory passed in
	//directory entry is each directory where the directory iterator is located
	for (fs::directory_entry directory : fs::directory_iterator(currentDir))
	{
		fs::path directoryPath = directory.path();
		std::string directoryName = directoryPath.stem().string();

		//Assign ID to icons for drag and drop
		//ImGui::PushID();

		//for folders
		if (directory.is_directory())
		{
		

			//for making button background transparent
			//push style set Vec4 to 0
			ImGui::ImageButton((ImTextureID)m_FolderThumbnail->GetRendererID(), ImVec2(m_ThumbnailSize, m_ThumbnailSize), ImVec2(0, 1), ImVec2(1, 0));
			//pop style
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
			{
				m_CurrentDirectory = directoryPath.string();
			}
			ImGui::Text(directoryName.c_str());
		}



		//for files
		if (directory.is_regular_file())
		{
			
			std::string extension = directoryPath.extension().string();
			std::string file= directoryPath.filename().string();

			//setup for file content as image for png and jpg files
			/*if (extension == ".png" || extension == ".jpg")
			{
				ImGui::ImageButton((ImTextureID)m_ImageThumbnail->GetRendererID(), ImVec2(m_ThumbnailSize, m_ThumbnailSize), ImVec2(0, 1), ImVec2(1, 0));

			}
			else
			{
				ImGui::ImageButton((ImTextureID)m_FileThumbnail->GetRendererID(), ImVec2(m_ThumbnailSize, m_ThumbnailSize), ImVec2(0, 1), ImVec2(1, 0));
			}*/

			ImGui::ImageButton((ImTextureID)m_FileThumbnail->GetRendererID(), ImVec2(m_ThumbnailSize, m_ThumbnailSize), ImVec2(0, 1), ImVec2(1, 0));

			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
			{
				//Open file here
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
