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

void HUD::DrawCharacterHP(bool hidden)
{
	//float port_x = Quack::GetUILayer()->GetViewport()->GetSize().x;
	//float port_y = Quack::GetUILayer()->GetViewport()->GetSize().y;

	OrthographicCamera* camera = Quack::GetOrthoCam();
	glm::vec4 camDimensions = camera->GetDimensions();
	float camPort_x = camera->GetPosition().x;
	float camPort_y = camera->GetPosition().y;

	if (hidden == false)
	{
		//Health Hearts
		GameObject* temp = EngineManager::GetGameObject("Heart0");
		temp->SetPosition({ camPort_x + camDimensions.x + 0.45f, camPort_y + camDimensions.w - 0.5f, 0.0f });

		GameObject* temp1 = EngineManager::GetGameObject("Heart1");
		temp1->SetPosition({ camPort_x + camDimensions.x + 1.25f, camPort_y + camDimensions.w - 0.5f, 0.0f });

		GameObject* temp2 = EngineManager::GetGameObject("Heart2");
		temp2->SetPosition({ camPort_x + camDimensions.x + 2.0f, camPort_y + camDimensions.w - 0.5f, 0.0f });

		GameObject* temp3 = EngineManager::GetGameObject("Heart3");
		temp3->SetPosition({ camPort_x + camDimensions.x + 2.75f, camPort_y + camDimensions.w - 0.5f, 0.0f });

		GameObject* temp4 = EngineManager::GetGameObject("Heart4");
		temp4->SetPosition({ camPort_x + camDimensions.x + 3.5f, camPort_y + camDimensions.w - 0.5f, 0.0f });
	}
	else
	{
		//Health Hearts
		GameObject* temp = EngineManager::GetGameObject("Heart0");
		temp->SetPosition({ camPort_x + camDimensions.x + 0.45f, camPort_y + camDimensions.w + 1, 0.0f });

		GameObject* temp1 = EngineManager::GetGameObject("Heart1");
		temp1->SetPosition({ camPort_x + camDimensions.x + 1.25f, camPort_y + camDimensions.w + 1, 0.0f });

		GameObject* temp2 = EngineManager::GetGameObject("Heart2");
		temp2->SetPosition({ camPort_x + camDimensions.x + 2.0f, camPort_y + camDimensions.w + 1, 0.0f });

		GameObject* temp3 = EngineManager::GetGameObject("Heart3");
		temp3->SetPosition({ camPort_x + camDimensions.x + 2.75f, camPort_y + camDimensions.w + 1, 0.0f });

		GameObject* temp4 = EngineManager::GetGameObject("Heart4");
		temp4->SetPosition({ camPort_x + camDimensions.x + 3.5f, camPort_y + camDimensions.w + 1, 0.0f });
	}

	UpdateCharacterHP();
}

void HUD::DrawBossHP(bool hidden)
{
	//float port_x = Quack::GetUILayer()->GetViewport()->GetSize().x;
	//float port_y = Quack::GetUILayer()->GetViewport()->GetSize().y;

	OrthographicCamera* camera = Quack::GetOrthoCam();
	glm::vec4 camDimensions = camera->GetDimensions();
	float camPort_x = camera->GetPosition().x;
	float camPort_y = camera->GetPosition().y;
	if (hidden == false)
	{
		//Boss Health Bar
		GameObject* temp0 = EngineManager::GetGameObject("BossHPBack");
		temp0->SetPosition({ camPort_x, camPort_y + camDimensions.z + 0.5f, 0.0f });

		GameObject* temp1 = EngineManager::GetGameObject("BossHPHealth");
		temp1->SetPosition({ camPort_x, camPort_y + camDimensions.z + 0.5f, 0.0f });

		GameObject* temp2 = EngineManager::GetGameObject("BossHPFancy");
		temp2->SetPosition({ camPort_x, camPort_y + camDimensions.z + 0.5f, 0.0f });
	}
	else
	{
		//Boss Health Bar
		GameObject* temp0 = EngineManager::GetGameObject("BossHPBack");
		temp0->SetPosition({ camPort_x, camPort_y + camDimensions.z - 1, 0.0f });

		GameObject* temp1 = EngineManager::GetGameObject("BossHPHealth");
		temp1->SetPosition({ camPort_x, camPort_y + camDimensions.z - 1, 0.0f });

		GameObject* temp2 = EngineManager::GetGameObject("BossHPFancy");
		temp2->SetPosition({ camPort_x, camPort_y + camDimensions.z - 1, 0.0f });
	}
	UpdateBossHP();
}

void HUD::UpdateBossHP()
{
	GameObject* temp = EngineManager::GetGameObject("BossHPHealth");

	//Needs to get Boss object and access health
	float currentBossHealth = 100;

	temp->SetScale({ currentBossHealth / 10, 0.5, 0 });

}

void HUD::UpdateCharacterHP()
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

