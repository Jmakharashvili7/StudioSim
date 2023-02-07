#include "pch.h"

#include "Actor.h"
#include "Animate.h"
#include "Quack.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"

Actor::Actor(std::string name, VertexData* data, const TransformData& transformData, const CollisionData& collisionData, const std::string& textureName, const PhysicsData& physicsData, const AnimationData& animationData)
	: GameObject{ name, data, transformData, collisionData, textureName }, m_physicsData(physicsData), m_animationData(animationData)
{
	m_type = GameObjectType::ACTOR;

	//Animation init
	m_animator = new Animate(this, animationData);
	SetCurrentAnimation(GetAnimationByName("idle"));

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

void Actor::Draw(OrthographicCamera* camera)
{
	if (m_animator)
	{
		m_animator->UpdateTextCoord(Quack::GetDeltaTime());
	}

	GameObject::Draw(camera);
}

void Actor::Update(const float deltaTime)
{
	GameObject::Update(deltaTime);

	for (auto component : m_components)
	{
		component->Update(deltaTime);
	}
}

void Actor::AdjustPosition(const Vector3 adjustPosition)
{
	SetCurrentAnimation(GetAnimationByName("move"));

	GameObject::AdjustPosition(adjustPosition);
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

inline void Actor::SetAnimationStatus(bool animated)
{
	if (m_animationData.banimated == animated)
	{
		return;
	}

	m_animationData.banimated = animated;

	if (m_animator)
	{
		m_animator->SetAnimationStatus(animated);
	}
}

void Actor::SetAnimationRowData(std::vector<AnimationRowData> newAnimationRowData)
{
	m_animationData.animationRowData = newAnimationRowData;

	if (m_animator)
	{
		m_animator->SetAnimationRowData(newAnimationRowData);
	}
}

void Actor::SetAnimationDataRowName(const AnimationRowData& animationRowData, const std::string newName)
{
	int indexToChange = -1;

	for (int i = 0; i < m_animationData.animationRowData.size(); i++)
	{
		if (m_animationData.animationRowData[i].name == animationRowData.name)
		{
			indexToChange = i;
			break;
		}
	}
	
	m_animationData.animationRowData[indexToChange].name = newName;

	if (m_currentAnimationData.name == animationRowData.name)
	{
		if (m_animator)
		{
			m_animator->SetAnimationName(newName);
		}
	}
}

const std::string Actor::GetAnimationDataRowName(const AnimationRowData& animationRowData)
{
	for (const AnimationRowData& loopAnimationRowData : m_animationData.animationRowData)
	{
		if (loopAnimationRowData.name == animationRowData.name)
		{
			return loopAnimationRowData.name;
		}
	}

	return "";
}

void Actor::SetAnimationDataRowNumber(const AnimationRowData& animationRowData, const int newRowNumber)
{
	int indexToChange = -1;

	for (int i = 0; i < m_animationData.animationRowData.size(); i++)
	{
		if (m_animationData.animationRowData[i].name == animationRowData.name)
		{
			indexToChange = i;
			break;
		}
	}

	m_animationData.animationRowData[indexToChange].rowNumber = newRowNumber;

	if (m_currentAnimationData.name == animationRowData.name)
	{
		if (m_animator)
		{
			m_animator->SetAnimationRowNumber(newRowNumber);
		}
	}
}

const int Actor::GetAnimationDataRowNumber(const AnimationRowData& animationRowData)
{
	for (const AnimationRowData& loopAnimationRowData : m_animationData.animationRowData)
	{
		if (loopAnimationRowData.name == animationRowData.name)
		{
			return loopAnimationRowData.rowNumber;
		}
	}

	return 0;
}

void Actor::SetAnimationDataNumberOfColumns(const AnimationRowData& animationRowData, const int newNumberOfColumns)
{
	int indexToChange = -1;

	for (int i = 0; i < m_animationData.animationRowData.size(); i++)
	{
		if (m_animationData.animationRowData[i].name == animationRowData.name)
		{
			indexToChange = i;
			break;
		}
	}

	m_animationData.animationRowData[indexToChange].amountOfColumns = newNumberOfColumns;

	if (m_currentAnimationData.name == animationRowData.name)
	{
		if (m_animator)
		{
			m_animator->SetAnimationNumberOfColumns(newNumberOfColumns);
		}
	}
}

const int Actor::GetAnimationDataNumberOfColumns(const AnimationRowData& animationRowData)
{
	for (const AnimationRowData& loopAnimationRowData : m_animationData.animationRowData)
	{
		if (loopAnimationRowData.name == animationRowData.name)
		{
			return loopAnimationRowData.amountOfColumns;
		}
	}
	
	return 0;
}

void Actor::SetAnimationDataPlayRate(const AnimationRowData& animationRowData, const float newPlayRate)
{
	int indexToChange = -1;

	for (int i = 0; i < m_animationData.animationRowData.size(); i++)
	{
		if (m_animationData.animationRowData[i].name == animationRowData.name)
		{
			indexToChange = i;
			break;
		}
	}

	m_animationData.animationRowData[indexToChange].playRate = newPlayRate;

	if (m_currentAnimationData.name == animationRowData.name)
	{
		if (m_animator)
		{
			m_animator->SetAnimationPlayRate(newPlayRate);
		}
	}
}

const float Actor::GetAnimationDataPlayRate(const AnimationRowData& animationRowData)
{
	for (const AnimationRowData& loopAnimationRowData : m_animationData.animationRowData)
	{
		if (loopAnimationRowData.name == animationRowData.name)
		{
			return loopAnimationRowData.playRate;
		}
	}

	return 0;
}

void Actor::SetAnimationDataTotalRows(const int newTotalRows)
{
	m_animationData.totalRows = newTotalRows;

	if (m_animator)
	{
		m_animator->SetAnimationTotalRows(newTotalRows);
	}
}

void Actor::SetAnimationDataTotalColumns(const int newTotalColumns)
{
	m_animationData.totalColumns = newTotalColumns;

	if (m_animator)
	{
		m_animator->SetAnimationTotalColumns(newTotalColumns);
	}
}

void Actor::AddAnimationData()
{
	std::vector<AnimationRowData> tempAnimationRowData = m_animationData.animationRowData;
	tempAnimationRowData.push_back(AnimationRowData());
	SetAnimationRowData(tempAnimationRowData);
}

const AnimationRowData& Actor::GetAnimationByName(std::string name)
{
	for (const AnimationRowData& anim : m_animationData.animationRowData)
	{
		if (anim.name == name)
		{
			return anim;
		}
	}

	return AnimationRowData();
}

void Actor::SetCurrentAnimation(const AnimationRowData& newCurrentAnimation)
{
	m_currentAnimationData = newCurrentAnimation;
	
	if (m_animator)
	{
		m_animator->SetAnimation(newCurrentAnimation);
	}
}

void Actor::AddCollision(GameObject* collidingObject)
{
	if (collidingObject->GetName() == "ground" || collidingObject->GetName() == "Ground")
	{
		SetCollidingWithGround(true);
	}

	GameObject::AddCollision(collidingObject);
}

void Actor::RemoveCollision(GameObject* gameObject)
{
	if (gameObject->GetName() == "ground" || gameObject->GetName() == "Ground")
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
