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
	m_currentWeaponData = WeaponData("test", "twist.png", AttackData(25.0f, 0.5f, 10.0f, Vector3(0.85f, 1.0f, 1.0f), 0.0f, 0.1f, 0.1f, 0.2f, 0.05f), AttackData(40.0f, 1.0f, 20.0f, Vector3(1.25f, 1.0f, 1.0f), 0.2f, 0.2f, 0.25f, 0.25f, 0.05f)); // todo move
	m_combatComponent = new CombatComponent(this, 2, m_currentWeaponData);
	AddComponent(m_combatComponent);

	m_CanMove = true;
	m_DashTime = 0.2f;
	m_DashCooldowm = 2.5f;
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
	CheckDash();
}

void Character::AdjustPosition(const Vector3 adjustPosition)
{
	if (!m_CanMove)
	{
		return;
	}

	bool bforceStopAttack = false;

	if (GetAttacking() && m_facingDirection == FacingDirection::RIGHT && adjustPosition.x < 0)
	{
		bforceStopAttack = true;
	}

	if (GetAttacking() && m_facingDirection == FacingDirection::LEFT && adjustPosition.x > 0)
	{
		bforceStopAttack = true;
	}

	if (bforceStopAttack)
	{
		if (m_combatComponent)
		{
			m_combatComponent->ForceStopAttack();
		}

		if (GetCollidingWithGround())
		{
			StartAnimation("move", true);
		}
		else
		{
			StartAnimation("jump", true);
		}
	}

	const Vector3 newPosition = GetPosition();
	
	if (m_combatComponent)
	{
		m_combatComponent->UpdateAttackHitboxPosition(newPosition);
	}

	if (adjustPosition.x > 0)
	{
		StartAnimation("move");
		
		m_facingDirection = FacingDirection::RIGHT;

		if (GetScale().x < 0)
		{
			SetScale(Vector3(-1 * GetScale().x, GetScale().y, GetScale().z));
		}
	}
	else if (adjustPosition.x < 0)
	{
		StartAnimation("move");

		m_facingDirection = FacingDirection::LEFT;

		if (GetScale().x > 0)
		{
			SetScale(Vector3(-1 * GetScale().x, GetScale().y, GetScale().z));
		}
	}

	GameObject::AdjustPosition(adjustPosition);
}

void Character::OnCollision(GameObject* collidingObject)
{
	

	if (collidingObject->GetName() == "ground" || collidingObject->GetName() == "Ground")
	{
		if (!HasObjectsCollidingWithName("Ground") && !HasObjectsCollidingWithName("ground"))
		{
			SetJumping(false);
			StartAnimation("idle", true);
		}
	}

	
	if (collidingObject->GetName() == "wall" || collidingObject->GetName() == "Wall")
	{
		/*SetJumping(false);
		StartAnimation("idle", true);*/
		if (m_facingDirection == FacingDirection::RIGHT)
		{
			 m_bHitLeftWall = true;
			 m_bHitRightWall = false;
		}
		else if(m_facingDirection == FacingDirection::LEFT)
		{
			m_bHitLeftWall = false;
			m_bHitRightWall = true;
		}
		//AdjustPosition({ -m_movementData.movementSpeed * Quack::GetDeltaTime(), 0.0f, 0.0f });
		
	}

	Actor::OnCollision(collidingObject);
}

void Character::OnCollisionOver(GameObject* gameObject)
{

	if (gameObject->GetName() == "ground" || gameObject->GetName() == "Ground")
	{
		if (!HasObjectsCollidingWithName("Ground") && !HasObjectsCollidingWithName("ground"))
		{
			SetCollidingWithGround(false);
			StartAnimation("jump");
		}
	}
	if (gameObject->GetName() == "wall" || gameObject->GetName() == "Wall")
	{
		//StartAnimation("jump");
		m_bHitLeftWall = false;
		m_bHitRightWall = false;
	}

	GameObject::OnCollisionOver(gameObject);
	//Actor::OnCollisionOver(gameObject);
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

void Character::AttackStarted(const std::string attackType)
{
	StartAnimation(attackType);
}

bool Character::GetAttacking() const
{
	if (m_combatComponent)
	{
		return m_combatComponent->GetAttacking();
	}

	return false;
}

void Character::AttemptToDash()
{
	if (Quack::GetGameTime() >= (m_TimeSinceLastDash + m_DashCooldowm))
	{
		m_IsDashing = true;
		m_DashTimeLeft = m_DashTime;
		m_TimeSinceLastDash = Quack::GetGameTime();
		cout << "attempttodash" << endl;
	}
}

void Character::CheckDash()
{
	if (m_IsDashing)
	{
		if (m_DashTimeLeft > 0)
		{
			//m_CanMove = false;
			AdjustPosition(Vector3((GetMovementSpeed() * Quack::GetDeltaTime()), 0.0f, 1.0f));
			m_DashTimeLeft -= Quack::GetDeltaTime();
		}
		if (m_DashTimeLeft <= 0)
		{
			m_IsDashing = false;
			m_CanMove = true;
			m_physicsComponent->ResetForces();
		}
		
		cout << m_DashTimeLeft << endl;
	}
}

void Character::SetIdleAnimation()
{
	StartAnimation("idle");
}

void Character::OnAnimationFinished(const AnimationRowData& finishedAnimation)
{
	if (GetCollidingWithGround())
	{
		StartAnimation("idle");
	}
	else
	{
		StartAnimation("jump");
	}
}

void Character::StartAnimation(const std::string animationName, const bool bForce)
{
	if (!bForce)
	{
		if (animationName == "move" && !GetCollidingWithGround())
		{
			return;
		}

		if (animationName == "move" && (GetCurrentAnimation().name == "lightAttack" || GetCurrentAnimation().name == "heavyAttack" || GetCurrentAnimation().name == "specialAttack"))
		{
			return;
		}

		if (animationName == "idle" && !GetCollidingWithGround())
		{
			return;
		}
	}
	
	Actor::StartAnimation(animationName);
}

void Character::TakeDamage(const float amount, const float knockbackAmount, const float knockbackSpeed, const FacingDirection damageDirection)
{
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
	StartAnimation("takeHit");
}

void Character::Kill()
{
	SetCurrentHealth(0.0f);
}

void Character::Die()
{
	StartAnimation("die");
	Quack::GetCurrentScene()->RemoveGameObject(this);
}
