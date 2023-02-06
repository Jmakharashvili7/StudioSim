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

	// x = left, y = right, z = bottom, w = top
	inline glm::vec4 GetDimensions() { return m_dimensions; }

	inline void SetRotation(const float& rotation) { m_rotation = rotation; RecalculateViewMatix(); }
	inline float GetRotation() { return m_rotation; }

	inline void SetZoom(float zoom) { m_Zoom = zoom; }
	inline float GetZoom() { return m_Zoom; }
	inline float GetZoomSpeed() { return m_ZoomSpeed; }

	inline void SetCanZoom(bool canZoom) { m_CanZoom = canZoom; }
	inline bool GetCanZoom() { return m_CanZoom; }

	const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
	const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
	const glm::mat4& GetViewProjectionMatrix() const { return m_viewProjectionMatrix; }
	const Matrix4 GetViewProjMatrix() const { return m_viewProj; }

	void RecalculateProjection(float l, float r, float b, float t);
private:
	void RecalculateViewMatix();
private:
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_viewProjectionMatrix;
	glm::vec4 m_dimensions;
	Matrix4 m_viewProj;

	glm::vec3 m_position;
	float m_rotation = 0.0f;

	float m_Zoom;
	float m_ZoomSpeed;

	bool m_CanZoom : 1;
};

