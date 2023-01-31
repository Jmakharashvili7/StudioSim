#include "EditorUI.h"
#include "Actor.h"
#include "Animate.h";
#include "PhysicsComponent.h"
#include "Quack.h"
#include "UILayer.h"
#include "ViewportUI.h"
#include <filesystem>

namespace fs = std::filesystem;

EditorUI::EditorUI(std::string name, GameObject* gameObject) :
	UIWindow(name),
	m_object(gameObject)
{
	m_Viewport = Quack::GetUILayer()->GetViewport();
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
		Texture* texture = m_object->GetTexture

		ImGui::Text(m_object->GetName().c_str());

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
		//ImGui::Text(m_object->GetName().c_str());
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
					actorObject->SetMass(mass);
					ImGui::PopItemWidth();

					//Slider to adjust the gravity multiplier of the actor
					//Ctrl click to use keyboard input to enter a value manually
					ImGui::PushItemWidth(itemWidth);
					float gravityMultiplier = actorObject->GetPhysicsData().gravityMultiplier;
					ImGui::SliderFloat("Gravity Multiplier", &gravityMultiplier, 1.0f, 10.0f, NULL, ImGuiSliderFlags_AlwaysClamp);
					actorObject->SetGravityMultiplier(gravityMultiplier);
					ImGui::PopItemWidth();

					//Check box to toggle simulation of gravity on and off
					ImGui::PushItemWidth(itemWidth);
					bool simGravity = actorObject->GetSimulatingGravity();
					ImGui::Checkbox("Simulate Gravity", &simGravity);

					if (simGravity != actorObject->GetSimulatingGravity())
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

	}
	ImGui::End();
}

void EditorUI::HandleInput(KeyEvent key)
{
	if (!MouseClass::IsEventBufferEmpty())
	{
		MouseEvent e = MouseClass::ReadEvent();
		//Size of viewport
		/*double port_x = m_Viewport->GetSize().x;
		double port_y = m_Viewport->GetSize().y;*/
		//Size of whole window

		if (e.GetType() == MouseEvent::EventType::L_CLICK)
		{


#pragma region Converts Click To Screen Position
			////Current mouse position within viewport scale
			//float viewStart_x = ImGui::GetMousePos().x - m_Viewport->GetStartX();
			//float viewStart_y = ImGui::GetMousePos().y - m_Viewport->GetStartY();
			////Only counting the click within viewport boundary
			//if ((viewStart_x >= 0 && viewStart_y >= 0) && (viewStart_x <= port_x && viewStart_y <= port_y))
			//{
			//	//get the camera viewProjection matrix, and inverse it
			//	glm::mat4 auxCamera = Quack::GetOrthoCam()->GetViewProjectionMatrix();
			//	glm::mat4 invCamera = glm::inverse(auxCamera);

			//	//new position of the duck based on the mouse's position normalised based on 
			//	//the viewport
			//	float newposition_x = (viewStart_x / (port_x / 2) - 1),
			//		newposition_y = -(viewStart_y / (port_y / 2) - 1);

			//	Vector3 ndc = Vector3(newposition_x, newposition_y, 0);

			//	//Does the inverse of the camera, turning the screen's 2D coord into a world space 3D coord
			//	ndc.x = invCamera[0].x * ndc.x + invCamera[1].x * ndc.y + invCamera[2].x * ndc.z;
			//	ndc.y = invCamera[0].y * ndc.x + invCamera[1].y * ndc.y + invCamera[2].y * ndc.z;
			//	ndc.z = invCamera[0].z * ndc.x + invCamera[1].z * ndc.y + invCamera[2].z * ndc.z;

			//	//get the int part of the number
			//	int integer_x = (int)ndc.x;
			//	int integer_y = (int)ndc.y;
			//	int integer_z = (int)ndc.z;

			//	//get the decimals of the number
			//	float floater_x = ndc.x - integer_x;
			//	float floater_y = ndc.y - integer_y;
			//	float floater_z = ndc.z - integer_z;
#pragma endregion

#pragma region Adjusting Position to Snap On Grid

	//check if the number is closer to 0 or to 0.5
			if (floater_x >= 0)
			{
				if (floater_x >= 0.25 && floater_x <= 0.75)
					floater_x = 0.5;
				else if (floater_x < 0.25)
					floater_x = 0.0f;
				else if (floater_x > 0.75)
					floater_x = 1.0f;
			}
			else
			{
				if (floater_x <= -0.25 && floater_x >= -0.75)
					floater_x = -0.5;
				else if (floater_x > -0.25)
					floater_x = 0.0f;
				else if (floater_x < -0.75)
					floater_x = -1.0f;
			}
			if (floater_y >= 0)
			{
				if (floater_y >= 0.25 && floater_y <= 0.75)
					floater_y = 0.5;
				else if (floater_y < 0.25)
					floater_y = 0.0f;
				else if (floater_y > 0.75)
					floater_y = 1.0f;
			}
			else
			{
				if (floater_y <= -0.25 && floater_y >= -0.75)
					floater_y = -0.5;
				else if (floater_y > -0.25)
					floater_y = 0.0f;
				else if (floater_y < -0.75)
					floater_y = -1.0f;
			}
			if (integer_z > 0)
			{
				if (floater_z >= 0.25 && floater_z <= 0.75)
					floater_z = -0.5;
				else if (floater_z < 0.25)
					floater_z = 0.0f;
				else if (floater_z > 0.75)
					floater_z = -1.0f;
			}
			else
			{
				if (floater_z <= -0.25 && floater_z >= -0.75)
					floater_z = 0.5;
				else if (floater_z > -0.25)
					floater_z = 0.0f;
				else if (floater_z < -0.75)
					floater_z = -1.0f;
			}
			float finalPosition_x, finalPosition_y, finalPosition_z;
			//calculate the final position X
			if (integer_x > 0)
			{
				finalPosition_x = integer_x + floater_x;
			}
			else if (integer_x == 0)
			{
				finalPosition_x = floater_x;
			}
			else
			{
				finalPosition_x = integer_x + floater_x;
			}

			//calculate the final position Y
			if (integer_y > 0)
			{
				finalPosition_y = integer_y + floater_y;
			}
			else if (integer_y == 0)
			{
				finalPosition_y = floater_y;
			}
			else
			{
				finalPosition_y = integer_y + floater_y;
			}
			//calculate the final position Z
			if (integer_z > 0)
			{
				finalPosition_z = integer_z + floater_z;
			}
			else if (integer_z == 0)
			{
				finalPosition_z = floater_z;
			}
			else
			{
				finalPosition_z = integer_z + floater_z;
			}

			Vector3 finalPosition = Vector3(finalPosition_x, finalPosition_y, finalPosition_z);

			m_object->SetPosition(finalPosition);

			//}
#pragma endregion
		}
	}
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

vector<Vector3> EditorUI::ConvertClickToScreen()
{
	vector<Vector3> values;

	//Size of viewport
	double port_x = m_Viewport->GetSize().x;
	double port_y = m_Viewport->GetSize().y;

	//Current mouse position within viewport scale
	float viewStart_x = ImGui::GetMousePos().x - m_Viewport->GetStartX();
	float viewStart_y = ImGui::GetMousePos().y - m_Viewport->GetStartY();

	//Only counting the click within viewport boundary
	if ((viewStart_x >= 0 && viewStart_y >= 0) && (viewStart_x <= port_x && viewStart_y <= port_y))
	{
		//get the camera viewProjection matrix, and inverse it
		glm::mat4 auxCamera = Quack::GetOrthoCam()->GetViewProjectionMatrix();
		glm::mat4 invCamera = glm::inverse(auxCamera);

		//new position of the duck based on the mouse's position normalised based on 
		//the viewport
		float newposition_x = (viewStart_x / (port_x / 2) - 1),
			newposition_y = -(viewStart_y / (port_y / 2) - 1);

		Vector3 ndc = Vector3(newposition_x, newposition_y, 0);

		//Does the inverse of the camera, turning the screen's 2D coord into a world space 3D coord
		ndc.x = invCamera[0].x * ndc.x + invCamera[1].x * ndc.y + invCamera[2].x * ndc.z;
		ndc.y = invCamera[0].y * ndc.x + invCamera[1].y * ndc.y + invCamera[2].y * ndc.z;
		ndc.z = invCamera[0].z * ndc.x + invCamera[1].z * ndc.y + invCamera[2].z * ndc.z;

		//get the int part of the number
		int integer_x = (int)ndc.x;
		int integer_y = (int)ndc.y;
		int integer_z = (int)ndc.z;
		Vector3 ints = Vector3(integer_x, integer_y, integer_z);
		values.push_back(ints);
		//get the decimals of the number
		float floater_x = ndc.x - integer_x;
		float floater_y = ndc.y - integer_y;
		float floater_z = ndc.z - integer_z;
		Vector3 floats = Vector3(floater_x, floater_y, floater_z);
		values.push_back(floats);

		return values;
	}
}

Vector3 EditorUI::SnapOnGrid(vector<Vector3> values)
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
	float finalPosition_x, finalPosition_y, finalPosition_z;
	//calculate the final position X
	if (values[0].x > 0)
	{
		finalPosition_x = values[0].x + values[1].x;
	}
	else if (values[0].x == 0)
	{
		finalPosition_x = values[1].x;
	}
	else
	{
		finalPosition_x = values[0].x + values[1].x;
	}

	//calculate the final position Y
	if (values[0].y > 0)
	{
		finalPosition_y = values[0].y + values[1].y;
	}
	else if (values[0].y == 0)
	{
		finalPosition_y = values[1].y;
	}
	else
	{
		finalPosition_y = values[0].y + values[1].y;
	}
	//calculate the final position Z
	if (values[0].z > 0)
	{
		finalPosition_z = values[0].z + values[1].z;
	}
	else if (values[0].z == 0)
	{
		finalPosition_z = values[1].z;
	}
	else
	{
		finalPosition_z = values[0].z + values[1].z;
	}

	Vector3 finalPosition = Vector3(finalPosition_x, finalPosition_y, finalPosition_z);

	m_object->SetPosition(finalPosition);

	return Vector3();
}