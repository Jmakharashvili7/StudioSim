#pragma once
#include "UIWindow.h"
#include "UIWindow.h"
#include "GameObject.h"

class EditorUI : public UIWindow
{
public:
	EditorUI(std::string name, GameObject* gameObject);
	~EditorUI();

	void Render() override;
	void HandleInput(KeyEvent key) override;
private:
	GameObject* m_object;
};