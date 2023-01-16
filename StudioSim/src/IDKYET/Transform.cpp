#include "Transform.h"

Transform::Transform(class Actor* _owner, int _updateOrder) : Component(_owner, _updateOrder)
{
	
	m_Position = Vector2::Zero;
	m_Orientation = Vector2::Zero;
	m_Scale = Vector2::One * 100;
	m_Right = GetForward();
	m_Up = GetUp();
	m_TransformMatrix = Matrix4::CreateScale(m_Scale);
	SetPositionAndRotation(m_Position, m_fRotation);
	//m_TransformMatrix = Matrix3::CreateScale(m_Scale);
	


	
	//transforms object space to world space
	//transform.x = m_Scale.x * (m_Position.x * cos(m_fRotation)) - m_Scale.y * (m_Position.y * sin(m_fRotation)) + translation.x;
	//transform.y = m_Scale.x * (m_Position.x * sin(m_fRotation)) + m_Scale.y * (m_Position.y * cos(m_fRotation)) + translation.y;

}

Vector2 Transform::GetForward() const
{
	return Vector2(cos(m_fRotation),sin(m_fRotation));
}

Vector2 Transform::GetUp() const
{
	return Vector2(cos(m_fRotation+90), sin(m_fRotation+90));
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
	if (_relativeTo == Space::ESelf)
	{
		m_fRotation += _angle;
		//m_TransformMatrix *= Matrix3::CreateRotation(m_fRotation);
		m_TransformMatrix *= Matrix4::CreateRotationZ(m_fRotation);
	}
	else
	{
		RotateAround(Vector2::Zero, _angle);
	}


}

void Transform::SetRotation(float _angle, Space _relativeTo, bool clockwise)
{
	m_fRotation = _angle;
	m_TransformMatrix *= Matrix4::CreateRotationZ(m_fRotation);
}


void Transform::RotateAround(Vector2 _point, float _angle)
{
	m_fRotation += _angle;
	//m_TransformMatrix *= Matrix3::CreateRotationAboutPoint(_point.x, _point.y, m_fRotation);
	m_TransformMatrix *= Matrix4::CreateRotationZAboutPoint(_point.x, _point.y, m_fRotation);
}

void Transform::SetRotateAround(Vector2 _point, float _angle)
{
	m_fRotation = _angle;
	m_TransformMatrix *= Matrix4::CreateRotationZAboutPoint(_point.x, _point.y, m_fRotation);
}

void Transform::SetPositionAndRotation(Vector2 _Position, float _Rotation)
{
	SetRotation(_Rotation);
	Translate(_Position);
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
	m_TransformMatrix *= Matrix4::CreateTranslation(m_Position);
}

void Transform::Translate(float _x, float _y, Space _relativeTo)
{
	//change this but use local position
	m_Position.x += _x;
	m_Position.y += _y;

	m_TransformMatrix *= Matrix4::CreateTranslation(m_Position);
}

void Transform::Translate(Vector2 _translation, Transform _relativeTo)
{
	//change this but use local position
	m_Position += _relativeTo.m_Position;
	m_Position += _translation;
	m_TransformMatrix *= Matrix4::CreateTranslation(Vector2(m_Position.x, m_Position.y));
}

void Transform::SetPosition(Vector2 _translation)
{
	m_Position = _translation;
	m_TransformMatrix *= Matrix4::CreateTranslation(Vector2(m_Position.x, m_Position.y));
}

void Transform::ComputeTransform()
{
	if (m_ReComputeWorldTransform)
	{
		m_ReComputeWorldTransform = false;
	}
	

}
