#include "pch.h"

#include "Character.h"
#include "Quack.h"
#include "PhysicsComponent.h"
#include "EngineManager.h"
#include "JsonLoader.h"
#include "Animate.h"

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
	m_currentWeaponData = WeaponData("test", "blue.png", AttackData(25.0f, 0.5f, 10.0f, Vector3(0.5f, 0.5f, 0.5f), 0.25f, 0.05f, 0.01f, 0.1f, 0.01f)); // todo move
	m_combatComponent = new CombatComponent(this, 2, m_currentWeaponData);
	AddComponent(m_combatComponent);
}

Character::~Character()
{

}

void Character::Update(const float deltaTime)
{
	Actor::Update(deltaTime);

	if (m_beingKnockbacked)
	{
		const float tickKnockbackAmount = m_knockbackSpeed * deltaTime;
		m_currentKnockbackAmount += glm::abs(tickKnockbackAmount);
		AdjustPosition(Vector3(tickKnockbackAmount, 0.0f, 0.0f));

		if (m_currentKnockbackAmount >= glm::abs(m_totalKnockbackAmount))
		{
			m_beingKnockbacked = false;
			m_currentKnockbackAmount = 0.0f;
			m_totalKnockbackAmount = 0.0f;
		}
	}
}

void Character::AdjustPosition(const Vector3 adjustPosition)
{
	GameObject::AdjustPosition(adjustPosition);
	const Vector3 newPosition = GetPosition();
	
	if (m_combatComponent)
	{
		m_combatComponent->UpdateAttackHitboxPosition(newPosition);
	}

	if (adjustPosition.x > 0)
	{
		m_facingDirection = FacingDirection::RIGHT;

		if (GetScale().x < 0)
		{
			SetScale(Vector3(-1 * GetScale().x, GetScale().y, GetScale().z));
		}

	    
	}
	else if (adjustPosition.x < 0)
	{
		m_facingDirection = FacingDirection::LEFT;

		if (GetScale().x > 0)
		{
			SetScale(Vector3(-1 * GetScale().x, GetScale().y, GetScale().z));
		}
	}
}

void Character::AddCollision(GameObject* collidingObject)
{
	if (collidingObject->GetName() == "ground" || collidingObject->GetName() == "Ground")
	{
		SetJumping(false); 
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

void Character::SetLightAttackAnimationRow(const int newRow)
{
	m_animationData.lightAttackRow = newRow;

	if (m_animator)
	{
		m_animator->SetLightAttackAnimationRow(newRow);
	}
}

void Character::SetHeavyAttackAnimationRow(const int newRow)
{
	m_animationData.heavyAttackRow = newRow;

	if (m_animator)
	{
		m_animator->SetHeavyAttackAnimationRow(newRow);
	}
}

void Character::SetSpecialAttackAnimationRow(const int newRow)
{
	m_animationData.specialAttackRow = newRow;

	if (m_animator)
	{
		m_animator->SetSpecialAttackAnimationRow(newRow);
	}
}

void Character::SetDeathAnimationRow(const int newRow)
{
	m_animationData.deathRow = newRow;

	if (m_animator)
	{
		m_animator->SetDeathAnimationRow(newRow);
	}
}

void Character::SetJumpAnimationRow(const int newRow)
{
	m_animationData.jumpRow = newRow;

	if (m_animator)
	{
		m_animator->SetJumpAnimationRow(newRow);
	}
}

void Character::SetTakeHitAnimationRow(const int newRow)
{
	m_animationData.takeHitRow = newRow;

	if (m_animator)
	{
		m_animator->SetTakeHitAnimationRow(newRow);
	}
}

void Character::TakeDamage(const float amount, const float knockbackAmount, const float knockbackSpeed, const FacingDirection damageDirection)
{
	std::cout << "Ouch - " + m_name << std::endl;
	if (knockbackAmount > 0.0f)
	{
		const float bdamageDirectionRight = damageDirection == FacingDirection::RIGHT;
		const float finalKnockbackSpeed = knockbackSpeed / GetMass();
		const float finalKnockbackAmount = knockbackAmount / GetMass();

		m_beingKnockbacked = true;
		m_knockbackSpeed = bdamageDirectionRight ? -finalKnockbackSpeed : finalKnockbackSpeed;
		m_totalKnockbackAmount = bdamageDirectionRight ? -finalKnockbackAmount : finalKnockbackAmount;
	}
	AdjustCurrentHealth(-amount);
}

void Character::Kill()
{
	SetCurrentHealth(0.0f);
}

void Character::Die()
{
	std::cout << "Im dead - " + m_name << std::endl;
	Quack::GetCurrentScene()->RemoveGameObject(this);
}
