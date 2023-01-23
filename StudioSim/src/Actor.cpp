#include "Actor.h"
#include "Animate.h"
#include "Quack.h"

Actor::Actor(std::string name, GameObjectData* data, const TransformData& transformData, const TextureData& textureData, const PhysicsData& physicsData, const AnimationData& animationData)
	: GameObject{ name, data, transformData, textureData }
{
	// Physics init
	m_bsimulateGravity = physicsData.bsimulateGravity;
	m_mass = physicsData.mass;
	m_jumpHeight = physicsData.jumpHeight;

	//Animation init
	m_banimated = animationData.banimated;
	if (m_banimated)
	{
		m_animator = new Animate(this, animationData.rows, animationData.columns);
	}
	m_weight = this->GetMass() * GFORCE;
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
	if (m_bsimulateGravity && !m_bjumping)
	{
		m_bjumping = true;
		m_currentJumpForce = m_jumpHeight;
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

void Actor::AddImpulseForce(glm::vec3 force)
{
	if (m_bsimulateGravity && !m_bimpulseActive)
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

void Actor::Update(float deltaTime)
{
	UpdateNetForce();
	UpdateAcceleration();
	std::cout << "Velocity" << m_velocity.x << endl;
	moveConstAcceleration(m_acceleration, deltaTime);

}
void Actor::UpdateNetForce()
{
	m_netForce.x += m_thrustForce.x + m_brakeForce.x + m_gravityForce.x;
	m_netForce.y += m_thrustForce.y + m_brakeForce.y + m_gravityForce.y;
	m_netForce.z += m_thrustForce.z + m_brakeForce.z + m_gravityForce.z;
}

void Actor::UpdateAcceleration()
{
	m_acceleration.x = m_netForce.x / this->GetMass();
	m_acceleration.y = m_netForce.y / this->GetMass();
	m_acceleration.z = m_netForce.z / this->GetMass();
}

void Actor::moveUp()
{

	Vector3 position = this->GetPosition();
	position.y += 0.02f;
	this->SetPosition(position);

}

void Actor::moveDown()
{

	Vector3 position = this->GetPosition();
	position.y -= 0.02f;
	this->SetPosition(position);

}

void Actor::moveLeft()
{

	Vector3 position = this->GetPosition();
	position.x -= 0.02f;
	this->SetPosition(position);

}

void Actor::moveRight()
{

	Vector3 position = this->GetPosition();
	position.x += 0.02f;
	this->SetPosition(position);

}

void Actor::Reset()
{
	m_acceleration = Vector3();
	m_netForce = Vector3();
	m_thrustForce = Vector3();
	m_brakeForce = Vector3();
	m_gravityForce = Vector3();
}

void Actor::moveConstVelocity(Vector3 velocity, float deltaTime)
{
	Vector3 position = this->GetPosition();

	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
	position.z += velocity.z * deltaTime;

	this->SetPosition(position);

}

void Actor::moveConstAcceleration(Vector3 acceleration, float deltaTime)
{

	Vector3 position = this->GetPosition();
	position.x += m_velocity.x * deltaTime + 0.5f * acceleration.x * deltaTime * deltaTime;
	position.y += m_velocity.y * deltaTime + 0.5f * acceleration.y * deltaTime * deltaTime;
	position.z += m_velocity.z * deltaTime + 0.5f * acceleration.z * deltaTime * deltaTime;

	m_velocity.x += acceleration.x * deltaTime;
	m_velocity.y += acceleration.y * deltaTime;
	m_velocity.z += acceleration.z * deltaTime;

	this->SetPosition(position);


}