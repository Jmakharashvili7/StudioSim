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
	typedef map<string, FMOD::Studio::Bank*> pBankMap;
	typedef map<string, FMOD::Studio::EventDescription*> pEventMap;

	void InitUpdate();

	//System, Studio System and Result

	/// <summary>
	/// Low Level FMOD system
	/// </summary>
	FMOD::System* pSystem;

	/// <summary>
	/// Fmod studio system
	/// </summary>
	FMOD::Studio::System* pStudioSystem;


	FMOD_RESULT m_Result;

	//Channels
	int ChannelID;

	//Calls to map
	pSoundMap m_SoundMap;
	pBankMap m_BankMap;
	pEventMap m_EventMap;
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

	/// <summary>
	/// This function is used to load sounds
	/// </summary>
	/// <param name="pathToSound"> ->Path to the sound </param>
	/// <param name="isloop"> ->Set to true if sound needs to loop </param>
	/// <param name="is3D"> ->Set to false and keep it if 2D game </param>
	/// <param name="isStream"> -> set to true if Larger Sounds, set to false if smaller sounds </param> 
	void LoadSound(const string& pathToSound, bool isloop, bool is3D, bool isStream);
	
	/// <summary>
	/// This function is used to load bank
	/// </summary>
	/// <param name="pathToSound"></param>
	void LoadBank(const string& pathToSound);

	void UnloadingSound(const string& pathToSound);

	//Playing Functions
	void PlaySound(const string& pathToSound, const Vector2D& pos = Vector2D{ 0,0 }, float DBVolume = 0.0f);
	
	bool IsSoundPlaying(const string& pathToSound);
	
	//Volume Control
	void SetChannelVolume(int channelID, float volume);

	//Stop Functions
	void StopChannel(int channelID);

	//Calculation Functions
	float ChangingDBToVolume(float DB);
	float ChangingVolumeToDB(float volume);

	FMOD_VECTOR ChangingVectorToFmodVector(const Vector2D& pos);

	FMOD_RESULT m_EngineResult;
};

//Books and reference
//https://www.programmer-books.com/wp-content/uploads/2018/08/Game-Programming-in-C-Creating-3D-Games.pdf
//https://www.fmod.com/docs/2.02/api/studio-guide.html