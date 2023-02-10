#include "pch.h"

#include "MiniPontiff.h"
#include "PontiffState.h"
#include "Quack.h"
#include "EnemyProjectile.h"
#include "PontiffBaseState.h"
#include "AIComponent.h"
#include "UILayer.h"

MiniPontiff::MiniPontiff(std::string name, VertexData* data, const TransformData& transformData, const CollisionData& collisionData, const std::string& textureName, const PhysicsData& physicsData, const MovementData& movementData, const EntityData& entityData, const AnimationData& animationData, EnemyType enemyType) : 
	Enemy(name, data, transformData, collisionData, textureName, physicsData, movementData, entityData, animationData, enemyType)
{
	m_enemyType = EnemyType::MINI_PONTIFF;
	m_state = new PontiffBaseState(this);
}

MiniPontiff::~MiniPontiff()
{

}

void MiniPontiff::Update(const float deltaTime)
{
	if (m_animationDataRowsToAdd > 0)
	{
		for (int i = 0; i < m_animationDataRowsToAdd; i++)
		{
			m_animationData.animationRowData.push_back(AnimationRowData());
		}
		m_animationDataRowsToAdd = 0;
	}

	if (m_animationDataRowsToRemove.size() > 0)
	{
		for (int animIndexToRemove : m_animationDataRowsToRemove)
		{
			m_animationData.animationRowData.erase(m_animationData.animationRowData.begin() + animIndexToRemove);
		}
		m_animationDataRowsToRemove.clear();
	}

	for (Component* component : m_components)
	{
		AIComponent* aiComp = dynamic_cast<AIComponent*>(component);

		// Dont update AI component as its manually called in the right state
		if (aiComp == nullptr)
			component->Update(deltaTime);
	}

	if (Quack::GetUILayer()->GetInPlay())
		m_state->Update(deltaTime);
}

void MiniPontiff::OnCollision(GameObject* collidingObject)
{
	Enemy::OnCollision(collidingObject);
}

void MiniPontiff::OnCollisionOver(GameObject* gameObject)
{
	Enemy::OnCollisionOver(gameObject);	
}

void MiniPontiff::SwitchState(PontiffState* newState)
{
	if (newState)
	{
		delete m_state;
		m_state = newState;
	}
}

void MiniPontiff::Blink(Vector3 pos)
{
	SetPosition(pos);
}

void MiniPontiff::WideSlash(float attackSpeed)
{

}

void MiniPontiff::FloatAttack(Vector3 dir, float attackSpeed)
{

}


void MiniPontiff::ThrowBlades(float projectileNumber)
{
}

void MiniPontiff::UltimateAttack(Vector3 posToAttackFrom, float attackSpeed)
{

}

void MiniPontiff::Wait(float deltaTime, float duration)
{
	static int timer = 0.0f;

	if (timer < duration)
	{
		timer += deltaTime;
	}
	timer = 0.0f;
}
