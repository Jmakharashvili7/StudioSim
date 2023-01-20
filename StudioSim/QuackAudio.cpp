#include "QuackAudio.h"

void QuackAudio::InitFmod()
{
	FMOD_RESULT result;
	
	result = FMOD::System_Create(&pSystem); //Creating main system
	if (result != FMOD_OK)
	{
		printf("Error creating FMOD main system: (%d) %s\n", result, FMOD_ErrorString(result));
	}

	//Reverb setup
	result = pSystem->createReverb3D(&pReverb);
	FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_CONCERTHALL;
	FMOD_VECTOR pos = m_ReverbPosition;
	FMOD_VECTOR listenerPos = m_ListenerPos;
	float minDist = m_ReverbMinDist;
	float maxDist = m_ReverbMaxDist;
	pReverb->setProperties(&prop);
	pReverb->set3DAttributes(&pos, minDist, maxDist);
	pSystem->set3DListenerAttributes(0, &listenerPos, 0, 0, 0);

	//Set 3D Sounds later 3D sounds setup

	//DPS setup
	pSystem->createDSPByType(FMOD_DSP_TYPE_ECHO, &pDspEcho);
	pSystem->createDSPByType(FMOD_DSP_TYPE_LOWPASS, &pDspLowpass);


	//Channel group setup
	pSystem->createChannelGroup("Sounds", &pGroupChannel);

	result = pSystem->init(512, FMOD_INIT_NORMAL, 0); //Init of FMOD
	if (result != FMOD_OK)
	{
		printf("Error Init FMOD: (%d) %s\n", result, FMOD_ErrorString(result));
	}
}

FMOD_MODE QuackAudio::SetMode(bool is3D, bool isLoop, bool isStream)
{
	FMOD_MODE fMode = FMOD_DEFAULT; // Look into FMOD_NONBLOCKING
	fMode |= is3D ? FMOD_3D : FMOD_2D;
	fMode |= isLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	fMode |= isStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

	return fMode;

}

QuackAudio::QuackAudio()
{
	pSystem = NULL;
	pReverb = NULL;
	m_IsPlaying = false;
	m_ReverbPosition = FMOD_VECTOR{ -10.0f , 0.0f, 0.0f };
	m_ListenerPos = FMOD_VECTOR{ 0.0f, 0.0f, -1.0f };
	m_ReverbMinDist = 10.0f;
	m_ReverbMaxDist = 20.0f;
	m_NextChannelID = 0;

	//Write error check, check FMOD SYSTEM CALLBACK
	pSystem->update();
}

QuackAudio::~QuackAudio()
{
	pSystem->release();
}

void QuackAudio::LoadSound(const std::string& pathToSound,
	bool is3D, bool isLoop, bool isStream)
{
	FMOD_RESULT result;

	//checking to avoid double loading
	auto foundSound = m_SoundMap.find(pathToSound);
	if (foundSound != m_SoundMap.end())
	{
		return;
	}

	FMOD_MODE fMode = FMOD_DEFAULT; // Look into FMOD_NONBLOCKING
	fMode |= is3D ? FMOD_3D : FMOD_2D;
	fMode |= isLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	fMode |= isStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

	FMOD::Sound* sound = nullptr;
	result = pSystem->createSound(pathToSound.c_str(),
		fMode,
		nullptr,
		&sound
	);
	if (result != FMOD_OK)
	{
		printf("Error creating sound: (%d) %s", result, FMOD_ErrorString(result));
		exit(-1);
	}
	if (sound)
	{
		m_SoundMap[pathToSound] = sound;
	}
}

void QuackAudio::UnloadSound(const std::string& pathToSound)
{
	auto foundSound = m_SoundMap.find(pathToSound);
	if (foundSound == m_SoundMap.end())
	{
		return;
	}
	foundSound->second->release();
	m_SoundMap.erase(foundSound);
}

int QuackAudio::PlaySound(const std::string& pathToSound,
	const Vec3& vecPos, 
	bool is3D, bool isLoop, bool isStream, float volumeDB, float pitch)
{
	FMOD_RESULT result;

	int channelID = m_NextChannelID;
	
	auto foundSound = m_SoundMap.find(pathToSound);
	if (foundSound == m_SoundMap.end())
	{
		LoadSound(pathToSound,
			is3D,
			isLoop,
			isStream);
		foundSound = m_SoundMap.find(pathToSound);
		if (foundSound == m_SoundMap.end())
		{
			return channelID;
		}
	}

	FMOD::Channel* channel = nullptr;
	pSystem->playSound(foundSound->second,
		nullptr,
		true,
		&channel
	);
	

	if (channel)
	{
		FMOD_MODE currentMode;
		foundSound->second->getMode(&currentMode);
		if (currentMode & FMOD_3D)
		{
			FMOD_VECTOR pos = VectorToFmodVc(vecPos);
			channel->set3DAttributes(&pos, nullptr);
			

		}
		channel->setVolume(ChangingDBToVolume(volumeDB));
		channel->setPaused(false);
		channel->setPitch(pitch);
		channel->setReverbProperties(0, 0.0f);
		channel->addDSP(0, pDspEcho);
		channel->setChannelGroup(pGroupChannel);
		pGroupChannel->addDSP(1, pDspLowpass);

		if (channel->isPlaying(&m_IsPlaying))
		{
			m_IsPlaying = true;
		}

		m_ChannelMap[channelID] = channel;
	}

	channel->getDSP(FMOD_CHANNELCONTROL_DSP_HEAD, &pDspChannelHead);
	pDspChannelHead->setChannelFormat(0, 0, FMOD_SPEAKERMODE_QUAD);

	float matrix[4][4] =
	{
		/*FL  FR    SL SR*/
		/*Row 0 = front left out*/		{ 0,  0,    0,  0},
		/*Row 1 = front right out*/		{ 0,  0,	0,  0},
		/*Row 2 = surround left out*/	{ 1,  0,	0,  0},
		/*Row 3 = surround right out*/	{ 0,  1,	0,  0}
	};
	pDspChannelHead->getOutput(0, 0, &pDspChannelConnection);
	pDspChannelConnection->setMixMatrix(&matrix[0][0], 4, 4);


	return channelID;
}


FMOD_VECTOR QuackAudio::VectorToFmodVc(const Vec3& pos3D)
{
	FMOD_VECTOR fmodV;
	fmodV.x = pos3D.x;
	fmodV.y = pos3D.y;
	fmodV.z = pos3D.z;

	return fmodV;
}

float QuackAudio::ChangingDBToVolume(float dB)
{
	return powf(10.0/*X*/, 0.5f * dB/*Y*/);
}