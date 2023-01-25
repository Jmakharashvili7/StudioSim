#pragma once
#include "fmod.hpp"
#include "fmod_dsp.h"
#include "fmod_dsp_effects.h"
#include "fmod_errors.h"

#include "BasicIncludes.h"

//#define _7_1_AUDIO
#define _5_1_AUDIO

const int SOUNDCOUNT = 1;
const int CHANNELCOUNT = 1;
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

	bool  m_IsPlaying;

	unsigned int m_Version;

	FMOD_VECTOR m_ListenerPos;
	FMOD_VECTOR m_ReverbPos;
	FMOD_VECTOR m_Pos;
	FMOD_VECTOR m_Vel;

};

class AudioEngine
{
public:

	void  Init();
	void  Update();
	void  Shutdown();
	void	 CreateSound(const std::string& pathtoSound, 
		bool isLoop, bool is3D, bool isStream,
		FMOD_CREATESOUNDEXINFO* soundInfo, FMOD::Sound** sound);
	void  CreateChannelGroup(const char* groupName, FMOD::ChannelGroup** channelGroup);
	void  MasterChannelManager();
	void  Play(FMOD::Sound* sound, FMOD::ChannelGroup* channelGroup, bool isPaused, FMOD::Channel** channel);
	void  SetVolume(int channelID, float volumeDB);
	void  SetMasterChannelVolume(float volumeDB);
	void  SetPitch(int channelID, float pitch);
	void  SetMasterChannelPitch(float pitch);
	void  SetChannelGroup(int channelID, FMOD::ChannelGroup* channelGroup);
	void  Set3DMinMax(int soundID,float min, float max);
	void  Set3DAttributes(int channelID, const FMOD_VECTOR* pos, const FMOD_VECTOR* vel);
	void  AddDsp(int channelID, int index, FMOD::DSP* dsp);
	void  MuteChannel(int channelID, bool mute);
	void  MuteMasterChannel(bool mute);
	void  Pause(int channelID, bool pause);
	void  FadeIn(int channelID, float fadeTime );
	void  FadeOut(int channelID, float fadeTime );
	
	bool  IsPlaying(int channelID);
				 
	float ChangingDBToVolume(float DB);

	FMOD_VECTOR VectorToFmodVec(const Vec3& soundPo);
};

