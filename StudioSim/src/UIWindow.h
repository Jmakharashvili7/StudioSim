#pragma once
#include "BasicIncludes.h"

class UIWindow
{
public:
	UIWindow(std::string name);
	~UIWindow();

	void Init();
	void Render();

	inline void SetPosition(glm::vec2 pos) { m_position = pos; }
	inline glm::vec2 GetPosition() { return m_position; }

	inline void SetSize(glm::vec2 size) { m_size = size; }
	inline glm::vec2 GetSize() { return m_size; }

	inline void SetIsFocused(bool isFocused) { m_isFocused = isFocused; }
	inline bool GetIsFocused() { return m_isFocused; }
private:
	std::string m_name;
	glm::vec2 m_position;
	glm::vec2 m_size;
	bool m_isFocused;
};

