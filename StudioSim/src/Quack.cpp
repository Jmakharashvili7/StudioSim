#include "Quack.h"
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

VertexArray* Quack::m_squareVAO;
QuackPhysics* Quack::p_QuackPhysics;

bool Quack::m_jumping = false;
float Quack::m_jump_force = 10.0f;
bool Quack::m_thrown = false;
float Quack::m_throw_force = 10.0f;
Quack::Facing Quack::m_direction;
float Quack::m_rotation;
float Quack::m_projectileForce = 1.388f;


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

glm::vec4 Quack::m_objColor;
glm::vec4 Quack::m_lightPos;

glm::vec4 Quack::m_dirAmbient = { glm::vec4(0.5, 0.5, 0.5, 1.0f) };
glm::vec4 Quack::m_dirDiffuse = { glm::vec4(5.2f, 3.4f, 1.8f, 1.0f) };
glm::vec4 Quack::m_dirSpecular = { glm::vec4(3.4f, 5.43f, 2.4f, 1.0f) };

glm::vec3 Quack::m_pointLightPositions[] =
{
	glm::vec3(0.0f,  0.0f,  -2.0f),
	glm::vec3(0.0f,  0.0f,  -2.0f),
	glm::vec3(0.0f,  0.0f,  -2.0f)
};
glm::vec4 Quack::m_pointAmbient = { glm::vec4(-0.15f, 0.15f, 0.15f, 1.0f) };
glm::vec4 Quack::m_pointDiffuse = { glm::vec4(3.42f, 3.08f, 3.2f, 1.0f) };
glm::vec4 Quack::m_pointSpecular = { glm::vec4(1.3f, 0.6f, 1.85f, 1.0f) };

glm::vec4 Quack::m_spotAmbient = { glm::vec4(3.5f, 0.2f, 0.05f, 1.0f) };
glm::vec4 Quack::m_spotDiffuse = { glm::vec4(0.15f, 0.05f, 0.0f, 1.0f) };
glm::vec4 Quack::m_spotSpecular = { glm::vec4(0.0f,0.0f,0.0f, 1.0f) };

GameObject* Quack::m_duck;

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
		case 'I': // JUMP
		{
			Jump();
			break;
		}
		case 'L': // JUMP Right
		{
			m_direction = RIGHT;
			Jump();
			Projectile(m_projectileForce);
			break;
		}
		case 'J': // JUMP Left
		{
			m_direction = LEFT;
			Jump();
			Projectile(m_projectileForce);
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

	if (m_jumping)
	{
		JumpDecrement();
	}
	if (m_thrown)
	{
		ProjectileDecrement(m_direction);
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
	m_mainShader->SetUniform4x4("u_viewProjection", m_mainCamera->GetViewProjectionMatrix());
	m_mainShader->SetUniform4f("u_color", 0.5f, 0.5, 0.5f, 1.f);

	//Light
	m_mainShader->SetUniform4f("u_viewPos", 1.0f, 4.0f, 1.0f, 1.0f);

	//Material Struct
	m_mainShader->SetUniform1i("u_material.diffuse", 0);
	m_mainShader->SetUniform1i("u_material.specular", 1);
	m_mainShader->SetUniform1f("u_material.shine", 32.0f);

	//Directional Light
	m_mainShader->SetUniform4f("u_dirLight.direction", 0.0f, 0.0f, -0.3f, 1.0f);
	m_mainShader->SetUniform4f("u_dirLight.ambient", m_dirAmbient.x, m_dirAmbient.y, m_dirAmbient.z, m_dirAmbient.a);
	m_mainShader->SetUniform4f("u_dirLight.diffuse", m_dirDiffuse.x, m_dirDiffuse.y, m_dirDiffuse.z, m_dirDiffuse.a);
	m_mainShader->SetUniform4f("u_dirLight.specular", m_dirSpecular.x, m_dirSpecular.y, m_dirSpecular.z, m_dirSpecular.a);

	//Point Lights
	
	m_mainShader->SetUniform4f("u_pointLights[0].position", m_pointLightPositions[0].x, m_pointLightPositions[0].y, m_pointLightPositions[0].z, 1.0f);
	m_mainShader->SetUniform4f("u_pointLights[1].position", m_pointLightPositions[1].x, m_pointLightPositions[1].y, m_pointLightPositions[1].z, 1.0f);
	m_mainShader->SetUniform4f("u_pointLights[2].position", m_pointLightPositions[2].x, m_pointLightPositions[2].y, m_pointLightPositions[2].z, 1.0f);

	m_mainShader->SetUniform4f("u_pointLights[0].ambient", m_pointAmbient.x, m_pointAmbient.y, m_pointAmbient.z, m_pointAmbient.a);
	m_mainShader->SetUniform4f("u_pointLights[1].ambient", m_pointAmbient.x, m_pointAmbient.y, m_pointAmbient.z, m_pointAmbient.a);
	m_mainShader->SetUniform4f("u_pointLights[2].ambient", m_pointAmbient.x, m_pointAmbient.y, m_pointAmbient.z, m_pointAmbient.a);
	m_mainShader->SetUniform4f("u_pointLights[0].diffuse", m_pointDiffuse.x, m_pointDiffuse.y, m_pointDiffuse.z, m_pointDiffuse.a);
	m_mainShader->SetUniform4f("u_pointLights[1].diffuse", m_pointDiffuse.x, m_pointDiffuse.y, m_pointDiffuse.z, m_pointDiffuse.a);
	m_mainShader->SetUniform4f("u_pointLights[2].diffuse", m_pointDiffuse.x, m_pointDiffuse.y, m_pointDiffuse.z, m_pointDiffuse.a);
	m_mainShader->SetUniform4f("u_pointLights[0].specular", m_pointSpecular.x, m_pointSpecular.y, m_pointSpecular.z, m_pointSpecular.a);
	m_mainShader->SetUniform4f("u_pointLights[1].specular", m_pointSpecular.x, m_pointSpecular.y, m_pointSpecular.z, m_pointSpecular.a);
	m_mainShader->SetUniform4f("u_pointLights[2].specular", m_pointSpecular.x, m_pointSpecular.y, m_pointSpecular.z, m_pointSpecular.a);
	//dont change																													
	m_mainShader->SetUniform1f("u_pointLights[0].constant", 1.0f);
	m_mainShader->SetUniform1f("u_pointLights[1].constant", 1.0f);
	m_mainShader->SetUniform1f("u_pointLights[2].constant", 1.0f);
	m_mainShader->SetUniform1f("u_pointLights[0].linear", 0.09f);
	m_mainShader->SetUniform1f("u_pointLights[1].linear", 0.09f);
	m_mainShader->SetUniform1f("u_pointLights[2].linear", 0.09f);
	m_mainShader->SetUniform1f("u_pointLights[0].quadratic", 0.032f);
	m_mainShader->SetUniform1f("u_pointLights[1].quadratic", 0.032f);
	m_mainShader->SetUniform1f("u_pointLights[2].quadratic", 0.032f);

	//Spot Light
	m_mainShader->SetUniform4f("u_spotLight.position", m_mainCamera->GetPosition().x, m_mainCamera->GetPosition().y, m_mainCamera->GetPosition().z, 1.0f);
	m_mainShader->SetUniform4f("u_spotLight.direction", 0.0f, 0.0f, -0.3f, 1.0f);
	m_mainShader->SetUniform4f("u_spotLight.ambient", m_spotAmbient.x, m_spotAmbient.y, m_spotAmbient.z, m_spotAmbient.a);
	m_mainShader->SetUniform4f("u_spotLight.diffuse", m_spotDiffuse.x, m_spotDiffuse.y, m_spotDiffuse.z, m_spotDiffuse.a);
	m_mainShader->SetUniform4f("u_spotLight.specular", m_spotDiffuse.x, m_spotDiffuse.y, m_spotDiffuse.z, m_spotDiffuse.a);
	//dont change
	m_mainShader->SetUniform1f("u_spotLight.constant", 1.0f);
	m_mainShader->SetUniform1f("u_spotLight.linear", 0.09f);
	m_mainShader->SetUniform1f("u_spotLight.quadratic", 0.032f);
	m_mainShader->SetUniform1f("u_spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	m_mainShader->SetUniform1f("u_spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));



	// render sqaure
	glm::mat4 model = glm::mat4(1.0f);
	// square position
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	m_mainShader->SetUniform4x4("u_model", model);
	// draw square
	m_duck->Draw();

	// bind vertex array object
	//glBindVertexArray(m_square1VAO);
	for (unsigned int i = 0; i < 4; i++)
	{
		// render sqaure
		glm::mat4 model = glm::mat4(1.0f);
		// square position
		model = glm::translate(model, squarePositionData[i]);
		model = glm::scale(model, squareScaleData[i]);
		model = glm::rotate(model, glm::radians(m_rotation), glm::vec3(0, 0, 1));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		m_mainShader->SetUniform4x4("u_model", model);
		// bind texture
		m_duck->Draw();
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
	////position, center
	BoundingBox box1 = BoundingBox(glm::vec3(squarePositionData[0].x, squarePositionData[0].y, squarePositionData[0].z),
		//size
		glm::vec3(squareScaleData[0].x, squareScaleData[0].y, squareScaleData[0].z));

	BoundingBox box2 = BoundingBox(glm::vec3(squarePositionData[1].x, squarePositionData[1].y, squarePositionData[1].z),
		//size
		glm::vec3(squareScaleData[1].x, squareScaleData[1].y, squareScaleData[1].z));

	BoundingBox box3 = BoundingBox(glm::vec3(squarePositionData[2].x, squarePositionData[2].y, squarePositionData[2].z),
		//size
		glm::vec3(squareScaleData[2].x, squareScaleData[2].y, squareScaleData[2].z));

	BoundingBox box4 = BoundingBox(glm::vec3(squarePositionData[3].x, squarePositionData[3].y, squarePositionData[3].z),
		//size
		glm::vec3(squareScaleData[3].x, squareScaleData[3].y, squareScaleData[3].z));
	BoundingBox boxes[NUMBER_OF_SQUARES]{};
	for (int i = 0; i < NUMBER_OF_SQUARES; i++)
		boxes[i] = BoundingBox(glm::vec3(squarePositionData[i].x, squarePositionData[i].y, squarePositionData[i].z),
			//size
			glm::vec3(squareScaleData[i].x, squareScaleData[i].y, squareScaleData[i].z));
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
	ImGui::DragFloat("Rotation", &m_rotation, 0.1f);
	ImGui::DragFloat("Force", &m_projectileForce, 0.1f);


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
	for (int i = 0; i < NUMBER_OF_SQUARES; i++)
		for (int j = 0; j < NUMBER_OF_SQUARES && j != i; j++)
		{
			if (p_QuackPhysics->BoxToBox(box1, box3) ||
				p_QuackPhysics->BoxToBox(box1, box4))
			{
				areColliding = true;
				//std::cout << "The objects are collidiing";
			}
			else
			{
				areColliding = false;
				//std::cout << "The objects are not collidiing";
			}

		}
	if (gravityEnabled && !areColliding)
	{
		//QuackPhysics::Gravity();
		Gravity();
	}
	/// <summary>
	/// Create button for jump
	/// </summary>
	if (ImGui::Button("Jump"))
	{
		Jump();
		gravityEnabled = true;
	}
	ImGui::SameLine();
	/// <summary>
	/// Create button for throw left
	/// </summary>
	if (ImGui::Button("Throw left"))
	{
		Projectile(m_projectileForce);
		Jump();
		gravityEnabled = true;
		m_direction = Facing::LEFT;
	}
	ImGui::SameLine();
	/// <summary>
	/// Create button for throw right
	/// </summary>
	if (ImGui::Button("Throw right"))
	{
		Projectile(m_projectileForce);
		Jump();
		gravityEnabled = true;
		m_direction = Facing::RIGHT;
	}
	/// <summary>
	/// Light components directional, point, spotlight
	/// Changing the values how we want
	/// </summary>
	if (ImGui::TreeNode("Lights"))
	{
		/// <summary>
		/// Directional ambient, diffuse, specular
		/// </summary>
		if (ImGui::TreeNode("Directional"))
		{
			ImGui::DragFloat4("Ambient", &m_dirAmbient.x, 0.001f);
			ImGui::DragFloat4("Diffuse", &m_dirDiffuse.x, 0.001f);
			ImGui::DragFloat4("Specular", &m_dirSpecular.x, 0.001f);
			ImGui::TreePop();
		}
		/// <summary>
		/// Point ambient, diffuse, specular
		/// </summary>
		if (ImGui::TreeNode("Point"))
		{
			for (int i = 0; i < std::size(m_pointLightPositions); i++)
			{
				if (ImGui::TreeNode((void*)(intptr_t)i, "Point Light %d", i))
				{
					ImGui::DragFloat3("Position", &m_pointLightPositions[i].x, 0.01f);
					ImGui::DragFloat4("Ambient", &m_pointAmbient.x, 0.001f);
					ImGui::DragFloat4("Diffuse", &m_pointDiffuse.x, 0.001f);
					ImGui::DragFloat4("Specular", &m_pointSpecular.x, 0.001f);
					ImGui::TreePop();
				}
			}
			ImGui::TreePop();
		}
		/// <summary>
		/// Directional ambient, diffuse, specular
		/// </summary>
		if (ImGui::TreeNode("Spot"))
		{
			ImGui::DragFloat4("Ambient", &m_spotAmbient.x, 0.001f);
			ImGui::DragFloat4("Diffuse", &m_spotDiffuse.x, 0.001f);
			ImGui::DragFloat4("Specular", &m_spotSpecular.x, 0.001f);
			ImGui::TreePop();
		}
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

void Quack::Projectile(float force)
{
	if (!m_thrown)
	{
		m_throw_force = m_projectileForce;
		m_thrown = true;
	}
}

void Quack::ProjectileDecrement(Facing direction)
{
	if (direction == RIGHT)
		//adjust position
		squarePositionData[0].x += m_throw_force * m_deltaTime;
	else if (direction == LEFT)
		//adjust position
		squarePositionData[0].x -= m_throw_force * m_deltaTime;
	//squarePositionData[0].y += m_throw_force * m_deltaTime;

	//reduce jump force
	m_throw_force -= m_projectileForce / 2 * m_deltaTime;

	//is jump force 0?
	if (m_throw_force <= 0.0f)
	{
		m_thrown = false;
	}
}
void Quack::Gravity()
{
	//weight = mass * gforce
	float weight = 0.1f * GFORCE;
	squarePositionData[0].y -= weight * m_deltaTime;
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


