#include "Quack.h"
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
glm::vec4 Quack::m_lightPos;

GameObject* Quack::m_duck;

Shader* Quack::m_mainShader;
OrthographicCamera* Quack::m_mainCamera;
#pragma endregion DeclareMembers

int Quack::InitEngine()
{
	s_running = true;

	m_mainCamera = new OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f);
	m_mainCamera->SetPosition(glm::vec3(0.0f));
	m_lightPos = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);
	m_window = new Window("Quack", 1280, 960, FullScreenMode::WINDOWED);

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

	float lightNormals[] = {
		 0.0f, 0.0f, 0.0f,1.0f,
		 0.0f, 0.0f, 0.0f,1.0f,
		 1.0f, 1.0f,0.0f,1.0f,
		 1.0f, 1.0f,0.0f,1.0f,
		 0.0f, 1.0f,0.0f,1.0f,
		 0.0f, 0.0f,0.0f,1.0f
	};

	GameObjectData data;
	data.vertices.first = vertices;
	data.vertices.second = sizeof(vertices);
	data.colors.first = colors;
	data.colors.second = sizeof(colors);
	data.textCoords.first = textureCoords;
	data.textCoords.second = sizeof(textureCoords);
	data.lights.first = lightNormals;
	data.lights.second = sizeof(lightNormals);

	m_duck = new GameObject(data, "res/textures/duck.png");

	// Shader setup
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

	//Light
	m_mainShader->SetUniform4f("u_viewPos", 1.0f, 4.0f, 1.0f, 1.0f);

	//Material Struct
	m_mainShader->SetUniform1i("u_material.diffuse", 0);
	m_mainShader->SetUniform1i("u_material.specular", 1);
	m_mainShader->SetUniform1f("u_material.shine", 32.0f);

	//Directional Light
	m_mainShader->SetUniform4f("u_dirLight.direction", -0.2f, -1.0f, -0.3f, 1.0f);
	m_mainShader->SetUniform4f("u_dirLight.ambient", 0.05f, 2.05f, 2.05f, 1.0f);
	m_mainShader->SetUniform4f("u_dirLight.diffuse", 5.4f, 3.4f, 1.4f, 1.0f);
	m_mainShader->SetUniform4f("u_dirLight.specular", 3.5f, 5.5f, 2.5f, 1.0f);

	//Point Lights
	glm::vec3 pointLightPositions[] = {
	   glm::vec3(0.7f,  0.2f,  2.0f)
	};
	m_mainShader->SetUniform4f("u_pointLights[0].position" , pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z, 1.0f);
	m_mainShader->SetUniform4f("u_pointLights[0].ambient" , 5.0f, 5.05f, 5.05f, 1.0f);
	m_mainShader->SetUniform4f("u_pointLights[0].diffuse" , 2.8f, 2.8f, 2.8f, 1.0f);
	m_mainShader->SetUniform4f("u_pointLights[0].specular" , 1.0f, 1.0f, 1.0f, 1.0f);
	m_mainShader->SetUniform1f("u_pointLights[0].constant" , 1.0f);
	m_mainShader->SetUniform1f("u_pointLights[0].linear" , 0.09f);
	m_mainShader->SetUniform1f("u_pointLights[0].quadratic", 0.032f);

	//Spot Light
	m_mainShader->SetUniform4f("u_spotLight.position", m_mainCamera->GetPosition().x, m_mainCamera->GetPosition().y, m_mainCamera->GetPosition().z, 1.0f);
	m_mainShader->SetUniform4f("u_spotLight.direction", 2.0f, 2.0f, -1.0f, 1.0f);
	m_mainShader->SetUniform4f("u_spotLight.ambient", 5.0f, 5.0f, 5.0f, 1.0f);
	m_mainShader->SetUniform4f("u_spotLight.diffuse", 5.0f, 5.0f, 5.0f, 1.0f);
	m_mainShader->SetUniform4f("u_spotLight.specular", 5.0f, 5.0f, 5.0f, 1.0f);
	m_mainShader->SetUniform1f("u_spotLight.constant", 1.0f);
	m_mainShader->SetUniform1f("u_spotLight.linear", 0.09f);
	m_mainShader->SetUniform1f("u_spotLight.quadratic", 0.032f);
	m_mainShader->SetUniform1f("u_spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	m_mainShader->SetUniform1f("u_spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

	//Light Struct
	/*m_mainShader->SetUniform4f("u_light.ambient", 0.1f, 0.1f, 0.1f,  1.0f);
	m_mainShader->SetUniform4f("u_light.diffuse", 0.8f, 0.8f, 0.8f,  1.0f);
	m_mainShader->SetUniform4f("u_light.specular", 1.0f, 1.0f, 1.0f, 1.0f);
	m_mainShader->SetUniform4f("u_light.position", m_mainCamera->GetPosition().x, m_mainCamera->GetPosition().y, m_mainCamera->GetPosition().z, 1.0f);
	m_mainShader->SetUniform4f("u_light.direction", 0.0f, 0.0f, -1.0f, 1.0f);

	m_mainShader->SetUniform1f("u_light.constant", 1.0f);
	m_mainShader->SetUniform1f("u_light.linear", 0.09f);
	m_mainShader->SetUniform1f("u_light.quadratic", 0.032f);
	m_mainShader->SetUniform1f("u_light.cutOff", glm::cos(glm::radians(12.5f)));
	m_mainShader->SetUniform1f("u_light.outerCutOff", glm::cos(glm::radians(17.5f)));*/

	// render sqaure
	glm::mat4 model = glm::mat4(1.0f);
	// square position
	model = glm::translate(model, glm::vec3(0.0f,0.0f,0.0f));
	m_mainShader->SetUniform4x4("u_model", model);
	// draw square
	m_duck->Draw();

	ImGui::Begin("Set Object Color");
	ImGui::Text("Hello");
	ImGui::End();

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


