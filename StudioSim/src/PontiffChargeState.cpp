#include "pch.h"

#include "PontiffChargeState.h"
#include "PontiffBaseState.h"
#include "EngineManager.h"


PontiffChargeState::PontiffChargeState(MiniPontiff* pontiff) : 
	PontiffState(pontiff),
	m_chargeNum(3),
	m_chargeCounter(0),
	m_attacked(false),
	m_teleported(false),
	m_speed(9.0f),
	m_distance(5.0f),
	m_directionChange(false)
{
	m_player = EngineManager::GetInputCharacter();
	m_timer = 0.7f;
}

void PontiffChargeState::Update(float deltaTime)
{
	if (m_chargeCounter < m_chargeNum)
	{
		if (!m_teleported)
		{
			// teleport boss
			Vector3 spawnPos = m_player->GetPosition();
			if (!m_directionChange)
			{
				spawnPos.x -= 2;
				m_directionChange = !m_directionChange;
			}
			else
			{
				spawnPos.x += 2;
				m_directionChange = !m_directionChange;
			}
			m_pontiff->SetPosition(spawnPos);
			m_originPos = spawnPos;

			// set direction to the player
			m_direction = Vector3::Direction(m_pontiff->GetPosition(), m_player->GetPosition());
			m_direction.y = 0.0f;
			m_direction.z = 0.0f;
			m_teleported = true;
		}
		else
		{
			if (!m_attacked)
			{
				Vector3 traveledDistance = deltaTime * m_direction * m_speed;
				m_pontiff->AdjustPosition(traveledDistance);
				m_traveled += traveledDistance.Length();
				if (m_traveled >= m_distance)
				{
					m_attacked = true;
					m_traveled = 0;
					m_chargeCounter++;

					// put pontiff off screen
					m_pontiff->SetPosition({-999999.0f, 0.0f, 0.0f});
				}
			}
			else
			{
				m_currTime += deltaTime;
				if (m_currTime >= m_timer)
				{
					m_teleported = false;
					m_attacked = false;
					m_currTime = 0.0f;
				}
			}
		}
	}
	else
	{
		m_currTime += deltaTime;
		if (m_currTime >= m_timer)
		{
			m_pontiff->SetPosition(m_originPos);
			m_pontiff->SwitchState(new PontiffBaseState(m_pontiff));
		}
	}
}
