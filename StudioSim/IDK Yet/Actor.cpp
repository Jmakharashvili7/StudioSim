#include "Actor.h"
#include "Component.h"

Actor::Actor()
{
	// init all things such as transform, components etc
}

Actor::~Actor()
{
}

void Actor::Update(float _deltaTime)
{
	if (m_State != EActive)
	{
		return;
	}
	UpdateActor(_deltaTime);
	UpdateComponents(_deltaTime);
}

void Actor::Draw()
{
}

void Actor::UpdateComponents(float _deltaTime)
{
	if (m_State != EActive)
	{
		return;
	}
	for (auto Components : m_Components)
	{
		Components->Update(_deltaTime);
	}
}

void Actor::UpdateActor(float _deltaTime)
{
	if (m_State != EActive)
	{
		return;
	}
}

void Actor::AddComponent(Component* _component)
{
	m_Components.push_back(_component);
	//sort(m_Components.begin(), m_Components.end(), SortComponents);
}

void Actor::RemoveComponent(Component* _component)
{
	remove(m_Components.begin(), m_Components.end(), _component);
	//(m_Components.begin(), m_Components.end(), SortComponents);
}

bool Actor::SortComponents(Component* i, Component* j)
{
	 return i->GetUpdateOrder() > j->GetUpdateOrder(); 
}
