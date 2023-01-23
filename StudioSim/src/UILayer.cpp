#include "UILayer.h"
#include "Quack.h"
#include "Window.h"
#include "EngineManager.h"

UILayer::UILayer() : Layer("UI Layer"), m_color(1.0f, 1.0f, 1.0f, 1.0f)
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
	m_viewportUI = new ViewportUI("Viewport", Quack::GetFrameBuffer());
	m_editorUI = new EditorUI("Settings", EngineManager::GetGameObject("duck"));
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

	ImGui::PopStyleVar();

	// Menu at the top of the window
	if (ImGui::BeginMenuBar())
	{
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

/*
		////position, center
	BoundingBox box1 = BoundingBox(glm::vec3(squarePositionData[0].x, squarePositionData[0].y, squarePositionData[0].z),
		//size
		glm::vec3(squareScaleData[0].x, squareScaleData[0].y, squareScaleData[0].z));

	BoundingBox box2 = BoundingBox(glm::vec3(squarePositionData[1].x, squarePositionData[1].y, squarePositionData[1].z),
		//size
		glm::vec3(squareScaleData[1].x, squareScaleData[1].y, squareScaleData[1].z));

	BoundingBox box3 = BoundingBox(glm::vec3(squarePositionData[2].x, squarePositionData[2].y, squarePositionData[2].z),
		//size
		glm::vec3(squareScaleData[2].x, squareScaleData[2].y, squareScaleData[2].z));

	BoundingBox box4 = BoundingBox(glm::vec3(squarePositionData[3].x, squarePositionData[3].y, squarePositionData[3].z),
		//size
		glm::vec3(squareScaleData[3].x, squareScaleData[3].y, squareScaleData[3].z));
	BoundingBox boxes[NUMBER_OF_SQUARES]{};
	for (int i = 0; i < NUMBER_OF_SQUARES; i++)
		boxes[i] = BoundingBox(glm::vec3(squarePositionData[i].x, squarePositionData[i].y, squarePositionData[i].z),
			//size
			glm::vec3(squareScaleData[i].x, squareScaleData[i].y, squareScaleData[i].z));
	/// <summary>
	/// Start IMGUI window
	/// </summary>
	ImGui::Begin("My name is window, ImGui window");
	ImGui::Text("Hello");
	bool temp = false;

	/// <summary>
	/// Changing position of each square
	/// </summary>
	ImGui::DragFloat3("First Square", &squarePositionData[0].x, 0.001f);
	ImGui::DragFloat3("Second Square", &squarePositionData[1].x, 0.001f);
	ImGui::DragFloat3("Third Square", &squarePositionData[2].x, 0.001f);
	ImGui::DragFloat3("Fourth Square", &squarePositionData[3].x, 0.001f);
	ImGui::DragFloat("Rotation", &m_rotation, 0.1f);
	ImGui::DragFloat("Force", &m_projectileForce, 0.1f);


	/// <summary>
	/// Check box, needs to be static to be pressable
	/// </summary>
	static bool gravityEnabled = false;
	bool areColliding = false;
	ImGui::Checkbox("Gravity", &gravityEnabled);

	/// <summary>
	/// Check collision between box 1(top left) with box 4(bottom right)
	/// If they donw collide, add gravity to box 1
	/// </summary>
	for (int i = 0; i < NUMBER_OF_SQUARES; i++)
		for (int j = 0; j < NUMBER_OF_SQUARES && j != i; j++)
		{
			if (p_QuackPhysics->BoxToBox(box1, box3) ||
				p_QuackPhysics->BoxToBox(box1, box4))
			{
				areColliding = true;
				//std::cout << "The objects are collidiing";
			}
			else
			{
				areColliding = false;
				//std::cout << "The objects are not collidiing";
			}

		}
	if (gravityEnabled && !areColliding)
	{
		//QuackPhysics::Gravity();
		Gravity();
	}
	/// <summary>
	/// Create button for jump
	/// </summary>
	if (ImGui::Button("Jump"))
	{
		Jump();
		gravityEnabled = true;
	}
	ImGui::SameLine();
	/// <summary>
	/// Create button for throw left
	/// </summary>
	if (ImGui::Button("Throw left"))
	{
		Projectile(m_projectileForce);
		Jump();
		gravityEnabled = true;
		m_direction = Facing::LEFT;
	}
	ImGui::SameLine();
	/// <summary>
	/// Create button for throw right
	/// </summary>
	if (ImGui::Button("Throw right"))
	{
		Projectile(m_projectileForce);
		Jump();
		gravityEnabled = true;
		m_direction = Facing::RIGHT;
	}
	/// <summary>
	/// Light components directional, point, spotlight
	/// Changing the values how we want
	/// </summary>
#ifdef _3D_SHADER
	if (ImGui::TreeNode("Lights"))
	{
		/// <summary>
		/// Directional ambient, diffuse, specular
		/// </summary>
		if (ImGui::TreeNode("Directional"))
		{
			ImGui::DragFloat4("Ambient", &m_dirAmbient.x, 0.001f);
			ImGui::DragFloat4("Diffuse", &m_dirDiffuse.x, 0.001f);
			ImGui::DragFloat4("Specular", &m_dirSpecular.x, 0.001f);
			ImGui::TreePop();
		}
		/// <summary>
		/// Point ambient, diffuse, specular
		/// </summary>
		if (ImGui::TreeNode("Point"))
		{
			for (int i = 0; i < std::size(m_pointLightPositions); i++)
			{
				if (ImGui::TreeNode((void*)(intptr_t)i, "Point Light %d", i))
				{
					ImGui::DragFloat3("Position", &m_pointLightPositions[i].x, 0.01f);
					ImGui::DragFloat4("Ambient", &m_pointAmbient.x, 0.001f);
					ImGui::DragFloat4("Diffuse", &m_pointDiffuse.x, 0.001f);
					ImGui::DragFloat4("Specular", &m_pointSpecular.x, 0.001f);
					ImGui::TreePop();
				}
			}
			ImGui::TreePop();
		}
		/// <summary>
		/// Directional ambient, diffuse, specular
		/// </summary>
		if (ImGui::TreeNode("Spot"))
		{
			ImGui::DragFloat4("Ambient", &m_spotAmbient.x, 0.001f);
			ImGui::DragFloat4("Diffuse", &m_spotDiffuse.x, 0.001f);
			ImGui::DragFloat4("Specular", &m_spotSpecular.x, 0.001f);
			ImGui::TreePop();
		}
	}
#endif // _3D_SHADER
#ifdef _2D_SHADER


	if (ImGui::TreeNode("Light"))
	{
		/// <summary>
		/// Directional ambient, diffuse, specular
		/// </summary>
			ImGui::DragFloat4("Ambient", &m_lightAmbient.x, 0.001f);

			ImGui::TreePop();

	}
#endif // _2D_SHADER

	/// <summary>
	/// End of IMGUI window
	/// </summary>
	ImGui::End();

	/// <summary>
	/// Show the help commands window
	/// </summary>
	ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
*/ // old gui code