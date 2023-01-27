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
