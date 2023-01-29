#pragma once
#include "UIWindow.h"
#include "GameObject.h"

class EditorUI : public UIWindow
{
public:
	EditorUI(std::string name, GameObject* gameObject);
	~EditorUI();

	void Render() override;
	void HandleInput(KeyEvent key) override;

	inline void RemoveDisplayedGameObject() { m_object = nullptr; }
	inline void SetDisplayedGameObject(GameObject* object) { m_object = object; }
private:
	GameObject* m_object;
};