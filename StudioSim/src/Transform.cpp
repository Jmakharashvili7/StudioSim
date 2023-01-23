#include "Transform.h"

Transform::Transform(const glm::vec3 inPosition, const glm::vec3 inRotation, const glm::vec3 inScale)
	: m_position(inPosition), m_rotation(inRotation), m_scale(inScale)
{
	UpdateTransformMatrix();
}

Transform::Transform()
{

}

Transform::~Transform()
{

}

void Transform::UpdateTransformMatrix()
{
	glm::mat4 startingMatrix = glm::mat4(1.0f);

	glm::vec3 screenPosition = glm::vec3(m_position.x, m_position.y, 0.0f);

	startingMatrix = glm::translate(startingMatrix, glm::vec3(screenPosition));

	// x
	startingMatrix = glm::rotate(startingMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	// y
	startingMatrix = glm::rotate(startingMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	// z
	startingMatrix = glm::rotate(startingMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	startingMatrix = glm::scale(startingMatrix, glm::vec3(m_scale));



	m_transformationMatrix = startingMatrix;
}

void Transform::SetPosition(const glm::vec3 newPosition)
{
	m_position = newPosition;
	UpdateTransformMatrix();
}

void Transform::AdjustPosition(const glm::vec3 adjustPosition)
{
	m_position += adjustPosition;
	UpdateTransformMatrix();
}

void Transform::SetRotation(const glm::vec3 newRotation)
{
	m_rotation = newRotation;
	UpdateTransformMatrix();
}

void Transform::AdjustRotation(const glm::vec3 adjustRotation)
{
	m_rotation.x += adjustRotation.x;
	m_rotation.y += adjustRotation.y;
	m_rotation.z += adjustRotation.z;
	UpdateTransformMatrix();
}

void Transform::SetRotationAroundPivot(const glm::vec3 pivotPosition, const glm::vec3 newRotation)
{

}

void Transform::SetScale(const glm::vec3 newScale)
{
	m_scale = newScale;
	UpdateTransformMatrix();
}

void Transform::AdjustScale(const glm::vec3 adjustScale)
{
	m_scale += adjustScale;
	UpdateTransformMatrix();
}
