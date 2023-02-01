#include "pch.h"

#include "EditorUI.h"
#include "Character.h"
#include "Animate.h";
#include "PhysicsComponent.h"
#include "Quack.h"
#include "UILayer.h"
#include "ViewportUI.h"
#include "EngineManager.h"

namespace fs = std::filesystem;

EditorUI::EditorUI(std::string name, GameObject* gameObject) :
	UIWindow(name),
	m_object(gameObject)
{
	m_Viewport = Quack::GetUILayer()->GetViewport();

	m_ItemWidth = 0.0f;
}

EditorUI::~EditorUI()
{
}

void EditorUI::Render()
{
	ImGui::Begin("Settings", NULL, ImGuiWindowFlags_AlwaysAutoResize);

	//ImGui::ShowDemoWindow();

	if (m_object)
	{
		//sets the push width of ImGui items 
		//to stop text being cut off when making window smaller
		//although if the window gets too small it will cut off anyway
		m_ItemWidth = ImGui::GetContentRegionAvail().x * 0.5f;

		std::string objectClass = "Object Type: " + (std::string)typeid(*m_object).name();
		ImGui::PushItemWidth(m_ItemWidth);
		ImGui::Text(objectClass.c_str());
		ImGui::PopItemWidth();

		ImGui::Separator();

		if (ImGui::TreeNode("Object Name"))
		{
			std::string stringName = m_object->GetName();
			std::string textItem = "Current Name: " + stringName;

			ImGui::PushItemWidth(m_ItemWidth);
			ImGui::Text(textItem.c_str());
			ImGui::PopItemWidth();

			ImGui::PushItemWidth(m_ItemWidth);
			static char charName[128] = "_____";
			strcpy_s(charName, stringName.c_str());
			ImGui::InputText("Object Name", charName, IM_ARRAYSIZE(charName));
			m_object->SetName(std::string(charName));
			Quack::GetCurrentScene()->ToggleStopInput(ImGui::IsItemActive());
			ImGui::PopItemWidth();

			ImGui::TreePop();
			ImGui::Separator();
		}

		Texture* texture = m_object->GetTexture();

		ImGui::PushItemWidth(m_ItemWidth);
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
			ImGui::PushItemWidth(m_ItemWidth);
			Vector3 pos = m_object->GetPosition();
			ImGui::DragFloat3("Position", &pos.x);
			m_object->SetPosition(pos);
			ImGui::PopItemWidth();

			ImGui::PushItemWidth(m_ItemWidth);
			Vector3 rot = m_object->GetRotation();
			ImGui::DragFloat("Rotation", &rot.z);
			m_object->SetRotation(rot);
			ImGui::PopItemWidth();

			ImGui::PushItemWidth(m_ItemWidth);
			Vector3 scale = m_object->GetScale();
			ImGui::DragFloat3("Scale", &scale.x);
			m_object->SetScale(scale);
			ImGui::PopItemWidth();

			ImGui::TreePop();
			ImGui::Separator();
		}

		if (ImGui::TreeNode("Collision"))
		{
			ImGui::PushItemWidth(m_ItemWidth);
			std::string collisionTitle = "Current Type: ";
			collisionTitle += GetCollisionTypeName(m_object->GetCollisionType());
			if (ImGui::BeginMenu(collisionTitle.c_str()))
			{
				GenerateCollisionMenu();

				ImGui::EndMenu();
			}
			ImGui::PopItemWidth();

			if (m_object->GetCollisionType() == CollisionType::SPHERE)
			{
				ImGui::PushItemWidth(m_ItemWidth);
				float sphereRadius = m_object->GetCollisionSphereRadius();
				ImGui::SliderFloat("Sphere Radius", &sphereRadius, 1.0f, 30.0f, NULL, ImGuiSliderFlags_AlwaysClamp);
				if (m_object->GetCollisionSphereRadius() != sphereRadius)
				{
					m_object->SetCollisionSphereRadius(sphereRadius);
				}
				ImGui::PopItemWidth();
			}

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
					ImGui::PushItemWidth(m_ItemWidth);
					float mass = actorObject->GetPhysicsData().mass;
					ImGui::SliderFloat("Mass", &mass, 1.0f, 30.0f, NULL, ImGuiSliderFlags_AlwaysClamp);
					if (actorObject->GetMass() != mass)
					{
						actorObject->SetMass(mass);
					}
					ImGui::PopItemWidth();

					//Slider to adjust the gravity multiplier of the actor
					//Ctrl click to use keyboard input to enter a value manually
					ImGui::PushItemWidth(m_ItemWidth);
					float gravityMultiplier = actorObject->GetPhysicsData().gravityMultiplier;
					ImGui::SliderFloat("Gravity Multiplier", &gravityMultiplier, 1.0f, 10.0f, NULL, ImGuiSliderFlags_AlwaysClamp);
					if (actorObject->GetGravityMultiplier() != gravityMultiplier)
					{
						actorObject->SetGravityMultiplier(gravityMultiplier);
					}
					ImGui::PopItemWidth();

					//Check box to toggle simulation of gravity on and off
					ImGui::PushItemWidth(m_ItemWidth);
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
					ImGui::PushItemWidth(m_ItemWidth);
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
					ImGui::PushItemWidth(m_ItemWidth);
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
				ImGui::PushItemWidth(m_ItemWidth);
				float jumpHeight = characterObject->GetJumpHeight();
				ImGui::SliderFloat("Jump Height", &jumpHeight, 0.0f, 1000.0f, NULL, ImGuiSliderFlags_AlwaysClamp);
				if (characterObject->GetJumpHeight() != jumpHeight)
				{
					characterObject->SetJumpHeight(jumpHeight);
				}
				ImGui::PopItemWidth();

				ImGui::PushItemWidth(m_ItemWidth);
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
				ImGui::PushItemWidth(m_ItemWidth);
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

			if (ImGui::TreeNode("Input"))
			{
				ImGui::PushItemWidth(m_ItemWidth);
				bool consumingInput = EngineManager::GetCharacterConsumingInput(characterObject);
				ImGui::Checkbox("Consume Input", &consumingInput);
				if (EngineManager::GetCharacterConsumingInput(characterObject) != consumingInput)
				{
					if (consumingInput)
					{
						EngineManager::SetInputCharacter(characterObject);
					}
					else
					{
						EngineManager::SetInputCharacter(nullptr);
					}
				}
				ImGui::PopItemWidth();

				ImGui::TreePop();
				ImGui::Separator();
			}
		}

	}
	ImGui::End();
}

void EditorUI::HandleInput(KeyEvent key, MouseEvent e)
{
	if (e.GetType() == MouseEvent::EventType::L_CLICK && Quack::GetUILayer()->GetViewport()->GetIsFocused())
	{
		Vector2 port;
		//Size of viewport
		port.x = m_Viewport->GetSize().x;
		port.y = m_Viewport->GetSize().y;

		//Current mouse position within viewport scale
		Vector2 viewStart;
		viewStart.x = ImGui::GetMousePos().x - m_Viewport->GetStartX();
		viewStart.y = ImGui::GetMousePos().y - m_Viewport->GetStartY();

		//Only counting the click within viewport boundary
		if ((viewStart.x >= 0 && viewStart.y >= 0) && (viewStart.x <= port.x && viewStart.y <= port.y))
		{
			SnapOnGrid(ConvertClickToScreen(viewStart, port));
		}
	}
}

vector<Vector3> EditorUI::ConvertClickToScreen(Vector2 viewStart, Vector2 port)
{
	vector<Vector3> values;

	//get the camera viewProjection matrix, and inverse it
	glm::mat4 auxCamera = Quack::GetOrthoCam()->GetViewProjectionMatrix();
	glm::mat4 invCamera = glm::inverse(auxCamera);

	//new position of the duck based on the mouse's position normalised based on 
	//the viewport
	Vector2 newPosition;
	newPosition.x = (viewStart.x / (port.x / 2) - 1);
	newPosition.y = -(viewStart.y / (port.y / 2) - 1);

	Vector3 ndc = Vector3(newPosition.x, newPosition.y, 0);

	//Does the inverse of the camera, turning the screen's 2D coord into a world space 3D coord
	ndc.x = invCamera[0].x * ndc.x + invCamera[1].x * ndc.y + invCamera[2].x * ndc.z;
	ndc.y = invCamera[0].y * ndc.x + invCamera[1].y * ndc.y + invCamera[2].y * ndc.z;
	ndc.z = invCamera[0].z * ndc.x + invCamera[1].z * ndc.y + invCamera[2].z * ndc.z;

	Vector3 integers;
	//get the int part of the number
	integers.x = (int)ndc.x;
	integers.y = (int)ndc.y;
	integers.z = (int)ndc.z;
	values.push_back(integers);

	//get the decimals of the number
	Vector3 floats;
	floats.x = ndc.x - integers.x;
	floats.y = ndc.y - integers.y;
	floats.z = ndc.z - integers.z;
	values.push_back(floats);

	return values;
}

void EditorUI::SnapOnGrid(vector<Vector3> values)
{
	if (values[1].x >= 0)
	{
		if (values[1].x >= 0.25 && values[1].x <= 0.75)
			values[1].x = 0.5;
		else if (values[1].x < 0.25)
			values[1].x = 0.0f;
		else if (values[1].x > 0.75)
			values[1].x = 1.0f;
	}
	else
	{
		if (values[1].x <= -0.25 && values[1].x >= -0.75)
			values[1].x = -0.5;
		else if (values[1].x > -0.25)
			values[1].x = 0.0f;
		else if (values[1].x < -0.75)
			values[1].x = -1.0f;
	}
	if (values[1].y >= 0)
	{
		if (values[1].y >= 0.25 && values[1].y <= 0.75)
			values[1].y = 0.5;
		else if (values[1].y < 0.25)
			values[1].y = 0.0f;
		else if (values[1].y > 0.75)
			values[1].y = 1.0f;
	}
	else
	{
		if (values[1].y <= -0.25 && values[1].y >= -0.75)
			values[1].y = -0.5;
		else if (values[1].y > -0.25)
			values[1].y = 0.0f;
		else if (values[1].y < -0.75)
			values[1].y = -1.0f;
	}
	if (values[1].z > 0)
	{
		if (values[1].z >= 0.25 && values[1].z <= 0.75)
			values[1].z = -0.5;
		else if (values[1].z < 0.25)
			values[1].z = 0.0f;
		else if (values[1].z > 0.75)
			values[1].z = -1.0f;
	}
	else
	{
		if (values[1].z <= -0.25 && values[1].z >= -0.75)
			values[1].z = 0.5;
		else if (values[1].z > -0.25)
			values[1].z = 0.0f;
		else if (values[1].z < -0.75)
			values[1].z = -1.0f;
	}
	Vector3 finalPosition;

	//calculate the final position X
	if (values[0].x > 0)
	{
		finalPosition.x = values[0].x + values[1].x;
	}
	else if (values[0].x == 0)
	{
		finalPosition.x = values[1].x;
	}
	else
	{
		finalPosition.x = values[0].x + values[1].x;
	}

	//calculate the final position Y
	if (values[0].y > 0)
	{
		finalPosition.y = values[0].y + values[1].y;
	}
	else if (values[0].y == 0)
	{
		finalPosition.y = values[1].y;
	}
	else
	{
		finalPosition.y = values[0].y + values[1].y;
	}
	//calculate the final position Z
	if (values[0].z > 0)
	{
		finalPosition.z = values[0].z + values[1].z;
	}
	else if (values[0].z == 0)
	{
		finalPosition.z = values[1].z;
	}
	else
	{
		finalPosition.z = values[0].z + values[1].z;
	}

	m_object->SetPosition(finalPosition);

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

	//m_isFocused = true;
	//SetInMenu(true);

	if (ImGui::MenuItem(GetCollisionTypeName(CollisionType::BOX).c_str()))
	{
		m_object->SetCollisionType(CollisionType::BOX);
		//SetInMenu(false);
	}
	if (ImGui::MenuItem(GetCollisionTypeName(CollisionType::SPHERE).c_str()))
	{
		m_object->SetCollisionType(CollisionType::SPHERE);
		//SetInMenu(false);
	}
	if (ImGui::MenuItem(GetCollisionTypeName(CollisionType::NONE).c_str()))
	{
		m_object->SetCollisionType(CollisionType::NONE);
		//SetInMenu(false);
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