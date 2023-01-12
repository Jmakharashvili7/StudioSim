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

/// <summary>
/// Convert Vector3 struct to FMOD vector 3
/// Used to set 3D position on the word
/// </summary>
/// <param name="vectorPos"></param>
/// <returns></returns>
FMOD_VECTOR AudioEngine2D::VectorToFmod(const Vector3& vectorPos)
{
	FMOD_VECTOR vecFmod;
	vecFmod.x = vectorPos.x;
	vecFmod.x = vectorPos.x;
	vecFmod.x = vectorPos.x;
	return vecFmod;
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

/// <summary>
	/// Function used to load sounds
	/// </summary>
	/// <param name="pathToSound"> ->Path to Sound e.g "StudioSim/Sounds/Quack.wav </param>
	/// <param name="isloop"> ->Is the sound going to loop ? used here for the FMOD_MODE</param>
	/// <param name="isStream"> ->Set to true if using a larger file</param>
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

/// <summary>
/// Function used to play sound
/// </summary>
/// <param name="pathToSound"> ->Path to Sound e.g "StudioSim/Sounds/Quack.wav</param>
/// <param name="isloop"> ->Should the sound loop when it ends ?</param>
/// <param name="isStream"> ->Set to true if using a larger file</param>
/// <param name="volumeDB"> ->Volume of the sound</param>
/// <returns></returns>
int AudioEngine2D::PlaySound(const std::string& pathToSound, 
	const Vector3& vectorPos, bool is3D, bool isloop, bool isStream, float volumeDB)
{
	FMOD_RESULT result;
	std::cout << "Playing" << endl;

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
			nullptr,
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
		pFmodSys->m_ChannelMap[channelID] = pChannel;
	}
	return channelID;


}

