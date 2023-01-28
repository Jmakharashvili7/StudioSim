#pragma once
#include "BasicIncludes.h"
#include "GameObject.h"
#include "Actor.h"
#include "Scene.h"
#include "PhysicsManager.h"

using json = nlohmann::json;

namespace nlohmann
{
	template<>
	struct adl_serializer<Vector3>
	{
		static Vector3 from_json(const json& j)
		{
			Vector3 temp = Vector3(j["x"].get<float>(), j["y"].get<float>(), j["z"].get<float>());
			return temp;
		}

		static void to_json(json& j, Vector3 vec)
		{
			j["x"] = vec.x;
			j["y"] = vec.y;
			j["z"] = vec.z;
		}
	};

	template<>
	struct adl_serializer<GameObject*>
	{
		static GameObject* from_json(const json& j)
		{
			VertexData* data = new VertexData();
			TransformData transformData;
			CollisionData collisionData;
			TextureData textureData;

			// Load name
			std::string name = j["name"].get<std::string>();

			// Load Game Object Data
			data->vertices = j["vertices"].get<std::vector<float>>();
			data->colors = j["colors"].get<std::vector<float>>();
			data->texCoords = j["texCoords"].get<std::vector<float>>();

			// Load Transform Data
			//f(j["position"].get<std::vector<float>>(), transformData.position);
			transformData.position = j["position"].get<Vector3>();
			//f(j["rotation"].get<std::vector<float>>(), transformData.rotation);
			transformData.rotation = j["rotation"].get<Vector3>();
			//f(j["scale"].get<std::vector<float>>(), transformData.scale);
			transformData.scale = j["scale"].get<Vector3>();

			// Load Collision Data
			collisionData.centerPosition = j["centerPosition"].get<Vector3>();
			collisionData.collisionType = (CollisionType)j["collisionType"].get<int>();
			collisionData.radius = j["radius"].get<float>();
			collisionData.size = j["size"].get<Vector3>();

			// Load textureData
			textureData.texturePath = j["texturePath"].get<std::string>();
			textureData.imageFormat = j["imageFormat"].get<GLint>();
			textureData.internalFormat = j["internalFormat"].get<GLint>();

			GameObjectType type = (GameObjectType)j["objectType"];

			switch (type)
			{
			case GameObjectType::OBJECT:
				return new GameObject(name, data, transformData, collisionData, textureData);

			case GameObjectType::ACTOR:
				PhysicsData physicsData;
				AnimationData animationData;

				// Load PhysicsData
				physicsData.bsimulateGravity = j["bsimulateGravity"].get<bool>();
				physicsData.mass = j["mass"].get<float>();

				// Load AnimationData
				animationData.banimated = j["banimated"].get<bool>();
				animationData.columns = j["columns"].get<int>();
				animationData.rows = j["rows"].get<int>();

				return new Actor(name, data, transformData, collisionData, textureData, physicsData, animationData);
			}
		}

		static void to_json(json& j, GameObject* gameObject)
		{
			// Store Name
			j["name"] = gameObject->GetName();
			j["objectType"] = (int)gameObject->GetType();

			// Load Object Data
			j["vertices"] = gameObject->GetGameObjectData()->vertices;
			j["colors"] = gameObject->GetGameObjectData()->colors;
			j["texCoords"] = gameObject->GetGameObjectData()->texCoords;

			// Load Transform Data
			Transform* transformData = gameObject->GetTransform();
			j["position"] = transformData->GetPosition();
			j["rotation"] = transformData->GetRotation();
			j["scale"] = transformData->GetScale();

			// Load Collision Data
			CollisionData collisionData = gameObject->GetCollisionData();
			j["collisionType"] = (int)collisionData.collisionType;
			j["centerPosition"] = collisionData.centerPosition;
			j["size"] = collisionData.size;
			j["radius"] = collisionData.radius;

			// Load Texture Data
			TextureData textureData = gameObject->GetTextureData();
			j["texturePath"] = textureData.texturePath;
			j["internalFormat"] = textureData.internalFormat;
			j["imageFormat"] = textureData.imageFormat;

			if (gameObject->GetType() == GameObjectType::ACTOR)
			{
				Actor* actor = dynamic_cast<Actor*>(gameObject);
				PhysicsData physicsData = actor->GetPhysicsData();
				j["mass"] = physicsData.mass;
				j["bsimulateGravity"] = physicsData.bsimulateGravity;

				AnimationData animationData = actor->GetAnimationData();
				j["banimated"] = animationData.banimated;
				j["columns"] = animationData.columns;
				j["rows"] = animationData.rows;
			}
		}
	};
}

namespace QuackEngine {
	namespace JsonLoader {

		static VertexData* LoadObjectData2D(const std::string& path)
		{
			std::ifstream file(path);

			// check if the file was found
			if (!file)
			{
				QE_LOG(path + " does not exist!");
				return new VertexData();
			}

			json j = json::parse(file);

			// load the json values	
			VertexData* data = new VertexData();
			data->vertices = j["vertices"].get<std::vector<float>>();
			data->colors = j["colors"].get<std::vector<float>>();
			data->texCoords = j["texCoords"].get<std::vector<float>>();
			// return the sphere
			return data;
		}

		static bool StoreGameObjectData2D(const std::string& filename, const VertexData& data)
		{
			json j;
			j["vertices"] = data.vertices;
			j["colors"] = data.colors;
			j["texCoords"] = data.texCoords;

			std::ofstream o(filename + ".json");
			o << std::setw(4) << j << std::endl;
			return true;
		}

		static bool StoreGameObject2D(std::string filename, GameObject* gameObject)
		{
			json j;

			j[gameObject->GetName()] = gameObject;

			std::ofstream o(filename);
			o << std::setw(4) << j << std::endl;
			return true;
		}

		static GameObject* LoadGameObject2D(std::string path, std::string name)
		{
			std::ifstream file(path);

			// check if the file was found
			if (!file)
			{
				QE_LOG(path + " does not exist!");
				return nullptr;
			}

			json j = json::parse(file);

			return j[name].get<GameObject*>();
		}

		static SceneInfo LoadScene(std::string sceneName, std::vector<GameObject*>& gameObjects, PhysicsManager* physicsManager, CollisionManager* collisionManager)
		{
			std::string path = "res/scenes/" + sceneName + ".json";

			std::ifstream file(path);
				
			// check if the file was found
			if (!file)
			{
				QE_LOG(path + " does not exist!");
				return SceneInfo({0});
			}

			json j = json::parse(file);

			SceneInfo sceneInfo;
			sceneInfo.objectCount = j["ObjectCount"].get<int>();
			sceneInfo.sceneName = sceneName;

			for (int i = 0; i < sceneInfo.objectCount; i++)
			{
				GameObject* obj = j["GameObject" + std::to_string(i)].get<GameObject*>();
				gameObjects.push_back(obj);

				if (obj->GetCollisionType() != CollisionType::NONE)
				{
					collisionManager->AddGameObject(obj);
				}

				if (obj->GetType() == GameObjectType::ACTOR || obj->GetType() == GameObjectType::CHARACTER) // check if game object an actor or character
				{ 
					physicsManager->AddGameActor(static_cast<Actor*>(obj));
				}
			}
			
			return sceneInfo;
		}

		static void StoreScene(SceneInfo sceneInfo, std::vector<GameObject*>& gameObjects)
		{
			json j;

			j["ObjectCount"] = gameObjects.size();

			for (uint32_t i = 0; i < gameObjects.size(); i++)
				j["GameObject" + std::to_string(i)] = gameObjects[i];

			std::string path = "res/scenes/" + sceneInfo.sceneName + ".json";
			std::ofstream o(path);
			o << std::setw(4) << j << std::endl;
		}
	}
}


