#include "CollisionManager.h"

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
					/*if (Actor* actor = dynamic_cast<Actor*>(gameObject))
					{
						std::cout << "Duck Boi		" << (owningBox.center - owningBox.size / Vector3(2.0f, 2.0f, 2.0f)).y << std::endl;
						std::cout << "Ground Boi		" << (otherBox.center + otherBox.size / Vector3(2.0f, 2.0f, 2.0f)).y << std::endl;
					}*/
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

//Vector3 CollisionManager::RepositionGameObject(GameObject* a, GameObject* b)
//{
//	//Vector3 pen = Vector3(a->GetPosition() - a->GetPreviousPosition());
//	//Vector3 outPosition = Vector3(a->GetPosition() - pen);
//
//	//Vector3 outPosition = Vector3(a->GetPosition().x, (b->GetCollisionCenter().y + b->GetCollisionBoxSize().y / 2.0f) - (a->GetCollisionCenter().y - a->GetCollisionBoxSize().y / 2.0f), 0.0f);
//	return Vector3();
//}

void CollisionManager::RemoveGameObject(GameObject* gameObjectToRemove)
{
	if (gameObjectToRemove)
	{
		const int gameObjectIndex = QuackOperations::GetGameObjectIndex(gameObjectToRemove, m_gameObjects);
		m_gameObjects.erase(m_gameObjects.begin() + gameObjectIndex);
	}
}
