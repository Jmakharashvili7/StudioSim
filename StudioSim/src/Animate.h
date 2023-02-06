#pragma once
#include "BasicIncludes.h"
#include "QuackDataTypes.h"

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
	Animate(Actor* target, const AnimationData& animationData);
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

	virtual inline void SetAnimationRows(const int newRowNumber) { m_animationData.rows = newRowNumber; }
	virtual inline void SetAnimationColumns(const int newColumnNumber) { m_animationData.columns = newColumnNumber; }
	virtual inline void SetIdleAnimationRow(const int newRow) { m_animationData.idleRow = newRow; }
	virtual inline void SetMoveAnimationRow(const int newRow) { m_animationData.runRow = newRow; }
	virtual inline void SetLightAttackAnimationRow(const int newRow) { m_animationData.lightAttackRow = newRow; }
	virtual inline void SetHeavyAttackAnimationRow(const int newRow) { m_animationData.heavyAttackRow = newRow; }
	virtual inline void SetSpecialAttackAnimationRow(const int newRow) { m_animationData.specialAttackRow = newRow; }
	virtual inline void SetDeathAnimationRow(const int newRow) { m_animationData.deathRow = newRow; }
	virtual inline void SetJumpAnimationRow(const int newRow) { m_animationData.jumpRow = newRow; }
	virtual inline void SetTakeHitAnimationRow(const int newRow) { m_animationData.takeHitRow = newRow; }
	virtual inline void SetAnimationStatus(const bool newAnimating) { m_animationData.banimated = newAnimating; }

private:
	Actor* m_object;

	std::map<std::pair<int, int>, float> m_durationData;

	std::pair<int, int> m_frameToPlay;

	AnimationData m_animationData = AnimationData();

	float m_delay;
	float m_playRate;

	int m_spriteFrame;
	int m_rowToPlay ;

};
