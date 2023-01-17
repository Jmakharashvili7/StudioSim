#pragma once

#include "BasicIncludes.h"

class GameObject;

class Animate
{
private: 
	void GenerateFrameList();

public:
	Animate(GameObject* target, int rows, int columns);
	~Animate();

	void UpdateTextCoord(float deltaTime, float playRate, int rowToPlay);

	void SetFramePlayTime(int row, int column, float duration);

private:
	GameObject* m_object;

	std::map<std::pair<int, int>, float> m_durationData;

	std::pair<int, int> m_frameToPlay;

	float m_delay;
	float m_rows;
	float m_columns;

	int m_spriteFrame;

};
