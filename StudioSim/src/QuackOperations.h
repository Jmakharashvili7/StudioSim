#pragma once
#include <vector>

class GameObject;
class Actor;
class Character;

class QuackOperations
{
public:
	static const int GetGameObjectIndex(GameObject* gameObject, std::vector<GameObject*> gameObjectArray);
	static const int GetActorIndex(Actor* actor, std::vector<Actor*> actorArray);
	static const int GetCharacterIndex(Character* character, std::vector<Character*> characterArray);
};

