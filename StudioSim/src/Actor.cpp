#include "Actor.h"
#include "Animate.h"
#include "Quack.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"

Actor::Actor(std::string name, VertexData* data, const TransformData& transformData, const CollisionData& collisionData, const TextureData& textureData, const PhysicsData& physicsData, const AnimationData& animationData)
	: GameObject{ name, data, transformData, collisionData, textureData }, m_physicsData(physicsData), m_animationData(animationData)
{
	m_type = GameObjectType::ACTOR;

	//Animation init
	m_banimated = animationData.banimated;
	if (m_banimated)
	{
		m_animator = new Animate(this, animationData.rows, animationData.columns);
	}

	// Input init
	m_inputComponent = new InputComponent(this, 0);
	AddComponent(m_inputComponent);

	// Physics init
	m_physicsComponent = new PhysicsComponent(this, 1, physicsData.mass, physicsData.bsimulateGravity, physicsData.gravityMultiplier);
	AddComponent(m_physicsComponent);
}

Actor::~Actor()
{
	delete m_animator;
	m_animator = nullptr;

	for (auto component : m_components)
	{
		delete component;
		component = nullptr;
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

void Actor::Update(const float deltaTime)
{
	GameObject::Update(deltaTime);

	for (auto component : m_components)
	{
		component->Update(deltaTime);
	}
}

void Actor::SetMass(float newMass)
{
	m_physicsData.mass = newMass;

	if (m_physicsComponent)
	{
		m_physicsComponent->SetMass(newMass);
	}
}

void Actor::SetSimulateGravity(bool gravityStatus)
{
	m_physicsData.bsimulateGravity = gravityStatus;

	if (m_physicsComponent)
	{
		m_physicsComponent->SetSimulateGravity(gravityStatus);
	}
}

void Actor::SetGravityMultiplier(const float gravityMultiplier)
{
	m_physicsData.gravityMultiplier = gravityMultiplier;

	if (m_physicsComponent)
	{
		m_physicsComponent->SetGravityValue(gravityMultiplier);
	}
}

void Actor::AddCollision(GameObject* collidingObject)
{
	// Debug
	
	/*if (GetPosition().y < collidingObject->GetPosition().y)
	{
		std::cout << "BOTTOM HIT" << std::endl;
	}
	else
	{
		std::cout << "BOTTOM HIT" << std::endl;
	}
	if (GetPosition().x < collidingObject->GetPosition().x)
	{
		std::cout << "Right HIT" << std::endl;
	}
	else
	{
		std::cout << "Bottom HIT" << std::endl;
	}*/

	if (collidingObject->GetName() == "ground")
	{
		SetCollidingWithGround(true);
	}

	GameObject::AddCollision(collidingObject);
}

void Actor::RemoveCollision(GameObject* gameObject)
{
	if (gameObject->GetName() == "ground")
	{
		SetCollidingWithGround(false);
	}

	GameObject::RemoveCollision(gameObject);
}

void Actor::SetCollidingWithGround(const bool bcollidingWithGround)
{
	m_bcollidingWithGround = bcollidingWithGround;

	if (m_physicsComponent)
	{
		m_physicsComponent->SetOnGround(bcollidingWithGround);
	}
}

void Actor::AddComponent(Component* component)
{
	m_components.push_back(component);
}

void Actor::ClearComponents()
{
	m_components.clear();
}

void Actor::ReorderComponents()
{
	return;
}
