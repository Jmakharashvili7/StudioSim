#include "Transform.h"

Transform::Transform(class Actor* _owner, int _updateOrder) : Component(_owner, _updateOrder)
{
	m_Position = Vector2(0, 0);//vector2. zero
	m_Rotation = Vector2(0, 0);//vector2. zero
	m_Scale = Vector2(1, 1);//vector2.one
	m_Right = Vector2(1, 0);
	m_Up = Vector2(0, 1);

}

void Transform::LookAt(Transform _target)
{
	Vector2 dir = _target.m_Position - m_Position;
	float dirToAngle = atan2(dir.x, dir.y);
	Rotate(m_Right, dirToAngle);

}

void Transform::LookAt(Transform _target, Vector2 _worldUp)
{
}

void Transform::Rotate(float _xAngle, float _yAngle, Space _relativeTo)
{
	
}

void Transform::Rotate(Vector2& _axis, float _angle, Space _relativeTo)
{
	Vector2 newAngle(0, 0);
	newAngle.x = _axis.x * cos(_angle) + _axis.y * sin(_angle);
	newAngle.y = _axis.x * -sin(_angle) + _axis.y * cos(_angle);
	_axis.x = newAngle.x;
	_axis.y = newAngle.y;
}

void Transform::Rotate(float _angle, Space _relativeTo, bool clockwise)
{
	if (clockwise)
	{
		Vector2 newAngle(0, 0);
		newAngle.x = m_Rotation.x * cos(_angle) + m_Rotation.y * sin(_angle);
		newAngle.y = m_Rotation.x * -sin(_angle) + m_Rotation.y * cos(_angle);
		m_Rotation.x = newAngle.x;
		m_Rotation.y = newAngle.y;
	}
	else {
		Vector2 newAngle(0, 0);
		newAngle.x = m_Rotation.x * cos(_angle) - m_Rotation.y * sin(_angle);
		newAngle.y = m_Rotation.x * sin(_angle) + m_Rotation.y * cos(_angle);
		m_Rotation.x = newAngle.x;
		m_Rotation.y = newAngle.y;
	}
}

void Transform::RotateAround(Vector2 _point, Vector2 _axis, float _angle)
{

}

void Transform::RotateAround(Vector2 _point, float _angle)
{
	//If you rotate point(px, py) around point(ox, oy) by angle theta you'll get:

	//	p'x = cos(theta) * (px-ox) - sin(theta) * (py-oy) + ox

	//	p'y = sin(theta) * (px-ox) + cos(theta) * (py-oy) + oy

	//	this is an easy way to rotate a point in 2D.
}

void Transform::SetPositionAndRotation(Vector2 _localPosition, Vector2 _localRotation)
{
}

Vector2 Transform::TransformDirection(Vector2 _direction)
{
	return Vector2();
}

Vector2 Transform::TransformDirection(float _xAngle, float _yAngle)
{
	return Vector2();
}

Vector2 Transform::TransformPosition(Vector2 _point)
{
	return Vector2();
}

Vector2 Transform::TransformPosition(float _xAngle, float _yAngle)
{
	return Vector2();
}

Vector2 Transform::TransformVector(Vector2 _vector)
{
	return Vector2();
}

Vector2 Transform::TransformVector(float _xAngle, float _yAngle)
{
	return Vector2();
}

void Transform::Translate(Vector2 _translation, Space _relativeTo)
{
}

void Transform::Translate(float _x, float _y, Space _relativeTo)
{
}

void Transform::Translate(Vector2 _translation, Transform _relativeTo)
{
}
