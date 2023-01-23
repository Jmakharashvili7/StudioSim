#include "Actor.h"
#include "Animate.h"
#include "Quack.h"

Actor::Actor(std::string name, GameObjectData* data, const TransformData& transformData, const CollisionData& collisionData, const TextureData& textureData, const PhysicsData& physicsData, const AnimationData& animationData)
	: GameObject{ name, data, transformData, collisionData, textureData }, m_physicsData(physicsData)
{
	//Animation init
	m_banimated = animationData.banimated;
	if (m_banimated)
	{
		m_animator = new Animate(this, animationData.rows, animationData.columns);
	}

	m_velocity = { 0.0f,0.0f,0.0f };
	m_acceleration = { 0.0f,0.0f,0.0f };
	m_netForce = { 0.0f,0.0f,0.0f };
	m_thrustForce = { 0.0f,0.0f,0.0f };
	m_brakeForce = { 0.0f,0.0f,0.0f };
	m_gravityForce = { 0.0f,0.0f,0.0f };
	m_mass = 1;
	m_weight = m_mass * GFORCE;
}

Actor::~Actor()
{

}
void Actor::Update(float deltaTime)
{
	UpdateNetForce();
	UpdateAcceleration();

	moveConstAcceleration(m_acceleration, deltaTime);

}
void Actor::Jump()
{
	if (m_physicsData.bsimulateGravity && !m_bjumping)
	{
		m_bjumping = true;
		m_currentJumpForce = m_physicsData.jumpHeight;
	}
}

void Actor::Draw(Shader* mainShader)
{
	if (m_animator)
	{
		m_animator->UpdateTextCoord(Quack::GetDeltaTime());
	}

	GameObject::Draw(mainShader);
}

void Actor::AddCollision(GameObject* collidingObject)
{
	if (collidingObject->GetName() == "ground")
	{
		std::cout << "HIT GROUND" << std::endl;
		SetCollidingWithGround(true);
	}

	GameObject::AddCollision(collidingObject);
}

void Actor::RemoveCollision(GameObject* gameObject)
{
	if (gameObject->GetName() == "ground")
	{
		std::cout << "END GROUND" << std::endl;
		SetCollidingWithGround(false);
	}

	GameObject::RemoveCollision(gameObject);
}

bool const Actor::GetCollidingWithGround()
{
	return m_bcollidingWithGround;
}

void Actor::AddImpulseForce(Vector3 force)
{
	if (m_physicsData.bsimulateGravity && !m_bimpulseActive)
	{
		m_bimpulseActive = true;
		m_currentImpulseForce = force;
		m_testImpulseForceMag = force;
	}
}

void Actor::UpdateNetForce()
{
	m_netForce.x += m_thrustForce.x + m_brakeForce.x + m_gravityForce.x;
	m_netForce.y += m_thrustForce.y + m_brakeForce.y + m_gravityForce.y;
	m_netForce.z += m_thrustForce.z + m_brakeForce.z + m_gravityForce.z;
}

void Actor::UpdateAcceleration()
{
	m_acceleration.x = m_netForce.x / m_mass;
	m_acceleration.y = m_netForce.y / m_mass;
	m_acceleration.z = m_netForce.z / m_mass;
}

void Actor::moveUp()
{

	glm::vec3 position = this->GetPosition();
	position.y += 0.02f;
	this->SetPosition(position);

}

void Actor::moveDown()
{

	glm::vec3 position = this->GetPosition();
	position.y -= 0.02f;
	this->SetPosition(position);

}

void Actor::moveLeft()
{

	glm::vec3 position = this->GetPosition();
	position.x -= 0.02f;
	this->SetPosition(position);

}

void Actor::moveRight()
{

	glm::vec3 position = this->GetPosition();
	position.x += 0.02f;
	this->SetPosition(position);

}

void Actor::Reset()
{
	m_acceleration = glm::vec3();
	m_netForce = glm::vec3();
	m_thrustForce = glm::vec3();
	m_brakeForce = glm::vec3();
	m_gravityForce = glm::vec3();
}

void Actor::moveConstVelocity(glm::vec3 velocity, float deltaTime)
{
	glm::vec3 position = this->GetPosition();

	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
	position.z += velocity.z * deltaTime;

	this->SetPosition(position);

}

void Actor::moveConstAcceleration(glm::vec3 acceleration, float deltaTime)
{

	glm::vec3 position = this->GetPosition();
	position.x += m_velocity.x * deltaTime + 0.5f * acceleration.x * deltaTime * deltaTime;
	position.y += m_velocity.y * deltaTime + 0.5f * acceleration.y * deltaTime * deltaTime;
	position.z += m_velocity.z * deltaTime + 0.5f * acceleration.z * deltaTime * deltaTime;

	m_velocity.x += acceleration.x * deltaTime;
	m_velocity.y += acceleration.y * deltaTime;
	m_velocity.z += acceleration.z * deltaTime;

	this->SetPosition(position);


}
