#pragma once
#include <vector>
#include <string>

class GameObject;
class Actor;
class Character;

class QuackOperations
{
public:
	static const int GetGameObjectIndex(GameObject* gameObject, std::vector<GameObject*> gameObjectArray);
	static const int GetGameObjectIndex(std::string gameObjectName, std::vector<GameObject*> gameObjectArray);
	static const int GetActorIndex(Actor* actor, std::vector<Actor*> actorArray);
	static const int GetActorIndex(std::string actorName, std::vector<Actor*> actorArray);
	static const int GetCharacterIndex(Character* character, std::vector<Character*> characterArray);
	static const int GetCharacterIndex(std::string characterName, std::vector<Character*> characterArray);
};

