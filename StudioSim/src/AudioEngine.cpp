#include "AudioEngine.h"

/// <summary>
/// Function initializing Fmod
/// </summary>
Init::Init()
{
	pSystem = nullptr;

	m_Result = FMOD::System_Create(&pSystem);

	//Error Check
	if (m_Result != FMOD_OK)
	{
		printf("Error creating the main system FMOD! (%d)\n", m_Result);
		exit(-1);
	}

	//Fmod Initialization
	m_Result = pSystem->init(512, FMOD_INIT_NORMAL, 0); 

	if (m_Result != FMOD_OK)
	{
		printf("Error initializing FMOD! (%d)", m_Result);
		exit(-1);
	}

}

/// <summary>
/// Checking if a channel stopped playing, if yes, destroy and clear a new channel
/// </summary>
void Init::InitUpdate()
{
	vector<ChannelMap::iterator> channelsThatStooped;

	for (auto i = m_Channels.begin(), iEnd = m_Channels.end(); i != iEnd; ++i)
	{
		bool playing = false;
		i->second->isPlaying(&playing);
		if (!playing)
		{
			channelsThatStooped.push_back(i);
		}
	}
	for (auto& i : channelsThatStooped)
	{
		m_Channels.erase(i);
	}
	
	pSystem->update();

}

Init* pInit = nullptr;

//Start of the creation of the audio engine

/// <summary>
/// Initializing Audio Engine;
/// </summary>
void AudioEngine::InitializingAudioEngine()
{
	pInit = new Init;
}

/// <summary>
/// Audio Engine Update
/// </summary>
void AudioEngine::UpdateAudioEngine()
{
	pInit->InitUpdate();
}

/// <summary>
/// loading Sound
/// </summary>
/// <param name="soundName"></param>
/// <param name="looping"></param>
/// <param name="is2D"></param>
void AudioEngine::LoadSound(const std::string& soundName, bool looping, bool is2D)
{
	auto foundSound = pInit->m_Sounds.find(soundName);

	///Sound description bitfields, bitwise OR them together for loading and describing sounds.
	FMOD_MODE fmodMode = FMOD_DEFAULT;
	fmodMode |= looping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	fmodMode |= is2D ? FMOD_2D : FMOD_3D;
	FMOD::Sound* pSound = nullptr;
	
	pInit->pSystem->createSound(soundName.c_str(), fmodMode, nullptr, &pSound);
	if (pSound)
	{
		pInit->m_Sounds[soundName] = pSound;
	}
}

/// <summary>
/// Unloading Sound
/// Unloading to free memory.
/// </summary>
/// <param name="soundName"></param>
void AudioEngine::UnloadSound(const std::string& soundName)
{
	auto foundSound = pInit->m_Sounds.find(soundName);

	if (foundSound == pInit->m_Sounds.end())
	{
		return;
	}

	foundSound->second->release();
	pInit->m_Sounds.erase(foundSound);

}


/// <summary>
/// Playing Sound
/// Checks if the sound is in the map, if not Load
/// </summary>
/// <param name="soundName"></param>
/// <param name="pos"></param>
/// <param name="volume"></param>
int AudioEngine::PlaySound(const string& soundName, const Vector2D& pos, float volume)
{
	int channelID = pInit->m_ChannelID++;
	auto foundSound = pInit->m_Sounds.find(soundName);
	if (foundSound == pInit->m_Sounds.end())
	{
		LoadSound(soundName);
		foundSound = pInit->m_Sounds.find(soundName);
		if (foundSound == pInit->m_Sounds.end())
		{
			return channelID;
		}
	}

	FMOD::Channel* pChannel = nullptr;
	pInit->pSystem->playSound(foundSound->second, nullptr, true, &pChannel);

	if (pChannel)
	{
		FMOD_MODE currentMode;
		foundSound->second->getMode(&currentMode);
		FMOD_VECTOR position = FmodVector(pos);
		pChannel->setVolume(volume);
		pChannel->setPaused(false);
		pInit->m_Channels[channelID] = pChannel;
			
	}

	return channelID;

}

/// <summary>
/// Setting Volume
/// </summary>
/// <param name="channelID"></param>
/// <param name="volume"></param>
void AudioEngine::SetVolume(int channelID, float volume)
{
	auto foundSound = pInit->m_Channels.find(channelID);
	if (foundSound == pInit->m_Channels.end())
	{
		return;
	}

	foundSound->second->setVolume(volume);
}

//Creating Events

/// <summary>
/// Loading banks, banks stores all the sound and information for each event
/// </summary>
/// <param name="bankName"></param>
/// <param name="flags"></param>
void AudioEngine::LoadBank(const std::string& bankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags)
{
	auto foundSound = pInit->m_Banks.find(bankName);
	if (foundSound != pInit->m_Banks.end())
	{
		return;
	}
	FMOD::Studio::Bank* pBank;
	pInit->pStudioSystem->loadBankFile(bankName.c_str(), flags, &pBank);
	if (pBank)
	{
		pInit->m_Banks[bankName] = pBank;
	}

}

/// <summary>
/// Each event store in a bank, Load Events in two parts Event Description and EventInstance
/// Description = information
/// Instance = plays the sound
/// </summary>
/// <param name="eventName"></param>
void AudioEngine::LoadEvent(const std::string& eventName)
{
	auto foundSound = pInit->m_Events.find(eventName);
	if (foundSound != pInit->m_Events.end())
	{
		return;
	}
	FMOD::Studio::EventDescription* pEvDescription = NULL;
	pInit->pStudioSystem->getEvent(eventName.c_str(), &pEvDescription);
	if (pEvDescription)
	{
		FMOD::Studio::EventInstance* pEvInstance = NULL;
		pEvDescription->createInstance(&pEvInstance);
		if (pEvInstance)
		{
			pInit->m_Events[eventName] = pEvInstance;
		}
	}
}

/// <summary>
/// Plays event, also checks if it was loaded, if not load it
/// </summary>
/// <param name="eventName"></param>
void AudioEngine::PlayEvent(const string& eventName)
{
	auto foundSound = pInit->m_Events.find(eventName);
	if (foundSound == pInit->m_Events.end())
	{
		LoadEvent(eventName);
		foundSound = pInit->m_Events.find(eventName);
		if (foundSound == pInit->m_Events.end())
		{
			return;
		}
	}
	foundSound->second->start();
}


/// <summary>
/// Check if event is playing 
/// </summary>
/// <param name="eventName"></param>
/// <returns></returns>
bool AudioEngine::EventPlaying(const string& eventName)
{
	auto foundSound = pInit->m_Events.find(eventName);
	if (foundSound == pInit->m_Events.end())
		return false;

	FMOD_STUDIO_PLAYBACK_STATE* pstate = NULL;
	if (foundSound->second->getPlaybackState(pstate) == FMOD_STUDIO_PLAYBACK_PLAYING)
	{
		return true;
	}

	return false;
}

//Maths functions that help 
FMOD_VECTOR AudioEngine::FmodVector(const Vector2D& pos)
{
	FMOD_VECTOR fVector;
	fVector.x = pos.x;
	fVector.y = pos.y;

	return fVector;
}

float AudioEngine::DBtoVolume(float db)
{
	return powf(10.0f, 0.05f * db);
}

float AudioEngine::VolumetoDB(float volume)
{
	return 20.0f * log10f(volume);
}


