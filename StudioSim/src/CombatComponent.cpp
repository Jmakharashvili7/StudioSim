#include "pch.h"
#include "CombatComponent.h"
#include "Quack.h"
#include "EngineManager.h"
#include "JsonLoader.h"
#include "Character.h"

CombatComponent::CombatComponent(Actor* owner, int updateOrder, const WeaponData& startingWeaponData) : Component {owner, updateOrder}
{
	// Character init
	m_owningCharacter = dynamic_cast<Character*>(owner);

	// Weapon init
	m_currentWeaponData = startingWeaponData;
}

CombatComponent::~CombatComponent()
{

}

void CombatComponent::Update(const float deltaTime)
{
	if (m_battacking)
	{
		const float totalAttackTime = m_currentAttackData.totalAttackTime;

		m_currentAttackTimer -= deltaTime;

		if (!m_bactivateDelayTimerFinished && m_currentAttackTimer <= totalAttackTime - m_currentAttackData.hitboxActivateDelay)
		{
			ActivateDelayTimerFinished();
		}
		
		if (!m_bactivateTimerFinished && m_currentAttackTimer <= totalAttackTime - m_currentAttackData.hitboxActiveTime - m_currentAttackData.hitboxActivateDelay)
		{
			ActiveTimerFinished();
		}

		if (!m_bdeactivateTimerFinished && m_currentAttackTimer <= totalAttackTime - m_currentAttackData.hitboxDeactivateTime - m_currentAttackData.hitboxActivateDelay - m_currentAttackData.hitboxActiveTime)
		{
			DeactivateTimerFinished();
		}

		if (m_currentAttackTimer <= 0.0f)
		{
			AttackFinished();
		}
	}
}

void CombatComponent::LightAttack()
{
	StartAttack(m_currentWeaponData.lightAttackData);
}

void CombatComponent::HeavyAttack()
{
	StartAttack(m_currentWeaponData.heavyAttackData);
}

void CombatComponent::SpecialAttack()
{
	StartAttack(m_currentWeaponData.specialAttackData);
}

void CombatComponent::StartAttack(const AttackData& attackData)
{
	if (attackData.damage > 0.0f && CanAttack())
	{
		m_battacking = true;
		m_currentAttackData = attackData;
		m_currentAttackTimer = attackData.totalAttackTime;
		m_currentAttackFacingDirection = m_owningCharacter->GetFacingDirection();
	}
}

bool const CombatComponent::CanAttack() const
{
	if (!m_battacking)
	{
		return true;
	}

	return false;
}

void CombatComponent::ResetTimerBools()
{
	m_bactivateDelayTimerFinished = false;
	m_bactivateTimerFinished = false;
	m_bdeactivateTimerFinished = false;
}

void CombatComponent::ActivateDelayTimerFinished()
{
	m_bactivateDelayTimerFinished = true;

	// temp todo change
	const Vector3 hitboxScale = m_owningActor->GetScale();

	const bool RightAttack = m_currentAttackFacingDirection == FacingDirection::RIGHT ? true : false;
	const Vector3 HitboxPosition = RightAttack ? Vector3(m_owningActor->GetPosition().x + (m_owningActor->GetScale().x * 0.5f) + (hitboxScale.x * 0.5f), m_owningActor->GetPosition().y, m_owningActor->GetPosition().z) : Vector3(m_owningActor->GetPosition().x - (m_owningActor->GetScale().x * 0.5f) - (hitboxScale.x * 0.5f), m_owningActor->GetPosition().y, m_owningActor->GetPosition().z);
	VertexData* weaponHitboxVertexData = QuackEngine::JsonLoader::LoadObjectData2D("res/ObjectData/Square.json");

	TransformData weaponHitboxTransformData = TransformData(HitboxPosition, m_owningActor->GetRotation(), hitboxScale);
	CollisionData weaponHitboxCollisionData = CollisionData(m_owningActor->GetCollisionData());

	m_weaponHitbox = new GameObject("tempWeaponHitbox", weaponHitboxVertexData, weaponHitboxTransformData, weaponHitboxCollisionData, m_currentWeaponData.textureName);
	Quack::GetCurrentScene()->AddGameObject(m_weaponHitbox);
}

void CombatComponent::ActiveTimerFinished()
{
	m_bactivateTimerFinished = true;

	Quack::GetCurrentScene()->RemoveGameObject(m_weaponHitbox);
	m_weaponHitbox = nullptr;
}

void CombatComponent::DeactivateTimerFinished()
{
	m_bdeactivateTimerFinished = true;
}

void CombatComponent::AttackFinished()
{
	m_battacking = false;
	m_currentAttackTimer = 0.0f;
	ResetTimerBools();
}
