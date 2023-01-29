#include "Actor.h"
#include "Animate.h"
#include "Quack.h"
#include "InputComponent.h"

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
}

Actor::~Actor()
{
	delete m_animator;
	m_animator = nullptr;

	for (Component* component : m_components)
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

	for (Component* component : m_components)
	{
		component->Update(deltaTime);
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
		/*Vector3 duckLeft = GetPosition() - GetScale() / Vector3(2.0f);
		Vector3 duckRight = GetPosition() + GetScale() / Vector3(2.0f);
		Vector3 floorLeft = collidingObject->GetPosition() - collidingObject->GetScale() / Vector3(2.0f);
		Vector3 floorRight = collidingObject->GetPosition() + collidingObject->GetScale() / Vector3(2.0f);

		std::cout << "DUCK CENTRE: " << GetPosition().x << "  DUCK LEFT: " << duckLeft.x << "  DUCK RIGHT: " << duckRight.x << std::endl;
		std::cout << "FLOOR CENTRE:  " << collidingObject->GetPosition().x << "  FLOOR LEFT: " << floorLeft.x << "  FLOOR RIGHT: " << floorRight.x << std::endl;*/


		//SetPosition(CollisionManager::RepositionGameObject(this, collidingObject));
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
