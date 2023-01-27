#include "Quack.h"
#include "Shader.h"
#include "Texture.h"
#include "IndexBuffer.h"
#include "KeyboardClass.h"
#include "MouseClass.h"
#include "QuackPhysics.h"
#include "Animate.h"
#include "QuackCallbacks.h"
#include "EngineManager.h"
#include "Renderer.h"

//#define _2D_SHADER
#include "Animate.h"
#include "JsonLoader.h"
#include "LayerStack.h"
#include "UIRenderer.h"
#include "UILayer.h"

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

GameTimer Quack::m_gameTimer;

LayerStack* Quack::m_layerStack;
std::vector<GameObject*> Quack::m_gameObjects;
std::vector<Actor*> Quack::m_gameActors;

int Quack::m_frameCounter;
int Quack::m_currentFrameRate;

FrameBuffer* Quack::m_frameBuffer;

VertexArray* Quack::m_squareVAO;
QuackPhysics* Quack::p_QuackPhysics;

bool Quack::m_jumping = false;
float Quack::m_jump_force = 10.0f;
bool Quack::m_thrown = false;
float Quack::m_throw_force = 10.0f;
Quack::Facing Quack::m_direction;
float Quack::m_rotation;
float Quack::m_projectileForce = 1.388f;

Grid<PathNode> Quack::m_grid;

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

glm::vec4 Quack::m_lightAmbient = { glm::vec4(1.0f,1.0f,1.0f, 1.0f) };

Actor* Quack::m_duck;
GameObject* Quack::m_ground;
GameObject* Quack::m_testSprite;

UILayer* Quack::m_uiMain;

Shader* Quack::m_mainShader;
Shader* Quack::m_3dShader;
Shader* Quack::m_primitiveShader;

OrthographicCamera* Quack::m_mainCamera;
PhysicsManager* Quack::m_physicsManager;
CollisionManager* Quack::m_collisionManager;

float Quack::viewStart_x;
float Quack::viewStart_y;
float Quack::viewEnd_x;
float Quack::viewEnd_y;

#pragma endregion DeclareMembers

void Quack::InitObjects()
{

	// Init game objects
	GameObjectData* groundObjectData = QuackEngine::JsonLoader::LoadObject2D("res/ObjectData/Square.json");
	const TransformData groundTransformData = TransformData(Vector3(0.0f, -2.5f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 0.6f, 1.0f));
	const CollisionData groundCollisionData = CollisionData(groundTransformData.position, groundTransformData.scale);
	const TextureData groundTextureData = TextureData("res/textures/concretefloor.png", GL_RGB, GL_RGB);
	m_ground = CreateNewGameObject("ground", groundObjectData, groundTransformData, groundCollisionData, groundTextureData);

	// Init actors
	GameObjectData* duckObjectData = QuackEngine::JsonLoader::LoadObject2D("res/ObjectData/Square.json");
	const TransformData duckTransformData = TransformData(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f));
	const CollisionData duckCollisionData = CollisionData(duckTransformData.position, duckTransformData.scale);
	const TextureData duckTextureData = TextureData("res/textures/duck2.png", GL_RGBA, GL_RGBA);
	const PhysicsData duckPhysicsData = PhysicsData(true, 1.0f, 25.0f);
	const AnimationData duckAnimationData = AnimationData();
	m_duck = CreateNewActor("duck", duckObjectData, duckTransformData, duckCollisionData, duckTextureData, duckPhysicsData, duckAnimationData);

	// Update engine manager
	m_grid = Grid<PathNode>(30, 30, 0.5, { -6,-6,0 });
	EngineManager::SetGameObjects(m_gameObjects);
}

void Quack::SetupShaders()
{
#ifdef _2D_SHADER

	// Shader setup
	m_mainShader = new Shader("res/shaders/basic.shader");
	m_mainShader->Bind();
	m_mainShader->SetUniform4x4("u_viewProjection", m_mainCamera->GetViewProjectionMatrix());
	m_mainShader->Unbind();

	m_primitiveShader = new Shader("res/shaders/Primitive.shader");
	m_primitiveShader->Bind();
	m_primitiveShader->SetUniform4x4("u_viewProjection", m_mainCamera->GetViewProjectionMatrix());
	m_primitiveShader->Unbind();

#endif // _2D_SHADER

#ifdef _3D_SHADER

	//3D Shader setup
	m_3dShader = new Shader("res/shaders/3Dbasic.shader");
	m_3dShader->Bind();
	m_3dShader->SetUniform4x4("u_viewProjection", m_mainCamera->GetViewProjectionMatrix());
	m_3dShader->Unbind();

#endif // !_3D_SHADER
}

int Quack::InitEngine()
{
	s_running = true;

	m_mainCamera = new OrthographicCamera(-5.0f, 5.0f, -5.0f, 5.0f);
	m_mainCamera->SetPosition(glm::vec3(0.0f));
	m_window = new Window("Quack", 1920, 1080, FullScreenMode::WINDOWED);
	m_layerStack = new LayerStack();
	m_uiMain = new UILayer();
	m_physicsManager = new PhysicsManager();
	m_collisionManager = new CollisionManager();

	m_layerStack->PushOverlay(m_uiMain);

	// Initilaize window
	m_window->UseWindow();

	m_gameTimer.Start();

	/* Initialize the Glew Library*/
	glewExperimental = GL_TRUE;
	glewInit();

	/* Initialize the input classes */
	KeyboardClass::Init();
	MouseClass::Init();

	/* Setup glfw callbacks */
	glfwSetKeyCallback(m_window->GetGLFWWindow(), QuackEngine::key_callback);
	glfwSetWindowCloseCallback(m_window->GetGLFWWindow(), QuackEngine::window_close_callback);
	glfwSetWindowSizeCallback(m_window->GetGLFWWindow(), QuackEngine::window_size_callback);
	glfwSetMouseButtonCallback(m_window->GetGLFWWindow(), QuackEngine::mouse_button_callback);
	glfwSetCursorPosCallback(m_window->GetGLFWWindow(), QuackEngine::cursor_position_callback);


	FrameBufferSpecificiation fbs;
	fbs.width = m_window->GetWidth();
	fbs.height = m_window->GetHeight();
	m_frameBuffer = new FrameBuffer(fbs);

	///
	///	Initialize IMGUI (Must be after keyboard and mouse callbacks)
	/// 
	m_uiMain->OnAttach();

	InitObjects();
	SetupShaders();
	m_uiMain->InitWindows(); // should always be after init objects

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
			if (m_uiMain->GetViewport()->GetIsFocused())
			{
				glm::vec3 temp = m_mainCamera->GetPosition();
				temp.y += 0.3f;
				m_mainCamera->SetPosition(temp);
			}
			break;
		}
		case 'S': // move camera down
		{
			if (m_uiMain->GetViewport()->GetIsFocused())
			{
				glm::vec3 temp = m_mainCamera->GetPosition();
				temp.y -= 0.3f;
				m_mainCamera->SetPosition(temp);
			}
			break;
		}
		case 'A': // move camera left
		{
			if (m_uiMain->GetViewport()->GetIsFocused())
			{
				glm::vec3 temp = m_mainCamera->GetPosition();
				temp.x -= 0.3f;
				m_mainCamera->SetPosition(temp);
			}
			break;
		}
		case 'D': // move camera right
		{
			if (m_uiMain->GetViewport()->GetIsFocused())
			{
				glm::vec3 temp = m_mainCamera->GetPosition();
				temp.x += 0.3f;
				m_mainCamera->SetPosition(temp);
			}
			break;
		}
		case 'J': // MOVE LEFT
		{
			m_duck->AdjustPosition(Vector3(-2.5f * m_gameTimer.GetDeltaTime(), 0.0f, 0.0f));
			break;
		}
		case 'L': // MOVE RIGHT
		{
			m_duck->AdjustPosition(Vector3(2.5f * m_gameTimer.GetDeltaTime(), 0.0f, 0.0f));
			break;
		}
		case 'H': // MOVE UP
		{
			m_duck->AdjustPosition(Vector3(0.0f, -2.5f * m_gameTimer.GetDeltaTime(), 0.0f));
			break;
		}
		case 'Y': // MOVE DOWN
		{
			m_duck->AdjustPosition(Vector3(0.0f, 2.5f * m_gameTimer.GetDeltaTime(), 0.0f));
			break;
		}
		case 'O': // JUMP UP
		{
			m_duck->Jump();
			break;
		}
		}
	}

	if (!MouseClass::IsEventBufferEmpty())
	{
		MouseEvent e = MouseClass::ReadEvent();
		//Size of viewport
		double port_x = m_uiMain->GetViewport()->GetSize().x;
		double port_y = m_uiMain->GetViewport()->GetSize().y;
		//Size of whole window
		double screen_x = m_window->GetWidth();
		double screen_y = m_window->GetHeight();

		if (e.GetType() == MouseEvent::EventType::L_CLICK)
		{
			//Current mouse position within viewport scale
			viewStart_x = ImGui::GetMousePos().x - ViewportUI::startViewportX;
			viewStart_y = ImGui::GetMousePos().y - ViewportUI::startViewportY;

			//Only counting the click within viewport boundary
			if ((viewStart_x >= 0 && viewStart_y >= 0) && (viewStart_x <= port_x && viewStart_y <= port_y))
			{
				Vector2 mousePos;

				mousePos.x = ImGui::GetMousePos().x;
				mousePos.y = ImGui::GetMousePos().y;

				//get the camera viewProjection matrix, and inverse it
				glm::mat4 auxCamera = m_mainCamera->GetViewProjectionMatrix();
				glm::mat4 invCamera = glm::inverse(auxCamera);

				//new position of the duck based on the mouse's position normalised based on 
				//the viewport
				float newposition_x = (viewStart_x / (port_x / 2) - 1),
					newposition_y = -(viewStart_y / (port_y / 2) - 1);

				Vector3 ndc = Vector3(newposition_x, newposition_y, 0);

				//Does the inverse of the camera, turning the screen's 2D coord into a world space 3D coord
				ndc.x = invCamera[0].x * ndc.x + invCamera[1].x * ndc.y + invCamera[2].x * ndc.z;
				ndc.y = invCamera[0].y * ndc.x + invCamera[1].y * ndc.y + invCamera[2].y * ndc.z;
				ndc.z = invCamera[0].z * ndc.x + invCamera[1].z * ndc.y + invCamera[2].z * ndc.z;

				//get the int part of the number
				int integer_x = (int)ndc.x;
				int integer_y = (int)ndc.y;
				int integer_z = (int)ndc.z;

				//get the decimals of the number
				float floater_x = ndc.x - integer_x;
				float floater_y = ndc.y - integer_y;
				float floater_z = ndc.z - integer_z;

				std::cout << "Click Y:  " << ndc.y << "			Int Y:  " << integer_y << "			Floater Y:  " << floater_y << std::endl;

				//check if the number is closer to 0 or to 0.5
				if (floater_x >= 0)
				{
					if (floater_x >= 0.25 && floater_x <= 0.75)
						floater_x = 0.5;
					else if (floater_x < 0.25)
						floater_x = 0.0f;
					else if (floater_x > 0.75)
						floater_x = 1.0f;
				}
				else
				{
					if (floater_x <= -0.25 && floater_x >= -0.75)
						floater_x = -0.5;
					else if (floater_x > -0.25)
						floater_x = 0.0f;
					else if (floater_x < -0.75)
						floater_x = -1.0f;
				}
				if (floater_y >= 0)
				{
					if (floater_y >= 0.25 && floater_y <= 0.75)
						floater_y = 0.5;
					else if (floater_y < 0.25)
						floater_y = 0.0f;
					else if (floater_y > 0.75)
						floater_y = 1.0f;
				}
				else
				{
					if (floater_y <= -0.25 && floater_y >= -0.75)
						floater_y = -0.5;
					else if (floater_y > -0.25)
						floater_y = 0.0f;
					else if (floater_y < -0.75)
						floater_y = -1.0f;
				}
				if (integer_z > 0)
				{
					if (floater_z >= 0.25 && floater_z <= 0.75)
						floater_z = -0.5;
					else if (floater_z < 0.25)
						floater_z = 0.0f;
					else if (floater_z > 0.75)
						floater_z = -1.0f;
				}
				else
				{
					if (floater_z <= -0.25 && floater_z >= -0.75)
						floater_z = 0.5;
					else if (floater_z > -0.25)
						floater_z = 0.0f;
					else if (floater_z < -0.75)
						floater_z = -1.0f;
				}
				float finalPosition_x, finalPosition_y, finalPosition_z;
				//calculate the final position X
				if (integer_x > 0)
				{
					finalPosition_x = integer_x + floater_x;
				}
				else if (integer_x == 0)
				{
					finalPosition_x = floater_x;
				}
				else
				{
					finalPosition_x = integer_x + floater_x;
				}
				//if(integer_x==0)

				//calculate the final position Y
				if (integer_y > 0)
				{
					finalPosition_y = integer_y + floater_y;
				}
				else if (integer_y == 0)
				{
					finalPosition_y = floater_y;
				}
				else
				{
					finalPosition_y = integer_y + floater_y;
				}
				//calculate the final position Z
				if (integer_z > 0)
				{
					finalPosition_z = integer_z + floater_z;
				}
				else if (integer_z == 0)
				{
					finalPosition_z = floater_z;
				}
				else
				{
					finalPosition_z = integer_z + floater_z;
				}

				std::cout << "Final Y: " << finalPosition_y << std::endl;

				Vector3 finalPosition = Vector3(finalPosition_x, finalPosition_y, finalPosition_z);

				//Vector3 *a = new Vector3(newposition_x * invCamera, newposition_y * invCamera,0.0f);
				m_duck->SetPosition(finalPosition);
				/*std::cout << "Mouse Screen X: " << MouseClass::GetPosX() << std::endl;
				std::cout << "Mouse Screen Y: " << MouseClass::GetPosY() << std::endl;
				std::cout << "viewStart_x X: " << viewStart_x << std::endl;
				std::cout << "viewStart_y Y: " << viewStart_y << std::endl;
				std::cout << "Duck pos X: " << m_duck->GetPosition().x << std::endl;
				std::cout << "Duck pos Y: " << m_duck->GetPosition().y << std::endl;*/
			}
			//m_duck->GetPosition();
		}
		if (e.GetType() == MouseEvent::EventType::R_CLICK)
		{
			std::cout << "Viewport X size: " << port_x << std::endl;
			std::cout << "Viewport Y size: " << port_y << std::endl;
			std::cout << "Screen X size: " << screen_x << std::endl;
			std::cout << "Screen Y size: " << screen_y << std::endl;
		}
		if (e.GetType() == MouseEvent::EventType::MOVE)
		{

		}
		/*
		if (e.GetType() == MouseEvent::EventType::R_CLICK)
		{
			viewEnd_x = ImGui::GetMousePos().x - ViewportUI::startViewportX;
			viewEnd_y = ImGui::GetMousePos().y - ViewportUI::startViewportY;

			viewDiff_x = viewEnd_x - viewStart_x;
			viewDiff_y = viewEnd_y - viewStart_y;

			m_duck->AdjustPosition(Vector3(viewDiff_x * m_gameTimer.GetDeltaTime(), 0.0f, 0.0f));
			m_duck->AdjustPosition(Vector3(0.0f, viewDiff_y * m_gameTimer.GetDeltaTime(), 0.0f));
		}
		*/
	}
}

void Quack::HandleLights()
{
#ifdef _3D_SHADER
	// bind shader
	m_3dShader->Bind();
	m_3dShader->SetUniform4x4("u_viewProjection", m_mainCamera->GetViewProjectionMatrix());
	m_3dShader->SetUniform4f("u_color", 0.5f, 0.5, 0.5f, 1.f);
	//Light
	m_3dShader->SetUniform4f("u_viewPos", 1.0f, 4.0f, 1.0f, 1.0f);
	//Material Struct
	m_3dShader->SetUniform1i("u_material.diffuse", 0);
	m_3dShader->SetUniform1i("u_material.specular", 1);
	m_3dShader->SetUniform1f("u_material.shine", 32.0f);
	//Directional Light
	m_3dShader->SetUniform4f("u_dirLight.direction", 0.0f, 0.0f, -0.3f, 1.0f);
	m_3dShader->SetUniform4f("u_dirLight.ambient", m_dirAmbient.x, m_dirAmbient.y, m_dirAmbient.z, m_dirAmbient.a);
	m_3dShader->SetUniform4f("u_dirLight.diffuse", m_dirDiffuse.x, m_dirDiffuse.y, m_dirDiffuse.z, m_dirDiffuse.a);
	m_3dShader->SetUniform4f("u_dirLight.specular", m_dirSpecular.x, m_dirSpecular.y, m_dirSpecular.z, m_dirSpecular.a);

	//Point Lights

	m_3dShader->SetUniform4f("u_pointLights[0].position", m_pointLightPositions[0].x, m_pointLightPositions[0].y, m_pointLightPositions[0].z, 1.0f);
	m_3dShader->SetUniform4f("u_pointLights[1].position", m_pointLightPositions[1].x, m_pointLightPositions[1].y, m_pointLightPositions[1].z, 1.0f);
	m_3dShader->SetUniform4f("u_pointLights[2].position", m_pointLightPositions[2].x, m_pointLightPositions[2].y, m_pointLightPositions[2].z, 1.0f);

	m_3dShader->SetUniform4f("u_pointLights[0].ambient", m_pointAmbient.x, m_pointAmbient.y, m_pointAmbient.z, m_pointAmbient.a);
	m_3dShader->SetUniform4f("u_pointLights[1].ambient", m_pointAmbient.x, m_pointAmbient.y, m_pointAmbient.z, m_pointAmbient.a);
	m_3dShader->SetUniform4f("u_pointLights[2].ambient", m_pointAmbient.x, m_pointAmbient.y, m_pointAmbient.z, m_pointAmbient.a);
	m_3dShader->SetUniform4f("u_pointLights[0].diffuse", m_pointDiffuse.x, m_pointDiffuse.y, m_pointDiffuse.z, m_pointDiffuse.a);
	m_3dShader->SetUniform4f("u_pointLights[1].diffuse", m_pointDiffuse.x, m_pointDiffuse.y, m_pointDiffuse.z, m_pointDiffuse.a);
	m_3dShader->SetUniform4f("u_pointLights[2].diffuse", m_pointDiffuse.x, m_pointDiffuse.y, m_pointDiffuse.z, m_pointDiffuse.a);
	m_3dShader->SetUniform4f("u_pointLights[0].specular", m_pointSpecular.x, m_pointSpecular.y, m_pointSpecular.z, m_pointSpecular.a);
	m_3dShader->SetUniform4f("u_pointLights[1].specular", m_pointSpecular.x, m_pointSpecular.y, m_pointSpecular.z, m_pointSpecular.a);
	m_3dShader->SetUniform4f("u_pointLights[2].specular", m_pointSpecular.x, m_pointSpecular.y, m_pointSpecular.z, m_pointSpecular.a);
	//dont change																													
	m_3dShader->SetUniform1f("u_pointLights[0].constant", 1.0f);
	m_3dShader->SetUniform1f("u_pointLights[1].constant", 1.0f);
	m_3dShader->SetUniform1f("u_pointLights[2].constant", 1.0f);
	m_3dShader->SetUniform1f("u_pointLights[0].linear", 0.09f);
	m_3dShader->SetUniform1f("u_pointLights[1].linear", 0.09f);
	m_3dShader->SetUniform1f("u_pointLights[2].linear", 0.09f);
	m_3dShader->SetUniform1f("u_pointLights[0].quadratic", 0.032f);
	m_3dShader->SetUniform1f("u_pointLights[1].quadratic", 0.032f);
	m_3dShader->SetUniform1f("u_pointLights[2].quadratic", 0.032f);

	//Spot Light
	m_3dShader->SetUniform4f("u_spotLight.position", m_mainCamera->GetPosition().x, m_mainCamera->GetPosition().y, m_mainCamera->GetPosition().z, 1.0f);
	m_3dShader->SetUniform4f("u_spotLight.direction", 0.0f, 0.0f, -0.3f, 1.0f);
	m_3dShader->SetUniform4f("u_spotLight.ambient", m_spotAmbient.x, m_spotAmbient.y, m_spotAmbient.z, m_spotAmbient.a);
	m_3dShader->SetUniform4f("u_spotLight.diffuse", m_spotDiffuse.x, m_spotDiffuse.y, m_spotDiffuse.z, m_spotDiffuse.a);
	m_3dShader->SetUniform4f("u_spotLight.specular", m_spotDiffuse.x, m_spotDiffuse.y, m_spotDiffuse.z, m_spotDiffuse.a);
	//dont change
	m_3dShader->SetUniform1f("u_spotLight.constant", 1.0f);
	m_3dShader->SetUniform1f("u_spotLight.linear", 0.09f);
	m_3dShader->SetUniform1f("u_spotLight.quadratic", 0.032f);
	m_3dShader->SetUniform1f("u_spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	m_3dShader->SetUniform1f("u_spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

#endif // _3D_SHADER

#ifdef _2D_SHADER

	// bind shader
	m_mainShader->Bind();
	m_mainShader->SetUniform4x4("u_viewProjection", m_mainCamera->GetViewProjectionMatrix());

	m_mainShader->SetUniform4f("u_lightColor", 1.0f, 1.0f, 1.0f, 1.0f);

	//Ambient light
	m_mainShader->SetUniform4f("u_light.position", 0.0f, 0.0f, 0.0f, -2.0f);
	m_mainShader->SetUniform4f("u_light.ambient", 1.0f, 1.0f, 1.0f, 1.0f);

#endif // _2D_SHADER
		}

void Quack::Update()
{
	m_gameTimer.Tick();

	// get mouse position
	double xpos, ypos;
	glfwGetCursorPos(m_window->GetGLFWWindow(), &xpos, &ypos);
	//glfwGetCursorPos(m_window->GetGLFWWindow(), &m_mouseX, &m_mouseY);

	HandleInput();
}

void Quack::RenderUpdate()
{
	glClearColor(m_uiMain->GetColor().x, m_uiMain->GetColor().y, m_uiMain->GetColor().z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// Draw layers 
	for (Layer* layer : m_layerStack->GetLayers())
	{
		if (layer) layer->OnUpdate();
	}

	m_frameBuffer->Bind();
	/* Render here */
	glClearColor(m_uiMain->GetColor().x, m_uiMain->GetColor().y, m_uiMain->GetColor().z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	HandleLights();

	// Draw game objects
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject) gameObject->Draw(m_mainShader);
	}

	glm::vec3 p0 = { 1.0f, 1.0f, 1.0f };
	glm::vec3 p1 = { 0.0f, 0.0f, 1.0f };
	glm::vec4 color = { 0.0f, 0.0f, 0.0f, 0.0f };

	m_primitiveShader->Bind();
	m_primitiveShader->SetUniform4x4("u_viewProjection", m_mainCamera->GetViewProjectionMatrix());
	Renderer::DrawDebugLines();
	m_primitiveShader->Unbind();

	/* Swap front and back buffers */
	glfwSwapBuffers(m_window->GetGLFWWindow());
	/* Poll for and process events */
	glfwPollEvents();

	m_frameBuffer->Unbind();
}

void Quack::PhysicsUpdate()
{
	const float deltaTime = m_gameTimer.GetDeltaTime();
	//m_collisionManager->Update(deltaTime);
	//m_physicsManager->Update(deltaTime);
}

void Quack::ImGUIInit()
{

}

GameObject* Quack::CreateNewGameObject(std::string name, GameObjectData* objectData, const TransformData& transformData, const CollisionData& collisionData, const TextureData& textureData)
{
	GameObject* createdGameObject = nullptr;
	createdGameObject = new GameObject(name, objectData, transformData, collisionData, textureData);

	if (createdGameObject)
	{
		m_gameObjects.push_back(createdGameObject);

		if (collisionData.collisionType != CollisionType::NONE)
		{
			// Update collision managers game object array
			m_collisionManager->AddGameObject(createdGameObject);
		}
	}

	return createdGameObject;
}

Actor* Quack::CreateNewActor(std::string name, GameObjectData* objectData, const TransformData& transformData, const CollisionData& collisionData, const TextureData& textureData, const PhysicsData& physicsData, const AnimationData& animationData)
{
	Actor* createdActor = nullptr;
	createdActor = new Actor(name, objectData, transformData, collisionData, textureData, physicsData, animationData);

	if (createdActor)
	{
		m_gameObjects.push_back(createdActor);
		m_gameActors.push_back(createdActor);

		if (collisionData.collisionType != CollisionType::NONE)
		{
			// Update collision managers game object array
			m_collisionManager->AddGameObject(createdActor);
		}

		if (physicsData.bsimulateGravity)
		{
			// Update physics managers actor object array
			m_physicsManager->AddGameActor(createdActor);
		}
	}

	return createdActor;
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

void Quack::ShutDown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(m_window->GetGLFWWindow());
	glfwTerminate();
};


