#pragma once
#include "fmod.hpp"
#include "fmod_dsp.h"
#include "fmod_errors.h"

#include "BasicIncludes.h"

using namespace std;

struct  Vec3
{
	float x;
	float y;
	float z;

};

class QuackAudio
{
public:
	QuackAudio();
	~QuackAudio();

	//FMOD FUNCTIONS
	void					InitFmod();
	void					LoadSound(const string& pathToSound,
							bool is3D, bool isLoop, bool isStream);
	void					UnloadSound(const string& pathToSound);

	int						PlaySound(const string& pathToSound,
							const Vec3& vecPos,
							bool is3D, bool isLoop, bool isStream, float volumeDB, float pitch);

	float					ChangingDBToVolume(float dB);

	

	FMOD_MODE				SetMode(bool is3D, bool isLoop, bool isStream);
	FMOD_VECTOR				VectorToFmodVc(const Vec3 & pos3D);
	 
	//Maps
	typedef					map<string, FMOD::Sound*> SoundMap;
	typedef					map<int, FMOD::Channel*> ChannelMap;

	//FMOD VARIABLES
	FMOD::System*			pSystem;
	FMOD::Reverb3D*			pReverb;
	FMOD::Channel*			pChannel;
	FMOD::DSP*				pDspEcho;
	FMOD::DSP*				pDspLowpass;
	FMOD::DSP*				pDspChannelHead;
	FMOD::DSPConnection*	pDspChannelConnection;
	FMOD::ChannelGroup*		pGroupChannel;
	
	FMOD_VECTOR				m_ReverbPosition;
	FMOD_VECTOR				m_ListenerPos;

	int						m_NextChannelID;

	bool					m_IsPlaying;

	float					m_ReverbMinDist;
	float					m_ReverbMaxDist;

	SoundMap				m_SoundMap;
	ChannelMap				m_ChannelMap;

private:

};

