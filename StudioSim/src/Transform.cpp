#include "Transform.h"

Transform::Transform(const glm::vec3 inPosition, const glm::vec3 inRotation, const glm::vec3 inScale)
	: m_worldPosition(inPosition), m_rotation(inRotation), m_scale(inScale)
{
	m_screenPosition = glm::vec3(inPosition.x / 1280.0f, inPosition.y / 960.0f, 0.0f);
	UpdateTransformMatrixPosition();
	//UpdateTransformMatrixRotation();
	UpdateTransformMatrixScale();
}

Transform::Transform()
{

}

Transform::~Transform()
{

}

void Transform::UpdateTransformMatrixPosition()
{
	m_transformationMatrix = glm::translate(m_transformationMatrix, glm::vec3(m_screenPosition));
}

void Transform::UpdateTransformMatrixScale()
{
	m_transformationMatrix = glm::scale(m_transformationMatrix, glm::vec3(m_scale));
}

void Transform::SetPosition(const glm::vec3 newPosition)
{
	m_worldPosition = newPosition;
	m_screenPosition = glm::vec3(newPosition.x / 1280.0f, newPosition.y / 960.0f, 0.0f);
	UpdateTransformMatrixPosition();
}

void Transform::AdjustPosition(const glm::vec3 adjustPosition)
{
	m_worldPosition += adjustPosition;
	UpdateTransformMatrixPosition();
}

void Transform::SetScale(const glm::vec3 newScale)
{
	m_scale = newScale;
	UpdateTransformMatrixScale();
}

void Transform::AdjustScale(const glm::vec3 adjustScale)
{
	m_scale += adjustScale;
	UpdateTransformMatrixScale();
}
