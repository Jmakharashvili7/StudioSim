#pragma once
#include "BasicIncludes.h"

class Actor;

class Animate 
{
private: 
	/// <summary>
	/// Setting up a dictionary to map a frame at a location on the spritesheet to how long it should be played.
	/// Default play time is 1 second
	/// </summary>
	void GenerateFrameList();

public:
	Animate(Actor* target, int rows, int columns);
	~Animate();

	/// <summary>
	/// Animates a sprite using a row from a sprite sheet
	/// </summary>
	/// <param name="deltaTime">Delta time</param>
	/// <param name="playRate">Adjusts time taken to play frame by dividing frame duration by playrate</param>
	void UpdateTextCoord(float deltaTime);
	/// <summary>
	/// Edits how long a frame plays for within the spritesheet
	/// </summary>
	/// <param name="row">Row of frame to edit</param>
	/// <param name="column">Column of frame to edit</param>
	/// <param name="duration">New duration to play frame at location</param>
	void SetFramePlayTime(int row, int column, float duration);
	void SetRowToPlay(int row);
	/// <summary>
	/// Changes the played duration of a frame at a given row and column
	/// </summary>
	/// <param name="row">Row of frame to edit</param>
	/// <param name="column">Column of frame to edit</param>
	/// <param name="time">New duration to play frame</param>
	void EditFramePlayTime(int row, int column, float time);


	/// <summary>
	/// Gets total playtime of animation from a given row in the sprite sheet
	/// </summary>
	/// <param name="row"></param>
	/// <returns>Playtime in seconds</returns>
	float GetAnimationPlayTime(int row);

	inline void SetPlayRate(float inRate) { m_playRate = inRate; }
	inline int GetRowToPlay() { return m_rowToPlay; }

	inline int GetRows() { return m_rows; }
	inline void SetRows(int rows) { m_rows = rows; }

	inline int GetColumns() { return m_columns; }
	inline void SetColumns(int columns) { m_columns = columns; }

	

private:
	Actor* m_object;

	std::map<std::pair<int, int>, float> m_durationData;

	std::pair<int, int> m_frameToPlay;

	float m_delay;
	float m_rows;
	float m_columns;
	float m_playRate;

	int m_spriteFrame;
	int m_rowToPlay ;

};
