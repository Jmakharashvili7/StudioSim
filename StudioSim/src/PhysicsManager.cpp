#include "PhysicsManager.h"

#pragma region DeclareMembers
std::vector<Actor*> PhysicsManager::m_gameActors;

PhysicsManager::PhysicsManager()
{

}

PhysicsManager::~PhysicsManager()
{

}

void PhysicsManager::Update(const float deltaTime)
{
	// Update physics for each actor
	for (Actor* actor : m_gameActors)
	{
		if (actor->GetSimulatingGravity())
		{
			// Gravity calculations
			//TODO
			//const std::vector currentPosition = actor->GetPosition();
			// weight = mass * gravitaional force
			float weight = actor->GetMass() * GFORCE;
			//TODO
			//const float newActorYPosition = currentPosition.y - (weight * deltaTime);
			//actor->UpdatePosition(currentPosition.x, newActorYPosition, currentPosition.z);

			// Jumping calculations
			if (actor->GetJumping())
			{
				const float currentJumpForce = actor->GetCurrentJumpForce();
				const float jumpHeight = actor->GetJumpHeight();
				//TODO
				//const std::vector currentPosition = actor->GetPosition();

				// Adjust current position
				//TODO
				//const float newActorYPosition = currentPosition.y + (currentJumpForce * deltaTime);
				//actor->UpdatePosition(currentPosition.x, newActorYPosition, currentPosition.z);
				
				// Update jump force
				const float newJumpForce = currentJumpForce - (jumpHeight * deltaTime);

				// feel like this can be better - collision with ground maybe
				if (newJumpForce <= 0.0f)
				{
					actor->SetJumping(false);
					actor->SetCurrentJumpForce(0.0f);
				}
				else
				{
					actor->SetCurrentJumpForce(newJumpForce);
				}
			}

			//// Impulse calculations
			//if (actor->GetImpulseActive())
			//{
			//	const glm::vec3 currentImpulseForce = actor->GetCurrentImpulseForce();
			//	const glm::vec3 forceMagnitude = actor->GetImpulseForceMag();
			//	//TODO
			//	//const glm::vec3 currentPosition = actor->GetPosition();

			//	//Adjust current position
			//	//TODO
			//	const glm::vec3 newActorPosition = glm::vec3(
			//		currentPosition.x + (currentImpulseForce.x * deltaTime),
			//		currentPosition.y + (currentImpulseForce.y * deltaTime),
			//		currentPosition.z + (currentImpulseForce.z * deltaTime))
			//	actor->UpdatePosition(newActorPosition);

			//	// Update impulse force
			//	const glm::vec3 newImpulseForce = glm::vec3(
			//		currentImpulseForce.x - (forceMagnitude.x * deltaTime),
			//		currentImpulseForce.y - (forceMagnitude.y * deltaTime),
			//		currentImpulseForce.z - (forceMagnitude.z * deltaTime))
			//	)

			//	if (newImpulseForce.length < 0.0f)
			//	{
			//		actor->SetImpulseActive(false);
			//		actor->SetCurrentImpulseForce(glm::vec3(0.0f));
			//	}
			//	else
			//	{
			//		if (newImpulseForce.x < 0.0f)
			//			newImpulseForce.x = 0.0f;
			//		if (newImpulseForce.y < 0.0f)
			//			newImpulseForce.y = 0.0f;
			//		if (newImpulseForce.z < 0.0f)
			//			newImpulseForce.z = 0.0f;

			//		actor->SetCurrentImpulseForce(newJumpForce);
			//	}
			//}
		}
	}
}
