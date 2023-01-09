#pragma once

#include <vector>
#include "QuackMath.h"

class PhysicsWorld
{
private:
	std::vector<Object*> m_Objects;
	Vector2 m_Gravity = Vector2{0, -9.81f};

public:
	void AddObject(Object* object)
	{
		m_Objects.push_back(object);
	}
	
	void RemoveObject(Object* object)
	{
		if (!object) return;
		auto itr = std::find(m_Objects.begin(), m_Objects.end(), object);
		if (itr == m_Objects.end()) return;
		m_Objects.erase(itr);
	}

	void step(float dt)
	{
		for (Object* obj : m_Objects)
		{
			//obj->Force += obj->Mass *  m_Gravity;
		}
	}
};

