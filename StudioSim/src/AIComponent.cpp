#include "pch.h"

#include "AIComponent.h"
#include "EngineManager.h"

AIComponent::AIComponent(Actor* owningActor, const int updateOrder) :
	Component{ owningActor, updateOrder },
	m_state(EnemyState::IDLE),
	m_targetRange(10.0f),
	m_attackRange(1.0f),
	m_pathUpdateTime(0.5f),
	m_speed(1.0f)
{
	m_pathFinder = new Pathfinding();
	m_player = EngineManager::GetInputCharacter();	
}

void AIComponent::Update(const float deltaTime)
{
	Vector3 enemyPos = m_owningActor->GetPosition();
	Vector3 playerPos = m_player->GetPosition();

	switch (m_state)
	{
	case EnemyState::IDLE:
		if (Vector3::Distance(enemyPos, playerPos) <= m_targetRange)
		{
			m_path = m_pathFinder->FindPath(enemyPos, playerPos);
			m_state = EnemyState::CHASING;
			break;
		}
		break;
	case EnemyState::CHASING:
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
				if (m_path.empty())
				{
					m_state = EnemyState::ATTACKING;
					m_timer = 0.0f;
					break;
				}
			}

			Vector3 dir = Vector3::Direction(enemyPos, m_path[0]);
			m_owningActor->AdjustPosition(dir * deltaTime * m_speed);
		}
		
		break;
	case EnemyState::ATTACKING:
		if (Vector3::Distance(enemyPos, playerPos) >= m_attackRange)
		{
				m_state = EnemyState::IDLE;
				break;
		}
		break;
	}
}
