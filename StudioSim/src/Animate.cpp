#include "Animate.h"
#include "GameObject.h"

Animate::Animate(GameObject* target)
{
	object = target;

	m_delay = 50.0f;
	m_spriteFrame = 0;
	m_rowToPlay = 0;
}

Animate::~Animate()
{
	delete object;
	object = nullptr;
}

/// <summary>
/// Animates a sprite using a row from a sprite sheet
/// </summary>
/// <param name="rows">Number of rows in the sprite sheet</param>
/// <param name="columns">Number of columns in the sprite sheet</param>
/// <param name="deltaTime">Delta time</param>
/// <param name="playRate">Time taken to update frame in seconds</param>
void Animate::UpdateTextCoord(float rows, float columns, float deltaTime, float playRate)
{
	//Use delay to adjust play rate of the animation
	m_delay = m_delay + deltaTime;

	if (m_delay > playRate)
	{
		//Calculate starting position in sprite sheet based of the current frame
		glm::vec2 startLocation = glm::vec2(0, 0);

		//making sure the sprite frame value isn't more than the number of columns
		m_spriteFrame = m_spriteFrame > columns ? m_spriteFrame - columns : m_spriteFrame;
		startLocation.x = (1 / columns) * m_spriteFrame;

		startLocation.y = (1 / rows) * m_rowToPlay;

		//Updating texture co-ordinates
		float texCoords[] =
		{
			startLocation.x,						startLocation.y,
			startLocation.x + 1.0f / columns,		startLocation.y,
			startLocation.x + 1.0f / columns,		startLocation.y + 1.0f / rows,
			startLocation.x + 1.0f / columns,		startLocation.y + 1.0f / rows,
			startLocation.x,						startLocation.y + 1.0f / rows,
			startLocation.x,						startLocation.y
		};

		//Adjusting values for the vertex array and adding updates to buffer
		GameObjectData spriteData;
		spriteData.textCoords.first = texCoords;
		spriteData.textCoords.second = sizeof(texCoords);


		VertexBuffer texCoordsBuffer = VertexBuffer(spriteData.textCoords.first, spriteData.textCoords.second);


		VertexBufferLayout texCoordsLayout;
		texCoordsLayout.Push<float>(2);

		object->GetVertexArray()->AddBuffer(texCoordsBuffer, texCoordsLayout, VertexType::TEX_COORDS);

		m_spriteFrame++;
		m_delay = 0;
	}
}
