#include "WorldOutlinerUI.h"

WorldOutlinerUI::WorldOutlinerUI(std::string name) : UIWindow(name)
{

}

WorldOutlinerUI::~WorldOutlinerUI()
{
}

void WorldOutlinerUI::Render()
{
	ImGui::Begin("World Outliner");
	ImGui::End();
}

void WorldOutlinerUI::HandleInput(KeyEvent key)
{
}
