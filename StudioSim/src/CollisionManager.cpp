#include "CollisionManager.h"

#pragma region DeclareMembers
std::vector<GameObject*> CollisionManager::m_gameObjects;
QuackPhysics* CollisionManager::m_quackPhysics;
#pragma endregion DeclareMembers

CollisionManager::CollisionManager()
{
	m_quackPhysics = new QuackPhysics();
}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::Update(const float deltaTime)
{
	int index = 0;

	// Update collision for each game object
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject->GetCollisionType() != CollisionType::NONE)
		{
			std::vector<GameObject*> tempGameObjects = m_gameObjects;
			tempGameObjects.erase(tempGameObjects.begin() + index);

			for (GameObject* otherGameObject : tempGameObjects)
			{
				bool bColliding = false;
				std::vector<CollisionSide> sidesCollided;


				// box to box
				if (gameObject->GetCollisionType() == CollisionType::BOX && otherGameObject->GetCollisionType() == CollisionType::BOX) 
				{
					BoundingBox owningBox = BoundingBox(gameObject->GetCollisionCenter(), gameObject->GetCollisionBoxSize());
					BoundingBox otherBox = BoundingBox(otherGameObject->GetCollisionCenter(), otherGameObject->GetCollisionBoxSize());
					sidesCollided = m_quackPhysics->BoxToBox(owningBox, otherBox);
					bColliding = sidesCollided.size() != 0;
				}
				// sphere to sphere
				else if (gameObject->GetCollisionType() == CollisionType::SPHERE && otherGameObject->GetCollisionType() == CollisionType::SPHERE)
				{
					BoundingSphere owningSphere = BoundingSphere(gameObject->GetCollisionCenter(), gameObject->GetCollisionSphereRadius());
					BoundingSphere otherSphere = BoundingSphere(otherGameObject->GetCollisionCenter(), otherGameObject->GetCollisionSphereRadius());
					bColliding = m_quackPhysics->SpheretoSphere(owningSphere, otherSphere);
				}

				//// TODO: box to sphere / sphere to box
				//else if
				//{

				//}

				if (bColliding)
				{
					Actor* isActor = dynamic_cast<Actor*>(gameObject);
					if (isActor)
						gameObject->AddCollision(otherGameObject, sidesCollided);
				}
				else
				{
					gameObject->RemoveCollision(otherGameObject);
				}
			}
		}

		index++;
	}
}
