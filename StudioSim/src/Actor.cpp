#include "Actor.h"
#include "Animate.h"
#include "Quack.h"

Actor::Actor(std::string name, GameObjectData* data, const TransformData& transformData, const CollisionData& collisionData, const TextureData& textureData, const PhysicsData& physicsData, const AnimationData& animationData)
	: GameObject{ name, data, transformData, collisionData, textureData }, m_physicsData(physicsData)
{
	//Animation init
	m_banimated = animationData.banimated;
	if (m_banimated)
	{
		m_animator = new Animate(this, animationData.rows, animationData.columns);
	}
	m_Input = new InputComponent(this, 2, Quack::GetWindow()->GetGLFWWindow());
}

Actor::~Actor()
{

}

void Actor::Jump()
{
	if (m_physicsData.bsimulateGravity && !m_bjumping)
	{
		m_bjumping = true;
		m_currentJumpForce = m_physicsData.jumpHeight;
	}
}

void Actor::Draw(Shader* mainShader)
{
	if (m_animator)
	{
		m_animator->UpdateTextCoord(Quack::GetDeltaTime());
	}

	GameObject::Draw(mainShader);
}

void Actor::Update(float deltaTime)
{

	GameObject::Update(deltaTime);
	m_Input->Update(deltaTime);
}
	
void Actor::AddCollision(GameObject* collidingObject, const std::map<CollisionSide, bool>& collidingSides)
{
	// Debug
	/*for (auto side : collidingSides)
	{
		switch (side.first)
		{
		case CollisionSide::LEFT:
			std::cout << "LEFT COLLISION:  " << side.second << std::endl;
			break;
		case CollisionSide::RIGHT:
			std::cout << "RIGHT COLLISION:  " << side.second << std::endl;
			break;
		case CollisionSide::TOP:
			std::cout << "TOP COLLISION:  " << side.second << std::endl;
			break;
		case CollisionSide::BOTTOM:
			std::cout << "BOTTOM COLLISION:  " << side.second << std::endl;
			break;
		default:
			std::cout << "NO COLLISION" << std::endl;
			break;
		}
	}

	std::cout << " " << std::endl;*/

	if (collidingObject->GetName() == "ground")
	{
		//std::cout << "HIT GROUND" << std::endl;
		SetCollidingWithGround(true);
	}

	GameObject::AddCollision(collidingObject, collidingSides);
}

void Actor::RemoveCollision(GameObject* gameObject)
{
	if (gameObject->GetName() == "ground")
	{
		//std::cout << "END GROUND" << std::endl;
		SetCollidingWithGround(false);
	}

	GameObject::RemoveCollision(gameObject);
}

bool const Actor::GetCollidingWithGround()
{
	return m_bcollidingWithGround;
}

void Actor::AddImpulseForce(Vector3 force)
{
	if (m_physicsData.bsimulateGravity && !m_bimpulseActive)
	{
		m_bimpulseActive = true;
		m_currentImpulseForce = force;
		m_testImpulseForceMag = force;
	}
}
