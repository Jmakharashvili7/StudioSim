#pragma once
#include "component.h"
#include "Pathfinding.h"
#include "Character.h"

class AIComponent : public Component
{
public:
	AIComponent(Actor* owningActor, const int updateOrder, Grid<PathNode> grid);

	virtual void Update(const float deltaTime) override;
private:
	Pathfinding* m_pathFinder;
	Character* m_player;
	std::vector<Vector3> m_path;
};

