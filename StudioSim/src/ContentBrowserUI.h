#pragma once
#include "UIWindow.h"


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
};