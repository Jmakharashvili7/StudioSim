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
		std::cout << "Error creating fmod system:  (%d) %s ", result, FMOD_ErrorString(result);
		exit(-1);

	}

	//Initialize FMOD
	result = pFmodSystem->init(512, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
	{
		std::cout << "Error initializing fmod:  (%d) %s ", result, FMOD_ErrorString(result);
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
	for (auto i = m_ChannelMap.begin(), iEnd = m_ChannelMap.end(); i != iEnd; ++i)
	{
		bool isChannelPLaying = false;
		i->second->isPlaying(&isChannelPLaying);
		if (!isChannelPLaying)
		{
			pChannelStopped.push_back(i);
		}
		for (auto& i : pChannelStopped)
		{
			m_ChannelMap.erase(i);
		}
		pFmodSystem->update();
	}
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

/// <summary>
/// Convert DB to linear Volume
/// </summary>
/// <param name="DB"> -> Logarithmic unit used to measure sound level </param>
/// <returns> Returns the value of X to the power of Y </returns>
float AudioEngine2D::ChangingDBToVolume(float DB)
{
	return powf(10.0/*X*/, 0.05f * DB/*Y*/);
}


void AudioEngine2D::LoadSound(const string& pathToSound, bool isloop, bool isStream)
{
	FMOD_RESULT result;

	auto foundSound = pFmodSys->m_SoundMap.find(pathToSound);
	if (foundSound != pFmodSys->m_SoundMap.end())
	{
		return;
	}

	//Creating FMOD MODE
	FMOD_MODE fMode = FMOD_DEFAULT;
	fMode = isloop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	fMode = isStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

	FMOD::Sound* pSound = nullptr;
	result = pFmodSys->pFmodSystem->createSound(pathToSound.c_str(),
		fMode,
		nullptr,
		&pSound
	);
	//
	if (result != FMOD_OK)
	{
		std::cout << "Error creating sound:  (%d) %s ", result, FMOD_ErrorString(result);
		exit(-1);
	}
	
	if (pSound)
	{
		pFmodSys->m_SoundMap[pathToSound] = pSound;
	}
}

int AudioEngine2D::PlaySound(const std::string& pathToSound, bool isloop, bool isStream, float volumeDB)
{
	FMOD_RESULT result;

	int channelID = pFmodSys->m_NextChannelID++;
	auto foundSound = pFmodSys->m_SoundMap.find(pathToSound);

	if (foundSound == pFmodSys->m_SoundMap.end())
	{
		LoadSound(pathToSound, isloop, isStream);
		foundSound = pFmodSys->m_SoundMap.find(pathToSound);
		if (foundSound == pFmodSys->m_SoundMap.end())
		{
			return channelID;
		}
	}

	FMOD::Channel* pChannel = nullptr;
	pFmodSys->pFmodSystem->playSound(
		foundSound->second,
		nullptr,
		true,
		&pChannel);
	if (pChannel)
	{
		pChannel->setVolume(ChangingDBToVolume(volumeDB));
		pChannel->setPaused(false);
		pFmodSys->m_ChannelMap[channelID] = pChannel;
	}
	return channelID;


}

