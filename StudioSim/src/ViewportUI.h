#pragma once
#include "UIWindow.h"
#include "FrameBuffer.h"

class ViewportUI : public UIWindow
{
public:
	ViewportUI(std::string name);
	~ViewportUI();

	void Render() override;
	void HandleInput(KeyEvent key, MouseEvent e) override;

	inline float GetStartX() { return startViewportX; }
	inline float GetStartY() { return startViewportY; }

private:
	float startViewportX;
	float startViewportY;
};

