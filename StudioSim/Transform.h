#pragma once
#include "IDK Yet/Component.h"
#include <cmath>
#include <complex>

using namespace std;

struct Vector2
{
	float x;
	float y;


	Vector2() : x(0), y(0)
	{
	}

	static Vector2 Up() {
		return Vector2(0, 1);
	}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2(const Vector2& v)
	{
		this->x = v.x;
		this->y = v.y;
	}

	Vector2& operator=(const Vector2& v)
	{
		this->x = v.x;
		this->y = v.y;
		return *this;
	}
	const float& operator[](int i) const
	{
		return i == 0 ? x : y;
	}

	const float& operator()(int i) const
	{
		return (*this)[i];
	}


	Vector2 operator()() const
	{
		return normalize();
	}

	bool operator==(const Vector2& v) const
	{
		return x == v.x && y == v.y;
	}

	bool operator!=(const Vector2& v) const
	{
		return !(*this == v);
	}

	Vector2 operator+(const Vector2& v) const
	{
		return Vector2(x + v.x, y + v.y);
	}

	Vector2 operator-(const Vector2& v) const
	{
		return Vector2(x - v.x, y - v.y);
	}

	//scaling
	Vector2 operator*(float v) const
	{
		return Vector2(x * v, y * v);
	}

	//scaling
	Vector2 operator/(float v) const
	{
		return Vector2(x / v, y / v);
	}

	//component-wise scaling
	Vector2 operator*(const Vector2& v) const
	{
		return Vector2(x * v.x, y * v.y);
	}

	//component-wise scaling
	Vector2 operator/(const Vector2& v) const
	{
		return Vector2(x / v.x, y / v.y);
	}

	Vector2 operator-() const
	{
		return (Vector2(-x, -y));
	}

	Vector2 operator+() const
	{
		return *this;
	}

	float length2() const
	{
		return x * x + y * y;
	}

	float length() const
	{
		return (float)sqrt(length2());
	}

	Vector2 normalize() const
	{
		return *this * (1 / length());
	}

	Vector2 cw() const
	{
		return Vector2(-y, +x);
	}

	Vector2 ccw() const
	{
		return Vector2(+y, -x);
	}

	Vector2 rotate(float angle) const
	{
		float s = sin(angle), c = cos(angle);
		return Vector2(x * c - y * s, y * c + x * s);
	}

	static float dot(const Vector2& a, const Vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}

};
/// <summary>
/// The coordinate space in which to operate. Use Space.world to transform a GameObject using Unity’s world coordinates, ignoring the GameObject’s rotation state.Use Space.self to transform a GameObject using its own coordinatesand consider its rotations.
/// </summary>
enum Space
{
	/// <summary>
	/// Applies transformation relative to the world coordinate system. Use this to apply transformations to a GameObject using the world’s coordinates.This means that the GameObject’s Transform is altered via the world’s space instead of the GameObject’s local space.To transform a GameObject considering the GameObject’s rotation, use Space.Self.
	/// </summary>
	EWorld,
	/// <summary>
	/// Applies transformation relative to the local coordinate system. Use this to transform a GameObject considering the GameObject’s rotation.To apply transformations to a GameObject using the world’s coordinates, use Space.world.
	/// </summary>
	ESelf
};

class Transform : Component
{


public:
	Transform(class Actor* _owner, int _updateOrder);
	Vector2 m_Position;
	Vector2 m_Scale;
	Vector2 m_Rotation;

public:
	//Vector2 m_LocalPosition;
	//Vector2 m_LocalRotation;
	//Vector2 m_LocalScale;
	Vector2 m_LocalToWorldMatrix;
	Vector2 m_WorldToLocalMatrix;
	Vector2 m_Right;
	Vector2 m_Up;

	/// <summary>
	/// Rotates the transform so the forward vector points at /target/'s current position
	/// </summary>
	/// <param name="_target"></param>
	void LookAt(Transform _target);


	/// <summary>
	/// Then it rotates the transform to point its up direction vector in the direction hinted at by the worldUp vector. If you leave out the worldUp parameter, the function will use the world y axis. The up vector of the rotation will only match the worldUp vector if the forward direction is perpendicular to worldUp.
	/// </summary>
	/// <param name="_target"></param>
	/// <param name="_worldUp"></param>
	void LookAt(Transform _target, Vector2 _worldUp = Vector2(1,0));


	/// <summary>
	/// The implementation of this method applies a rotation of xAngle degrees around the x axis, and yAngle degrees around the y axis (in that order).
	/// </summary>
	/// <param name="_xAngle"></param>
	/// <param name="_yAngle"></param>
	/// <param name="_relativeTo"></param>
	void Rotate(float _xAngle, float _yAngle, Space _relativeTo = Space::ESelf);
	
	
	/// <summary>
	/// Rotates the object around the given axis by the number of degrees defined by the given angle.
	/// </summary>
	/// <param name="_axis"></param>
	/// <param name="_angle"></param>
	/// <param name="_relativeTo"></param>
	void Rotate(Vector2& _axis, float _angle, Space _relativeTo = Space::ESelf);


	/// <summary>
	/// Rotates the object around the given axis by the number of degrees defined by the given angle.
	/// </summary>
	/// <param name="_axis"></param>
	/// <param name="_angle"></param>
	/// <param name="_relativeTo"></param>
	void Rotate(float _angle, Space _relativeTo = Space::ESelf, bool clockwise = true);

	/// <summary>
	/// Rotates the transform about axis passing through point in world coordinates by angle degrees.
	/// </summary>
	/// <param name="_point"></param>
	/// <param name="_axis"></param>
	/// <param name="_angle"></param>
	void RotateAround(Vector2 _point, Vector2 _axis, float _angle);

	/// <summary>
	/// Rotates the transform about axis passing through point in world coordinates by angle degrees.
	/// </summary>
	/// <param name="_point"></param>
	/// <param name="_axis"></param>
	/// <param name="_angle"></param>
	void RotateAround(Vector2 _point, float _angle);


	/// <summary>
	/// Sets the position and rotation of the Transform component in local space (i.e. relative to its parent transform). if we allow for child and parent GameObject
	/// </summary>
	/// <param name="_localPosition"></param>
	/// <param name="_localRotation"></param>
	//void SetLocalPositionAndRotation(Vector2 _localPosition, Vector2 _localRotation);


	/// <summary>
	/// Sets the world space position and rotation of the Transform component.
	/// </summary>
	/// <param name="_localPosition"></param>
	/// <param name="_localRotation"></param>
	void SetPositionAndRotation(Vector2 _localPosition, Vector2 _localRotation);


	/// <summary>
	/// Transforms direction from local space to world space. This operation is not affected by scale or position of the transform.The returned vector has the same length as direction.
	/// </summary>
	/// <param name="_direction"></param>
	/// <returns></returns>
	Vector2 TransformDirection(Vector2 _direction);


	Vector2 TransformDirection(float _xAngle, float _yAngle);

	/// <summary>
	/// Transforms position from local space to world space.
	/// </summary>
	/// <param name="_direction"></param>
	/// <returns></returns>
	Vector2 TransformPosition(Vector2 _point);


	Vector2 TransformPosition(float _xAngle, float _yAngle);


	/// <summary>
	/// Transforms vector from local space to world space.
	/// </summary>
	/// <param name="_direction"></param>
	/// <returns></returns>
	Vector2 TransformVector(Vector2 _vector);


	Vector2 TransformVector(float _xAngle, float _yAngle);

	/// <summary>
	/// Moves the transform in the direction and distance of translation.
	/// </summary>
	/// <param name="_translation"></param>
	/// <param name="_relativeTo"></param>
	void Translate(Vector2 _translation, Space _relativeTo = Space::ESelf);
	
	void Translate(float _x, float _y, Space _relativeTo = Space::ESelf);
	
	/// <summary>
	/// Moves the transform in the direction and distance of translation.
	/// </summary>
	/// <param name="_translation"></param>
	/// <param name="_relativeTo"></param>
	void Translate(Vector2 _translation, Transform _relativeTo );


	bool operator!=(const Transform& v) const
	{
		return (*this != v);
	}

	bool operator==(const Transform& v) const
	{
		return !(*this != v);
	}

};

