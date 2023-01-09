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


// Gravity
void AddGravity(float deltaTime)
{
	RigidBody object;
	float weight = object.mass * GFORCE;
	object.position.y += weight * deltaTime;
}

// Player Movement
void PlayerMovement(float deltaTime)
{
	RigidBody object;
	//input to change
	if (GetAsyncKeyState('D'))
	{
		object.position.x += 0.1f * deltaTime;
		std::cout << "Character moves right";
	}
	if (GetAsyncKeyState('A'))
	{
		object.position.x -= 0.1f * deltaTime;
		std::cout << "Character moves left";

	}
	if (GetAsyncKeyState('W'))
	{
		//JUMP
		CharacterJump(deltaTime);
		std::cout << "Character Jumps";

	}
	if (GetAsyncKeyState('S'))
	{
		//CROUCH
		std::cout << "Character Crouches";

	}
}


// Jump
void CharacterJump(float deltaTime)
{
	RigidBody object;
	float jumpForce;
	
	object.position.y -= jumpForce * deltaTime;

}


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


/// <summary>
/// Check if 2 spheres collide
/// </summary>
/// <param name="sphere 1"></param>
/// <param name="sphere 2"></param>
/// <returns></returns>
bool SpheretoSphere(BoundingSphere& sp1, BoundingSphere& sp2)
{
	float distance = sqrt(
		(sp1.center.x - sp2.center.x) * (sp1.center.x - sp2.center.x)
		+ (sp1.center.y - sp2.center.y) * (sp1.center.y - sp2.center.y));

	return distance < (sp1.radius + sp2.radius);
}




