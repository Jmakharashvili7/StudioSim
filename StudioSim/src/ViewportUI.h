#pragma once
#include "UIWindow.h"
#include "FrameBuffer.h"

class ViewportUI : public UIWindow
{
public:
	ViewportUI(std::string name, FrameBuffer* frameBuffer);
	~ViewportUI();

	void Render() override;
	void HandleInput(KeyEvent key) override;

	inline float GetStartX() { return startViewportX; }
	inline float GetStartY() { return startViewportY; }

private:
	FrameBuffer* m_frameBuffer;
	float startViewportX;
	float startViewportY;
};

