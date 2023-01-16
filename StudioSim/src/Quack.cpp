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
#include "QuackPhysics.h"



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

unsigned int Quack::m_square1VBO;
unsigned int Quack::m_square1VAO;

Texture* Quack::m_duckTexture;
QuackPhysics* Quack::p_QuackPhysics;

bool Quack::m_jumping = false;
float Quack::m_jump_force = 10.0f;


glm::vec3 Quack::squarePositionData[] = {
		glm::vec3(-0.7f, 0.7f, 0.0f),       //0
		glm::vec3(0.7f, 0.7f, 0.0f),		//1
		glm::vec3(-0.7f, -0.7f, 0.0f),		//2
		glm::vec3(0.7f, -0.7f, 0.0f), };	//3

glm::vec3 Quack::squareScaleData[] = {
		glm::vec3(0.5f,0.5f,0.5f),       //0
		glm::vec3(0.5f,0.5f,0.5f),		//1
		glm::vec3(0.5f,0.5f,0.5f),		//2
		glm::vec3(0.5f,0.5f,0.5f), };	//3

Shader* Quack::m_mainShader;
OrthographicCamera* Quack::m_mainCamera;
#pragma endregion DeclareMembers

int Quack::InitEngine()
{

	s_running = true;

	m_mainCamera = new OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f);
	m_window = new Window("Quack", 1920, 1080, FullScreenMode::WINDOWED);

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
			m_mainShader->SetUniform4x4("projection", m_mainCamera->GetViewProjectionMatrix());
			break;
		}
		case 'S': // move camera down
		{
			glm::vec3 temp = m_mainCamera->GetPosition();
			temp.y -= 0.3f;
			m_mainCamera->SetPosition(temp);
			m_mainShader->SetUniform4x4("projection", m_mainCamera->GetViewProjectionMatrix());
			break;
		}
		case 'A': // move camera left
		{
			glm::vec3 temp = m_mainCamera->GetPosition();
			temp.x -= 0.3f;
			m_mainCamera->SetPosition(temp);
			m_mainShader->SetUniform4x4("projection", m_mainCamera->GetViewProjectionMatrix());
			break;
		}
		case 'D': // move camera right
		{
			glm::vec3 temp = m_mainCamera->GetPosition();
			temp.x += 0.3f;
			m_mainCamera->SetPosition(temp);
			m_mainShader->SetUniform4x4("projection", m_mainCamera->GetViewProjectionMatrix());
			break;
		}
		}
	}
}

void Quack::InitObjects()
{
	//Setup stuff
	float square1[] = {
		// positions          // colors           // texture coords
		-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
		 0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // bottom left
		 0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,  // top left 
		 -0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,  // top left 
		 -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,  // top left 
	};

	float square2[] = {
		// positions          // colors           // texture coords
		-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
		 0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // bottom left
		 0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,  // top left 
		 -0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,  // top left 
		 -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,  // top left 
	};



	//Create vertex buffer object, vertex array for square1
	glGenVertexArrays(1, &m_square1VAO);


	glGenBuffers(1, &m_square1VBO);

	//Bind vertex array object
	glBindVertexArray(m_square1VAO);

	//Copy the vertices into the buffer 
	glBindBuffer(GL_ARRAY_BUFFER, m_square1VBO);


	glBufferData(GL_ARRAY_BUFFER, sizeof(square1), square1, GL_STATIC_DRAW);


	// position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	// texture coord attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glBindVertexArray(0);

	//Texture setup
	m_duckTexture = new Texture("res/textures/duck.png");

	//Shader setup
	m_mainShader = new Shader("res/shaders/basic.shader");
	m_mainShader->Bind();
	m_mainShader->SetUniform4x4("u_viewProjection", m_mainCamera->GetViewProjectionMatrix());
	m_mainShader->Unbind();


	// dont think needed anymore?
	/*GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));*/
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

	if (m_jumping)
	{
		JumpDecrement();
	}

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

	// update camera projection
	m_mainShader->SetUniform4x4("projection", m_mainCamera->GetViewProjectionMatrix());
	// update camera view
	m_mainShader->SetUniform4x4("view", m_mainCamera->GetViewMatrix());

	// bind texture
	m_duckTexture->Bind();

	// bind vertex array object
	glBindVertexArray(m_square1VAO);
	for (unsigned int i = 0; i < 4; i++)
	{
		// render sqaure
		glm::mat4 model = glm::mat4(1.0f);
		// square position
		model = glm::translate(model, squarePositionData[i]);
		model = glm::scale(model, squareScaleData[i]);
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		m_mainShader->SetUniform4x4("model", model);
		// draw square
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}


	ImGUIInit();


	/* Swap front and back buffers */
	glfwSwapBuffers(m_window->GetGLFWWindow());
	/* Poll for and process events */
	glfwPollEvents();
}

void Quack::ImGUIInit()
{
	//position, center
	BoundingBox box1 = BoundingBox(glm::vec3(squarePositionData[0].x, squarePositionData[0].y, squarePositionData[0].z),
		//size
		glm::vec3(squareScaleData[0].x, squareScaleData[0].y, squareScaleData[0].z));

	BoundingBox box2 = BoundingBox(glm::vec3(squarePositionData[3].x, squarePositionData[3].y, squarePositionData[3].z),
		//size
		glm::vec3(squareScaleData[3].x, squareScaleData[3].y, squareScaleData[3].z));

	/// <summary>
	/// Start IMGUI window
	/// </summary>
	ImGui::Begin("My name is window, ImGui window");
	ImGui::Text("Hello");
	bool temp = false;

	/// <summary>
	/// Changing position of each square
	/// </summary>
	ImGui::DragFloat3("First Square", &squarePositionData[0].x, 0.001f);
	ImGui::DragFloat3("Second Square", &squarePositionData[1].x, 0.001f);
	ImGui::DragFloat3("Third Square", &squarePositionData[2].x, 0.001f);
	ImGui::DragFloat3("Fourth Square", &squarePositionData[3].x, 0.001f);

	/// <summary>
	/// Check box, needs to be static to be pressable
	/// </summary>
	static bool gravityEnabled = false;
	bool areColliding = false;
	ImGui::Checkbox("Gravity", &gravityEnabled);

	/// <summary>
	/// Check collision between box 1(top left) with box 4(bottom right)
	/// If they donw collide, add gravity to box 1
	/// </summary>
	if (p_QuackPhysics->BoxToBox(box1, box2))
	{
		areColliding = true;
		//std::cout << "The objects are collidiing";
	}
	else
	{
		areColliding = false;
		//std::cout << "The objects are not collidiing";
	}
	if (gravityEnabled && !areColliding)
	{
		Gravity();
	}

	/// <summary>
	/// Create button for jump
	/// </summary>
	if (ImGui::Button("Jump"))
	{
		Jump();
	}

	/// <summary>
	/// End of IMGUI window
	/// </summary>
	ImGui::End();

	/// <summary>
	/// Show the help commands window 
	/// </summary>
	ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Quack::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = JUMP_HEIGHT;
		m_jumping = true;
	}
}
void Quack::JumpDecrement()
{
	//adjust position
	squarePositionData[0].y += m_jump_force * m_deltaTime;

	//reduce jump force
	m_jump_force -= JUMP_HEIGHT * m_deltaTime;

	//is jump force 0?
	if (m_jump_force <= 0.0f)
	{
		m_jumping = false;
	}
}
void Quack::Gravity()
{
	float weight = 0.1f * GFORCE;
	squarePositionData[0].y -= weight * m_deltaTime;
}

void Quack::ShutDown()
{
	glDeleteVertexArrays(1, &m_square1VAO);

	glDeleteBuffers(1, &m_square1VBO);


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


