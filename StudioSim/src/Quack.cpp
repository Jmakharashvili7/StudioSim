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
#include "Animate.h"

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

glm::vec4 Quack::m_lightAmbient = { glm::vec4(1.0f,1.0f,1.0f, 1.0f) };

Actor* Quack::m_duck;
GameObject* Quack::m_ground;
GameObject* Quack::m_testSprite;

UILayer* Quack::m_uiMain;

Shader* Quack::m_mainShader;
Shader* Quack::m_3dShader;

OrthographicCamera* Quack::m_mainCamera;
PhysicsManager* Quack::m_physicsManager;
CollisionManager* Quack::m_collisionManager;
#pragma endregion DeclareMembers

void Quack::InitObjects()
{
	// Init game objects
	GameObjectData* groundObjectData = QuackEngine::JsonLoader::LoadObject2D("res/ObjectData/Square.json");
	const TransformData groundTransformData = TransformData(glm::vec3(0.0f, -750.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	const CollisionData groundCollisionData = CollisionData(glm::vec3(groundTransformData.position.x/1280, groundTransformData.position.y/960, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	const TextureData groundTextureData = TextureData("res/textures/concretefloor.png", GL_RGB, GL_RGB);
	m_ground = CreateNewGameObject(groundObjectData, groundTransformData, groundCollisionData, groundTextureData);

	// Init actors
	GameObjectData* duckObjectData = QuackEngine::JsonLoader::LoadObject2D("res/ObjectData/Square.json");
	const TransformData duckTransformData = TransformData(glm::vec3(1200.0f, 600.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	const CollisionData duckCollisionData = CollisionData(glm::vec3(duckTransformData.position.x / 1280, duckTransformData.position.y / 960, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	const TextureData duckTextureData = TextureData("res/textures/duck2.png", GL_RGBA, GL_RGBA);
	const PhysicsData duckPhysicsData = PhysicsData(true, 150.0f, 5000.0f);
	const AnimationData duckAnimationData = AnimationData();
	m_duck = CreateNewActor(duckObjectData, duckTransformData, duckCollisionData, duckTextureData, duckPhysicsData, duckAnimationData);
}

void Quack::SetupShaders()
{
#ifdef _2D_SHADER
	// Shader setup
	m_mainShader = new Shader("res/shaders/basic.shader");
	m_mainShader->Bind();
	m_mainShader->SetUniform4x4("u_viewProjection", m_mainCamera->GetViewProjectionMatrix());
	m_mainShader->Unbind();

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

	m_mainCamera = new OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f);
	m_mainCamera->SetPosition(glm::vec3(0.0f));
	m_window = new Window("Quack", 1280, 960, FullScreenMode::WINDOWED);
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

	///
	///	Initialize IMGUI
	/// 
	m_uiMain->OnAttach();

	/* Initialize the keyboard class*/
	KeyboardClass::Init();
	glfwSetKeyCallback(m_window->GetGLFWWindow(), QuackEngine::key_callback);
	glfwSetWindowCloseCallback(m_window->GetGLFWWindow(), QuackEngine::window_close_callback);

	InitObjects();
	SetupShaders();

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
			/*if (m_duck)
			{
				m_duck->AddImpulseForce(glm::vec3(-1000.0f, 5000.0f, 0.0f));
			}*/
			m_duck->AdjustPosition(glm::vec3(1500.0f * m_gameTimer.GetDeltaTime(), 0.0f, 0.0f));
			break; 
		}
		case 'L': // JUMP Right
		{
			//m_duck->SetPosition(glm::vec3(-600.0f, -600.0f, 0.0f));
			m_duck->AdjustPosition(glm::vec3(-1500.0f * m_gameTimer.GetDeltaTime(), 0.0f, 0.0f));
			//m_duck->AdjustScale(glm::vec3(1.25f * m_gameTimer.GetDeltaTime(), 1.25f * m_gameTimer.GetDeltaTime(), 0.f));
			break;
		}
		case 'J': // JUMP Left
		{
			//m_duck->SetRotationAroundPivot(glm::vec3(600.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 90.0f));
			//m_duck->AdjustRotation(glm::vec3(0.0f, 0.0f, 10.0f));
			m_duck->Jump();
			break;
		}
		}
	}
}

void Quack::Update()
{
	m_gameTimer.Tick();

	// get mouse position
	double xpos, ypos;
	glfwGetCursorPos(m_window->GetGLFWWindow(), &xpos, &ypos);

	HandleInput();
}

void Quack::RenderUpdate()
{
	/* Render here */
	glClearColor(m_uiMain->GetColor().x, m_uiMain->GetColor().y, m_uiMain->GetColor().z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

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

	// Draw game objects
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject) gameObject->Draw(m_mainShader);
	}

	// Draw layers 
	for (Layer* layer : m_layerStack->GetLayers())
	{
		if (layer) layer->OnUpdate();
	}

	/* Swap front and back buffers */
	glfwSwapBuffers(m_window->GetGLFWWindow());
	/* Poll for and process events */
	glfwPollEvents();
}

void Quack::PhysicsUpdate()
{
	const float deltaTime = m_gameTimer.GetDeltaTime();
	m_collisionManager->Update(deltaTime);
	m_physicsManager->Update(deltaTime);
}

void Quack::ImGUIInit()
{

}

GameObject* Quack::CreateNewGameObject(GameObjectData* objectData, const TransformData& transformData, const CollisionData& collisionData, const TextureData& textureData)
{
	GameObject* createdGameObject = nullptr;
	createdGameObject = new GameObject(objectData, transformData, collisionData, textureData);

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

Actor* Quack::CreateNewActor(GameObjectData* objectData, const TransformData& transformData, const CollisionData& collisionData, const TextureData& textureData, const PhysicsData& physicsData, const AnimationData& animationData)
{
	Actor* createdActor = nullptr;
	createdActor = new Actor(objectData, transformData, collisionData, textureData, physicsData, animationData);

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


