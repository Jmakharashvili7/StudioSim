#pragma once
#include "BasicIncludes.h"
#include "glm\ext\vector_common.hpp"

class OrthographicCamera
{
public:
	OrthographicCamera(float l, float r, float b, float t);
	OrthographicCamera(float width, float height);

	inline void SetPosition(const glm::vec3& position) { m_position = position; RecalculateViewMatix(); }
	inline glm::vec3 GetPosition() { return m_position; }

	inline void SetRotation(const float& rotation) { m_rotation = rotation; RecalculateViewMatix(); }
	inline float GetRotation() { return m_rotation; }

	const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
	const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
	const glm::mat4& GetViewProjectionMatrix() const { return m_viewProjectionMatrix; }
	const Matrix4 GetViewProjMatrix() const { return m_viewProj; }
	void SetViewMatrix(float aspect);
private:
	void RecalculateViewMatix();
private:
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_viewProjectionMatrix;
	Matrix4 m_viewProj;

	glm::vec3 m_position;
	float m_rotation = 0.0f;
};

