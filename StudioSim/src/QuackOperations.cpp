#include "QuackOperations.h"
#include "Character.h"

const int QuackOperations::GetGameObjectIndex(GameObject* gameObject, std::vector<GameObject*> gameObjectArray)
{
	int i = 0;
	int indexToReturn = -1;

	for (GameObject* loopedGameObject : gameObjectArray)
	{
		if (gameObject == loopedGameObject)
		{
			indexToReturn = i;
		}

		i++;
	}

	return indexToReturn;
}

const int QuackOperations::GetGameObjectIndex(std::string gameObjectName, std::vector<GameObject*> gameObjectArray)
{
	int i = 0;
	int indexToReturn = -1;

	for (GameObject* loopedGameObject : gameObjectArray)
	{
		if (gameObjectName == loopedGameObject->GetName())
		{
			indexToReturn = i;
		}

		i++;
	}

	return indexToReturn;
}

const int QuackOperations::GetActorIndex(Actor* actor, std::vector<Actor*> actorArray)
{
	int i = 0;
	int indexToReturn = -1;

	for (Actor* loopedActor : actorArray)
	{
		if (actor == loopedActor)
		{
			indexToReturn = i;
		}

		i++;
	}

	return indexToReturn;
}

const int QuackOperations::GetActorIndex(std::string actorName, std::vector<Actor*> actorArray)
{
	int i = 0;
	int indexToReturn = -1;

	for (Actor* loopedActor : actorArray)
	{
		if (actorName == loopedActor->GetName())
		{
			indexToReturn = i;
		}

		i++;
	}

	return indexToReturn;
}

const int QuackOperations::GetCharacterIndex(Character* character, std::vector<Character*> characterArray)
{
	int i = 0;
	int indexToReturn = -1;

	for (Actor* loopedCharacter : characterArray)
	{
		if (character == loopedCharacter)
		{
			indexToReturn = i;
		}

		i++;
	}

	return indexToReturn;
}

const int QuackOperations::GetCharacterIndex(std::string characterName, std::vector<Character*> characterArray)
{
	int i = 0;
	int indexToReturn = -1;

	for (Actor* loopedCharacter : characterArray)
	{
		if (characterName == loopedCharacter->GetName())
		{
			indexToReturn = i;
		}

		i++;
	}

	return indexToReturn;
}
