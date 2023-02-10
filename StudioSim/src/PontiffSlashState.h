#pragma once
#include "PontiffState.h"

class PontiffSlashState : public PontiffState
{
public:
	PontiffSlashState(MiniPontiff* pontiff);
	~PontiffSlashState() {}

	void Update(float deltaTime) override;
};

