#include "pch.h"

#include "Scene.h"
#include "GameObject.h"
#include "Actor.h"
#include "Shader.h"
#include "OrthographicCamera.h"
#include "CollisionManager.h"
#include "EngineManager.h"
#include "JsonLoader.h"
#include "KeyboardClass.h"
#include "MouseClass.h"
#include "UILayer.h"
#include "Window.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "MiniPontiff.h"

Scene::Scene(const std::string& name, UILayer* uiLayer, Window* window, FrameBuffer* frameBuffer) :
	m_uiMain(uiLayer),
	m_window(window),
	m_name(name),
	m_frameBuffer(frameBuffer)
{
	// Setup camera
	m_activeCamera = new OrthographicCamera(-5.0f, 5.0f, -5.0f, 5.0f);
	m_activeCamera->SetPosition(glm::vec3(0.0f));

	// Setup collision Manager
	m_collisionManager = new CollisionManager();

	m_grid = Grid<PathNode>(160, 40, 0.5, { -15.5,-10, 0 });

	// Load scene
	m_sceneInfo = QuackEngine::JsonLoader::LoadScene(name, m_gameObjects, m_grid);
	m_gameTimer.Start();

	// Update engine manager
	m_pathfinder = new Pathfinding(m_grid);
	EngineManager::SetGameObjects(m_gameObjects);
}

void Scene::RenderScene()
{
	m_frameBuffer->Bind();
	/* Render here */
	glClearColor(12.0f/255.0f, 19.0f/255.0f, 25.0f/255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	Render();

	/* Swap front and back buffers */
	glfwSwapBuffers(m_window->GetGLFWWindow());
	/* Poll for and process events */
	glfwPollEvents();

	m_frameBuffer->Unbind();
}

void Scene::SetGravity(const bool bactive)
{
	for (GameObject* gameObject : m_gameObjects)
	{
		if (Actor* actorObject = dynamic_cast<Actor*>(gameObject))
		{
			if (bactive)
			{
				actorObject->SetSimulateGravity(true);
			}
			else
			{
				actorObject->SetSimulateGravity(false);
			}
		}
	}
}

void Scene::SetInput(const bool bactive)
{
	m_StopInput = !bactive;
}

void Scene::HandleLights()
{
	//#ifdef _3D_SHADER
	//	// bind shader
	//	m_3dShader->Bind();
	//	m_3dShader->SetUniform4x4("u_viewProjection", m_mainCamera->GetViewProjectionMatrix());
	//	m_3dShader->SetUniform4f("u_color", 0.5f, 0.5, 0.5f, 1.f);
	//	//Light
	//	m_3dShader->SetUniform4f("u_viewPos", 1.0f, 4.0f, 1.0f, 1.0f);
	//	//Material Struct
	//	m_3dShader->SetUniform1i("u_material.diffuse", 0);
	//	m_3dShader->SetUniform1i("u_material.specular", 1);
	//	m_3dShader->SetUniform1f("u_material.shine", 32.0f);
	//	//Directional Light
	//	m_3dShader->SetUniform4f("u_dirLight.direction", 0.0f, 0.0f, -0.3f, 1.0f);
	//	m_3dShader->SetUniform4f("u_dirLight.ambient", m_dirAmbient.x, m_dirAmbient.y, m_dirAmbient.z, m_dirAmbient.a);
	//	m_3dShader->SetUniform4f("u_dirLight.diffuse", m_dirDiffuse.x, m_dirDiffuse.y, m_dirDiffuse.z, m_dirDiffuse.a);
	//	m_3dShader->SetUniform4f("u_dirLight.specular", m_dirSpecular.x, m_dirSpecular.y, m_dirSpecular.z, m_dirSpecular.a);
	//
	//	//Point Lights
	//
	//	m_3dShader->SetUniform4f("u_pointLights[0].position", m_pointLightPositions[0].x, m_pointLightPositions[0].y, m_pointLightPositions[0].z, 1.0f);
	//	m_3dShader->SetUniform4f("u_pointLights[1].position", m_pointLightPositions[1].x, m_pointLightPositions[1].y, m_pointLightPositions[1].z, 1.0f);
	//	m_3dShader->SetUniform4f("u_pointLights[2].position", m_pointLightPositions[2].x, m_pointLightPositions[2].y, m_pointLightPositions[2].z, 1.0f);
	//
	//	m_3dShader->SetUniform4f("u_pointLights[0].ambient", m_pointAmbient.x, m_pointAmbient.y, m_pointAmbient.z, m_pointAmbient.a);
	//	m_3dShader->SetUniform4f("u_pointLights[1].ambient", m_pointAmbient.x, m_pointAmbient.y, m_pointAmbient.z, m_pointAmbient.a);
	//	m_3dShader->SetUniform4f("u_pointLights[2].ambient", m_pointAmbient.x, m_pointAmbient.y, m_pointAmbient.z, m_pointAmbient.a);
	//	m_3dShader->SetUniform4f("u_pointLights[0].diffuse", m_pointDiffuse.x, m_pointDiffuse.y, m_pointDiffuse.z, m_pointDiffuse.a);
	//	m_3dShader->SetUniform4f("u_pointLights[1].diffuse", m_pointDiffuse.x, m_pointDiffuse.y, m_pointDiffuse.z, m_pointDiffuse.a);
	//	m_3dShader->SetUniform4f("u_pointLights[2].diffuse", m_pointDiffuse.x, m_pointDiffuse.y, m_pointDiffuse.z, m_pointDiffuse.a);
	//	m_3dShader->SetUniform4f("u_pointLights[0].specular", m_pointSpecular.x, m_pointSpecular.y, m_pointSpecular.z, m_pointSpecular.a);
	//	m_3dShader->SetUniform4f("u_pointLights[1].specular", m_pointSpecular.x, m_pointSpecular.y, m_pointSpecular.z, m_pointSpecular.a);
	//	m_3dShader->SetUniform4f("u_pointLights[2].specular", m_pointSpecular.x, m_pointSpecular.y, m_pointSpecular.z, m_pointSpecular.a);
	//	//dont change																													
	//	m_3dShader->SetUniform1f("u_pointLights[0].constant", 1.0f);
	//	m_3dShader->SetUniform1f("u_pointLights[1].constant", 1.0f);
	//	m_3dShader->SetUniform1f("u_pointLights[2].constant", 1.0f);
	//	m_3dShader->SetUniform1f("u_pointLights[0].linear", 0.09f);
	//	m_3dShader->SetUniform1f("u_pointLights[1].linear", 0.09f);
	//	m_3dShader->SetUniform1f("u_pointLights[2].linear", 0.09f);
	//	m_3dShader->SetUniform1f("u_pointLights[0].quadratic", 0.032f);
	//	m_3dShader->SetUniform1f("u_pointLights[1].quadratic", 0.032f);
	//	m_3dShader->SetUniform1f("u_pointLights[2].quadratic", 0.032f);
	//
	//	//Spot Light
	//	m_3dShader->SetUniform4f("u_spotLight.position", m_mainCamera->GetPosition().x, m_mainCamera->GetPosition().y, m_mainCamera->GetPosition().z, 1.0f);
	//	m_3dShader->SetUniform4f("u_spotLight.direction", 0.0f, 0.0f, -0.3f, 1.0f);
	//	m_3dShader->SetUniform4f("u_spotLight.ambient", m_spotAmbient.x, m_spotAmbient.y, m_spotAmbient.z, m_spotAmbient.a);
	//	m_3dShader->SetUniform4f("u_spotLight.diffuse", m_spotDiffuse.x, m_spotDiffuse.y, m_spotDiffuse.z, m_spotDiffuse.a);
	//	m_3dShader->SetUniform4f("u_spotLight.specular", m_spotDiffuse.x, m_spotDiffuse.y, m_spotDiffuse.z, m_spotDiffuse.a);
	//	//dont change
	//	m_3dShader->SetUniform1f("u_spotLight.constant", 1.0f);
	//	m_3dShader->SetUniform1f("u_spotLight.linear", 0.09f);
	//	m_3dShader->SetUniform1f("u_spotLight.quadratic", 0.032f);
	//	m_3dShader->SetUniform1f("u_spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	//	m_3dShader->SetUniform1f("u_spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
	//
	//#endif // _3D_SHADER
	//
	//#ifdef _2D_SHADER
	//
	//	// bind shader
	//	m_mainShader->Bind();
	//	m_mainShader->SetUniform4x4("u_viewProjection", m_activeCamera->GetViewProjectionMatrix());
	//
	//	m_mainShader->SetUniform4f("u_lightColor", 1.0f, 1.0f, 1.0f, 1.0f);
	//
	//	//Ambient light
	//	m_mainShader->SetUniform4f("u_light.position", 0.0f, 0.0f, 0.0f, -2.0f);
	//	m_mainShader->SetUniform4f("u_light.ambient", 1.0f, 1.0f, 1.0f, 1.0f);
	//
	//#endif // _2D_SHADER
}

void Scene::Update()
{
	m_gameTimer.Tick();

	if (!Quack::GetUILayer()->GetInPlay())
	{
		return;
	}

	const float deltaTime = m_gameTimer.GetDeltaTime();

	// Make the camera and the background follow the player
	Vector3 playerPos = EngineManager::GetInputCharacter()->GetPosition();
	m_activeCamera->SetPosition(playerPos.GetglmVec3());
	playerPos.y = 0;
	m_gameObjects[1]->SetPosition(playerPos);

	if (!m_gameObjectsToAdd.empty())
	{
		for (GameObject* gameObjectToAdd : m_gameObjectsToAdd)
		{
			m_gameObjects.push_back(gameObjectToAdd);
		}
		m_gameObjectsToAdd.clear();
	}
	
	if (!m_gameObjectsToRemove.empty())
	{
		for (GameObject* gameObjectToRemove : m_gameObjectsToRemove)
		{
			m_gameObjects.erase(m_gameObjects.begin() + EngineManager::GetGameObjectIndex(gameObjectToRemove));
		}
		m_gameObjectsToRemove.clear();
	}

	// Update game objects
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject) gameObject->Update(deltaTime);
	}

	// get mouse position
	double xpos, ypos;
	glfwGetCursorPos(Quack::GetWindow()->GetGLFWWindow(), &xpos, &ypos);

	HandleInput();
}

void Scene::Render()
{
	HandleLights();
	Update();
	PhysicsUpdate();

	// Draw game objects
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject) gameObject->Draw(m_activeCamera);
	}

	if (m_StopInput)
	{
		Renderer::DrawDebugLines(m_activeCamera);
	}
}

void Scene::PhysicsUpdate()
{
	float deltaTime = m_gameTimer.GetDeltaTime();
	m_collisionManager->Update(deltaTime);
}

void Scene::HandleInput()
{
	const float deltaTime = m_gameTimer.GetDeltaTime();

	Character* inputCharacter = dynamic_cast<Character*>(EngineManager::GetInputCharacter());

	if (inputCharacter && !m_StopInput && inputCharacter->GetCurrentHealth() > 0.0f)
	{
		if (InputComponent* inputComponent = inputCharacter->GetComponent<InputComponent>())
		{
			// JUMP
			if (inputComponent->GetKeyPressed(' '))
			{
				inputCharacter->Jump();
			}

			// LIGHT ATTACK
			if (inputComponent->GetKeyPressed('j'))
			{
				inputCharacter->LightAttack();
			}

			// HEAVY ATTACK
			if (inputComponent->GetKeyPressed('l'))
			{
				inputCharacter->HeavyAttack();
			}

			// SPECIAL ATTACK
			if (inputComponent->GetKeyPressed('k'))
			{
				inputCharacter->SpecialAttack();
			}

			// MOVE RIGHT
			if (inputComponent->GetKeyDown('d'))
			{
				if (!inputCharacter->GetHittingWallLeft()) 
				{
					inputCharacter->AdjustPosition(Vector3((inputCharacter->GetMovementSpeed() * deltaTime), 0.0f, 0.0f));
				}
			}

			// MOVE LEFT
			if (inputComponent->GetKeyDown('a'))
			{
				if (!inputCharacter->GetHittingWallRight())
				{
					inputCharacter->AdjustPosition(Vector3((-inputCharacter->GetMovementSpeed() * deltaTime), 0.0f, 0.0f));
				}
			}

			// IDLE
			if (inputComponent->GetKeyUp('d') && !inputComponent->GetKeyDown('a') || inputComponent->GetKeyUp('a') && !inputComponent->GetKeyDown('d'))
			{
				inputCharacter->SetIdleAnimation();
			}

			if (inputComponent->GetKeyPressed('z'))
			{
				inputCharacter->AttemptToDash();
			}
		}
	}
}

void Scene::SaveScene()
{
	QuackEngine::JsonLoader::StoreScene(m_sceneInfo, m_gameObjects);
}

void Scene::LoadScene()
{
	if (!m_gameObjects.empty())
	{
		for (int i = 0; i < m_gameObjects.size(); i++)
		{
			delete m_gameObjects[i];
		}
		m_gameObjects.clear();
		m_gameObjectsToAdd.clear();
		m_gameObjectsToRemove.clear();
	}
	QuackEngine::JsonLoader::LoadScene(m_sceneInfo.sceneName, m_gameObjects, m_grid);
}

void Scene::AddGameObject(GameObject* newGameObject)
{
	m_gameObjectsToAdd.push_back(newGameObject);
}

void Scene::RemoveGameObject(GameObject* gameObject)
{
	m_gameObjectsToRemove.push_back(gameObject);
}
