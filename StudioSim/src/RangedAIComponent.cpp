#include "pch.h"

#include "RangedAIComponent.h"
#include "Quack.h"
#include "EnemyProjectile.h"

RangedAIComponent::RangedAIComponent(Actor* owningActor, const int updateOrder) : AIComponent(owningActor, updateOrder)
{

}

void RangedAIComponent::Update(const float deltaTime)
{
	Vector3 enemyPos = m_owningActor->GetPosition();
	Vector3 playerPos = m_player->GetPosition();

	switch (m_state)
	{
	case MeleeState::IDLE:
		if (Vector3::Distance(enemyPos, playerPos) <= m_targetRange)
		{
			m_path = m_pathFinder->FindPath(enemyPos, playerPos);
			m_state = MeleeState::CHASING;
			break;
		}
		break;
	case MeleeState::CHASING:
		m_timer += deltaTime;

		if (m_timer >= m_pathUpdateTime)
		{
			m_path = m_pathFinder->FindPath(enemyPos, playerPos);
			m_timer = 0.0f;
		}

		if (!m_path.empty())
		{
			if (Vector3::Distance(enemyPos, m_path[0]) < 0.5f)
			{
				m_path.erase(m_path.begin());

				// check if we're arrived at destination
				if (m_path.empty() || Vector3::Distance(enemyPos, playerPos) <= m_attackRange)
				{
					m_state = MeleeState::ATTACKING;
					m_timer = 0.0f;
					break;
				}
			}

			Vector3 dir = Vector3::Direction(enemyPos, m_path[0]);
			m_owningActor->AdjustPosition(dir * deltaTime * m_speed);
		}
		break;
	case MeleeState::ATTACKING:
		Quack::GetCurrentScene()->AddGameObject(new EnemyProjectile("IceBlock", 10.0f, Vector3::Direction(enemyPos, playerPos), enemyPos));
		if (Vector3::Distance(enemyPos, playerPos) >= m_attackRange)
		{
			m_state = MeleeState::IDLE;
			break;
		}
		break;
	}
}
