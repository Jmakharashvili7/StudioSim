#include "Animate.h"
#include "GameObject.h"

Animate::Animate(GameObject* target, int rows, int columns)
{
	object = target;

	m_delay = 50.0f;
	m_spriteFrame = 0;

	m_rows = rows;
	m_columns = columns;

	GenerateFrameList();
}

Animate::~Animate()
{
	delete object;
	object = nullptr;
}

/// <summary>
/// Animates a sprite using a row from a sprite sheet
/// </summary>
/// <param name="deltaTime">Delta time</param>
/// <param name="playRate">Time taken to update frame in seconds</param>
void Animate::UpdateTextCoord(float deltaTime, float playRate, int rowToPlay)
{
	//Use delay to adjust play rate of the animation
	m_delay = m_delay + deltaTime;

	float playTime = m_durationData[m_frameToPlay];

	if (m_delay > playTime)
	{
		//Calculate starting position in sprite sheet based of the current frame
		glm::vec2 startLocation = glm::vec2(0, 0);

		//making sure the sprite frame value isn't more than the number of columns
		m_spriteFrame = m_spriteFrame > m_columns - 1 ? m_spriteFrame - m_columns : m_spriteFrame;
		startLocation.x = (1 / m_columns) * m_spriteFrame;

		startLocation.y = (1 / m_rows) * rowToPlay;

		//Updating texture co-ordinates
		float texCoords[] =
		{
			startLocation.x,						startLocation.y,
			startLocation.x + 1.0f / m_columns,		startLocation.y,
			startLocation.x + 1.0f / m_columns,		startLocation.y + 1.0f / m_rows,
			startLocation.x + 1.0f / m_columns,		startLocation.y + 1.0f / m_rows,
			startLocation.x,						startLocation.y + 1.0f / m_rows,
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

		m_frameToPlay = { rowToPlay, m_spriteFrame };

		m_spriteFrame++;
		m_delay = 0;

	}
}

/// <summary>
/// Setting up a dictionary to map a frame at a location on the spritesheet to how long it should be played.
/// Default play time is 1 second
/// </summary>
void Animate::GenerateFrameList()
{
	float time = 1.0f;

	for (int row = 0; row < m_rows; ++row)
	{
		for (int column = 0; column < m_columns; ++column)
		{
			std::pair<int, int> location = { row, column };

			m_durationData[location] = time;
		}
	}
}

/// <summary>
/// Edits how long a frame plays for within the spritesheet
/// </summary>
/// <param name="row">Row of frame to edit</param>
/// <param name="column">Column of frame to edit</param>
/// <param name="duration">New duration to play frame at location</param>
void Animate::SetFramePlayTime(int row, int column, float duration)
{
	std::pair<int, int> location = { row, column };

	m_durationData[location] = duration;
}
