#include "Quack.h"

Quack::Quack()
{
	m_window = nullptr;

	m_running = true;

	m_deltaTime = 0;
	m_currentTime = 0;
	m_lastTime = 0;

	m_capFrames = true;
	m_frameTime = 0;
	m_currentFrameRate = 0;
	m_frameCounter = 0;
	m_frameDelay = 0;

}

Quack::~Quack()
{
	delete m_window;
	m_window = nullptr;
}

int Quack::InitEngine()
{
	//Set up here is is similar to original from Application.cpp
	//Addition of update loop and frame calculations
	m_running = true;

	if (!glfwInit())
	{
		m_running = false;
		return -1;
	}

	m_window = glfwCreateWindow(640, 480, "Studio Sim", NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		m_running = false;
		return -1;
	}

	glfwMakeContextCurrent(m_window);

	//Main Engine Loop
	while (m_running)
	{
		//Delta time is time between frames
		//Calculated using glfw get time funciton which gets time since glfw was initiated in seconds
		m_currentTime = glfwGetTime();
		m_deltaTime = m_currentTime - m_lastTime;

		GetFrameRate(m_deltaTime);

		Update(m_deltaTime, this);

		m_lastTime = m_currentTime;
	}

	return 0;
}

void Quack::Update(float deltatime, Quack* engineInstance)
{
	//Add renderer into this function

	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);

	/* Swap front and back buffers */
	glfwSwapBuffers(m_window);

	/* Poll for and process events */
	glfwPollEvents();
}

void Quack::GetFrameRate(float deltatime)
{
	m_frameCounter++;

	//frame time to keep track of time until one second so FPS can be calculated
	m_frameTime += deltatime;

	//seeing how many frames were processed within 1 second
	if (m_frameTime > 1.0f)
	{
		m_currentFrameRate = m_frameCounter;

		//resetting values so frames for the next second can be calculated
		m_frameCounter = 0;
		m_frameTime = 0;
	}

	std::cout << "FPS: " << m_currentFrameRate << std::endl;
}


