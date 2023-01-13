#include "Quack.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "KeyboardClass.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// Input handling
void Quack::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		KeyboardClass::OnKeyPressed(key);
		break;
	case GLFW_RELEASE:
		KeyboardClass::OnKeyReleased(key);
		break;
	}
}

#pragma region DeclareMembers
bool Quack::s_glfwInitialised = false;
bool Quack::s_running = false;
Window* Quack::m_window;

//Frame related variables
double Quack::m_currentTime;
double Quack::m_lastTime;
double Quack::m_deltaTime;
double Quack::m_frameTime;
double Quack::m_frameDelay;

int Quack::m_frameCounter;
int Quack::m_currentFrameRate;

Shader* Quack::m_mainShader;
OrthographicCamera* Quack::m_mainCamera;
#pragma endregion DeclareMembers

int Quack::InitEngine()
{
	s_running = true;

	m_mainCamera = new OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f);
	m_window = new Window("Quack", 600, 480, FullScreenMode::WINDOWED);

	// Initilaize window
	m_window->UseWindow();

	/* Initialize the Glew Library*/
	glewExperimental = GL_TRUE;
	glewInit();
	
	///
	///	Initialize IMGUI
	/// 
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_window->GetGLFWWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");

	/* Initialize the keyboard class*/
	KeyboardClass::Init();

	glfwSetKeyCallback(m_window->GetGLFWWindow(), Quack::key_callback);

	InitObjects();
	return 0;
}

void Quack::HandleInput()
{
	KeyEvent key = KeyboardClass::ReadKey();
	if (key.IsPressed())
	{
		switch (key.GetKeyCode())
		{
		case 0: // default value means no input so break out of loop
			break;
		case 'W': // move camera up
		{
			glm::vec3 temp = m_mainCamera->GetPosition();
			temp.y += 0.3f;
			m_mainCamera->SetPosition(temp);
			m_mainShader->SetUniform4x4("u_viewProjection", m_mainCamera->GetViewProjectionMatrix());
			break;
		}
		case 'S': // move camera down
		{
			glm::vec3 temp = m_mainCamera->GetPosition();
			temp.y -= 0.3f;
			m_mainCamera->SetPosition(temp);
			m_mainShader->SetUniform4x4("u_viewProjection", m_mainCamera->GetViewProjectionMatrix());
			break;
		}
		case 'A': // move camera left
		{
			glm::vec3 temp = m_mainCamera->GetPosition();
			temp.x -= 0.3f;
			m_mainCamera->SetPosition(temp);
			m_mainShader->SetUniform4x4("u_viewProjection", m_mainCamera->GetViewProjectionMatrix());
			break;
		}
		case 'D': // move camera right
		{
			glm::vec3 temp = m_mainCamera->GetPosition();
			temp.x += 0.3f;
			m_mainCamera->SetPosition(temp);
			m_mainShader->SetUniform4x4("u_viewProjection", m_mainCamera->GetViewProjectionMatrix());
			break;
		}
		}
	}
}

void Quack::InitObjects()
{
	m_mainShader = new Shader("shaders/basic.shader");
	m_mainShader->Bind();
	m_mainShader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
	m_mainShader->SetUniform4x4("u_viewProjection", m_mainCamera->GetViewProjectionMatrix());
	m_mainShader->Unbind();

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void Quack::Update()
{
	//Delta time is time between frames
	//Calculated using glfw get time funciton which gets time since glfw was initiated in seconds
	GetFrameRate(m_deltaTime);
	m_currentTime = glfwGetTime();
	m_deltaTime = m_currentTime - m_lastTime;

	HandleInput();
	GetFrameRate(m_deltaTime);

	// get mouse position
	double xpos, ypos;
	glfwGetCursorPos(m_window->GetGLFWWindow(), &xpos, &ypos);

	m_lastTime = m_currentTime;
}

void Quack::RenderUpdate()
{
	/* Poll for and process events */
	glfwPollEvents();

	// tell imgui we are working with a new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);

	m_mainShader->Bind();
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

	ImGui::Begin("My name is window, ImGui window");
	ImGui::Text("Hello");
	bool temp = false;
	ImGui::Checkbox("Draw", &temp); 
	ImGui::End();

	ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	/* Swap front and back buffers */
	glfwSwapBuffers(m_window->GetGLFWWindow());
}

void Quack::ShutDown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();	 
	glfwDestroyWindow(m_window->GetGLFWWindow());
	glfwTerminate();
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
}


