#include "pch.h"

#include "Animate.h"
#include "GameObject.h"
#include "Actor.h"

Animate::Animate(Actor* target, const AnimationData& animationData) : m_animationData(animationData)
{
	m_object = target;

	m_delay = 50.0f;
	m_spriteFrame = 0;

	m_rowToPlay = 0;
	m_playRate = 1.0f;

	GenerateFrameList();
}

Animate::~Animate()
{
	
}


void Animate::UpdateTextCoord(float deltaTime)
{
	//Use delay to adjust play rate of the animation
	m_delay = m_delay + deltaTime;

	float playTime = m_durationData[m_frameToPlay];

	if (m_delay > playTime/m_playRate)
	{
		//Calculate starting position in sprite sheet based of the current frame
		glm::vec2 startLocation = glm::vec2(m_frameToPlay.first, m_frameToPlay.second);

		//making sure the sprite frame value isn't more than the number of columns
		m_spriteFrame = m_spriteFrame > m_animationData.columns - 1 ? m_spriteFrame - m_animationData.columns : m_spriteFrame;
		startLocation.x = (1 / m_animationData.columns) * m_spriteFrame;

		startLocation.y = (1 / m_animationData.rows) * m_rowToPlay;

		
		//Updating texture co-ordinates
		m_object->GetGameObjectData()->texCoords =
		{
			startLocation.x,										startLocation.y,
			startLocation.x + 1.0f / m_animationData.columns,		startLocation.y,
			startLocation.x + 1.0f / m_animationData.columns,		startLocation.y + 1.0f / m_animationData.rows,
			startLocation.x + 1.0f / m_animationData.columns,		startLocation.y + 1.0f / m_animationData.rows,
			startLocation.x,										startLocation.y + 1.0f / m_animationData.rows,
			startLocation.x,										startLocation.y
		};
		m_object->UpdateVertexArray();

		m_frameToPlay = { m_rowToPlay, m_spriteFrame };

		m_spriteFrame++;
		m_delay = 0;

	}
}


void Animate::GenerateFrameList()
{
	float time = 1.0f;

	for (int row = 0; row < m_animationData.rows; ++row)
	{
		for (int column = 0; column < m_animationData.columns; ++column)
		{
			std::pair<int, int> location = { row, column };

			m_durationData[location] = time;
		}
	}
}


void Animate::SetFramePlayTime(int row, int column, float duration)
{
	std::pair<int, int> location = { row, column };

	m_durationData[location] = duration;
}

void Animate::SetRowToPlay(int row)
{
	m_rowToPlay = row;
	m_spriteFrame = 0;
	m_delay = 50.0f;
	
}


void Animate::EditFramePlayTime(int row, int column, float time)
{
	std::pair<int, int> frameLocation = { row, column };

	m_durationData[frameLocation] = time;
}


float Animate::GetAnimationPlayTime(int row)
{
	float playtime = 0.0f;

	for (int column = 0; column < m_animationData.columns; ++column)
	{
		std::pair<int, int> frame = { row, column };
		playtime += m_durationData[frame];
	}

	return playtime;
}
