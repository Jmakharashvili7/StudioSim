#pragma once
#include "UIWindow.h"
#include "Texture.h"


class ContentBrowserUI : public UIWindow
{
public:

	ContentBrowserUI(std::string name);
	~ContentBrowserUI();

	void Render() override;
	void HandleInput(KeyEvent key) override;

private:
	std::string m_ContentRoot = "res";
	std::string m_CurrentDirectory;

	ImGuiIO& m_IO = ImGui::GetIO();

	float m_thumbnailPadding;
	float m_thumbnailSize;

	Texture* m_folderThumbnail;
	Texture* m_fileThumbnail;
};