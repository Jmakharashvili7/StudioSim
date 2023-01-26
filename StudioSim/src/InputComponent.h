#pragma once
#include "Component.h"

class InputComponent : public Component
{
public:
	InputComponent(Actor* owningActor, const int updateOrder);

	virtual void Update(const float deltaTime) override;

	// Keys
	const bool GetKeyDown(const char key) const;
	const bool GetKeyUp(const char key) const;
	const bool GetKeyPressed(const char key) const;
	const bool AnyKeyDown() const;
	const bool AnyKeyPressed() const;

	// Mouse
	const bool GetMouseButtonDown(const int mouseClick);
	const bool GetMouseButtonUp(const int mouseClick);
	const bool GetMouseButtonPressed(const int mouseClick);

protected:
	virtual void ProcessInput();

private:
	GLFWwindow* m_window = nullptr;
	map <KeyType, int> buttonKeys;
	KeyEvent keyEvent = KeyEvent();
	MouseEvent mouseEvent = MouseEvent();
};