#include "pch.h"

#include "PontiffSlashState.h"
#include "PontiffBaseState.h"

PontiffSlashState::PontiffSlashState(MiniPontiff* pontiff) : PontiffState(pontiff)
{
	m_timer = 2.0f;
	QE_LOG("SLASH");
	pontiff->StartAnimation("wideslash");
}

void PontiffSlashState::Update(float deltaTime)
{
	if (m_currTime <= m_timer)
	{
		m_currTime += deltaTime;
	}
	else
	{
		m_pontiff->SwitchState(new PontiffBaseState(m_pontiff));
	}
}
