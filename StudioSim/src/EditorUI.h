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

	inline void RemoveDisplayedGameObject() { m_object = nullptr; }
	inline void SetDisplayedGameObject(GameObject* object) { m_object = object; }

	void GenerateTextureMenu();

	vector<Vector3> ConvertClickToScreen();
	Vector3 SnapOnGrid(vector<Vector3> values);
private:
	GameObject* m_object;
	ViewportUI* m_Viewport;
};