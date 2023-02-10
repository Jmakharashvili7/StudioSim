#include "pch.h"

#include "PontiffBaseState.h"
#include "PontiffSlashState.h"
#include "PontiffChargeState.h"
#include "PontiffUltimateState.h"
#include "PontiffFireState.h"
#include "AIComponent.h"
#include <random>

PontiffBaseState::PontiffBaseState(MiniPontiff* pontiff) : PontiffState(pontiff)
{
	m_timer = 2.0f;
	m_pontiff->StartAnimation("idle");
}

void PontiffBaseState::Update(float deltaTime)
{
	m_currTime += deltaTime;
	m_pontiff->GetAIComponent()->Update(deltaTime);
	m_pontiff->StartAnimation("move");

	if (m_currTime >= m_timer)
	{
		int attack = rand() % 3;
		switch (attack)
		{
		case 0:
			m_pontiff->SwitchState(new PontiffSlashState(m_pontiff));
			break;
		case 1:
			m_pontiff->SwitchState(new PontiffChargeState(m_pontiff));
			break;
		case 2:
			m_pontiff->SwitchState(new PontiffFireState(m_pontiff));
			break;
		}
	}
}
