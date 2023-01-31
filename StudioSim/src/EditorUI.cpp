#include "EditorUI.h"
#include "Character.h"
#include "Animate.h";
#include "PhysicsComponent.h"
#include <filesystem>

namespace fs = std::filesystem;

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
	ImGui::Begin("Settings", NULL, ImGuiWindowFlags_AlwaysAutoResize);
	if (m_object)
	{
		//sets the push width of ImGui items 
		//to stop text being cut off when making window smaller
		//although if the window gets too small it will cut off anyway
		float itemWidth = ImGui::GetContentRegionAvail().x * 0.5f;

		if (ImGui::TreeNode("Name"))
		{
			ImGui::PushItemWidth(itemWidth);
			std::string stringName = m_object->GetName();
			static char charName[128] = "_____";
			strcpy_s(charName, stringName.c_str());
			ImGui::InputText("", charName, IM_ARRAYSIZE(charName));
			m_object->SetName(std::string(charName));
			ImGui::PopItemWidth();

			ImGui::TreePop();
			ImGui::Separator();
		}

		Texture* texture = m_object->GetTexture();
		ImGui::PushItemWidth(itemWidth);
		if (m_object->GetTexture())
		{
			ImGui::Image((void*)m_object->GetTexture()->GetRendererID(), ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));
		}
		std::string menuTitle = "Current Texture: ";
		menuTitle += m_object->GetTextureName();
		if (ImGui::BeginMenu(menuTitle.c_str()))
		{
			GenerateTextureMenu();
			ImGui::EndMenu();
		}	

		ImGui::Separator();
		ImGui::PopItemWidth();

		//Set up for displaying objects transform information
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

		if (ImGui::TreeNode("Collision"))
		{
			ImGui::PushItemWidth(itemWidth);
			std::string collisionTitle = "Current Type: ";
			collisionTitle += GetCollisionTypeName(m_object->GetCollisionType());
			if (ImGui::BeginMenu(collisionTitle.c_str()))
			{
				GenerateCollisionMenu();
				ImGui::EndMenu();
			}
			ImGui::PopItemWidth();

			ImGui::TreePop();
			ImGui::Separator();
		}
		
		//Will only display the follwing information if object 
		//is an actor or subclass of an actor
		if (Actor* actorObject = dynamic_cast<Actor*>(m_object))
		{
			if (PhysicsComponent* actorPhysics = actorObject->GetComponent<PhysicsComponent>())
			{
				//Set up to display physics data
				if (ImGui::TreeNode("Physics"))
				{
					//Slider to adjust the mass of the actor
					//Ctrl click to use keyboard input to enter a value manually
					ImGui::PushItemWidth(itemWidth);
					float mass = actorObject->GetPhysicsData().mass;
					ImGui::SliderFloat("Mass", &mass, 1.0f, 100.0f, NULL, ImGuiSliderFlags_AlwaysClamp);
					if (actorObject->GetMass() != mass)
					{
						actorObject->SetMass(mass);
					}
					ImGui::PopItemWidth();

					//Slider to adjust the gravity multiplier of the actor
					//Ctrl click to use keyboard input to enter a value manually
					ImGui::PushItemWidth(itemWidth);
					float gravityMultiplier = actorObject->GetPhysicsData().gravityMultiplier;
					ImGui::SliderFloat("Gravity Multiplier", &gravityMultiplier, 1.0f, 10.0f, NULL, ImGuiSliderFlags_AlwaysClamp);
					if (actorObject->GetGravityMultiplier() != gravityMultiplier)
					{
						actorObject->SetGravityMultiplier(gravityMultiplier);
					}
					ImGui::PopItemWidth();

					//Check box to toggle simulation of gravity on and off
					ImGui::PushItemWidth(itemWidth);
					bool simGravity = actorObject->GetSimulatingGravity();
					ImGui::Checkbox("Simulate Gravity", &simGravity);
					if (actorObject->GetSimulatingGravity() != simGravity)
					{
						actorObject->SetSimulateGravity(simGravity);
					}
					ImGui::PopItemWidth();

					ImGui::TreePop();
					ImGui::Separator();
				}
			}

			//Set up to display animation data
			//will only show data if the animator on the actor is not a null pointer
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
					//Message if animator is a null pointer
					ImGui::PushItemWidth(itemWidth);
					ImGui::Text("No animator on this object");
					ImGui::PopItemWidth();
				}

				ImGui::TreePop();
				ImGui::Separator();
			}
		}

		//Will only display the follwing information if object 
		//is a character or subclass of a character
		if (Character* characterObject = dynamic_cast<Character*>(m_object))
		{
			if (ImGui::TreeNode("Movement"))
			{
				ImGui::PushItemWidth(itemWidth);
				float jumpHeight = characterObject->GetJumpHeight();
				ImGui::SliderFloat("Jump Height", &jumpHeight, 0.0f, 1000.0f, NULL, ImGuiSliderFlags_AlwaysClamp);
				if (characterObject->GetJumpHeight() != jumpHeight)
				{
					characterObject->SetJumpHeight(jumpHeight);
				}
				ImGui::PopItemWidth();

				ImGui::PushItemWidth(itemWidth);
				float movementSpeed = characterObject->GetMovementSpeed();
				ImGui::SliderFloat("Movement Speed", &movementSpeed, 1.0f, 25.0f, NULL, ImGuiSliderFlags_AlwaysClamp);
				if (characterObject->GetMovementSpeed() != movementSpeed)
				{
					characterObject->SetMovementSpeed(movementSpeed);
				}
				ImGui::PopItemWidth();

				ImGui::TreePop();
				ImGui::Separator();
			}

			if (ImGui::TreeNode("Health"))
			{
				ImGui::PushItemWidth(itemWidth);
				float maxHealth = characterObject->GetMaxHealth();
				ImGui::SliderFloat("Max Health", &maxHealth, 1.0f, 500.0f, NULL, ImGuiSliderFlags_AlwaysClamp);
				if (characterObject->GetMaxHealth() != maxHealth)
				{
					characterObject->SetMaxHealth(maxHealth, true);
				}
				ImGui::PopItemWidth();

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

std::string EditorUI::GetCollisionTypeName(const CollisionType collisionType)
{
	switch (collisionType)
	{
		case CollisionType::BOX:
			return "BOX";
		case CollisionType::SPHERE:
			return "SPHERE";
		case CollisionType::NONE:
			return "NONE";
		default:
			return "";
	}
}

void EditorUI::GenerateCollisionMenu()
{
	ImGui::MenuItem("Collision Types", NULL, false, false);

	if (ImGui::MenuItem(GetCollisionTypeName(CollisionType::BOX).c_str()))
	{
		m_object->SetCollisionType(CollisionType::BOX);
	}
	if (ImGui::MenuItem(GetCollisionTypeName(CollisionType::SPHERE).c_str()))
	{
		m_object->SetCollisionType(CollisionType::SPHERE);
	}
	if (ImGui::MenuItem(GetCollisionTypeName(CollisionType::NONE).c_str()))
	{
		m_object->SetCollisionType(CollisionType::NONE);
	}
}

void EditorUI::GenerateTextureMenu()
{
	ImGui::MenuItem("Available Textures", NULL, false, false);

	for (fs::directory_entry texture : fs::directory_iterator("res/textures"))
	{
		if (ImGui::MenuItem(texture.path().filename().string().c_str()))
		{
			m_object->SetNewTexture(texture.path().filename().string().c_str());
		}
	}
}
