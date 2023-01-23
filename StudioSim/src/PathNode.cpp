#include "PathNode.h"

PathNode::PathNode(Grid<PathNode>* grid, int x, int y, bool walkable) : 
	m_grid(grid),
	m_isWalkable(walkable)
{
	this->x = x;
	this->y = y;	
}

PathNode::~PathNode()
{
}

void PathNode::CalculateFCost()
{
	m_fCost = m_gCost + m_hCost;
}
