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
		: texturePath(""), internalFormat(GL_RGBA16), imageFormat(GL_RGB) {};

	std::string texturePath;
	GLint internalFormat;
	GLint imageFormat;
};

struct PhysicsData
{
	PhysicsData(const bool inSimulateGravity, const float inMass, const float inGravityMultiplier)
		: bsimulateGravity(inSimulateGravity), mass(inMass), gravityMultiplier(inGravityMultiplier) {};

	PhysicsData() 
		: bsimulateGravity(false), mass(0.0f), gravityMultiplier(1.0f) {};

	bool bsimulateGravity;
	float mass;
	float gravityMultiplier;
};

struct MovementData
{
	MovementData(const float inMovementSpeed, const float inJumpHeight)
		: movementSpeed(inMovementSpeed), jumpHeight(inJumpHeight) {};

	MovementData()
		: movementSpeed(0.0f), jumpHeight(0.0f) {};

	float movementSpeed;
	float jumpHeight;
};

struct EntityData
{
	EntityData(const float inMaxHealth) : maxHealth(inMaxHealth) {};

	EntityData() : maxHealth(0.0f) {};

	float maxHealth;
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
	TransformData(const Vector3 inPosition, const Vector3 inRotation, const Vector3 inScale)
		: position(inPosition), rotation(inRotation), scale(inScale) {};

	TransformData() : position(Vector3::Zero), rotation(Vector3::Zero), scale(Vector3::One) {};

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
};

enum class CollisionType
{
	BOX,
	SPHERE,
	NONE
};

struct CollisionData
{
	CollisionData(const Vector3 inCenterPosition, const Vector3 inSize)
		: collisionType(CollisionType::BOX), centerPosition(inCenterPosition), size(inSize), radius(0.0f) {};

	CollisionData(const Vector3 inCenterPosition, const float inRadius)
		: collisionType(CollisionType::SPHERE), centerPosition(inCenterPosition), size(Vector3::Zero), radius(inRadius) {};

	CollisionData() 
		: collisionType(CollisionType::NONE), centerPosition(Vector3::Zero), size(Vector3::Zero), radius(0.0f) {};

	CollisionType collisionType;
	Vector3 centerPosition;
	Vector3 size;
	float radius;
};

enum class KeyType
{
	/*A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9,
	ENTER, SPACE, BACKSPACE, LFSHIFT, RSHIFT*/
};

enum class AxisType
{
	HORIZONTAL,
	VERTICAL
};


enum class FacingDirection
{
	LEFT,
	RIGHT
};

struct AttackData
{
	AttackData(const float inDamage, const float inKnockbackAmount, const float inCooldownTime, const float inHitboxActivateDelay, const float inHitboxActiveTime, const float inHitboxDeactivateTime)
		: damage(inDamage), knockbackAmount(inKnockbackAmount), cooldownTime(inCooldownTime), hitboxActivateDelay(inHitboxActivateDelay), hitboxActiveTime(inHitboxActiveTime), hitboxDeactivateTime(inHitboxDeactivateTime)
		, totalAttackTime(inCooldownTime+inHitboxActivateDelay+inHitboxActiveTime+inHitboxDeactivateTime) {}

	AttackData() : damage(0.0f), knockbackAmount(0.0f), cooldownTime(0.0f), hitboxActivateDelay(0.0f), hitboxActiveTime(0.0f), hitboxDeactivateTime(0.0f), totalAttackTime(0.0f) {}

	// The damage the attack does
	float damage;

	// The amount the enemy is knocked back when hit
	float knockbackAmount;

	// After the attack is finished (after hitboxDeactivateTime) how long before you can press any attack again
	float cooldownTime;

	// Once the attack is pressed, how long before the hit box is activated 
	float hitboxActivateDelay;

	// How long the hit box is active for
	float hitboxActiveTime;

	// How long it takes for the attack to deactivate after (hitboxactivetime)
	float hitboxDeactivateTime;

	// Total attack time
	float totalAttackTime;
};

struct WeaponData
{
	WeaponData(const std::string inName, const std::string inTextureName, const AttackData& inLightAttackData, const AttackData& inHeavyAttackData, const AttackData& inSpecialAttackData)
		: name(inName), textureName(inTextureName), lightAttackData(inLightAttackData), heavyAttackData(inHeavyAttackData), specialAttackData(inSpecialAttackData) {}

	WeaponData(const std::string inName, const std::string inTextureName, const AttackData& inLightAttackData, const AttackData& inHeavyAttackData)
		: name(inName), textureName(inTextureName), lightAttackData(inLightAttackData), heavyAttackData(inHeavyAttackData), specialAttackData(AttackData()) {}

	WeaponData(const std::string inName, const std::string inTextureName, const AttackData& inLightAttackData)
		: name(inName), textureName(inTextureName), lightAttackData(inLightAttackData), heavyAttackData(AttackData()), specialAttackData(AttackData()) {}

	WeaponData() : name(""), textureName(""), lightAttackData(AttackData()), heavyAttackData(AttackData()), specialAttackData(AttackData()) {}

	std::string name;
	std::string textureName;
	AttackData lightAttackData;
	AttackData heavyAttackData;
	AttackData specialAttackData;
};


