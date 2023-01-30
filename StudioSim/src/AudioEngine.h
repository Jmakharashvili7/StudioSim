#pragma once
#include "fmod.hpp"
#include "fmod_dsp.h"
#include "fmod_dsp_effects.h"
#include "fmod_common.h"
#include "fmod_codec.h"
#include "fmod_output.h"
#include "fmod_errors.h"
#include <math.h>
#include <vector>
#include "BasicIncludes.h"

#define _7_1_AUDIO
//#define _5_1_AUDIO


const int DISTANCE = 1.0f; //Units per Meter

//Setting up override FMOD'S file system with callbacks

//FMOD_RESULT F_CALLBACK Open(const char* name, int code, unsigned int* fileSize, void** handle, void** userData)
//{
//	if (name)
//	{
//		FILE* pFile;
//
//		pFile = fopen(name, "rb");
//		if (!pFile)
//		{
//			return FMOD_ERR_FILE_NOTFOUND;
//		}
//
//		fseek(pFile, 0, SEEK_END);
//		*fileSize = ftell(pFile);
//		fseek(pFile, 0, SEEK_SET);
//
//		*userData = (void*)0x12345678;
//		*handle = pFile;
//	}
//
//	return FMOD_OK;
//};
//
//FMOD_RESULT F_CALLBACK Close(void* handle, void* userData)
//{
//	if (!handle)
//	{
//		return FMOD_ERR_INVALID_PARAM;
//	}
//
//	fclose((FILE*)handle);
//
//	return FMOD_OK;
//};
//
//FMOD_RESULT F_CALLBACK AsyncRead(FMOD_ASYNCREADINFO* info, void* userData)
//{
//	return; //PutReadRequestOntoQueue(info)
//};
//
//FMOD_RESULT F_CALLBACK AsyncCancel(void* handle, void* userData)
//{
//	return; //SearchQueueForFileHandleAndRemove(info);
//};



enum AudioState
{
	PLAYING,
	STOPPING,
	STOPPED
};

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

	//Maps
	typedef std::map<std::string, FMOD::Sound*> SoundMap;
	typedef std::map<int, FMOD::Channel*> ChannelMap;


	//Variables
	FMOD::System* pSystem;
	FMOD::Reverb3D* pReverb;
	FMOD::ChannelGroup* pSoundtracks;
	FMOD::ChannelGroup* pMasterGroup;
	FMOD::DSP* pDspFader;
	FMOD::DSP* pDspPan;
	
	int   m_NextChannelID;
	
	float m_SoundVolume;
	float m_SoundtrackVolume;
	float m_Pitch;
	float m_MasterVolume;
	float m_MinDistance;
	float m_MaxDistance;

	bool  m_StopRequested;
	bool  m_IsPlaying;

	unsigned int m_Version;

	FMOD_VECTOR m_ListenerPos;
	FMOD_VECTOR m_ReverbPos;
	FMOD_VECTOR m_Pos;
	FMOD_VECTOR m_Vel;

	SoundMap m_SoundMap;
	ChannelMap m_ChannelMap;

};


class AudioEngine
{
public:

	void  Init();
	void  Update();
	void  UpdateTest();
	void  Shutdown();
	
	//functions using map
	void CreateSound(const std::string& pathToSound,
		bool is3D = true, bool isLoop = false, bool isStream = false);
	void EraseSound(const std::string& pathToSound);
	int  PlaySound(const std::string& pathToSound,
		const Vec3& pos, float volume);
	
	void  SetVolume(int channelID, float volumeDB);
	void  SetMasterChannelVolume(float volumeDB);
	void  SetPitch(int channelID, float pitch);
	void  SetMasterChannelPitch(float pitch);
	void  SetChannelGroup(int channelID, FMOD::ChannelGroup* channelGroup);
	void  Set3DMinMax(const std::string& pathToSound, float min, float max);
	void  Set3DAttributes(int channelID, const FMOD_VECTOR* pos, const FMOD_VECTOR* vel);

	void  AddDsp(int channelID, int index, FMOD::DSP* dsp);

	void  MuteChannel(int channelID, bool mute);
	void  MuteMasterChannel(bool mute);

	void  Pause(int channelID, bool pause);
	void  FadeIn(int channelID, float fadeTime);
	void  FadeOut(int channelID, float fadeTime);
	
	void  CreateChannelGroup(const char* groupName, FMOD::ChannelGroup** channelGroup);
	void  MasterChannelManager();

	void  StopChannel(int channelID, float fadeTime);
				 
	float ChangingDBToVolume(float DB);

	FMOD_VECTOR VectorToFmodVec(const Vec3& soundPo);

	AudioState m_State;
};

