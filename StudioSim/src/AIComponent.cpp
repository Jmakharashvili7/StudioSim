#include "pch.h"

#include "AIComponent.h"
#include "EngineManager.h"

AIComponent::AIComponent(Actor* owningActor, const int updateOrder, Grid<PathNode> grid) : 
	Component{ owningActor, updateOrder }
{
	m_pathFinder = new Pathfinding(grid);
	m_player = EngineManager::GetInputCharacter();
}

void AIComponent::Update(const float deltaTime)
{
	//m_path = m_pathFinder->FindPath(m_owningActor->GetPosition(), m_player->GetPosition());	
	//if (Vector3::Distance(m_owningActor->GetPosition(), m_player->GetPosition()) < 0.5f)
	//{
	//	m_path.erase(m_path.begin());
	//}
	//
	//Vector3 newPos = m_owningActor->GetPosition();
	//newPos += 1.0f * deltaTime;
	//m_owningActor->AdjustPosition(newPos);
}
