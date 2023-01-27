#pragma once
#include "UIWindow.h"
#include <experimental/filesystem>

class ContentBrowserUI : public UIWindow
{
public:

	ContentBrowserUI(std::string name);
	~ContentBrowserUI();

	void Render() override;
	void HandleInput(KeyEvent key) override;
};