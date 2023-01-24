#pragma once
#include "component.h"

enum KeyType
{
	A,
	B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, ENTER, SPACE, BACKSPACE, LFSHIFT, RSHIFT
};

enum MouseClickType
{

};

enum ButtonNames
{
	EHorizontal,
	EVertical
};

class InputComponent : public Component
{
public:


	InputComponent(class Actor* Owner, int updateOrder, GLFWwindow* window);

	virtual void Update(float deltaTime) override;

	~InputComponent();

	/// <summary>
	/// Returns true during the frame the user pressed down the virtual button identified by buttonName.
	/// </summary>
	bool GetButtonDown(ButtonNames buttonNames);

	/// <summary>
	/// Returns true while the virtual button identified by buttonName is held down.
	/// </summary>
	/// <param name="buttonNames"></param>
	/// <returns></returns>
	bool GetButton(ButtonNames buttonNames);


	int GetAxisRaw(ButtonNames buttonNames);

	bool GetKey(char keyButton);


	bool GetKeyDown(char keyButton);

	bool GetKeyUp(char keyButton);

	bool GetMouseButton(int mouseClick);

	bool GetMouseButtonDown(int mouseClick);

	bool GetMouseButtonUp(int mouseClick);

	bool AnyKey();


	bool AnyKeyDown();

	
protected:
	void ProcessInput();

private:
	GLFWwindow* m_Window;

	map<KeyType, int>ButtonsKeys;
	
	KeyEvent key;
	MouseEvent e;
};

