#include "InputComponent.h"
#include "GameObject.h"
#include "QuackCallbacks.h"
#include "KeyboardClass.h"
#include "MouseClass.h"


InputComponent::InputComponent(Actor* Owner, int updateOrder, GLFWwindow* window) : Component(Owner, updateOrder)
{
	m_Window = window;
	glfwSetKeyCallback(m_Window, QuackEngine::key_callback);
}

void InputComponent::Update(float deltaTime)
{
	//KeyEvent key = KeyboardClass::ReadKey();

	//if (key.IsHeld())
	//{
	//	switch (key.GetKeyCode())
	//	{
	//	case 'W':
	//		cout << "I pressed" << endl;
	//		break;
	//	}
	//}

	//

	//if (!MouseClass::IsEventBufferEmpty())
	//{
	//	MouseEvent e = MouseClass::ReadEvent();

	//	if (e.GetType() == MouseEvent::EventType::L_CLICK)
	//	{
	//	}
	//	if (e.GetType() == MouseEvent::EventType::R_CLICK)
	//	{

	//	}
	//	if (e.GetType() == MouseEvent::EventType::MOVE)
	//	{

	//	}
	//}
}

InputComponent::~InputComponent()
{
}

bool InputComponent::GetButtonDown(ButtonNames buttonNames)
{
	return false;
}

bool InputComponent::GetButton(ButtonNames buttonNames)
{
	return false;
}

int InputComponent::GetAxisRaw(ButtonNames buttonNames)
{
	return 0;
}

bool InputComponent::GetKey(char keyButton)
{
	keyButton = toupper(keyButton);
	
	KeyEvent key = KeyboardClass::ReadKey();
	if (key.IsHeld())
	{
		if (key.GetKeyCode() == keyButton)
		{
			return true;
		}

	}
	else
	{
		return false;
	}
}

bool InputComponent::GetKeyDown(char keyButtony)
{
	return false;
}

bool InputComponent::GetKeyUp(char keyButton)
{
	return false;
}

bool InputComponent::GetMouseButton(int mouseClick)
{
	return false;
}

bool InputComponent::GetMouseButtonDown(int mouseClick)
{
	return false;
}

bool InputComponent::GetMouseButtonUp(int mouseClick)
{
	return false;
}

bool InputComponent::AnyKey()
{
	return false;
}

bool InputComponent::AnyKeyDown()
{
	return false;
}

