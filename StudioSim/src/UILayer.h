#pragma once
#include "Layer.h"

class UILayer : public Layer
{
public:
	UILayer();
	~UILayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate() override;
	void OnEvent() override;

	inline glm::vec4& GetColor() { return m_color; }
private:
	float m_time;
	glm::vec4 m_color;
};

