#include "pch.h"
#include "HUD.h"
#include "Quack.h"
#include "UILayer.h"
#include "EngineManager.h"


HUD::HUD()
{
}

HUD::~HUD()
{
}

void HUD::Draw()
{
	//Size of viewport
	//double port_x = m_uiMain->GetViewport()->GetSize().x;
	//double port_y = m_uiMain->GetViewport()->GetSize().y;

	float port_x = Quack::GetUILayer()->GetViewport()->GetSize().x;
	float port_y = Quack::GetUILayer()->GetViewport()->GetSize().y;

	OrthographicCamera* camera = Quack::GetOrthoCam();
	glm::vec4 camDimensions = camera->GetDimensions();
	float camPort_x = camera->GetPosition().x;
	float camPort_y = camera->GetPosition().y;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, port_x, port_y, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);
	glClear(GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS);

	//Health bar
	GameObject* temp = EngineManager::GetGameObject("Heart0");
	temp->SetPosition({ camPort_x + camDimensions.x + 1, camPort_y + camDimensions.z + 1, 0.0f });

	GameObject* temp1 = EngineManager::GetGameObject("Heart1");
	temp1->SetPosition({ camPort_x + camDimensions.x + 2, camPort_y + camDimensions.z + 1, 0.0f });

	GameObject* temp2 = EngineManager::GetGameObject("Heart2");
	temp2->SetPosition({ camPort_x + camDimensions.x + 3, camPort_y + camDimensions.z + 1, 0.0f });

	GameObject* temp3 = EngineManager::GetGameObject("Heart3");
	temp3->SetPosition({ camPort_x + camDimensions.x + 4, camPort_y + camDimensions.z + 1, 0.0f });

	GameObject* temp4 = EngineManager::GetGameObject("Heart4");
	temp4->SetPosition({ camPort_x + camDimensions.x + 5, camPort_y + camDimensions.z + 1, 0.0f });

	////Health bar
	//glColor3f(1.0f, 1.0f, 0.0f);
	//glVertex2f(0.0, port_y - 100);
	//glVertex2f(400.0, port_y - 100);
	//glVertex2f(400.0, port_y);
	//glVertex2f(0.0, port_y);
	////Blood meter
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex2f(port_x - 400.0, port_y - 100);
	//glVertex2f(port_x, port_y - 100);
	//glVertex2f(port_x, port_y);
	//glVertex2f(port_x - 400, port_y);
	////Coins?
	//glColor3f(0.0f, 0.0f, 1.0f);
	//glVertex2f(0.0, 0.0);
	//glVertex2f(200.0, 0.0);
	//glVertex2f(200.0, 100.0);
	//glVertex2f(0.0, 100.0);

	Update();

	glEnd();
}

void HUD::Update()
{
	Character* inputCharacter = dynamic_cast<Character*>(EngineManager::GetInputCharacter());

	GameObject* temp0 = EngineManager::GetGameObject("Heart0");
	GameObject* temp1 = EngineManager::GetGameObject("Heart1");
	GameObject* temp2 = EngineManager::GetGameObject("Heart2");
	GameObject* temp3 = EngineManager::GetGameObject("Heart3");
	GameObject* temp4 = EngineManager::GetGameObject("Heart4");

	if (!inputCharacter)
	{
		return;
	}

	switch (int(inputCharacter->GetCurrentHealth()))
	{
		case(100):
		{
			
			temp0->SetNewTexture("HeartFull.png");
			
			temp1->SetNewTexture("HeartFull.png");
			
			temp2->SetNewTexture("HeartFull.png");
			
			temp3->SetNewTexture("HeartFull.png");
			
			temp4->SetNewTexture("HeartFull.png");
			break;
		}
		case(90):
		{
			temp0->SetNewTexture("HeartFull.png");

			temp1->SetNewTexture("HeartFull.png");

			temp2->SetNewTexture("HeartFull.png");

			temp3->SetNewTexture("HeartFull.png");

			temp4->SetNewTexture("HeartHalf.png");
			break;
		}
		case(80):
		{
			temp0->SetNewTexture("HeartFull.png");

			temp1->SetNewTexture("HeartFull.png");

			temp2->SetNewTexture("HeartFull.png");

			temp3->SetNewTexture("HeartFull.png");

			temp4->SetNewTexture("HeartEmpty.png");
			break;
		}
		case(70):
		{
			temp0->SetNewTexture("HeartFull.png");

			temp1->SetNewTexture("HeartFull.png");

			temp2->SetNewTexture("HeartFull.png");

			temp3->SetNewTexture("HeartHalf.png");

			temp4->SetNewTexture("HeartEmpty.png");
			break;
		}
		case(60):
		{
			temp0->SetNewTexture("HeartFull.png");

			temp1->SetNewTexture("HeartFull.png");

			temp2->SetNewTexture("HeartFull.png");

			temp3->SetNewTexture("HeartEmpty.png");

			temp4->SetNewTexture("HeartEmpty.png");
			break;
		}
		case(50):
		{
			temp0->SetNewTexture("HeartFull.png");

			temp1->SetNewTexture("HeartFull.png");

			temp2->SetNewTexture("HeartHalf.png");

			temp3->SetNewTexture("HeartEmpty.png");

			temp4->SetNewTexture("HeartEmpty.png");
			break;
		}
		case(40):
		{
			temp0->SetNewTexture("HeartFull.png");

			temp1->SetNewTexture("HeartFull.png");

			temp2->SetNewTexture("HeartEmpty.png");

			temp3->SetNewTexture("HeartEmpty.png");

			temp4->SetNewTexture("HeartEmpty.png");
			break;
		}
		case(30):
		{
			temp0->SetNewTexture("HeartFull.png");

			temp1->SetNewTexture("HeartHalf.png");

			temp2->SetNewTexture("HeartEmpty.png");

			temp3->SetNewTexture("HeartEmpty.png");

			temp4->SetNewTexture("HeartEmpty.png");
			break;
		}
		case(20):
		{
			temp0->SetNewTexture("HeartFull.png");

			temp1->SetNewTexture("HeartEmpty.png");

			temp2->SetNewTexture("HeartEmpty.png");

			temp3->SetNewTexture("HeartEmpty.png");

			temp4->SetNewTexture("HeartEmpty.png");
			break;
		}
		case(10):
		{
			temp0->SetNewTexture("HeartHalf.png");

			temp1->SetNewTexture("HeartEmpty.png");

			temp2->SetNewTexture("HeartEmpty.png");

			temp3->SetNewTexture("HeartEmpty.png");

			temp4->SetNewTexture("HeartEmpty.png");
			break;
		}
		case(1):
		{
			temp0->SetNewTexture("HeartEmpty.png");

			temp1->SetNewTexture("HeartEmpty.png");

			temp2->SetNewTexture("HeartEmpty.png");

			temp3->SetNewTexture("HeartEmpty.png");

			temp4->SetNewTexture("HeartEmpty.png");
			break;
		}
	}
}