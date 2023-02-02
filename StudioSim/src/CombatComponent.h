#pragma once
#include "component.h"

class Character;

class CombatComponent : public Component
{
public:
	CombatComponent(Actor* owner, int updateOrder, const WeaponData& startingWeaponData);
	~CombatComponent();

	virtual void Update(const float deltaTime) override;

	virtual void LightAttack();
	virtual void HeavyAttack();
	virtual void SpecialAttack();
	virtual void StartAttack(const AttackData& attackData);
	virtual bool const CanAttack() const;

	virtual void ResetTimerBools();
	virtual void ActivateDelayTimerFinished();
	virtual void ActiveTimerFinished();
	virtual void DeactivateTimerFinished();
	virtual void AttackFinished();

	virtual inline void SetCurrentWeaponData(const WeaponData& newWeaponData) { m_currentWeaponData = newWeaponData; }
	virtual inline const WeaponData GetCurrentWeaponData() const { return m_currentWeaponData; }

protected:
	Character* m_owningCharacter = nullptr;

	WeaponData m_currentWeaponData = WeaponData();
	GameObject* m_weaponHitbox = nullptr;
	bool m_battacking = false;
	AttackData m_currentAttackData = AttackData();
	float m_currentAttackTimer = 0.0f;
	FacingDirection m_currentAttackFacingDirection = FacingDirection::RIGHT;
	
	bool m_bactivateDelayTimerFinished = false;
	bool m_bactivateTimerFinished = false;
	bool m_bdeactivateTimerFinished = false;
};

