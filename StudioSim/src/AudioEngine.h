#pragma once
#include "fmod.hpp"
#include "fmod_dsp.h"
#include "fmod_dsp_effects.h"
#include "fmod_errors.h"

#include "BasicIncludes.h"

//#define _7_1_AUDIO
#define _5_1_AUDIO

const int SOUNDCOUNT = 50;
const int CHANNELCOUNT = 5;
const int DISTANCE = 1.0f; //Units per Meter

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

	//Functions
	void Update();

	//Variables
	FMOD::System* pSystem;
	FMOD::Sound* pSounds[SOUNDCOUNT];
	FMOD::Reverb3D* pReverb;
	FMOD::Channel* pChannels[CHANNELCOUNT];
	FMOD::ChannelGroup* pTestGroup;
	FMOD::ChannelGroup* pMasterGroup;
	FMOD::DSP* pDspFader;
	FMOD::DSP* pDspPan;
	

	
	float m_SoundVolume;
	float m_SoundtrackVolume;
	float m_Pitch;
	float m_MasterVolume;
	float m_MinDistance;
	float m_MaxDistance;

	unsigned int m_Version;

	FMOD_VECTOR m_ListenerPos;
	FMOD_VECTOR m_ReverbPos;

};

class AudioEngine
{
public:




	static void  Init();
	static void  Update();
	static void  Shutdown();
	static void	 CreateSound(const std::string& pathtoSound, 
		bool isLoop, bool is3D, bool isStream,
		FMOD_CREATESOUNDEXINFO* soundInfo, FMOD::Sound** sound);
	static void  CreateChannelGroup(const char* groupName, FMOD::ChannelGroup** channelGroup);
	static void  MasterChannelManager();
	static void  Play(FMOD::Sound* sound, FMOD::ChannelGroup* channelGroup, bool isPaused, FMOD::Channel** channel);
	static void  SetVolume(float soundtrackVolume, float soundsVolume);
	static void  SetPitch(float pitch);
	static void  MuteChannel(bool mute);
	static void  FadeIn(int channelID );
	static void  FadeOut(int channelID);
	static void  IsPlaying();
				 
		
	static float ChangingDBToVolume(float DB);

	static FMOD_VECTOR VectorToFmodVec(const Vec3& soundPo);



	static AudioEngine* pQuackAudio;

};

