#pragma once
#include "UIWindow.h"
#include "GameObject.h"

class WorldOutlinerUI : public UIWindow
{
public:
	WorldOutlinerUI(std::string name);
	~WorldOutlinerUI();

	void Render() override;
	void HandleInput(KeyEvent key) override;
};