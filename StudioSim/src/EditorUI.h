#pragma once
#include "UIWindow.h"
#include "GameObject.h"

class ViewportUI;

class EditorUI : public UIWindow
{
public:
	EditorUI(std::string name, GameObject* gameObject);
	~EditorUI();

	void Render() override;
	void HandleInput(KeyEvent key) override;

	void SetInMenu(bool inMenu) { m_InMenu = inMenu; }

	inline void RemoveDisplayedGameObject() { m_object = nullptr; }
	inline void SetDisplayedGameObject(GameObject* object) { m_object = object; }

	std::string GetCollisionTypeName(const CollisionType collisionType);
	void GenerateCollisionMenu();

	void GenerateTextureMenu();

private:
	GameObject* m_object;
	ViewportUI* m_Viewport;

	float m_ItemWidth;

	bool m_InMenu : 1;
};