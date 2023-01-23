#pragma once
#include "fmod.hpp"
#include "fmod_dsp.h"
#include "fmod_dsp_effects.h"
#include "fmod_errors.h"
#include <filesystem>
#include "BasicIncludes.h"

struct Vec3
{
	float x;
	float y;
	float z;

};

/// <summary>
/// Struct for FMOD implementation
/// </summary>
struct FmodInit
{
	FmodInit();
	~FmodInit();

	//Maps
	typedef std::map<std::string, FMOD::Sound*> SoundMap;
	typedef std::map<int, FMOD::Channel*> ChannelMap;

	//Functions
	void Update();

	//Variables
	FMOD::System* pSystem;
	
	SoundMap m_SoundMap;
	ChannelMap m_ChannelMap;

	int m_NextChannel;


};

class AudioEngine
{
public:




	static void  Init();
	static void  Update();
	static void  Shutdown();
	static void  LoadSound(const std::string& pathToSound, bool is3D, bool isLoop, bool isStream);
	static void  UnloadSound(const std::string& pathToSound);
				 
	static int	 PlaySound(const std::string& pathToSound, const Vec3& soundPos, bool is3D, bool isLoop, bool isStream, float volumeDB, float pitch);
		
	static FMOD_MODE SetMode(bool is3D, bool isLoop, bool isStream);

	static float ChangingDBToVolume(float DB);

	static FMOD_VECTOR VectorToFmodVec(const Vec3& soundPo);



	static AudioEngine* pQuackAudio;

};

