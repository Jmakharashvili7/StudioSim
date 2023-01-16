#pragma once

#include "BasicIncludes.h"

class GameObject;

class Animate
{
public:
	Animate(GameObject* target);
	~Animate();

	void UpdateTextCoord(float rows, float columns, float deltaTime, float playRate);

private:
	GameObject* object;

	float m_delay;

	int m_spriteFrame;
	int m_rowToPlay;
};
