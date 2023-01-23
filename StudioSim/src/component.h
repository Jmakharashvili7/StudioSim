#pragma once
#include "BasicIncludes.h"
class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime);

	Component* GetComponentFromUpdateOrder(int updateOrder);

	int GetUpdateOrder() const { return m_UpdateOrder; }
protected:
	// Owning actor
	class Actor* m_Owner;
	// Update order of component
	int m_UpdateOrder;


};

