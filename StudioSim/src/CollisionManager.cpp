#include "pch.h"

#include "CollisionManager.h"
#include "EngineManager.h"

CollisionManager::CollisionManager()
{
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
				
				// box to box
				if (gameObject->GetCollisionType() == CollisionType::BOX && otherGameObject->GetCollisionType() == CollisionType::BOX) 
				{
					BoundingBox owningBox = BoundingBox(gameObject->GetCollisionCenter(), gameObject->GetCollisionBoxSize());
					BoundingBox otherBox = BoundingBox(otherGameObject->GetCollisionCenter(), otherGameObject->GetCollisionBoxSize());
					bColliding = CollisionHelper::BoxToBox(owningBox, otherBox);
				}
				// sphere to sphere
				else if (gameObject->GetCollisionType() == CollisionType::SPHERE && otherGameObject->GetCollisionType() == CollisionType::SPHERE)
				{
					BoundingSphere owningSphere = BoundingSphere(gameObject->GetCollisionCenter(), gameObject->GetCollisionSphereRadius());
					BoundingSphere otherSphere = BoundingSphere(otherGameObject->GetCollisionCenter(), otherGameObject->GetCollisionSphereRadius());
					bColliding = CollisionHelper::SpheretoSphere(owningSphere, otherSphere);
				}

				//// TODO: box to sphere / sphere to box
				//else if
				//{

				//}

				if (bColliding)
				{
					if (!gameObject->GetIsCollidingGameObject(otherGameObject))
					{
						gameObject->AddCollision(otherGameObject);
					}
				}
				else
				{
					if (gameObject->GetIsCollidingGameObject(otherGameObject))
					{
						gameObject->RemoveCollision(otherGameObject);
					}
				}
			}
		}

		index++;
	}
}

void CollisionManager::RemoveGameObject(GameObject* gameObjectToRemove)
{
	if (gameObjectToRemove)
	{
		const int gameObjectIndex = EngineManager::GetGameObjectIndex(gameObjectToRemove, m_gameObjects);
		m_gameObjects.erase(m_gameObjects.begin() + gameObjectIndex);
	}
}
