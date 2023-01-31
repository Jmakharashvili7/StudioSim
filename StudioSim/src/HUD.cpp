#include "pch.h"
#include "HUD.h"
#include "Quack.h"
#include "UILayer.h"

HUD::HUD()
{
}

HUD::~HUD()
{
}

void HUD::Draw()
{
	//Size of viewport
	//double port_x = m_uiMain->GetViewport()->GetSize().x;
	//double port_y = m_uiMain->GetViewport()->GetSize().y;

	double port_x = Quack::GetUILayer()->GetViewport()->GetSize().x;
	double port_y = Quack::GetUILayer()->GetViewport()->GetSize().y;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, port_x, port_y, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);
	glClear(GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS);

	//Blood meter
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(port_x - 400.0, port_y - 100);
	glVertex2f(port_x, port_y - 100);
	glVertex2f(port_x, port_y);
	glVertex2f(port_x - 400, port_y);
	//Coins?
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.0, 0.0);
	glVertex2f(200.0, 0.0);
	glVertex2f(200.0, 100.0);
	glVertex2f(0.0, 100.0);
	//Health bar
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(0.0, port_y - 100);
	glVertex2f(400.0, port_y - 100);
	glVertex2f(400.0, port_y);
	glVertex2f(0.0, port_y);

	glEnd();
}