#include "Actor.h"

Actor::Actor(GameObjectData* data, const TextureData& textureData) : GameObject{data, textureData }
{

}

Actor::~Actor()
{

}

void Actor::Jump()
{
	if (m_bSimulateGravity)
	{
		SetJumping(true);
	}
}
