#include "pch.h"

#include "EnemyProjectile.h"
#include "Quack.h"
#include "JsonLoader.h"
#include "Transform.h"

EnemyProjectile::EnemyProjectile(std::string projName, float speed, Vector3 dir, Vector3 pos) :
	GameObject(*JsonLoader::LoadGameObject2D(projName)),
	m_speed(speed),
	m_direction(dir)
{
	VertexData* vertexData = JsonLoader::LoadObjectData2D("Square");
	TransformData transform = TransformData(m_transform->GetPosition(), m_transform->GetRotation(), m_transform->GetScale());
	m_transform->SetPosition(pos);
	m_type = GameObjectType::PROJECTILE;
}

void EnemyProjectile::Update(float deltaTime)
{
	Vector3 travel = m_speed * m_direction * deltaTime;

	AdjustPosition(travel);

	m_distanceTraveled += travel.Length();
	if (m_distanceTraveled >= 10.0f)
	{
		Quack::GetCurrentScene()->RemoveGameObject(this);
	}
}

void EnemyProjectile::OnCollision(GameObject* collidingObject)
{
	if (collidingObject->GetType() != GameObjectType::ENEMY && collidingObject->GetType() != GameObjectType::PROJECTILE)
	{
		Quack::GetCurrentScene()->RemoveGameObject(this);
	}
}