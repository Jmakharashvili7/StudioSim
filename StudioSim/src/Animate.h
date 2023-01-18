#pragma once
#include "BasicIncludes.h"

class Actor;

class Animate 
{
private: 
	void GenerateFrameList();

public:
	Animate(Actor* target, int rows, int columns);
	~Animate();

	void UpdateTextCoord(float deltaTime);

	void SetFramePlayTime(int row, int column, float duration);

	inline void SetRowToPlay(int row) { m_rowToPlay = row; }
	inline int GetRowToPlay() { return m_rowToPlay; }

private:
	Actor* m_object;

	std::map<std::pair<int, int>, float> m_durationData;

	std::pair<int, int> m_frameToPlay;

	float m_delay;
	float m_rows;
	float m_columns;

	int m_spriteFrame;
	int m_rowToPlay = 0;

};
