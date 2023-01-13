#include "Quack.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "IndexBuffer.h"
#include "KeyboardClass.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "QuackCallbacks.h"

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

VertexArray* Quack::m_squareVAO;
Texture* Quack::m_duckTexture;

glm::vec4 Quack::m_objColor;

Shader* Quack::m_mainShader;
OrthographicCamera* Quack::m_mainCamera;
#pragma endregion DeclareMembers

int Quack::InitEngine()
{
	s_running = true;

	m_mainCamera = new OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f);
	m_mainCamera->SetPosition(glm::vec3(0.0f));
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

	glfwSetKeyCallback(m_window->GetGLFWWindow(), QuackEngine::key_callback);
	glfwSetWindowCloseCallback(m_window->GetGLFWWindow(), QuackEngine::window_close_callback);

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
			break;
		}
		case 'S': // move camera down
		{
			glm::vec3 temp = m_mainCamera->GetPosition();
			temp.y -= 0.3f;
			m_mainCamera->SetPosition(temp);
			break;
		}
		case 'A': // move camera left
		{
			glm::vec3 temp = m_mainCamera->GetPosition();
			temp.x -= 0.3f;
			m_mainCamera->SetPosition(temp);
			break;
		}
		case 'D': // move camera right
		{
			glm::vec3 temp = m_mainCamera->GetPosition();
			temp.x += 0.3f;
			m_mainCamera->SetPosition(temp);
			break;
		}
		}
	}
}

void Quack::InitObjects()
{
	//Setup stuff
	float vertices[] = {  
		-0.5f, -0.5f, 0.0f,  
		 0.5f, -0.5f, 0.0f,
		 0.5f, 0.5f, 0.0f,   
		 0.5f, 0.5f, 0.0f,   
		 -0.5f, 0.5f, 0.0f,  
		 -0.5f, -0.5f, 0.0f
	};
	
	float colors[] = {
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f
	};

	float textureCoords[] = {
		 0.0f, 0.0f,
		 1.0f, 0.0f,
		 1.0f, 1.0f,
		 1.0f, 1.0f,
		 0.0f, 1.0f,
		 0.0f, 0.0f
	};

	m_squareVAO = new VertexArray();
	VertexBuffer squareVertexBuffer = VertexBuffer(vertices, sizeof(vertices));
	VertexBuffer squareColorBuffer = VertexBuffer(colors, sizeof(colors));
	VertexBuffer squareTexCoordsBuffer = VertexBuffer(textureCoords, sizeof(textureCoords));

	VertexBufferLayout vertexLayout;
	vertexLayout.Push<float>(3);

	VertexBufferLayout colorLayout;
	colorLayout.Push<float>(3);

	VertexBufferLayout texCoordsLayout;
	texCoordsLayout.Push<float>(2);

	m_squareVAO->AddBuffer(squareVertexBuffer, vertexLayout, VertexType::VERTEX);
	m_squareVAO->AddBuffer(squareColorBuffer, colorLayout, VertexType::COLOR);
	m_squareVAO->AddBuffer(squareTexCoordsBuffer, texCoordsLayout, VertexType::TEX_COORDS);

	//Texture setup
	m_duckTexture = new Texture("res/textures/duck.png");

	//Shader setup
	m_mainShader = new Shader("res/shaders/basic.shader");
	m_mainShader->Bind();
	m_mainShader->SetUniform4x4("u_viewProjection", m_mainCamera->GetViewProjectionMatrix());
	m_mainShader->Unbind();
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
	// tell imgui we are working with a new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	/* Render here */
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// bind shader
	m_mainShader->Bind();
	m_mainShader->SetUniform4x4("u_viewProjection", m_mainCamera->GetViewProjectionMatrix());
	m_mainShader->SetUniform4f("u_color", 0.5f, 0.5, 0.5f, 1.f);

	// bind vertex array object
	m_squareVAO->Bind();

	// bind texture
	m_duckTexture->Bind();

	// render sqaure
	glm::mat4 model = glm::mat4(1.0f);
	// square position
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	m_mainShader->SetUniform4x4("u_model", model);
	// draw square
	glDrawArrays(GL_TRIANGLES, 0, 6);

	ImGui::Begin("Set Object Color");
	ImGui::Text("Hello");
	ImGui::End();

	ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	/* Swap front and back buffers */
	glfwSwapBuffers(m_window->GetGLFWWindow());
	/* Poll for and process events */
	glfwPollEvents();
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


