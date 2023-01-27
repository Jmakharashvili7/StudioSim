#include "Quack.h"
#include "Shader.h"
#include "Texture.h"
#include "IndexBuffer.h"
#include "KeyboardClass.h"
#include "MouseClass.h"
#include "Animate.h"
#include "QuackCallbacks.h"
#include "EngineManager.h"
#include "Renderer.h"
#include "Animate.h"
#include "JsonLoader.h"
#include "LayerStack.h"
#include "UIRenderer.h"
#include "UILayer.h"
#include "Scene.h"

#pragma region DeclareMembers
bool Quack::s_glfwInitialised = false;
bool Quack::s_running = false;
Window* Quack::m_window;

GameTimer Quack::m_gameTimer;

LayerStack* Quack::m_layerStack;

int Quack::m_frameCounter;
int Quack::m_currentFrameRate;

FrameBuffer* Quack::m_frameBuffer;

UILayer* Quack::m_uiMain;

Scene Quack::m_mainScene;

OrthographicCamera* Quack::m_mainCamera;
#pragma endregion DeclareMembers

int Quack::InitEngine()
{
	s_running = true;

	m_window = new Window("Quack", 1920, 1080, FullScreenMode::WINDOWED);
	m_layerStack = new LayerStack();
	m_uiMain = new UILayer();

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

	m_mainScene = Scene("MainScene", m_uiMain, m_window);
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
			m_mainScene = Scene("MainScene", m_uiMain, m_window);
			break; 
		}
		}
	}

	if (!MouseClass::IsEventBufferEmpty())
	{
		MouseEvent e = MouseClass::ReadEvent();

		if (e.GetType() == MouseEvent::EventType::L_CLICK)
		{
		}
		if (e.GetType() == MouseEvent::EventType::R_CLICK)
		{

		}
		if (e.GetType() == MouseEvent::EventType::MOVE)
		{

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

	m_mainScene.Render();

	/* Swap front and back buffers */
	glfwSwapBuffers(m_window->GetGLFWWindow());
	/* Poll for and process events */
	glfwPollEvents();

	m_frameBuffer->Unbind();
}

//GameObject* Quack::CreateNewGameObject(std::string name, GameObjectData* objectData, const TransformData& transformData, const CollisionData& collisionData, const TextureData& textureData)
//{
//	GameObject* createdGameObject = nullptr;
//	createdGameObject = QuackEngine::JsonLoader::LoadGameObject2D("res/ObjectData/floor.json");
//
//	if (createdGameObject)
//	{
//		m_gameObjects.push_back(createdGameObject);
//
//		if (collisionData.collisionType != CollisionType::NONE)
//		{
//			// Update collision managers game object array
//			m_collisionManager->AddGameObject(createdGameObject);
//		}
//	}
//
//	return createdGameObject;
//}
//
//Actor* Quack::CreateNewActor(std::string name, GameObjectData* objectData, const TransformData& transformData, const CollisionData& collisionData, const TextureData& textureData, const PhysicsData& physicsData, const AnimationData& animationData)
//{
//	Actor* createdActor = nullptr;
//	createdActor = QuackEngine::JsonLoader::LoadActor2D("res/ObjectData/duck.json");
//
//	if (createdActor)
//	{
//		m_gameObjects.push_back(createdActor);
//		m_gameActors.push_back(createdActor);
//
//		if (collisionData.collisionType != CollisionType::NONE)
//		{
//			// Update collision managers game object array
//			m_collisionManager->AddGameObject(createdActor);
//		}
//
//		if (physicsData.bsimulateGravity)
//		{
//			// Update physics managers actor object array
//			m_physicsManager->AddGameActor(createdActor);
//		}
//	}
//
//	return createdActor;
//}

void Quack::ShutDown()
{
	m_mainScene.CloseScene();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(m_window->GetGLFWWindow());
	glfwTerminate();
};


