#include "UILayer.h"
#include "Quack.h"
#include "Window.h"
#include "EngineManager.h"

UILayer::UILayer() : Layer("UI Layer"), m_color(0.0f, 1.0f, 0.0f, 1.0f)
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