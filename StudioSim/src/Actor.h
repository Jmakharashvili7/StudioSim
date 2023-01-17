#pragma once
#include "GameObject.h"
#include "BasicIncludes.h"

class Actor : public GameObject
{
public:
	Actor(GameObjectData* data, const TextureData& textureData);
	~Actor();

	void Jump();

	inline void SetJumping(const bool bJumping) {m_bJumping = bJumping;}

private:
	//Physics 
	bool m_bSimulateGravity = false;
	float m_Weight = 10.0f;
	float m_JumpHeight = 50.0f;
	bool m_bJumping = false;
};

