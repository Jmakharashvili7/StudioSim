#include "UILayer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Quack.h"

UILayer::UILayer() : Layer("UI Layer")
{

}

UILayer::~UILayer()
{
}

void UILayer::OnAttach()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui_ImplGlfw_InitForOpenGL(Quack::GetWindow()->GetGLFWWindow(), true);
}

void UILayer::OnDetach()
{
}

void UILayer::OnUpdate()
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(Quack::GetWindow()->GetWidth(), Quack::GetWindow()->GetHeight());

	float time = (float)glfwGetTime();
	io.DeltaTime = m_time > 0.0 ? (time - m_time) : (1.0f / 60.0f);
	m_time = time;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	static bool show = true;

	ImGui::Begin("Edit Background", &show);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Close", "Ctrl+W")) { show = false; }
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	// Edit a color stored as 4 floats
	ImGui::ColorEdit4("Color", &m_color[0]);

	// Generate samples and plot them
	float samples[100];
	for (int n = 0; n < 100; n++)
		samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
	ImGui::PlotLines("Samples", samples, 100);

	// Display contents in a scrolling region
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
	ImGui::BeginChild("Scrolling");
	for (int n = 0; n < 50; n++)
		ImGui::Text("%04d: Some text", n);
	ImGui::EndChild();
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UILayer::OnEvent()
{
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