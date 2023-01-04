//#pragma once
#include <fmod.h>
#include <fmod.hpp>
#include <fmod_studio.hpp>
#include "BasicIncludes.h"

/// <summary>
/// Vector used to position the sound in the game
/// </summary>
struct Vector2D
{
	float x;
	float y;
};

/// <summary>
/// Responsible for calling FMOD API 
/// </summary>
struct Init
{
	Init();
	~Init();

	void InitUpdate();

	FMOD::System* pSystem;
	FMOD_RESULT m_Result;
};

class AudioEngine
{
	AudioEngine();
	
};

