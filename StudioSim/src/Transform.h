#pragma once
#include "BasicIncludes.h"

class Transform
{
public:
	Transform(const glm::vec3 inPosition, const glm::vec3 inRotation, const glm::vec3 inScale);
	Transform();
	~Transform();

	void UpdateTransformMatrixPosition();
	void UpdateTransformMatrixRotation();
	void UpdateTransformMatrixScale();

	// Setters
	void SetPosition(const glm::vec3 newPosition);
	void AdjustPosition(const glm::vec3 adjustPosition);

	void SetRotation(const glm::vec3 newRotation);
	void AdjustRotation(const glm::vec3 adjustRotation);

	void SetScale(const glm::vec3 newScale);
	void AdjustScale(const glm::vec3 adjustScale);

	// Getters
	inline const glm::mat4 GetTransformationMatrix() const { return m_transformationMatrix; }
	inline const glm::vec3 GetPosition() const { return m_worldPosition; }
	inline const glm::vec3 GetRotation() const { return m_rotation; }
	inline const glm::vec3 GetScale() const { return m_scale; }

private:
	glm::mat4 m_transformationMatrix = glm::mat4(1.0f);
	glm::vec3 m_worldPosition = glm::vec3(0.0f);
	glm::vec3 m_screenPosition = glm::vec3(0.0f);
	glm::vec3 m_rotation = glm::vec3(0.0f);
	glm::vec3 m_scale = glm::vec3(1.0f);
};

