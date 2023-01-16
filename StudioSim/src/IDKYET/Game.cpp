#include "Game.h"
#include "Actor.h"

Game::Game()
{
	m_UpdatingActors = false;
	m_Gamestate = EPREGAME;
}

void Game::Start()
{
	//do whatever..



	//this must come after
	m_Gamestate = EINGAME;

}

void Game::AddActor(Actor* _actor)
{
	if (m_UpdatingActors)
	{
		m_PendingActors.emplace_back(_actor);
	}
	else
	{
		m_Actors.emplace_back(_actor);
	}
}

void Game::RemoveActor(Actor* _actor)
{
	if (m_UpdatingActors)
	{
		remove(m_PendingActors.begin(), m_PendingActors.end(), _actor);
		
	}
	else
	{
		remove(m_Actors.begin(), m_Actors.end(), _actor);
	}
}

void Game::UpdateGame(float _deltaTime)
{
	//engine update function



	m_UpdatingActors = true;
	for (int i = 0; i < m_Actors.size(); i++)
	{
		m_Actors[i]->Update(_deltaTime);
	}
	m_UpdatingActors = false;

	//moves any pending actors to actors list 
	for (auto actors : m_PendingActors)
	{
		m_Actors.emplace_back(actors);
	}
	m_PendingActors.clear();

	DeadActor();

}

void Game::DeadActor()
{
	vector<Actor*> deadActor;
	for (auto actor : m_Actors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActor.emplace_back(actor);

		}
	}

	for (auto actor : deadActor)
	{
		if (actor->GetState() == Actor::EDead)
		{
			delete actor;

		}
	}
}

void Game::PauseGame()
{
	if (m_Gamestate != GameState::EINGAME)
	{
		return;
	}
	m_Gamestate = GameState::EPAUSEGAME;
	m_UpdatingActors = false;
	for (auto actor: m_Actors)
	{
		if (actor->GetState() == Actor::EActive)
		{
			actor->SetState(Actor::EPaused);
		}
	}
}
