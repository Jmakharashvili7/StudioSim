#include "PhysicsManager.h"

#pragma region DeclareMembers
std::vector<Actor*> PhysicsManager::m_gameActors;
#pragma endregion DeclareMembers

PhysicsManager::PhysicsManager()
{

}

PhysicsManager::~PhysicsManager()
{

}

void PhysicsManager::Update(const float deltaTime)
{
	if (deltaTime > 1.0f)
	{
		return;
	}

	// Update physics for each actor
	for (Actor* actor : m_gameActors)
	{
		if (actor->GetSimulatingGravity())
		{
			if (!actor->GetCollidingWithGround())
			{
				// Gravity calculations
				// weight = mass * gravitaional force
				float weight = actor->GetMass() * GFORCE;
				actor->AdjustPosition(Vector3(0.0f, -weight * deltaTime, 0.0f));
			}

			// Check to see if the actor is a character
			Character* character = dynamic_cast<Character*>(actor);
			if (character)
			{
				// Jumping calculations, cast to character
				if (character->GetJumping())
				{
					const float currentJumpForce = character->GetCurrentJumpForce();
					const float jumpHeight = character->GetJumpHeight();
					character->AdjustPosition(Vector3(0.0f, currentJumpForce * deltaTime, 0.0f));

					// Update jump force
					const float newJumpForce = currentJumpForce - (jumpHeight * deltaTime);

					if (newJumpForce <= 0.0f)
					{
						character->SetCurrentJumpForce(0.0f);
					}
					else
					{
						character->SetCurrentJumpForce(newJumpForce);
					}
				}
			}
		}
	}
}

void PhysicsManager::RemoveGameActor(Actor* actorToRemove)
{
	if (actorToRemove)
	{
		const int actorIndex = QuackOperations::GetActorIndex(actorToRemove, m_gameActors);
		m_gameActors.erase(m_gameActors.begin() + actorIndex);
	}
}
