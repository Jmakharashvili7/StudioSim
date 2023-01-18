#pragma once
#include <vector>
#include <algorithm>

using namespace std;

class Game
{
public:
	enum GameState
	{
		EPREGAME,
		EINGAME,
		EPAUSEGAME,
		EPOSTGAME
	};
	//things to initialize before the game starts
	Game();

	//things to initialize when the game starts 
	void Start();

	void AddActor(class Actor* _actor);
	void RemoveActor(class Actor* _actor);
	void UpdateGame(float _deltaTime);

	void DeadActor();
	void PauseGame();

protected:
	GameState m_Gamestate;
	vector<class Actor*> m_Actors;
	vector<class Actor*> m_PendingActors;
	bool m_UpdatingActors;
};

