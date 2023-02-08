#include "pch.h"

#include "PontiffBaseState.h"
#include "PontiffSlashState.h"
#include "PontiffChargeState.h"
#include "PontiffUltimateState.h"
#include "PontiffFireState.h"
#include <random>

PontiffBaseState::PontiffBaseState(MiniPontiff* pontiff) : PontiffState(pontiff)
{
}

void PontiffBaseState::Update(float deltaTime)
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
