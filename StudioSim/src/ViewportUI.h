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
private:
	FrameBuffer* m_frameBuffer;
};

