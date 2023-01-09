#pragma once
#include "Structures.h"
/// <summary>
/// Adds two vectors together.
/// </summary>
/// <param name="start position"></param>
/// <param name="force"></param>
/// <returns></returns>
Vector2 AddVector2(Vector2 vec1, Vector2 vec2)
{
	float x = vec1.x + vec2.x;
	float y = vec1.y + vec2.y;

	return Vector2(x, y);
}


////
//
// Gravity
void AddGravity(float deltaTime)
{
	RigidBody object;
	object.center.y += GRAVITY * deltaTime;
}
// Player Movement
// Jump
// Collision detection

/// <summary>
/// Check if 2 rectangles collide
/// </summary>
/// <param name="box 1"></param>
/// <param name="box 2"></param>
/// <returns></returns>
bool BoxToBox(BoundingBox b1, BoundingBox b2)
{
	Vector2 min1 = b1.center - b1.size;
	Vector2 max1 = b1.center + b1.size;
	Vector2 min2 = b2.center - b2.size;
	Vector2 max2 = b2.center + b2.size;

	return (min1.x <= max2.x && max1.x >= min2.x) &&
		(min1.y <= max2.y && max1.y >= min2.y);
}

//Sphere collision
bool SpheretoSphere(BoundingSphere& sp1, BoundingSphere& sp2)
{
	float distance = sqrt(
		(sp1.center.x - sp2.center.x) * (sp1.center.x - sp2.center.x)
		+ (sp1.center.y - sp2.center.y) * (sp1.center.y - sp2.center.y));
		
	return distance < (sp1.radius + sp2.radius);
}




