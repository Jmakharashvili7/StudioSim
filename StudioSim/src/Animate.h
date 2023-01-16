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

	//std::vector<std::pair<int[2], float>> m_spriteSheetData;

	float m_delay;

	int m_spriteFrame;
	int m_rowToPlay;  
};
