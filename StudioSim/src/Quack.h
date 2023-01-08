#pragma once

#include "BasicIncludes.h"

#define MAX_FRAME_RATE 144

class Quack
{
public:

	Quack();
	~Quack();

	int InitEngine();
	void Update(float deltatime);
	void GetFrameRate(float deltatime);

private:

	GLFWwindow* m_window;

	bool m_running;

	//Frame related variables
	double m_currentTime;
	double m_lastTime;
	double m_deltaTime;
	double m_frameTime;
	double m_frameDelay;

	int m_frameCounter;
	int m_currentFrameRate;

public:
	bool m_capFrames;
};
