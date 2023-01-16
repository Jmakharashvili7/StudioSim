#pragma once
#include "Component.h"
#include <cmath>
#include <complex>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Math.h"

using namespace std;
using namespace glm;


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
	//Apply transformations in this order
	Vector2 m_Scale;//scale first
	Vector2 m_Orientation;//remove or dont use
	float m_fRotation;//rotation second
	Vector2 m_Position;// translation 3rd

	Vector2 transform;

public:
	//Vector2 m_LocalPosition;
	//Vector2 m_LocalRotation;
	//Vector2 m_LocalScale;
	//Vector2 m_LocalToWorldMatrix;
	//Vector2 m_WorldToLocalMatrix;
	Vector2 m_Right;
	Vector2 m_Up;

	Vector2 GetForward() const;
	Vector2 GetUp() const;

	/// <summary>
	/// Rotates the transform so the forward vector points at /target/'s current position
	/// </summary>
	/// <param name="_target"></param>
	void LookAt(Transform _target);



	/// <summary>
	/// Rotates the object by the number of degrees defined by the given angle adds or takes away degree.
	/// </summary>
	/// <param name="_axis"></param>
	/// <param name="_angle"></param>
	/// <param name="_relativeTo"></param>
	void Rotate(float _angle, Space _relativeTo = Space::ESelf, bool clockwise = true);

	/// <summary>
	/// Sets the roatation to a given angle
	/// </summary>
	/// <param name="_axis"></param>
	/// <param name="_angle"></param>
	/// <param name="_relativeTo"></param>
	void SetRotation(float _angle, Space _relativeTo = Space::ESelf, bool clockwise = true);


	/// <summary>
	/// Rotates the transform about axis passing through point in world coordinates by angle degrees.
	/// </summary>
	/// <param name="_point"></param>
	/// <param name="_axis"></param>
	/// <param name="_angle"></param>
	void RotateAround(Vector2 _point, float _angle);


	/// <summary>
	/// Rotates the transform about axis passing through point in world coordinates by angle degrees.
	/// </summary>
	/// <param name="_point"></param>
	/// <param name="_axis"></param>
	/// <param name="_angle"></param>
	void SetRotateAround(Vector2 _point, float _angle);


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
	void SetPositionAndRotation(Vector2 _Position, float _Rotation);


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


	private:
		Matrix4 m_TransformMatrix;
		bool m_ReComputeWorldTransform;
		void ComputeTransform();

};

