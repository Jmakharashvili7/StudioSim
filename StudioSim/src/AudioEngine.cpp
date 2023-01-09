#include "AudioEngine.h"

//FMOD construction 

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

	//Initialize Studio System
	m_Result = pStudioSystem->initialize(64, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL);
	if (m_Result != FMOD_OK)
	{
		std::cout << "ERROR INITIALIZING STUDIO SYSTEM: " << m_Result << endl;
		exit(-1);
	}

	//Gets core system
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
/// </summary>
void Init::InitUpdate()
{

}

//AudioEngine
