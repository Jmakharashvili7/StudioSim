#pragma once
#include "BasicIncludes.h"

struct BoundingBox
{
	Vector3 center;
	Vector3 size;
	BoundingBox()
	{
		center.x = 0;
		center.y = 0;
		center.z = 0;
		size.x = 0;
		size.y = 0;
		size.z = 0;	
	}
	BoundingBox(Vector3 position, Vector3 size)
	{
		center = position;
		this->size = size;
	}
};

struct BoundingSphere
{
	BoundingSphere()
	{
		center.x = 0;
		center.y = 0;
		center.z = 0;
		radius = 0;
	}
	BoundingSphere(Vector3 position, float radius)
	{
		center = position;
		this->radius = radius;
	}
	Vector3 center;
	float radius;
};

class QuackPhysics
{
public:

	QuackPhysics() {};
	~QuackPhysics() {};

	/// <summary>
	/// Check if 2 squares collide
	/// </summary>
	/// <param name="box 1"></param>
	/// <param name="box 2"></param>
	/// <returns></returns>
	bool BoxToBox(BoundingBox b1, BoundingBox b2)
	{
		Vector3 min1 = b1.center - b1.size/Vector3(2,2,2);
		Vector3 max1 = b1.center + b1.size/Vector3(2,2,2);
		Vector3 min2 = b2.center - b2.size/Vector3(2,2,2);
		Vector3 max2 = b2.center + b2.size/Vector3(2,2,2);

		if ((min1.x <= max2.x && max1.x >= min2.x) &&
			(min1.y <= max2.y && max1.y >= min2.y) &&
			(min1.z <= max2.z && max1.z >= min2.z))
		{
			return true;
		}

		return false;
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
			+ (sp1.center.y - sp2.center.y) * (sp1.center.y - sp2.center.y)
			+ (sp1.center.z - sp2.center.z) * (sp1.center.z - sp2.center.z));


		return distance < (sp1.radius + sp2.radius);
	}
};