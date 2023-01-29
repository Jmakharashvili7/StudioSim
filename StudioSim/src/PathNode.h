#pragma once
#include "BasicIncludes.h"
#include "Grid.h"

class PathNode
{
public:
	PathNode(Grid<PathNode>* grid, int x, int y, bool walkable = true);
	~PathNode();

	inline void SetIsWalkable(bool walkable) { m_isWalkable = walkable; }
	inline std::string ToString() { return std::to_string(x) + "," + std::to_string(y); }
	void CalculateFCost();
public:
	int x, y;
private:
	Grid<PathNode>* m_grid;
	int m_gCost, m_hCost, m_fCost;
	bool m_isWalkable;
	PathNode* m_parent;	
};

