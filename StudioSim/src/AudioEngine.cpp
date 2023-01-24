#include "AudioEngine.h"




FmodInit::FmodInit()
{
	FMOD_RESULT result;
	pSystem = nullptr;
	pDspFader = nullptr;
	pDspPan = nullptr;

	m_SoundVolume = 1.0f;
	m_SoundtrackVolume = 2.0f;
	m_Pitch = 1.0f;
	m_MasterVolume = 1.0f;
	m_MinDistance = 10.0f;
	m_MaxDistance = 20.0f;
	m_ListenerPos = { 0.0f, 0.0f, -1.0f * DISTANCE };
	m_ReverbPos = { -10.0f, 0.0f, 0.0f };
	
	result = FMOD::System_Create(&pSystem);
	if (result != FMOD_OK)
	{
		printf("Error creating fmod system:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = pSystem->getVersion(&m_Version);
	if(m_Version < FMOD_VERSION)
	{
		printf("Wrong FMOD Version: (%d) %s ", result, FMOD_ErrorString(result));
	}

#ifdef _5_1_AUDIO

	result = pSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0);
	if (result != FMOD_OK)
	{
		printf("Error setting 5.1 spatial audio:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = pSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT);
	if (result != FMOD_OK)
	{
		printf("Error setting output:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}


#endif // _5_1_AUDIO

#ifdef  _7_1_AUDIO

	result = pSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_7POINT1POINT4, 0);
	if (result != FMOD_OK)
	{
		printf("Error setting 7.1 spatial audio:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}


	result = pSystem->setOutput(FMOD_OUTPUTTYPE_WINSONIC);
	if (result != FMOD_OK)
	{
		printf("Error setting output:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);

#endif //  _7_1_AUDIO


	result = pSystem->init(512, FMOD_INIT_NORMAL | FMOD_INIT_PROFILE_ENABLE, 0);
	if (result != FMOD_OK)
	{
		printf("Error initializing fmod:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}

	//Setting up 3D sound
	result = pSystem->set3DSettings(1.0, DISTANCE, 1.0f);
	if (result != FMOD_OK)
	{
		printf("Error setting 3D settings:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = pSystem->set3DListenerAttributes(0, &m_ListenerPos, 0, 0, 0);
	if (result != FMOD_OK)
	{
		printf("Error setting 3D listener attributes:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}


	//Setting up Reverb
	result = pSystem->createReverb3D(&pReverb);
	if (result != FMOD_OK)
	{
		printf("Error creating Reverb:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = pReverb->set3DAttributes(&m_ReverbPos, m_MinDistance, m_MaxDistance);
	if (result != FMOD_OK)
	{
		printf("Error setting reverb 3D attributes:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}

	//Setting up Dsp
	result = pSystem->createDSPByType(FMOD_DSP_TYPE_FADER, &pDspFader);
	if (result != FMOD_OK)
	{
		printf("Error setting DSP Fader settings:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = pSystem->createDSPByType(FMOD_DSP_TYPE_PAN, &pDspPan);
	if (result != FMOD_OK)
	{
		printf("Error setting DSP pan settings:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}


}
FmodInit::~FmodInit()
{
	pSystem->release();
}

void FmodInit::Update()
{
	
	pSystem->update();
}

FmodInit* pFmod;

void AudioEngine::Init()
{
	pFmod = new FmodInit;


	FMOD_VECTOR pos = { 50.0f * DISTANCE, 0.0f, 0.0f };
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };

	CreateChannelGroup("Testgroup", &pFmod->pTestGroup);
	//pFmod->pDspFader->setActive(true);

	CreateSound("res/Sounds/a.mp3", true, true, false, nullptr, &pFmod->pSounds[0]);
	pFmod->pSounds[0]->set3DMinMaxDistance(0.5f * DISTANCE, 5000.0f * DISTANCE);
	pFmod->pChannels[0]->setChannelGroup(pFmod->pTestGroup);
	pFmod->pChannels[0]->addDSP(0, pFmod->pDspFader);
	pFmod->pChannels[0]->set3DAttributes(&pos, &vel);

	Play(pFmod->pSounds[0], nullptr, true, &pFmod->pChannels[0]); 
	//FadeIn(0);
	pFmod->pChannels[0]->setPaused(false);
	//FadeOut(0);
		


	SetVolume(2.0f, 2.0f);
	SetPitch(1.0f);
	MuteChannel(false);



}


void AudioEngine::Update()
{
	pFmod->Update();
}

void AudioEngine::Shutdown()
{
	delete pFmod;
}

void AudioEngine::CreateSound(const std::string& pathToSound, 
	bool isLoop, bool is3D, bool isStream, 
	FMOD_CREATESOUNDEXINFO* soundInfo, FMOD::Sound** sound)
{
	FMOD_RESULT result;
	FMOD_MODE defaultMode = FMOD_DEFAULT;
	defaultMode |= isLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	defaultMode |= is3D ? FMOD_3D : FMOD_2D;
	defaultMode |= isStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

	result = pFmod->pSystem->createSound(
		pathToSound.c_str(),
		defaultMode,
		soundInfo,
		sound
		);


	if (result != FMOD_OK)
	{
		printf("Error creating sound:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);

	}

}

void AudioEngine::CreateChannelGroup(const char* groupName, FMOD::ChannelGroup** channelGroup)
{
	FMOD_RESULT result;

	result = pFmod->pSystem->createChannelGroup(groupName, channelGroup);

	if (result != FMOD_OK)
	{
		printf("Error creating Channel group:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);

	}
}

void AudioEngine::MasterChannelManager()
{
	FMOD_RESULT result;

	result = pFmod->pSystem->getMasterChannelGroup(&pFmod->pMasterGroup);
	if (result != FMOD_OK)
	{
		printf("Error getting master Channel group:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);

	}

	//Setting other groups to be child of master group
	result = pFmod->pMasterGroup->addGroup(pFmod->pTestGroup);
	if (result != FMOD_OK)
	{
		printf("Error adding channel to master group:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}

}

void AudioEngine::SetVolume(float soundtrackVolume, float soundsVolume)
{
	FMOD_RESULT result;
	result = pFmod->pTestGroup->setVolume(ChangingDBToVolume(soundtrackVolume));
	if (result != FMOD_OK)
	{
		printf("Error setting up volume:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

void AudioEngine::SetPitch(float pitch)
{
	FMOD_RESULT result;
	result = pFmod->pTestGroup->setPitch(pitch);
	if (result != FMOD_OK)
	{
		printf("Error setting up pitch:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

void AudioEngine::MuteChannel(bool mute)
{
	if (mute == true)
	{
		bool mut = true;
		pFmod->pTestGroup->getMute(&mut);
		pFmod->pTestGroup->setMute(!mut);
	}
}

void  AudioEngine::FadeIn(int channelID)
{
	int rate = 0;
	unsigned long long dspClock;

	pFmod->pChannels[channelID]->getSystemObject(&pFmod->pSystem);
	pFmod->pSystem->getSoftwareFormat(&rate, 0, 0);
	pFmod->pChannels[channelID]->getDSPClock(0, &dspClock);
	pFmod->pChannels[channelID]->addFadePoint(dspClock, 0.0f);
	pFmod->pChannels[channelID]->addFadePoint(dspClock + (rate * 5), 1.0f);

}

void AudioEngine::FadeOut(int channelID)
{
	int rate = 0;
	unsigned long long dspClock;
	pFmod->pChannels[channelID]->getSystemObject(&pFmod->pSystem);
	pFmod->pSystem->getSoftwareFormat(&rate, 0, 0);
	pFmod->pChannels[channelID]->getDSPClock(0, &dspClock);
	pFmod->pChannels[channelID]->addFadePoint(dspClock, 1.0f);
	pFmod->pChannels[channelID]->addFadePoint(dspClock + (rate * 5), 0.0f);
	pFmod->pChannels[channelID]->setDelay(0, dspClock + (rate * 5), true);


}

void AudioEngine::Play(FMOD::Sound* sound, FMOD::ChannelGroup* channelGroup, bool isPaused, FMOD::Channel** channel)
{
	FMOD_RESULT result;

	result = pFmod->pSystem->playSound(sound, channelGroup, isPaused, channel);
	

	if (result != FMOD_OK)
	{
		printf("Error adding channel to master group:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}

}

FMOD_VECTOR  AudioEngine::VectorToFmodVec(const Vec3& soundPo) 
{ 
	FMOD_VECTOR vecFmod; 
	vecFmod.x = soundPo.x; 
	vecFmod.y = soundPo.y; 
	vecFmod.z = soundPo.z; 
	return vecFmod; 
}

float AudioEngine::ChangingDBToVolume(float DB)
{
	return powf(10.0/*X*/, 0.05f * DB/*Y*/);
}

