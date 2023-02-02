#include "pch.h"

#include "Character.h"
#include "Quack.h"
#include "PhysicsComponent.h"
#include "EngineManager.h"
#include "JsonLoader.h"

Character::Character(std::string name, VertexData* data, const TransformData& transformData, const CollisionData& collisionData, 
	const std::string& textureName, const PhysicsData& physicsData, const MovementData& movementData, const EntityData& entityData, const AnimationData& animationData, const bool bconsumeInput)
	: Actor {name, data, transformData, collisionData, textureName, physicsData, animationData}, m_movementData(movementData), m_entityData(entityData), m_bconsumingInput(bconsumeInput)
{
	m_type = GameObjectType::CHARACTER;

	// Input init
	if (m_bconsumingInput)
	{
		EngineManager::SetInputCharacter(this);
	}

	// Health init
	ResetCurrentHealth();

	// Combat init
	m_currentWeaponData = WeaponData("test", "blue.png", AttackData(25.0f, 5.0f, 0.1f, 0.01f, 0.25f, 0.01f)); // todo move
	m_combatComponent = new CombatComponent(this, 2, m_currentWeaponData);
	AddComponent(m_combatComponent);
}

Character::~Character()
{

}

void Character::Update(const float deltaTime)
{
	Actor::Update(deltaTime);
}

void Character::AdjustPosition(const Vector3 adjustPosition)
{
	GameObject::AdjustPosition(adjustPosition);

	if (adjustPosition.x > 0)
	{
		m_facingDirection = FacingDirection::RIGHT;
	}
	else if (adjustPosition.x < 0)
	{
		m_facingDirection = FacingDirection::LEFT;
	}
}

void Character::AddCollision(GameObject* collidingObject)
{
	if (collidingObject->GetName() == "ground")
	{
		SetJumping(false); 
		SetCollidingWithGround(true);
	}

	Actor::AddCollision(collidingObject);
}

void Character::RemoveCollision(GameObject* gameObject)
{
	Actor::RemoveCollision(gameObject);
}

void Character::Jump()
{
	if (m_physicsData.bsimulateGravity && !m_bjumping)
	{
		m_bjumping = true;

		if (m_physicsComponent)
		{
			m_physicsComponent->AddForce(Vector3(0.0f, m_movementData.jumpHeight, 0.0f));
		}
	}
}

void Character::SetCurrentHealth(const float inHealth)
{
	m_currentHealth = inHealth;
	CheckShouldDie();
}

void Character::AdjustCurrentHealth(const float adjustAmount)
{
	m_currentHealth += adjustAmount;
	CheckShouldDie();
}

void Character::CheckShouldDie()
{
	if (GetCurrentHealth() <= 0.0f)
	{
		Die();
	}
}

void Character::SetMaxHealth(const float newMaxHealth, const bool bUpdateHealth)
{
	m_entityData.maxHealth = newMaxHealth;

	if (bUpdateHealth)
	{
		SetCurrentHealth(newMaxHealth);
	}
}

void Character::SetCurrentWeaponData(const WeaponData& newWeaponData)
{
	m_currentWeaponData = newWeaponData;
	
	if (m_combatComponent)
	{
		m_combatComponent->SetCurrentWeaponData(newWeaponData);
	}
}

void Character::LightAttack()
{
	if (m_combatComponent)
	{
		m_combatComponent->LightAttack();;
	}
}

void Character::HeavyAttack()
{
	if (m_combatComponent)
	{
		m_combatComponent->HeavyAttack();;
	}
}

void Character::SpecialAttack()
{
	if (m_combatComponent)
	{
		m_combatComponent->SpecialAttack();
	}
}

void Character::TakeDamage(const float amount)
{
	std::cout << "Ouch - " + m_name << std::endl;
	AdjustCurrentHealth(amount);
}

void Character::Kill()
{
	SetCurrentHealth(0.0f);
}

void Character::Die()
{
	std::cout << "Im dead - " + m_name << std::endl;
}
