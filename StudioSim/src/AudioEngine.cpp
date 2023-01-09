#include "AudioEngine.h"


//Calculation Functions

/// <summary>
/// Convert DB to linear Volume
/// </summary>
/// <param name="DB"> -> Logarithmic unit used to measure sound level </param>
/// <returns> Returns the value of X to the power of Y </returns>
float AudioEngine::ChangingDBToVolume(float DB)
{
	return powf(10.0/*X*/, 0.05f * DB/*Y*/);
}


/// <summary>
/// Convert Linear Volume to DB
/// </summary>
/// <param name="volume"></param>
/// <returns> Returns the logarith to the base 10 of x </returns>
float AudioEngine::ChangingVolumeToDB(float volume)
{
	return 20.0f * log10f(volume);
}

/// <summary>
/// Converting Vector2D struct to FMOD's Vector2
/// </summary>
/// <param name="pos"> ->Position of the 2D sound</param>
/// <returns> Returns a FMOD Vector </returns>
FMOD_VECTOR AudioEngine::ChangingVectorToFmodVector(const Vector2D& pos)
{
	FMOD_VECTOR fVector;
	fVector.x = pos.x;
	fVector.y = pos.y;

	return fVector;
}

//FMOD construction 

/// <summary>
/// Creating FMOD studio system, Initializing FMOD studio System, Getting Low Level core system
/// Error checking 
/// </summary>
Init::Init()
{
	pSystem = NULL;
	pStudioSystem = NULL;

	//Creates core system
	m_Result = FMOD::Studio::System::create(&pStudioSystem);
	if (m_Result != FMOD_OK)
	{
		std::cout << "ERROR CREATING STUDIO SYSTEM: " << m_Result << endl;
		exit(-1);
	}

	//Initialize Studio System/ Witth studio System a connection with FMOD Studio can be made so live mixing can happen
	m_Result = pStudioSystem->initialize(64, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL);
	if (m_Result != FMOD_OK)
	{
		std::cout << "ERROR INITIALIZING STUDIO SYSTEM: " << m_Result << endl;
		exit(-1);
	}

	//Gets core system / Used to handle lower level system
	m_Result = pStudioSystem->getCoreSystem(&pSystem);
	if (m_Result != FMOD_OK)
	{
		std::cout << "ERROR GETTING CORE SYSTEM: " << m_Result << endl;
		exit(-1);
	}


}

/// <summary>
/// Deleting and releasing memory
/// </summary>
Init::~Init()
{
	pStudioSystem->unloadAll();
	pStudioSystem->release();
}

/// <summary>
/// Update Function for the initialization
/// ->Checks if a channel stopped playing, if yes, Destroy it
/// ->Call Fmod System update
/// </summary>
void Init::InitUpdate()
{
	vector<pChannelMap::iterator> channelStopped;

	// Loops channels map to check if channels stopped playing, if yes detroy it clearing up channel to use 
	for (auto i = m_ChannelsMap.begin(), iEnd = m_ChannelsMap.end(); i != iEnd; i++)
	{
		bool isSoundPlaying = false;
		i->second->isPlaying(&isSoundPlaying);

		if (!isSoundPlaying)
		{
			channelStopped.push_back(i);
		}
	}
	for (auto& i : channelStopped)
	{
		m_ChannelsMap.erase(i);
	}

	//Calls studio Update
	m_Result = pStudioSystem->update();
	if (m_Result != FMOD_OK)
	{
		std::cout << "ERROR UPDATING FMOD STUDIO SYSTEM: " << m_Result << endl;
		exit(-1);
	}

	
}

/// <summary>
/// Creating instance of the FMOD initialization
/// </summary>
Init* pInit = nullptr;

//AudioEngine

//Create a new instance of the FMOD initialization
void AudioEngine::Start()
{
	pInit = new Init();
}

//Calls the update of the FMOD initialization
void AudioEngine::Update()
{
	pInit->InitUpdate();
}

void AudioEngine::LoadSound(const string& pathToSound, bool isloop, bool is3D, bool isStream)
{
	//Look for the sound in the map
	auto foundSound = pInit->m_SoundMap.find(pathToSound);
	
	//Prevents double loading
	if (foundSound != pInit->m_SoundMap.end())
	{
		return;
	}

	FMOD_MODE mode = FMOD_DEFAULT;

	mode = is3D ? FMOD_3D : FMOD_2D;
	mode = isloop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	mode = isStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

	FMOD::Sound* pSound = nullptr;
	m_EngineResult = pInit->pSystem->createSound(
		pathToSound.c_str(),
		mode,
		nullptr,
		&pSound
	);
	if (m_EngineResult != FMOD_OK)
	{
		std::cout << "ERROR CREATING SOUND: " << m_EngineResult << endl;
	}
	
	if (pSound)
	{
		pInit->m_SoundMap[pathToSound] = pSound;
	}
	

}
