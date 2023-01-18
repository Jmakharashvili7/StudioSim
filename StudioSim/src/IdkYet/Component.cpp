#include "Component.h"

Component::Component(Actor* _owner, int _updateOrder)
{
	m_Owner = _owner;
	m_UpdateOrder = _updateOrder;
}

Component::~Component()
{
}

void Component::Update(float _deltaTime)
{

}

