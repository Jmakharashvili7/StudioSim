#include "Transform.h"

Transform::Transform(class Actor* _owner, int _updateOrder) : Component(_owner, _updateOrder)
{
	m_ReComputeWorldTransform = true;
	m_Position = vec2(500,500);
	m_Scale = vec2(100,100);
	m_Right = GetForward();
	m_Up = GetUp();
	m_TransformMatrix = mat4(1.0f);
	//m_TransformMatrix = scale(vec3(m_Scale, 0));
	SetPositionAndRotation(m_Position, m_fRotation);




	//transforms object space to world space
	//transform.x = m_Scale.x * (m_Position.x * cos(m_fRotation)) - m_Scale.y * (m_Position.y * sin(m_fRotation)) + translation.x;
	//transform.y = m_Scale.x * (m_Position.x * sin(m_fRotation)) + m_Scale.y * (m_Position.y * cos(m_fRotation)) + translation.y;

}

Transform::Transform()
{
	
	m_Position = vec2(500/1280, 500/960);
	m_Scale = vec2(1, 1);
	m_Right = GetForward();
	m_Up = GetUp();
	m_TransformMatrix = mat4(1.0f);
	m_TransformMatrix = translate(m_TransformMatrix, vec3(m_Position, 0));
	//ComputeTransform();
}

glm::vec2 Transform::GetForward() const
{
	return glm::vec2(cos(m_fRotation), sin(m_fRotation));
}

glm::vec2 Transform::GetUp() const
{
	return glm::vec2(cos(m_fRotation + 90), sin(m_fRotation + 90));
}

void Transform::LookAt(Transform _target)
{
	glm::vec2 dirToRotate = (_target.m_Position - m_Position);
	//dirToRotate.Normalize();
	normalize(dirToRotate);
	float angle = atan2(dirToRotate.y, dirToRotate.x);
	Rotate(angle);
}



void Transform::Rotate(float _angle, Space _relativeTo, bool clockwise)
{
	//change this but use local rotation
	if (_relativeTo == Space::ESelf)
	{
		m_fRotation += _angle;
		
	}
	else
	{
		
	}

	m_ReComputeWorldTransform = true;
}

void Transform::SetRotation(float _angle, Space _relativeTo, bool clockwise)
{
	m_fRotation = _angle;
	m_ReComputeWorldTransform = true;
}


void Transform::RotateAround(glm::vec2 _point, float _angle)
{
	m_fRotation += _angle;
	m_ReComputeWorldTransform = true;
}

void Transform::SetRotateAround(glm::vec2 _point, float _angle)
{
	m_fRotation = _angle;
	m_ReComputeWorldTransform = true;

}

void Transform::SetPositionAndRotation(glm::vec2 _Position, float _Rotation)
{
	SetRotation(_Rotation);
	Translate(_Position);
}

glm::vec2 Transform::TransformDirection(glm::vec2 _direction)
{
	return glm::vec2();
}

glm::vec2 Transform::TransformDirection(float _xAngle, float _yAngle)
{
	return glm::vec2();
}

glm::vec2 Transform::TransformPosition(glm::vec2 _point)
{
	return glm::vec2();
}

glm::vec2 Transform::TransformPosition(float _xAngle, float _yAngle)
{
	return glm::vec2();
}

glm::vec2 Transform::TransformVector(glm::vec2 _vector)
{
	return glm::vec2();
}

glm::vec2 Transform::TransformVector(float _xAngle, float _yAngle)
{
	return glm::vec2();
}

void Transform::Translate(glm::vec2 _translation, Space _relativeTo)
{
	//change this but use local position
	m_Position += _translation;
	m_ReComputeWorldTransform = true;
	
}

void Transform::Translate(float _x, float _y, Space _relativeTo)
{
	//change this but use local position
	m_Position.x += _x;
	m_Position.y += _y;
	m_ReComputeWorldTransform = true;
	
}

void Transform::Translate(glm::vec2 _translation, Transform _relativeTo)
{
	//change this but use local position
	m_Position += _relativeTo.m_Position;
	m_Position += _translation;
	m_ReComputeWorldTransform = true;
}

void Transform::SetPosition(glm::vec2 _translation)
{
	m_Position = _translation;
	m_ReComputeWorldTransform = true;
	m_TransformMatrix = translate(m_TransformMatrix, vec3(m_Position, 0));
}

void Transform::ComputeTransform()
{
	if (m_ReComputeWorldTransform)
	{
		//m_ReComputeWorldTransform = false;
	
	}
	//m_TransformMatrix = scale(m_TransformMatrix, vec3(m_Scale,1));
		//m_TransformMatrix = rotate(m_TransformMatrix,radians(m_fRotation), vec3(m_Orientation,1));
		

}

