#include "AudioEngine2D.h"

FmodImplementation::FmodImplementation()
{
	FMOD_RESULT result;
	pFmodSystem = NULL;

	
	m_NextChannelID = 0;

	//Creating main system object
	result = FMOD::System_Create(&pFmodSystem);
	if (result != FMOD_OK)
	{
		printf("Error creating fmod system:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);

	}

	//Initialize FMOD
	result = pFmodSystem->init(512, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
	{
		printf("Error initializing fmod:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}

	//Initialize Channels group
	result = pFmodSystem->createChannelGroup("Sounds", &pSoundsGroup);
	if (result != FMOD_OK)
	{
		printf("Error creating Sounds group:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = pFmodSystem->createChannelGroup("Soundtracks", &pTracksGroup);
	if (result != FMOD_OK)
	{
		printf("Error creating SoundTrack group:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}

}

FmodImplementation::~FmodImplementation()
{
	pFmodSystem->release();
}

/// <summary>
/// Update Function for the initialization
/// ->Checks if a channel stopped playing, if yes, Destroy it
/// ->Call Fmod System update
/// </summary>
void FmodImplementation::Update()
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
		pFmodSystem->update();
	
}


FmodImplementation* pFmodSys;



void AudioEngine2D::Initialization()
{
	pFmodSys = new FmodImplementation;
	
	
}

void AudioEngine2D::Update()
{
	pFmodSys->Update();
	
	
}

void AudioEngine2D::Shutdown()
{
	delete pFmodSys;
}

//Maths Calculation

FMOD_VECTOR AudioEngine2D::VectorToFmod(const Vector3& vectorPos)
{
	FMOD_VECTOR vecFmod;
	vecFmod.x = vectorPos.x;
	vecFmod.x = vectorPos.x;
	vecFmod.x = vectorPos.x;
	return vecFmod;
}



float AudioEngine2D::ChangingDBToVolume(float DB)
{
	return powf(10.0/*X*/, 0.05f * DB/*Y*/);
}

void AudioEngine2D::LoadSound(const string& pathToSound,bool is3D, bool isloop, bool isStream)
{
	FMOD_RESULT result;

	std::cout << "Loading" << endl;

	//Checks to avoid double loading
	auto foundSound = pFmodSys->m_SoundMap.find(pathToSound);
	if (foundSound != pFmodSys->m_SoundMap.end())
	{
		return;
	}

	//Creating FMOD MODE
	FMOD_MODE fMode = FMOD_DEFAULT;
	fMode |= is3D ? FMOD_3D : FMOD_2D;
	fMode |= isloop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	fMode |= isStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

	FMOD::Sound* pSound = nullptr;
	result = pFmodSys->pFmodSystem->createSound(pathToSound.c_str(),
		fMode,
		nullptr,
		&pSound
	);
	// mama mia
	if (result != FMOD_OK)
	{
		printf("Error creating sound:  (%d) %s ", result, FMOD_ErrorString(result));
		exit(-1);
	}
	
	if (pSound)
	{
		
		pFmodSys->m_SoundMap[pathToSound] = pSound;
	}
}

void AudioEngine2D::UnloadSound(const std::string& pathToSound)
{
	auto foundSound = pFmodSys->m_SoundMap.find(pathToSound);
	if (foundSound == pFmodSys->m_SoundMap.end())
	{
		return;
	}

	foundSound->second->release();
	pFmodSys->m_SoundMap.erase(foundSound);
}


int AudioEngine2D::PlaySound(const std::string& pathToSound, 
	const Vector3& vectorPos, bool is3D, bool isloop, bool isStream, float volumeDB, float pitch)
{
	FMOD_RESULT result;

	int channelID = pFmodSys->m_NextChannelID++;
	auto foundSound = pFmodSys->m_SoundMap.find(pathToSound);

	if (foundSound == pFmodSys->m_SoundMap.end())
	{
		LoadSound(pathToSound, is3D, isloop, isStream);
		foundSound = pFmodSys->m_SoundMap.find(pathToSound);
		if (foundSound == pFmodSys->m_SoundMap.end())
		{
			return channelID;
		}
	}

	FMOD::Channel* pChannel = nullptr;
	pFmodSys->pFmodSystem->playSound(
		foundSound->second,
		pFmodSys->pSoundsGroup,
			true,
			&pChannel);


	
	if (pChannel)
	{
		FMOD_MODE currentMode;
		foundSound->second->getMode(&currentMode);
		if (currentMode & FMOD_3D)
		{
			FMOD_VECTOR pos = VectorToFmod(vectorPos);
			pChannel->set3DAttributes(&pos, nullptr);
		}
	
		pChannel->setVolume(ChangingDBToVolume(volumeDB));
		pChannel->setPaused(false);
		pChannel->setPitch(pitch);
		pFmodSys->m_ChannelMap[channelID] = pChannel;
	}
	return channelID;


}

int AudioEngine2D::PlaySoundTrack(const std::string& pathToSound,
	const Vector3& vectorPos, bool is3D, bool isloop, bool isStream, float volumeDB, float pitch)
{
	FMOD_RESULT result;

	int channelID = pFmodSys->m_NextChannelID++;
	auto foundSound = pFmodSys->m_SoundMap.find(pathToSound);

	if (foundSound == pFmodSys->m_SoundMap.end())
	{
		LoadSound(pathToSound, is3D, isloop, isStream);
		foundSound = pFmodSys->m_SoundMap.find(pathToSound);
		if (foundSound == pFmodSys->m_SoundMap.end())
		{
			return channelID;
		}
	}

	FMOD::Channel* pChannel = nullptr;
	pFmodSys->pFmodSystem->playSound(
		foundSound->second,
		pFmodSys->pTracksGroup,
		true,
		&pChannel);

	if (pChannel)
	{
		FMOD_MODE currentMode;
		foundSound->second->getMode(&currentMode);
		if (currentMode & FMOD_3D)
		{
			FMOD_VECTOR pos = VectorToFmod(vectorPos);
			pChannel->set3DAttributes(&pos, nullptr);
		}

		pChannel->setVolume(ChangingDBToVolume(volumeDB));
		pChannel->setPaused(false);
		pChannel->setPitch(pitch);
		pFmodSys->m_ChannelMap[channelID] = pChannel;
	}
	return channelID;

}

void AudioEngine2D::StopTrackGroup()
{
	pFmodSys->pTracksGroup->stop();
}


