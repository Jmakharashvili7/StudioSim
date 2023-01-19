#pragma once
#include "Component.h"
#include "BasicIncludes.h"

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
	Transform();
	//Apply transformations in this order
	glm::vec2 m_Scale;//scale first
	glm::vec2 m_Orientation;//remove or dont use
	float m_fRotation;//rotation second
	glm::vec2 m_Position;// translation 3rd

	//glm::vec2 transform;

public:
	//glm::vec2 m_LocalPosition;
	//glm::vec2 m_LocalRotation;
	//glm::vec2 m_LocalScale;
	//glm::vec2 m_LocalToWorldMatrix;
	//glm::vec2 m_WorldToLocalMatrix;
	glm::vec2 m_Right;
	glm::vec2 m_Up;

	glm::vec2 GetForward() const;
	glm::vec2 GetUp() const;

	/// <summary>
	/// Rotates the transform so the forward vector points at /target/'s current position
	/// </summary>
	/// <param name="_target"></param>
	void LookAt(Transform _target);


	glm::mat4 GetWorldTransform() { return m_TransformMatrix; }


	/// <summary>
	/// Rotates the object by the number of degrees defined by the given angle adds or takes away degree.
	/// </summary>
	/// <param name="_axis"></param>
	/// <param name="_angle"></param>
	/// <param name="_relativeTo"></param>
	void Rotate(float _angle, Space _relativeTo = Space::ESelf, bool clockwise = true);

	/// <summary>
	/// Scales the object by a vector
	/// </summary>
	/// <param name="_axis"></param>
	/// <param name="_angle"></param>
	/// <param name="_relativeTo"></param>
	void Scale(vec2 _Scalar);

	/// <summary>
	/// Scales individual axis of the transform
	/// </summary>
	/// <param name="_axis"></param>
	/// <param name="_angle"></param>
	/// <param name="_relativeTo"></param>
	void Scale(float _xAxis, float _yAxis);

	/// <summary>
	/// Rotates the object by the number of degrees defined by the given angle adds or takes away degree.
	/// </summary>
	/// <param name="_axis"></param>
	/// <param name="_angle"></param>
	/// <param name="_relativeTo"></param>
	void UniformScale(float _Scale);

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
	void RotateAround(glm::vec2 _point, float _angle);


	/// <summary>
	/// Rotates the transform about axis passing through point in world coordinates by angle degrees.
	/// </summary>
	/// <param name="_point"></param>
	/// <param name="_axis"></param>
	/// <param name="_angle"></param>
	void SetRotateAround(glm::vec2 _point, float _angle);


	/// <summary>
	/// Sets the position and rotation of the Transform component in local space (i.e. relative to its parent transform). if we allow for child and parent GameObject
	/// </summary>
	/// <param name="_localPosition"></param>
	/// <param name="_localRotation"></param>
	//void SetLocalPositionAndRotation(glm::vec2 _localPosition, glm::vec2 _localRotation);


	/// <summary>
	/// Sets the world space position and rotation of the Transform component.
	/// </summary>
	/// <param name="_localPosition"></param>
	/// <param name="_localRotation"></param>
	void SetPositionAndRotation(glm::vec2 _Position, float _Rotation);


	/// <summary>
	/// Transforms direction from local space to world space. This operation is not affected by scale or position of the transform.The returned vector has the same length as direction.
	/// </summary>
	/// <param name="_direction"></param>
	/// <returns></returns>
	glm::vec2 TransformDirection(glm::vec2 _direction);


	glm::vec2 TransformDirection(float _xAngle, float _yAngle);

	/// <summary>
	/// Transforms position from local space to world space.
	/// </summary>
	/// <param name="_direction"></param>
	/// <returns></returns>
	glm::vec2 TransformPosition(glm::vec2 _point);


	glm::vec2 TransformPosition(float _xAngle, float _yAngle);


	/// <summary>
	/// Transforms vector from local space to world space.
	/// </summary>
	/// <param name="_direction"></param>
	/// <returns></returns>
	glm::vec2 TransformVector(glm::vec2 _vector);


	glm::vec2 TransformVector(float _xAngle, float _yAngle);

	/// <summary>
	/// Moves the transform in the direction and distance of translation.
	/// </summary>
	/// <param name="_translation"></param>
	/// <param name="_relativeTo"></param>
	void Translate(glm::vec2 _translation, Space _relativeTo = Space::ESelf);

	void Translate(float _x, float _y, Space _relativeTo = Space::ESelf);

	/// <summary>
	/// Moves the transform in the direction and distance of translation.
	/// </summary>
	/// <param name="_translation"></param>
	/// <param name="_relativeTo"></param>
	void Translate(glm::vec2 _translation, Transform _relativeTo);


	/// <summary>
	/// Moves the transform in the direction and distance of translation.
	/// </summary>
	/// <param name="_translation"></param>
	/// <param name="_relativeTo"></param>
	void SetPosition(glm::vec2 _translation);


	bool operator!=(const Transform& v) const
	{
		return (*this != v);
	}

	bool operator==(const Transform& v) const
	{
		return !(*this != v);
	}

	

private:
	void ComputeTransform();
	glm::mat4 m_TransformMatrix;
	bool m_ReComputeWorldTransform;
	

};

