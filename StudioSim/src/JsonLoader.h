#pragma once
#include "BasicIncludes.h"
#include "GameObject.h"

namespace QuackEngine {
	namespace JsonLoader {

		using json = nlohmann::json;

		static VertexArray* LoadObject2D(std::string path)
		{
			std::ifstream file(path);

			// check if the file was found
			if (!file)
			{
				QE_LOG(path + " does not exist!");
				return new VertexArray();
			}

			json data = json::parse(file);

			// load the json values	
			auto vectors = data["vectors"].get<std::vector<float>>();

			// return the sphere
			return new VertexArray();
		}
	}
}


