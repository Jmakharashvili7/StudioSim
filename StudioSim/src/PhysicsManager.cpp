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
	// Update physics for each actor
	for (Actor* actor : m_gameActors)
	{
		actor->Update(deltaTime);
		if (actor->GetSimulatingGravity())
		{
			if (!actor->GetCollidingWithGround())
			{
				// Gravity calculations
				// weight = mass * gravitaional force
				//float weight = actor->GetMass() * GFORCE;
				actor->AdjustPosition(Vector3(0.0f, -actor->GetWeight() * deltaTime, 0.0f));
			}

			// Jumping calculations
			if (actor->GetJumping())
			{
				const float currentJumpForce = actor->GetCurrentJumpForce();
				const float jumpHeight = actor->GetJumpHeight();
				actor->AdjustPosition(Vector3(0.0f, currentJumpForce * deltaTime, 0.0f));
				
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

			// Impulse calculations
			if (actor->GetImpulseActive())
			{
				const Vector3 currentImpulseForce = actor->GetCurrentImpulseForce();
				const Vector3 forceMagnitude = actor->GetImpulseForceMag();

				actor->AdjustPosition(Vector3(currentImpulseForce.x * deltaTime, currentImpulseForce.y * deltaTime, currentImpulseForce.z* deltaTime));

				// Update impulse force
				Vector3 newImpulseForce = Vector3(currentImpulseForce.x - (forceMagnitude.x * deltaTime), currentImpulseForce.y - (forceMagnitude.y * deltaTime), currentImpulseForce.z - (forceMagnitude.z * deltaTime));

				if (actor->GetCurrentImpulseForce().x > 0.0f)
				{
					if ((newImpulseForce.x) <= 0.0f)
						newImpulseForce.x = 0.0f;
				}
				else
				{
					if ((newImpulseForce.x) >= 0.0f)
						newImpulseForce.x = 0.0f;
				}
				if ((newImpulseForce.y) <= 0.0f)
					newImpulseForce.y = 0.0f;
				if ((newImpulseForce.z) <= 0.0f)
					newImpulseForce.z = 0.0f;
				if ((newImpulseForce.x) == 0.0f && (newImpulseForce.y) == 0.0f && (newImpulseForce.z) == 0.0f)
				{
					actor->SetImpulseActive(false);
					actor->SetCurrentImpulseForce(Vector3::Zero);
				}
				else
				{
					actor->SetCurrentImpulseForce(newImpulseForce);
				}
			}
		}
	}
}