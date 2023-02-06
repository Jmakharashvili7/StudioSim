#include "pch.h"
#include "PhysicsComponent.h"
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

void CollisionResolver::Resolve(float deltaTime)
{
	ResolveVelocity(deltaTime);
	ResolveInterpenetration(deltaTime);
}

void CollisionResolver::ResolveInterpenetration(float deltaTime)
{
	if (m_Penetration <= 0) return;

	float totalInverseMass = m_PhysicsObject[0]->GetInverseMass();
	if (m_PhysicsObject[1]) totalInverseMass += m_PhysicsObject[1]->GetInverseMass();

	if (totalInverseMass <= 0) return;

	Vector3 movePerIMass = m_contactNormal * (-m_Penetration / totalInverseMass);

	m_PhysicsObject[0]->GetOwningActor()->SetPosition(m_PhysicsObject[0]->GetOwningActor()->GetPosition() + movePerIMass * m_PhysicsObject[0]->GetInverseMass());

	if (m_PhysicsObject[1])
	{
		m_PhysicsObject[1]->GetOwningActor()->SetPosition(m_PhysicsObject[1]->GetOwningActor()->GetPosition() + movePerIMass * m_PhysicsObject[1]->GetInverseMass());
	}
}

float CollisionResolver::CalculateSeparateVelocity() const
{
	Vector3 relativeVelocity = m_PhysicsObject[0]->GetVelocity();
	if (m_PhysicsObject[1])
	{
		relativeVelocity -= m_PhysicsObject[1]->GetVelocity();
		
	}
	
	Vector3 contactNormal = m_contactNormal;
	contactNormal.Normalize();
	return Vector3::Dot(relativeVelocity,contactNormal);
	
}

void CollisionResolver::ResolveVelocity(float deltaTime)
{
	float separatingVelocity = CalculateSeparateVelocity();

	if (separatingVelocity > 0)
	{
		return;
	}

	float newSepVelocity = -separatingVelocity * restitution;

	//Vector3 accCausedVelocity = m_PhysicsObject[0]->GetAcceleration();

	//if (m_PhysicsObject[1])
	//{
	//	accCausedVelocity -= m_PhysicsObject[1]->GetAcceleration();
	//}

	//float accCausedSepVelocity = accCausedVelocity.Length() * m_contactNormal.Length() * deltaTime;
	//if (accCausedSepVelocity < 0)
	//{
	//	newSepVelocity += restitution * accCausedSepVelocity;
	//	if (newSepVelocity < 0)
	//	{
	//		newSepVelocity = 0;
	//	}
	//}


	float deltaVelocity = newSepVelocity - separatingVelocity;

	float totalInverseMass = m_PhysicsObject[0]->GetInverseMass();
	if (m_PhysicsObject[1])
	{
		totalInverseMass += m_PhysicsObject[1]->GetInverseMass();
	}
	if (totalInverseMass <=0)
	{
		return;
	}

	float impulse = deltaVelocity / totalInverseMass;

	Vector3 impulsePerMass = m_contactNormal * impulse;

	m_PhysicsObject[0]->SetVelocity(m_PhysicsObject[0]->GetVelocity() + impulsePerMass * m_PhysicsObject[0]->GetInverseMass());

	if (m_PhysicsObject[1])
	{
		m_PhysicsObject[1]->SetVelocity(m_PhysicsObject[1]->GetVelocity() + impulsePerMass * -m_PhysicsObject[1]->GetInverseMass());
	}

}
