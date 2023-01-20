#pragma once
#include "BasicIncludes.h"

struct TextureData
{
	TextureData(const std::string& inTexturePath, const GLint inInternalFormat, const GLint inImageFormat)
		: texturePath(inTexturePath), internalFormat(inInternalFormat),
		imageFormat(inImageFormat) {};

	TextureData(const std::string& inTexturePath) : texturePath(inTexturePath),
		internalFormat(GL_RGB), imageFormat(GL_RGB) {};

	TextureData() 
		: texturePath(""), internalFormat(0), imageFormat(0) {};

	std::string texturePath;
	GLint internalFormat;
	GLint imageFormat;
};

struct PhysicsData
{
	PhysicsData(const bool inSimulateGravity, const float inMass, const float inJumpHeight)
		: bsimulateGravity(inSimulateGravity), mass(inMass), jumpHeight(inJumpHeight) {};

	PhysicsData() 
		: bsimulateGravity(false), mass(0.0f), jumpHeight(0.0f) {};

	bool bsimulateGravity;
	float mass;
	float jumpHeight;
};

struct AnimationData
{
	AnimationData(const bool inAnimated, const int inRows, const int inColumns)
		: banimated(inAnimated), rows(inRows), columns(inColumns) {};

	AnimationData() 
		: banimated(false), rows(0), columns(0) {};

	bool banimated;
	int rows;
	int columns;
};

struct TransformData
{
	TransformData(const glm::vec3 inPosition, const glm::vec3 inRotation, const glm::vec3 inScale)
		: position(inPosition), rotation(inRotation), scale(inScale) {};

	TransformData() 
		: position(glm::vec3(0.0f)), rotation(glm::vec3(0.0f)), scale(glm::vec3(1.0f)) {};

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

enum class CollisionType
{
	BOX,
	SPHERE,
	NONE
};

struct CollisionData
{
	CollisionData(const glm::vec3 inCenterPosition, const glm::vec3 inSize)
		: collisionType(CollisionType::BOX), centerPosition(inCenterPosition), size(inSize), radius(0.0f) {};

	CollisionData(const glm::vec3 inCenterPosition, const float inRadius)
		: collisionType(CollisionType::SPHERE), centerPosition(inCenterPosition), size(glm::vec3(0.0f)), radius(inRadius) {};

	CollisionData() 
		: collisionType(CollisionType::NONE), centerPosition(glm::vec3(0.0f)), size(glm::vec3(0.0f)), radius(0.0f) {};

	CollisionType collisionType;
	glm::vec3 centerPosition;
	glm::vec3 size;
	float radius;
};


