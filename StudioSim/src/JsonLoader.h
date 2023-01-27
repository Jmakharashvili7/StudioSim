#pragma once
#include "BasicIncludes.h"
#include "GameObject.h"
#include "Actor.h"
#include "Scene.h"

namespace QuackEngine {
	namespace JsonLoader {

		using json = nlohmann::json;

		static GameObjectData* LoadObjectData2D(const std::string& path)
		{
			std::ifstream file(path);

			// check if the file was found
			if (!file)
			{
				QE_LOG(path + " does not exist!");
				return new GameObjectData();
			}

			json j = json::parse(file);

			// load the json values	
			GameObjectData* data = new GameObjectData();
			data->vertices = j["vertices"].get<std::vector<float>>();
			data->colors = j["colors"].get<std::vector<float>>();
			data->texCoords = j["texCoords"].get<std::vector<float>>();
			// return the sphere
			return data;
		}

		static bool StoreGameObjectData2D(const std::string& filename, const GameObjectData& data)
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

			// Store Name
			j["name"] = gameObject->GetName();
			j["objectType"] = (int)gameObject->GetType();

			// Load Object Data
			j["vertices"] = gameObject->GetGameObjectData()->vertices;
			j["colors"] = gameObject->GetGameObjectData()->colors;
			j["texCoords"] = gameObject->GetGameObjectData()->texCoords;

			// Load Transform Data
			Transform* transformData = gameObject->GetTransform();
			j["position"] = { transformData->GetPosition().x, transformData->GetPosition().y, transformData->GetPosition().z};
			j["rotation"] = { transformData->GetRotation().x, transformData->GetRotation().y, transformData->GetRotation().z};
			j["scale"] = { transformData->GetScale().x, transformData->GetScale().y, transformData->GetScale().z};

			// Load Collision Data
			CollisionData collisionData = gameObject->GetCollisionData();
			j["collisionType"] = (int)collisionData.collisionType;
			j["centerPosition"] = { collisionData.centerPosition.x, collisionData.centerPosition.y, collisionData.centerPosition.z };
			j["size"] = { collisionData.size.x, collisionData.size.y, collisionData.size.z };
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

			std::ofstream o(filename);
			o << std::setw(4) << j << std::endl;
			return true;
		}

		static GameObject* LoadGameObject2D(std::string path)
		{
			std::ifstream file(path);

			// check if the file was found
			if (!file)
			{
				QE_LOG(path + " does not exist!");
				return nullptr;
			}

			json j = json::parse(file);

			GameObjectData* data = new GameObjectData();
			TransformData transformData;
			CollisionData collisionData;
			TextureData textureData;

			auto f = [](std::vector<float> load, Vector3& store)
			{
				store.x = load[0];
				store.y = load[1];
				store.z = load[2];
			};

			// Load name
			std::string name = j["name"].get<std::string>();

			// Load Game Object Data
			data->vertices = j["vertices"].get<std::vector<float>>();
			data->colors = j["colors"].get<std::vector<float>>();
			data->texCoords = j["texCoords"].get<std::vector<float>>();

			// Load Transform Data
			f(j["position"].get<std::vector<float>>(), transformData.position);
			f(j["rotation"].get<std::vector<float>>(), transformData.rotation);
			f(j["scale"].get<std::vector<float>>(), transformData.scale);

			// Load Collision Data
			f(j["centerPosition"].get<std::vector<float>>(), collisionData.centerPosition);
			collisionData.collisionType = (CollisionType)j["collisionType"].get<int>();
			collisionData.radius = j["radius"].get<float>();
			f(j["size"].get<std::vector<float>>(), collisionData.size);

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

		static SceneInfo LoadSceneInfo(std::string sceneName)
		{
			std::string path = "res/scenes/" + sceneName + "/SceneInfo.json";

			std::ifstream file(path);

			// check if the file was found
			if (!file)
			{
				QE_LOG(path + " does not exist!");
				return SceneInfo({0});
			}

			json j = json::parse(file);

			SceneInfo sceneInfo;
			sceneInfo.objectCount = j["objectCount"].get<int>();
			
			return sceneInfo;
		}

		static bool StoreSceneInfo(std::string sceneName, SceneInfo sceneInfo)
		{
			std::string path = "res/scenes/" + sceneName + "/SceneInfo.json";
			json j;

			j["objectCount"] = sceneInfo.objectCount;

			std::ofstream o(path);
			o << std::setw(4) << j << std::endl;
			return true;
		}
	}
}


