#include "component.h"
#include "GameObject.h"

//Component::Component(GameObject* owner, int updateOrder )
//{
//}

Component::~Component()
{
}


Component::Component(Actor* owner, int updateOrder)
{
	m_Owner = owner;
	m_UpdateOrder = updateOrder;
}

void Component::Update(float deltaTime)
{
	
}

Component* Component::GetComponentFromUpdateOrder(int updateOrder)
{
	if (updateOrder == m_UpdateOrder)
	{
		return this;
	}
	return nullptr;
}
