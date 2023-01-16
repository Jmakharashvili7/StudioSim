#pragma once
#include "BasicIncludes.h"
#include "GameObject.h"

namespace QuackEngine {
	namespace JsonLoader {

		using json = nlohmann::json;

		static GameObjectData* LoadObject2D(const std::string& path)
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

		static bool StoreGameObject(const std::string& filename, const GameObjectData& data)
		{
			json j;
			j["vertices"] = data.vertices;
			j["colors"] = data.colors;
			j["texCoords"] = data.texCoords;

			std::ofstream o(filename + ".json");
			o << std::setw(4) << j << std::endl;
			return false;
		}
	}
}


