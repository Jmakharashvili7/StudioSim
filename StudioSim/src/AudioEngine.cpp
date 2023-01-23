#include "AudioEngine.h"




FmodInit::FmodInit()
{
	FMOD_RESULT result;
	pSystem = nullptr;
	m_NextChannel = 0;
	const std::string  a = "sex";

	result = FMOD::System_Create(&pSystem);
	if (result != FMOD_OK)
	{
		printf("Error creating fmod system:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = pSystem->init(512, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
	{
		printf("Error initializing fmod:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}
}
FmodInit::~FmodInit()
{
	pSystem->release();
}

void FmodInit::Update()
{
	std::vector<ChannelMap::iterator> pChannelStopped;
	for (auto i = m_ChannelMap.begin(), iEnd = m_ChannelMap.end(); i != iEnd; i++)
	{
		bool isChannelPLaying = false;
		i->second->isPlaying(&isChannelPLaying);
		if (!isChannelPLaying)
		{
			pChannelStopped.push_back(i);
		}
	}
	for (auto& i : pChannelStopped)
	{
		m_ChannelMap.erase(i);
	}
	pSystem->update();
}

FmodInit* pFmod;

void AudioEngine::Init()
{
	pFmod = new FmodInit;
}


void AudioEngine::Update()
{
	pFmod->Update();
}

void AudioEngine::Shutdown()
{
	delete pFmod;
}

void AudioEngine::LoadSound(const std::string& pathToSound, bool is3D, bool isloop, bool isStream)
{
	FMOD_RESULT result;

	//Check to avoid double loading
	auto found = pFmod->m_SoundMap.find(pathToSound);
	if (found != pFmod->m_SoundMap.end())
	{
		return;
	}

	FMOD_MODE defaultMode = FMOD_DEFAULT;
	defaultMode |= is3D ? FMOD_3D : FMOD_2D;
	defaultMode |= isloop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	defaultMode |= isStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

	FMOD::Sound* sound = nullptr;
	result = pFmod->pSystem->createSound(
		pathToSound.c_str(),
		defaultMode,
		nullptr,
		&sound);

	if (result != FMOD_OK)
	{
		printf("Error creating sound:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);

	}
	if (sound)
	{
		pFmod->m_SoundMap[pathToSound] = sound;
	}
}

void AudioEngine::UnloadSound(const std::string& pathToSound)
{
	auto foundSound = pFmod->m_SoundMap.find(pathToSound);
	if (foundSound == pFmod->m_SoundMap.end())
	{
		return;
	}

	foundSound->second->release();
	pFmod->m_SoundMap.erase(foundSound);
}

int AudioEngine::PlaySound(const std::string& pathToSound, const Vec3& soundPos,
	bool is3D, bool isLoop, bool isStream, float volumeDB, float pitch)
{
	FMOD_RESULT result;

	int channelID = pFmod->m_NextChannel++;

	auto found = pFmod->m_SoundMap.find(pathToSound);

	if (found == pFmod->m_SoundMap.end())
	{
		LoadSound(pathToSound, 
			is3D, 
			isLoop, 
			isStream);
		found = pFmod->m_SoundMap.find(pathToSound);
		if (found == pFmod->m_SoundMap.end())
		{
			return channelID;
		}
	}

	FMOD::Channel* channel = nullptr;
	pFmod->pSystem->playSound(
		found->second,
		nullptr,
		true,
		&channel);
	
	if (channel)
	{
		FMOD_MODE tempMode;
		found->second->getMode(&tempMode);
		if (tempMode & FMOD_3D)
		{
			FMOD_VECTOR pos = VectorToFmodVec(soundPos);
			channel->set3DAttributes(&pos, nullptr);
		}

		channel->setVolume(ChangingDBToVolume(volumeDB));
		channel->setPaused(false);
		channel->setPitch(pitch);
		pFmod->m_ChannelMap[channelID] = channel;

		
		
	}
	

	return channelID;
}

FMOD_MODE AudioEngine::SetMode(bool is3D, bool isLoop, bool isStream)
{
	FMOD_MODE defaultMode = FMOD_DEFAULT;
	defaultMode |= is3D ? FMOD_3D : FMOD_2D;
	defaultMode |= isLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	defaultMode |= isStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;
			
	return defaultMode;
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

//https://github.com/seandenigris/FMODExample/blob/master/Fmod%20Sample/FMOD%20Programmers%20API/api/lowlevel/examples/channel_groups.cpp