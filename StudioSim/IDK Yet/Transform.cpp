#include "Transform.h"

Transform::Transform(class Actor* _owner, int _updateOrder) : Component(_owner, _updateOrder)
{
	m_Position = Vector2::Zero;
	m_Orientation = Vector2::Zero;
	m_Scale = Vector2::One;
	m_Right = GetForward();
	m_Up = Vector2(0, 1);

	m_TransformMatrix = Matrix3::CreateScale(m_Scale);
	m_TransformMatrix *= Matrix3::CreateRotation(m_fRotation);
	m_TransformMatrix *= Matrix3::CreateTranslation(m_Position);

	
	//transforms object space to world space
	transform.x = m_Scale.x * (m_Position.x * cos(m_fRotation)) - m_Scale.y * (m_Position.y * sin(m_fRotation)) + translation.x;
	transform.y = m_Scale.x * (m_Position.x * sin(m_fRotation)) + m_Scale.y * (m_Position.y * cos(m_fRotation)) + translation.y;

}

Vector2 Transform::GetForward() const
{
	return Vector2(cos(m_fRotation),sin(m_fRotation));
}

void Transform::LookAt(Transform _target)
{
	Vector2 dirToRotate = ( _target.m_Position - m_Position);
	dirToRotate.Normalize();
	float angle = atan2(dirToRotate.y, dirToRotate.x);
	Rotate(angle);
}



void Transform::Rotate(float _angle, Space _relativeTo, bool clockwise)
{
	//change this but use local rotation
	m_fRotation = _angle;
	m_TransformMatrix *= Matrix3::CreateRotation(m_fRotation);
}


void Transform::RotateAround(Vector2 _point, float _angle)
{
	//If you rotate point(px, py) around point(ox, oy) by angle theta you'll get:

	//	p'x = cos(theta) * (px-ox) - sin(theta) * (py-oy) + ox

	//	p'y = sin(theta) * (px-ox) + cos(theta) * (py-oy) + oy

	//	this is an easy way to rotate a point in 2D.




	//POINT rotate_point(float cx, float cy, float angle, POINT p)
	//{
	//	float s = sin(angle);
	//	float c = cos(angle);

	//	// translate point back to origin:
	//	p.x -= cx;
	//	p.y -= cy;

	//	// rotate point
	//	float xnew = p.x * c - p.y * s;
	//	float ynew = p.x * s + p.y * c;

	//	// translate point back:
	//	p.x = xnew + cx;
	//	p.y = ynew + cy;
	//	return p;
	//}


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
	//change this but use local position
	m_Position += _translation;
	m_TransformMatrix = Matrix3::CreateTranslation(m_Position);
}

void Transform::Translate(float _x, float _y, Space _relativeTo)
{
	//change this but use local position
	m_Position.x += _x;
	m_Position.y += _y;

	m_TransformMatrix = Matrix3::CreateTranslation(m_Position);
}

void Transform::Translate(Vector2 _translation, Transform _relativeTo)
{
	//change this but use local position
	m_Position += _relativeTo.m_Position;
	m_Position += _translation;
	m_TransformMatrix = Matrix3::CreateTranslation(m_Position);
}
