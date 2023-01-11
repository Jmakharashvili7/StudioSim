////#pragma once
//#include <fmod.h>
//#include <fmod.hpp>
//#include <fmod_studio.hpp>
//#include <map>
//#include <unordered_map>
//#include <string>
//#include <vector>
//#include <math.h>
//#include "BasicIncludes.h"
//
//using namespace std;
//
//
///// <summary>
///// Responsible for calling FMOD API 
///// Bank -> A container for events, sample data and streaming data
///// Sample data is the raw audio data that events reference.
///// Streaming data is sample data that streams intor memory in small pieces at a time.
///// </summary>
//struct Init
//{
//	Init();
//	~Init();
//
//	//Maps
//
//	typedef map<string, FMOD::Sound*> pSoundMap;
//	typedef map<int, FMOD::Channel*> pChannelMap;
//	typedef map<string, FMOD::Studio::Bank*> pBankMap;
//	typedef map<string, FMOD::Studio::EventDescription*> pEventMap;
//	typedef map<unsigned int, FMOD::Studio::EventInstance*> pEventInstanceMap;
//
//	void InitUpdate();
//
//
//	//System, Studio System and Result
//
//	/// <summary>
//	/// Low Level FMOD system
//	/// </summary>
//	FMOD::System* pLowLevelSystem;
//
//	/// <summary>
//	/// Fmod studio system
//	/// </summary>
//	FMOD::Studio::System* pStudioSystem;
//
//
//	FMOD_RESULT m_Result;
//
//	//Channels
//	int ChannelID;
//
//	//Event ID
//	static int m_NextID;
//
//	//Calls to map
//	pSoundMap m_SoundMap;
//	pBankMap m_BankMap;
//	pEventMap m_EventMap;
//	pChannelMap m_ChannelsMap;
//	pEventInstanceMap m_EventInstanceMap;
//
//
//
//};
//
//
//
//
//class SoundEvent 
//{
//public:
//	SoundEvent();
//
//	//Returns true if associated event instance exists
//	bool IsAssociatedFMOD();
//	//Restart event from beggining
//	void RestartEvent();
//	//Stop event
//	void StopEvent(bool fadeout = true);
//	//Helper Functions
//
//	//Setters
//	void SetPause(bool pause);
//	void SetVolume(float volume);
//	void SetPitch(float pitch);
//	void SetParameter(const std::string& parameterName, float value);
//	//Getters
//	bool GetPause() const;
//
//	float GetVolume() const;
//	float GetPitch() const;
//	float GetParameter(const string& paramaterName);
//
//protected:
//	friend class AudioEngine;
//	SoundEvent(class AudioEngine* system, unsigned int id);
//private:
//	class AudioEngine* pAudioEngine;
//	unsigned int m_ID;
//
//	
//};
//
//class AudioEngine 
//{
//public:	
//	void Start();
//	void Update();
//	void Stop();
//
//	//Variables
//	
//
//	//Loading Functions
//
//	/// <summary>
//	/// This function is used to load sounds
//	/// </summary>
//	/// <param name="pathToSound"> ->Path to the sound </param>
//	/// <param name="isloop"> ->Set to true if sound needs to loop </param>
//	/// <param name="is3D"> ->Set to false and keep it if 2D game </param>
//	/// <param name="isStream"> -> set to true if Larger Sounds, set to false if smaller sounds </param> 
//	void LoadSound(const string& pathToSound, bool isloop, bool is3D, bool isStream);
//	void UnloadingSound(const string& pathToSound);
//	
//	/// <summary>
//	/// This function is used to load bank
//	/// </summary>
//	/// <param name="pathToSound"></param>
//	void LoadBank(const string& pathToSound);
//	void UnloadingBank(const string& pathToSound);
//
//	//Events
//	SoundEvent PlayEvent(const string& pathToSound);
//
//	FMOD::Studio::EventInstance* GetEventInstance(unsigned int ID);
//
//	//Calculation Functions
//	float ChangingDBToVolume(float DB);
//	float ChangingVolumeToDB(float volume);
//
//
//	FMOD_RESULT m_EngineResult;
//};
////Books and reference
////https://www.programmer-books.com/wp-content/uploads/2018/08/Game-Programming-in-C-Creating-3D-Games.pdf
////https://www.fmod.com/docs/2.02/api/studio-guide.html