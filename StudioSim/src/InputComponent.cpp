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
	Component::Update(deltaTime);
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
	ProcessInput();
	
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
	
	
	if (key.IsHeld())
	{
		if ((buttonNames == EVertical && key.GetKeyCode() == 'W') )//|| (buttonNames ==EVertical && key.GetKeyCode() == *glfwGetKeyName(GLFW_KEY_UP, 0)))
		{
			
			return 1;
			
		}
		else if((buttonNames == EVertical && key.GetKeyCode() == 'S'))// || (buttonNames == EVertical && key.GetKeyCode() == *glfwGetKeyName(GLFW_KEY_DOWN, 0)))
		{
			return -1;
		}
		else if ((buttonNames == EHorizontal&& key.GetKeyCode() == 'D') )//|| (buttonNames == EHorizontal && key.GetKeyCode() == *glfwGetKeyName(GLFW_KEY_RIGHT, 0)))
		{
			
			return 1;
			
		}
		else if((buttonNames == EHorizontal && key.GetKeyCode() == 'A'))//|| (buttonNames == EHorizontal && key.GetKeyCode() == *glfwGetKeyName(GLFW_KEY_LEFT , 0)))
		{
			
			return -1;
		}
		else
		{
			
			return 0;
		}
	}
	else
	{
		
		return 0;
	}
	
}

bool InputComponent::GetKey(char keyButton)
{
	keyButton = toupper(keyButton);
	
	
	if (key.IsHeld())
	{
		if (key.GetKeyCode() == keyButton)
		{
			return true;
		}
		else {
			return false;
		}

	}
	else
	{
		return false;
	}
}

bool InputComponent::GetKeyDown(char keyButton)
{
	keyButton = toupper(keyButton);

	if (key.IsPressed())
	{
		if (key.GetKeyCode() == keyButton)
		{
			return true;
		}
		else {
			return false;
		}

	}
	else
	{
		return false;
	}
}

bool InputComponent::GetKeyUp(char keyButton)
{
	keyButton = toupper(keyButton);

	if (key.IsReleased())
	{
		if (key.GetKeyCode() == keyButton)
		{
			return true;
		}
		else {
			return false;
		}

	}
	else
	{
		return false;
	}
}

bool InputComponent::GetMouseButton(int mouseClick)
{
	if (!MouseClass::IsEventBufferEmpty())
	{

		if (e.GetType() == MouseEvent::EventType::L_HELD && mouseClick == 0)
		{
			return true;
			
		}
		else if (e.GetType() == MouseEvent::EventType::R_HELD && mouseClick == 1)
		{
			return true;
		}
		else if (e.GetType() == MouseEvent::EventType::SCROLL_HELD && mouseClick == 2)
		{
			return true;
		}
		//if (e.GetType() == MouseEvent::EventType::MOVE)
		//{

		//}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool InputComponent::GetMouseButtonDown(int mouseClick)
{
	if (!MouseClass::IsEventBufferEmpty())
	{

		if (e.GetType() == MouseEvent::EventType::L_CLICK && mouseClick == 0)
		{
			return true;

		}
		else if (e.GetType() == MouseEvent::EventType::R_CLICK && mouseClick == 1)
		{
			return true;
		}
		else if (e.GetType() == MouseEvent::EventType::SCROLL_CLICK && mouseClick == 2)
		{
			return true;
		}
		//if (e.GetType() == MouseEvent::EventType::MOVE)
		//{

		//}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool InputComponent::GetMouseButtonUp(int mouseClick)
{
	if (!MouseClass::IsEventBufferEmpty())
	{

		if (e.GetType() == MouseEvent::EventType::L_RELEASE && mouseClick == 0)
		{
			return true;

		}
		else if (e.GetType() == MouseEvent::EventType::R_RELEASE && mouseClick == 1)
		{
			return true;
		}
		else if (e.GetType() == MouseEvent::EventType::SCROLL_RELEASE && mouseClick == 2)
		{
			return true;
		}
		//if (e.GetType() == MouseEvent::EventType::MOVE)
		//{

		//}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool InputComponent::AnyKey()
{
	
	if (key.IsHeld())
	{
		if (key.GetKeyCode() != NULL)
		{
			return true;
		}
		else {
			return false;
		}

	}
	else
	{
		return false;
	}
}

bool InputComponent::AnyKeyDown()
{
	
	if (key.IsPressed())
	{
		if (key.GetKeyCode() != NULL)
		{
			return true;
		}
		else {
			return false;
		}

	}
	else
	{
		return false;
	}
}

void InputComponent::ProcessInput()
{
	key = KeyboardClass::ReadKey();
	e = MouseClass::ReadEvent();
	//cout << "iam here" << endl;
}

