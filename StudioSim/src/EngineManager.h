#pragma once
#include "BasicIncludes.h"
#include "Quack.h"

class EngineManager
{
public:
	inline GameTimer* GetGameTimer() { return m_gameTimer; }
private:
	GameTimer* m_gameTimer;
private:
	EngineManager();
	~EngineManager();
};

