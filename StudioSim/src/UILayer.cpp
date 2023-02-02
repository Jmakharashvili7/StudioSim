#include "pch.h"

#include "UILayer.h"
#include "Quack.h"
#include "Window.h"
#include "EngineManager.h"
#include "GameObject.h"
#include "Actor.h"
#include "Character.h"
#include "Enemy.h"
#include "EngineManager.h"

namespace fs = std::filesystem;

UILayer::UILayer() : Layer("UI Layer"), m_color(0.0f, 1.0f, 1.0f, 1.0f)
{
	
}

UILayer::~UILayer()
{
}

void UILayer::OnAttach()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	ImGui::StyleColorsDark();

	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui_ImplGlfw_InitForOpenGL(Quack::GetWindow()->GetGLFWWindow(), true);
}

void UILayer::InitWindows()
{
	m_viewportUI = new ViewportUI("Viewport");
	m_editorUI = new EditorUI("Settings", EngineManager::GetGameObject(0));
	m_worldOutliner = new WorldOutlinerUI("World Outliner");
	m_worldOutliner->SetEditorUI(m_editorUI);
	m_contentBrowser = new ContentBrowserUI("Content Browser");
	
}

void UILayer::OnDetach()
{
}

void UILayer::OnUpdate()
{
	// Start a new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	// start a new frame

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.65f, 0.0f, 1.0f));
	// Insert UI Code here
	EnableDocking();
	ImGui::End();
	ImGui::PopStyleColor(1);

	// render the data
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// render the data
}

void UILayer::OnEvent()
{
}

void UILayer::EnableDocking()
{
	static bool opt_fullscreen = true;
	static bool p_open = true;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &p_open, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// Submit the DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	static glm::vec3 vector;

	m_viewportUI->Render();
	m_editorUI->Render();
	m_worldOutliner->Render();
	m_contentBrowser->Render();

	ImGui::PopStyleVar();

	// Menu at the top of the window
	if (ImGui::BeginMenuBar())
	{
		//Option to create new objects or scenes
		if (ImGui::BeginMenu("New"))
		{
			SetUpObjectCreator();

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Options"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows,
			// which we can't undo at the moment without finer window depth/z control.
			ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
			ImGui::Separator();

			if (ImGui::MenuItem("Close", NULL, false, &p_open != NULL))
				p_open = false;

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}

void UILayer::SetUpObjectCreator()
{
	if (ImGui::BeginMenu("Create New Object"))
	{
		if (ImGui::Button("Game Object"))
		{
			ImGui::OpenPopup("Create Game Object");
		}

		if (ImGui::BeginPopupModal("Create Game Object", NULL, ImGuiWindowFlags_MenuBar))
		{
			CreatePopupContent(Classes::GAMEOBJECT);

			if (ImGui::Button("Create"))
			{
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::Button("Close"))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		if (ImGui::Button("Actor"))
		{
			ImGui::OpenPopup("Create Actor");
		}

		if (ImGui::BeginPopupModal("Create Actor", NULL, ImGuiWindowFlags_MenuBar))
		{
			CreatePopupContent(Classes::ACTOR);

			if (ImGui::Button("Create"))
			{
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::Button("Close"))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		if (ImGui::Button("Character"))
		{
			ImGui::OpenPopup("Create Character");
		}

		if (ImGui::BeginPopupModal("Create Character", NULL, ImGuiWindowFlags_MenuBar))
		{
			CreatePopupContent(Classes::CHARACTER);

			if (ImGui::Button("Create"))
			{
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::Button("Close"))
			{
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		if (ImGui::Button("Enemy"))
		{
			ImGui::OpenPopup("Create Enemy");
		}

		if (ImGui::BeginPopupModal("Create Enemy", NULL, ImGuiWindowFlags_MenuBar))
		{
			CreatePopupContent(Classes::ENEMY);

			if (ImGui::Button("Create"))
			{
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::Button("Close"))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		ImGui::EndMenu();
	}

}

void UILayer::CreatePopupContent(Classes createClass)
{
	std::string name = " ";

	if (ImGui::TreeNode("Object Name"))
	{
		static char charName[128] = "_____";
		strcpy_s(charName, name.c_str());
		ImGui::InputText("Object Name", charName, IM_ARRAYSIZE(charName));
		name = charName;

		ImGui::TreePop();
		ImGui::Separator();
	}

	TransformData transformData;

	if (ImGui::TreeNode("Transform"))
	{
		
		Vector3 pos = Vector3(0.0f);
		ImGui::DragFloat3("Position", &pos.x);
		transformData.position = pos;

		
		Vector3 rot = Vector3(0.0f);
		ImGui::DragFloat("Rotation", &rot.z);
		transformData.rotation = rot;

		
		Vector3 scale = Vector3(1.0f);
		ImGui::DragFloat3("Scale", &scale.x);
		transformData.scale = scale;

		ImGui::TreePop();
		ImGui::Separator();
	}

	CollisionData collisionData;

	collisionData.centerPosition = transformData.position;
	
	if (ImGui::TreeNode("Collision"))
	{
		if (ImGui::BeginMenu("Collision Types"))
		{

			if (ImGui::MenuItem(CollisionName(CollisionType::BOX).c_str()))
			{
				collisionData.collisionType = CollisionType::BOX;

			}
			if (ImGui::MenuItem(CollisionName(CollisionType::SPHERE).c_str()))
			{
				collisionData.collisionType = CollisionType::SPHERE;
				collisionData.radius = transformData.scale.x / 2;

			}
			if (ImGui::MenuItem(CollisionName(CollisionType::NONE).c_str()))
			{
				collisionData.collisionType = CollisionType::NONE;

			}

			ImGui::EndMenu();
		}
		ImGui::TreePop();
		ImGui::Separator();
	}

	std::string textureName;

	if(ImGui::TreeNode("Available Textures", NULL, false, false));
	{
		for (fs::directory_entry texture : fs::directory_iterator("res/textures"))
		{
			if (ImGui::MenuItem(texture.path().filename().string().c_str()))
			{
				textureName = texture.path().filename().string();
				ImGui::EndMenu();
			}
		}
		ImGui::TreePop();
	}

	ImGui::Separator();

	if (createClass == Classes::ACTOR || createClass == Classes::CHARACTER)
	{
		bool addPhysicsComponent = false;
		bool hasPhysicsCompoonent = false;

		ImGui::Checkbox("Add Physics Component", &addPhysicsComponent);
		if (hasPhysicsCompoonent != addPhysicsComponent)
		{
			hasPhysicsCompoonent = addPhysicsComponent;
		}

		if (hasPhysicsCompoonent)
		{
			PhysicsData physicsData;
			float mass;

			bool simulateGravity;
			float gravMultiplier;

			ImGui::SliderFloat("Mass", &mass, 1.0f, 30.0f, NULL, ImGuiSliderFlags_AlwaysClamp);
			if (physicsData.mass != mass)
			{
				physicsData.mass = mass;
			}

			ImGui::Checkbox("Simulate Gravity", &simulateGravity);
			if (physicsData.bsimulateGravity != simulateGravity)
			{
				physicsData.bsimulateGravity = simulateGravity;
			}

			if (physicsData.bsimulateGravity)
			{
				ImGui::SliderFloat("Mass", &gravMultiplier, 1.0f, 30.0f, NULL, ImGuiSliderFlags_AlwaysClamp);
				if (physicsData.gravityMultiplier != gravMultiplier)
				{
					physicsData.gravityMultiplier = gravMultiplier;
				}
			}			

			ImGui::Separator();
		}

		bool addAnimator = false;
		bool hasAnimator = false;

		ImGui::Checkbox("Add Animator", &addAnimator);
		if (hasAnimator != addAnimator)
		{
			hasAnimator = addAnimator;
		}

		if (hasAnimator)
		{
			AnimationData animationData;

			int numOfColumns = 0;
			int numOfRows = 0;
			bool animated = false;

			ImGui::InputInt("Number of Rows", &numOfRows);
			if (animationData.rows != numOfRows)
			{
				animationData.rows = numOfRows;
			}

			ImGui::InputInt("Number of Columns", &numOfColumns);
			if (animationData.columns != numOfColumns)
			{
				animationData.columns = numOfColumns;
			}

			ImGui::Checkbox("Animated", &animated);
			if (animationData.banimated != animated)
			{
				animationData.banimated = animated;
			}

			ImGui::Separator();
		}

	}

	if (createClass == Classes::CHARACTER || createClass == Classes::ENEMY)
	{
		MovementData movementData;

		float jumpHeight = 1.0f;
		float movementSpeed = 1.0f;

		ImGui::SliderFloat("Jump Height", &jumpHeight, 0.0f, 1000.0f, NULL, ImGuiSliderFlags_AlwaysClamp);
		if (movementData.jumpHeight != jumpHeight)
		{
			movementData.jumpHeight = jumpHeight;
		}

		ImGui::SliderFloat("Movement Speed", &movementSpeed, 1.0f, 25.0f, NULL, ImGuiSliderFlags_AlwaysClamp);
		if (movementData.movementSpeed != movementSpeed)
		{
			movementData.movementSpeed = movementSpeed;
		}

		ImGui::Separator();

		EntityData entityData;

		float maxHealth = 10.0f;

		ImGui::SliderFloat("Max Health", &maxHealth, 1.0f, 500.0f, NULL, ImGuiSliderFlags_AlwaysClamp);
		if (entityData.maxHealth != maxHealth)
		{
			entityData.maxHealth = maxHealth;
		}

		ImGui::Separator();
	}
}

std::string UILayer::CollisionName(CollisionType type)
{
	switch (type)
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
