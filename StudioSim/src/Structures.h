#pragma once
#include <math.h>
#include<assert.h>
#include "BasicIncludes.h"

#define GFORCE 9.81


struct Vector2
{
	float x;
	float y;
	Vector2(float xVal = 0, float yVal = 0)
	{
		x = xVal;
		y = yVal;
	}
	Vector2 operator+(const  Vector2& vec)
	{
		return Vector2(x + vec.x, y + vec.y);
	}
	Vector2 operator+(const  Vector2& vec)
	{
		return Vector2(x + vec.x, y + vec.y);
	}
	Vector2 operator+=(const Vector2& vec)
	{
		x += vec.x;
		y += vec.y;

		return *this;
	}
	Vector2 operator-(const  Vector2& vec)
	{
		return Vector2(x - vec.x, y - vec.y);
	}
	Vector2 operator-=(const Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;

		return *this;
	}
	Vector2 operator*(float value)
	{
		return Vector2(x * value, y * value);
	}
	Vector2 operator*=(float value)
	{
		x *= value;
		y *= value;

		return *this;
	}
	Vector2 operator/(float value)
	{
		assert(value != 0);
		return Vector2(x / value, y / value);
	}
	Vector2 operator/=(float value)
	{
		assert(value != 0);
		x /= value;
		y /= value;

		return *this;
	}
	Vector2 operator=(const Vector2& vec)
	{
		return Vector2(x = vec.x, y = vec.y);
	}
};

struct RigidBody
{
	Vector2 position;
	float mass;
};

struct BoundingBox
{
	Vector2 center;
	Vector2 size;
	BoundingBox()
	{
		center.x = 0;
		center.y = 0;
		size.x = 0;
		size.y = 0;
	}
	BoundingBox(Vector2 position, Vector2 size)
	{
		center = position;
		this->size = size;
	}
};

struct BoundingSphere
{
	Vector2 center;
	float radius;
};
