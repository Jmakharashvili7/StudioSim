#pragma once
#include <math.h>
#include <cmath>
#include <assert.h>
#include <bit>
#include <cstdint>
#include <cstdio>
#include <limits>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iomanip>

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
	bool operator==(const Vector2& vec)
	{
		if (vec.x == x && vec.y == y)
			return true;
	}


	static Vector2 down()
	{
		return Vector2(0, -1);
	}
	static Vector2 up()
	{
		return Vector2(0, 1);
	}
	static Vector2 left()
	{
		return Vector2(-1, 0);
	}
	static Vector2 right()
	{
		return Vector2(1, 0);
	}
	static Vector2 negativeInfinity()
	{
		return Vector2(-INFINITY, -INFINITY);
	}
	static Vector2 positiveInfinity()
	{
		return Vector2(INFINITY, INFINITY);
	}
	static Vector2 one()
	{
		return Vector2(1, 1);
	}
	static Vector2 zero()
	{
		return Vector2(0, 0);
	}


	float magnitude()
	{
		return sqrt(x * x + y * y);
	}

	float squareMagnitude()
	{
		return x * x + y * y;
	}

	float showX()
	{
		return x;
	}

	float showY()
	{
		return y;
	}

	bool Equals(Vector2 vec)
	{
		if (vec.x == x && vec.y == y)
			return true;
	}

	Vector2 normalize()
	{
		return (x / this->magnitude(), y / this->magnitude());
	}

	void Set(float newX, float newY)
	{
		this->x = newX;
		this->y = newY;
	}

	float dotProduct(const Vector2& vec)
	{
		return vec.x * x + vec.y * y;
	}

	static Vector2 Reflect(Vector2 direction, Vector2 normal)
	{
		float num = -2.0f * direction.dotProduct(normal);
		Vector2 newVec(num * normal.x + direction.x, num * normal.y + direction.y);
		return newVec;
	}

	static Vector2 Perpendicular(Vector2 direction)
	{
		Vector2 perpendicularVec(0.0f - direction.y, direction.x);
		return perpendicularVec;
	}

	/// <summary>
	/// Gets the angle in degrees between 2 vectors
	/// </summary>
	/// <param name="first vector"></param>
	/// <param name="second vector"></param>
	/// <returns>Returns the angle in degrees</returns>
	/// <returns>Returns the angle in degrees</returns>
	static float Angle(Vector2 fromVec, Vector2 toVec)
	{
		float num = (float)sqrt(fromVec.squareMagnitude() * toVec.squareMagnitude());
		if (num < 1e-35f)
			return 0.0f;

		float num2;
		float dot = fromVec.dotProduct(toVec);
		float min = -1.0f, max = 1.0f;

		if (dot < min)
			num2 = min;
		if (dot > max)
			num2 = max;

		return (float)acos(num2) * 57.29578f;
	}

	static float Distance(Vector2 vec1, Vector2 vec2)
	{
		float num = vec1.x - vec2.x;
		float num2 = vec1.y - vec2.y;
		return (float)sqrt(num * num + num2 * num2);

	}

	static Vector2 Min(Vector2 vec1, Vector2 vec2)
	{
		return Vector2(std::min(vec1.x, vec2.x), std::min(vec1.y, vec2.y));
	}
	static Vector2 Max(Vector2 vec1, Vector2 vec2)
	{
		return Vector2(std::max(vec1.x, vec2.x), std::max(vec1.y, vec2.y));
	}
	static Vector2 Lerp(Vector2 vec1, Vector2 vec2, float t)
	{
		float min = -1.0f, max = 1.0f;
		float clampedT;
		if (t < min)
			clampedT = min;
		if (t > max)
			clampedT = max;
		return Vector2(vec1.x + (vec2.x - vec1.x) * clampedT, vec1.y + (vec2.y - vec1.y) * clampedT);
	}
	static Vector2 LerpUnclamped(Vector2 vec1, Vector2 vec2, float t)
	{

		return Vector2(vec1.x + (vec2.x - vec1.x) * t, vec1.y + (vec2.y - vec1.y) * t);
	}
	static Vector2 Move(Vector2 vec, Vector2 target, float distance)
	{
		float xDif = target.x - vec.x;
		float yDif = target.y - vec.y;
		float dist = xDif * xDif + yDif * yDif;

		if (dist == 0.0f || (distance >= 0.0f && dist <= distance * distance))
			return target;
		float mag = (float)sqrt(dist);
		return Vector2(vec.x + xDif / mag * distance, vec.y + yDif / mag * distance);
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
