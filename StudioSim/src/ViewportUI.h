#pragma once
#include "UIWindow.h"
#include "FrameBuffer.h"

class ViewportUI : public UIWindow
{
public:
	ViewportUI(std::string name);
	~ViewportUI();

	void Render() override;
	void HandleKeyboardInput(KeyEvent key) override;
	void HandleMouseInput(MouseEvent e) override;

	inline float GetStartX() { return startViewportX; }
	inline float GetStartY() { return startViewportY; }

private:
	float startViewportX;
	float startViewportY;

	float m_aspect;

	float m_horizontalMovement;
	float m_verticalMovement;
	
	glm::vec3 m_newPosition;
};
