#pragma once
#include "component.h"

class AIComponent : public Component
{
public:
	AIComponent(Actor* owningActor, const int updateOrder);

	virtual void Update(const float deltaTime) override;
};

