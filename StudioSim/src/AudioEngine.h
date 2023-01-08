//#pragma once
#include <fmod.h>
#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <string>
#include <iostream>
#include <map>
#include "BasicIncludes.h"

using namespace std;
/// <summary>
/// Vector used to position the sound in the game
struct Vector2D
{
	float x;
	float y;
};
/// </summary>

/// <summary>
/// Responsible for the initialization FMOD API 
struct Init
{
	Init();
	~Init();

	void InitUpdate();

	int m_ChannelID;

	/// <summary>
	/// Maps with file anme, key is the even or sound
	typedef map<string, FMOD::Sound*> SoundMap;
	typedef map<int, FMOD::Channel*> ChannelMap;
	typedef map<string, FMOD::Studio::EventInstance*> EventMap;
	typedef map<string, FMOD::Studio::Bank*> BankMap;
	/// </summary>

	SoundMap m_Sounds;
	ChannelMap m_Channels;
	EventMap m_Events;
	BankMap m_Banks;

	/// <summary>
	/// Fmod system and result
	FMOD::System* pSystem;
	FMOD::Studio::System* pStudioSystem;
	FMOD_RESULT m_Result;
	/// </summary>
};
/// </summary>

class AudioEngine
{
public:
	/// <summary>
	/// Audio Engine Setup and controll
	static void InitializingAudioEngine();
	static void UpdateAudioEngine();
	static void ShutDownAudioEngine();
	/// </summary>

	
	void LoadSound(const string& soundName, bool looping = false, bool is2D = false);
	void LoadEvent(const string& eventName);
	void LoadBank(const string& bankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags);
	void UnloadSound(const string& soundName);
	void PlayEvent(const string& eventName);
	void SetVolume(int channelID, float volume);
	void GetEventPar(const string& eventName, const string& parameterName, float pParameter);
	void SetEventPar(const string& eventName, const string& parameterName, float value);
	
	
	int PlaySound(const string& soundName, 
		const Vector2D& pos = Vector2D{ 0,0 }, float volume = 0.0f);

	bool EventPlaying(const string& eventName);

	float DBtoVolume(float db);
	float VolumetoDB(float volume);

	FMOD_VECTOR FmodVector(const Vector2D& pos);
	
};

