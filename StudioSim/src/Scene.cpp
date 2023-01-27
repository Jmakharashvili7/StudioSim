#include "Scene.h"
#include "GameObject.h"
#include "Actor.h"
#include "Shader.h"
#include "OrthographicCamera.h"
#include "PhysicsManager.h"
#include "CollisionManager.h"
#include "EngineManager.h"
#include "JsonLoader.h"
#include "KeyboardClass.h"
#include "MouseClass.h"
#include "UILayer.h"
#include "Window.h"
#include "InputComponent.h"
#include "QuackOperations.h"

Scene::Scene(const std::string& name, UILayer* uiLayer, Window* window) :
	m_uiMain(uiLayer),
	m_window(window),
	m_name(name)
{
	m_mainCamera = new OrthographicCamera(-5.0f, 5.0f, -5.0f, 5.0f);
	m_mainCamera->SetPosition(glm::vec3(0.0f));

	SceneInfo sceneInfo = QuackEngine::JsonLoader::LoadSceneInfo(name);
	m_gameTimer.Start();

	for (int i = 0; i < sceneInfo.objectCount; i++)
	{
		GameObject* gameObject = LoadGameObject("GameObject" + std::to_string(i));
	}

	m_physicsManager = new PhysicsManager();
	m_collisionManager = new CollisionManager();

	// Update engine manager
	m_grid = Grid<PathNode>(30, 30, 0.5, { -6,-6, 0 });
	EngineManager::SetGameObjects(m_gameObjects);
	SetupShaders();
}

void Scene::SetupShaders()
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

void Scene::HandleLights()
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

void Scene::Update()
{
	m_gameTimer.Tick();

	const float deltaTime = m_gameTimer.GetDeltaTime();

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
		if (gameObject) gameObject->Draw(m_mainShader);
	}

	m_primitiveShader->Bind();
	m_primitiveShader->SetUniform4x4("u_viewProjection", m_mainCamera->GetViewProjectionMatrix());
	Renderer::DrawDebugLines();
	m_primitiveShader->Unbind();
}

void Scene::PhysicsUpdate()
{
	const float deltaTime = m_gameTimer.GetDeltaTime();
	m_collisionManager->Update(deltaTime);
	m_physicsManager->Update(deltaTime);
}

void Scene::HandleInput()
{
	const float deltaTime = m_gameTimer.GetDeltaTime();
	const float movementAmount = 5.0f;

	// jabas engine manager get can also be used here 
	Actor* duck = m_gameActors[QuackOperations::GetActorIndex("duck", m_gameActors)];
	if (duck)
	{
		if (InputComponent* inputComponent = duck->GetInputComponent())
		{
			// MOVE RIGHT
			if (inputComponent->GetKeyDown('d'))
			{
				duck->AdjustPosition(Vector3((movementAmount * deltaTime), 0.0f, 0.0f));
			}

			// MOVE LEFT
			if (inputComponent->GetKeyDown('a'))
			{
				duck->AdjustPosition(Vector3((-movementAmount * deltaTime), 0.0f, 0.0f));
			}
		}
	}
}

GameObject* Scene::LoadGameObject(std::string name)
{
	GameObject* createdGameObject = nullptr;
	std::string path = "res/scenes/" + m_name + "/Objects/" + name + ".json";
	createdGameObject = QuackEngine::JsonLoader::LoadGameObject2D(path);

	if (createdGameObject)
	{
		m_gameObjects.push_back(createdGameObject);

		if (createdGameObject->GetCollisionData().collisionType != CollisionType::NONE)
		{
			// Update collision managers game object array
			m_collisionManager->AddGameObject(createdGameObject);
		}

		switch (createdGameObject->GetType())
		{
		case GameObjectType::ACTOR:
			Actor* actor = static_cast<Actor*>(createdGameObject);
			m_gameActors.push_back(actor);
			if (actor->GetPhysicsData().bsimulateGravity)
			{
				// Update physics managers actor object array
				m_physicsManager->AddGameActor(actor);
			}
			break;
		}
	}

	return createdGameObject;
}

/// <summary>
/// currently the game objects are being stored seperetly but it would probably be better to 
/// keep the whole game data 
/// </summary>
/// <param name="gameObject"></param>
/// <param name="index"></param>
/// <returns></returns>
bool Scene::StoreGameObject(GameObject* gameObject, int index)
{
	// where to store the object
	std::string path = "res/scenes/" + m_name + "/Objects/GameObject" + std::to_string(index) + ".json";
	return QuackEngine::JsonLoader::StoreGameObject2D(path, gameObject);
}

void Scene::CloseScene()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		StoreGameObject(m_gameObjects[i], i);
	}

	SceneInfo sceneInfo;
	sceneInfo.objectCount = m_gameObjects.size();
	QuackEngine::JsonLoader::StoreSceneInfo(m_name, sceneInfo);
}