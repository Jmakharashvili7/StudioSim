//#pragma once
#include <fmod.h>
#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <map>
#include <string>
#include <vector>
#include <math.h>
#include "BasicIncludes.h"

using namespace std;

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

	//Maps
	typedef map<string, FMOD::Sound*> pSoundMap;
	typedef map<int, FMOD::Channel*> pChannelMap;

	void InitUpdate();

	//System, Studio System and Result
	FMOD::System* pSystem;
	FMOD::Studio::System* pStudioSystem;
	FMOD_RESULT m_Result;

	//Channels
	int ChannelID;

	//Calls to map
	pSoundMap m_SoundMap;
	//pBankMap m_BankMap;
	//pEventMap m_EventMap;
	pChannelMap m_ChannelsMap;

};

class AudioEngine
{
public:
	void Start();
	void Update();
	void Stop();

	//Variables
	
	//Loading Functions
	void LoadSound(const string& soundName, bool isloop, bool is3D);
	void UnloadingSound(const string& soundName);

	//Playing Functions
	void PlaySound(const string& soundName, const Vector2D& pos = Vector2D{ 0,0 }, float DBVolume = 0.0f);
	
	bool IsSoundPlaying(const string& soundName);
	
	//Volume Control
	void SetChannelVolume(int channelID, float volume);

	//Stop Functions
	void StopChannel(int channelID);

	//Calculation Functions
	float ChangingDBToVolume(float DB);
	float ChangingVolumeToDB(float volume);

	FMOD_VECTOR ChangingVectorToFmodVector(const Vector2D& pos);
};

