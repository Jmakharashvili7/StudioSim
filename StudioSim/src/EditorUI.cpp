#include "EditorUI.h"
#include "Actor.h"
#include "Animate.h";

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
	ImGui::ShowDemoWindow();
	ImGui::Begin("Settings", NULL, ImGuiWindowFlags_AlwaysAutoResize);
	if (m_object)
	{
		float itemWidth = ImGui::GetContentRegionAvail().x * 0.5f;
		Texture* texture = m_object->GetTexture();
	
		ImGui::Text(m_object->GetName().c_str());

		ImGui::PushItemWidth(itemWidth);
		ImGui::Image((void*)m_object->GetTexture()->GetRendererID(), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::PopItemWidth();

		if (ImGui::TreeNode("Transform"))
		{
			ImGui::PushItemWidth(itemWidth);
			Vector3 pos = m_object->GetPosition();
			ImGui::DragFloat3("Position", &pos.x);
			m_object->SetPosition(pos);
			ImGui::PopItemWidth();

			ImGui::PushItemWidth(itemWidth);
			Vector3 rot = m_object->GetRotation();
			ImGui::DragFloat("Rotation", &rot.z);
			m_object->SetRotation(rot);
			ImGui::PopItemWidth();

			ImGui::PushItemWidth(itemWidth);
			Vector3 scale = m_object->GetScale();
			ImGui::DragFloat3("Scale", &scale.x);
			m_object->SetScale(scale);
			ImGui::PopItemWidth();

			ImGui::TreePop();
			ImGui::Separator();
		}
		
		if (Actor* actorObject = dynamic_cast<Actor*>(m_object))
		{
			if (ImGui::TreeNode("Physics"))
			{
				ImGui::PushItemWidth(itemWidth);
				float mass = actorObject->GetPhysicsData().mass;
				ImGui::SliderFloat("Object Mass", &mass, 1.0f, 100.0f, NULL, ImGuiSliderFlags_AlwaysClamp);
				actorObject->SetMass(mass);
				ImGui::PopItemWidth();

				ImGui::PushItemWidth(itemWidth);
				bool simGravity = actorObject->GetSimulatingGravity();
				ImGui::Checkbox("Simulate Gravity", &simGravity);
				actorObject->SetSimulateGravity(simGravity);
				ImGui::PopItemWidth();

				ImGui::TreePop();
				ImGui::Separator();
			}

			if (ImGui::TreeNode("Animation"))
			{
				if (actorObject->GetAnimator())
				{
					ImGui::PushItemWidth(itemWidth);
					bool animated = actorObject->GetAnimationStatus();
					ImGui::Checkbox("Animated", &animated);
					actorObject->SetAnimationStatus(animated);
					ImGui::PopItemWidth();

					if (actorObject->GetAnimationStatus())
					{
						int rows = actorObject->GetAnimator()->GetRows();
						ImGui::InputInt("Rows in Spritesheet", &rows);
						actorObject->GetAnimator()->SetRows(rows);

						int columns = actorObject->GetAnimator()->GetColumns();
						ImGui::InputInt("Columns in Spritesheet", &columns);
						actorObject->GetAnimator()->SetColumns(columns);
					}
				}
				else
				{
					ImGui::PushItemWidth(itemWidth);
					ImGui::Text("No animator on this object");
					ImGui::PopItemWidth();
				}

				ImGui::TreePop();
				ImGui::Separator();
			}
		}

	}
	ImGui::End();
}

void EditorUI::HandleInput(KeyEvent key)
{
}
