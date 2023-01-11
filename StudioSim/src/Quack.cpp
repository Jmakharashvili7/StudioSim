#include "Quack.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"

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
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	/* Initialize the Glew Library*/
	glewExperimental = GL_TRUE;
	glewInit();

#pragma region  temporary rectangle
	/*
	float positions[] = {
	-0.5f, -0.5f, // 0
	 0.5f, -0.5f, // 1
	 0.5f,  0.5f, // 2
	-0.5f,  0.5f, // 3
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &(vertexbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	VertexArray va;
	VertexBuffer vb(positions, 4 * 2 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	m_va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 6);

	Shader shader("shaders/basic.shader");
	shader.Bind();
	shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

	m_va = va;
	m_vb = vb;
	m_ib = ib;
	m_shader = shader;

	m_va.Unbind();
	m_vb.Unbind();
	m_ib.Unbind();
	m_shader.Unbind();

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	*/
#pragma endregion

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


	//QE_INFO("Testing!");

	////shader.Bind();
	/*va.Bind();
	ib.Bind();
	vb.Bind();
	shader.Bind();*/


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


