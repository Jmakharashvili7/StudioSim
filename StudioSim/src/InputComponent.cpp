#include "pch.h"

#include "InputComponent.h"

InputComponent::InputComponent(Actor* owningActor, const int updateOrder) : Component{ owningActor, updateOrder }
{

}

void InputComponent::Update(const float deltaTime)
{
	Component::Update(deltaTime);
	ProcessInput();
	KeyboardClass::ClearKeyBuffer();
}

const bool InputComponent::GetKeyDown(const char key) const
{
	bool bkeyHeld = false;
	const char upperCaseKey = toupper(key);

	if (KeyboardClass::IsKeyPressed(upperCaseKey))
	{
		KeyboardClass::OnKeyPressed(upperCaseKey);
		if (keyEvent.GetKeyCode() == upperCaseKey)
		{
			bkeyHeld = true;
		}
	}
	

	return bkeyHeld;
}

const bool InputComponent::GetKeyUp(const char key) const
{
	bool bkeyUp = false;
	const char upperCaseKey = toupper(key);

	if (keyEvent.IsReleased())
	{
		if (keyEvent.GetKeyCode() == upperCaseKey)
		{
			bkeyUp = true;
		}
	}

	return bkeyUp;
}

const bool InputComponent::GetKeyPressed(const char key) const
{
	bool bkeyPressed = false;
	const char upperCaseKey = toupper(key);

	if (keyEvent.IsPressed())
	{
		if (keyEvent.GetKeyCode() == upperCaseKey)
		{
			bkeyPressed = true;
		}
	}

	return bkeyPressed;
}

const bool InputComponent::AnyKeyDown() const
{
	bool banyKeyHeld = false;

	if (!KeyboardClass::KeyBufferIsEmpty())
	{
		if (keyEvent.GetKeyCode() != NULL)
		{
			banyKeyHeld = true;
		}
	}

	return banyKeyHeld;
}

const bool InputComponent::AnyKeyPressed() const
{
	bool banyKeyPressed = false;

	if (keyEvent.IsPressed())
	{
		if (keyEvent.GetKeyCode() != NULL)
		{
			banyKeyPressed = true;
		}
	}

	return banyKeyPressed;
}

const bool InputComponent::GetMouseButtonDown(const int mouseClick)
{
	bool bmouseButtonHeld = false;

	if (!MouseClass::IsEventBufferEmpty())
	{
		if (mouseEvent.GetType() == MouseEvent::EventType::L_HELD && mouseClick == 0)
		{
			bmouseButtonHeld = true;
		}
		else if (mouseEvent.GetType() == MouseEvent::EventType::R_HELD && mouseClick == 1)
		{
			bmouseButtonHeld = true;
		}
		else if (mouseEvent.GetType() == MouseEvent::EventType::SCROLL_HELD && mouseClick == 2)
		{
			bmouseButtonHeld = true;
		}
	}

	return bmouseButtonHeld;
}

const bool InputComponent::GetMouseButtonUp(const int mouseClick)
{
	bool bmouseButtonUp = false;

	if (!MouseClass::IsEventBufferEmpty())
	{
		if (mouseEvent.GetType() == MouseEvent::EventType::L_RELEASE && mouseClick == 0)
		{
			bmouseButtonUp = true;
		}
		else if (mouseEvent.GetType() == MouseEvent::EventType::R_RELEASE && mouseClick == 1)
		{
			bmouseButtonUp = true;
		}
		else if (mouseEvent.GetType() == MouseEvent::EventType::SCROLL_RELEASE && mouseClick == 2)
		{
			bmouseButtonUp = true;
		}
	}

	return bmouseButtonUp;
}

const bool InputComponent::GetMouseButtonPressed(const int mouseClick)
{
	bool bmouseButtonPressed = false;

	if (!MouseClass::IsEventBufferEmpty())
	{
		if (mouseEvent.GetType() == MouseEvent::EventType::L_CLICK && mouseClick == 0)
		{
			bmouseButtonPressed = true;
		}
		else if (mouseEvent.GetType() == MouseEvent::EventType::R_CLICK && mouseClick == 1)
		{
			bmouseButtonPressed = true;
		}
		else if (mouseEvent.GetType() == MouseEvent::EventType::SCROLL_CLICK && mouseClick == 2)
		{
			bmouseButtonPressed = true;
		}
	}

	return bmouseButtonPressed;
}

void InputComponent::ProcessInput()
{
	keyEvent = KeyboardClass::ReadKey();
	mouseEvent = MouseClass::ReadEvent();
}
