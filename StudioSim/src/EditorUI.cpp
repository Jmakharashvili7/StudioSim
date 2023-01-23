#include "EditorUI.h"

EditorUI::EditorUI(std::string name, GameObject* gameObject) : 
	UIWindow(name),
	m_object(gameObject)
{
}

EditorUI::~EditorUI()
{
}

void EditorUI::Render()
{
	ImGui::Begin("Settings");
	Texture* texture = m_object->GetTexture();
	ImGui::Text(m_object->GetName().c_str());
	ImGui::Image((void*)m_object->GetTexture()->GetRendererID(), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
	if (ImGui::TreeNode("Transform"))
	{
		glm::vec3 pos = m_object->GetPosition();
		ImGui::DragFloat3("Position", &pos[0]);
		m_object->SetPosition(pos);

		glm::vec3 rot = m_object->GetRotation();
		ImGui::DragFloat("Rotation", &rot.z);
		m_object->SetRotation(rot);

		glm::vec3 scale = m_object->GetScale();
		ImGui::DragFloat3("Scale", &scale[0]);
		m_object->SetScale(scale);

		ImGui::TreePop();
		ImGui::Separator();
	}
	ImGui::End();
}

void EditorUI::HandleInput(KeyEvent key)
{
}
