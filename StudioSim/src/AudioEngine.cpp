//#include "AudioEngine.h"
//
////Calculation Functions
//
///// <summary>
///// Convert DB to linear Volume
///// </summary>
///// <param name="DB"> -> Logarithmic unit used to measure sound level </param>
///// <returns> Returns the value of X to the power of Y </returns>
//float AudioEngine::ChangingDBToVolume(float DB)
//{
//	return powf(10.0/*X*/, 0.05f * DB/*Y*/);
//}
//
//
///// <summary>
///// Convert Linear Volume to DB
///// </summary>
///// <param name="volume"></param>
///// <returns> Returns the logarith to the base 10 of x </returns>
//float AudioEngine::ChangingVolumeToDB(float volume)
//{
//	return 20.0f * log10f(volume);
//}
//
///// <summary>
///// Converting Vector2D struct to FMOD's Vector2
///// </summary>
///// <param name="pos"> ->Position of the 2D sound</param>
///// <returns> Returns a FMOD Vector </returns>
////FMOD_VECTOR AudioEngine::ChangingVectorToFmodVector(const Vector2D& pos)
////{
////	FMOD_VECTOR fVector;
////	fVector.x = pos.x;
////	fVector.y = pos.y;
////
////	return fVector;
////}
//
////FMOD construction 
//
///// <summary>
///// Creating FMOD studio system, Initializing FMOD studio System, Getting Low Level core system
///// Error checking 
///// </summary>
//Init::Init()
//{
//	pLowLevelSystem = NULL;
//	pStudioSystem = NULL;
//
//	//Creates core system
//	m_Result = FMOD::Studio::System::create(&pStudioSystem);
//	if (m_Result != FMOD_OK)
//	{
//		std::cout << "ERROR CREATING STUDIO SYSTEM: " << m_Result << endl;
//		exit(-1);
//	}
//
//	//Initialize Studio System/ Witth studio System a connection with FMOD Studio can be made so live mixing can happen
//	m_Result = pStudioSystem->initialize(64, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL);
//	if (m_Result != FMOD_OK)
//	{
//		std::cout << "ERROR INITIALIZING STUDIO SYSTEM: " << m_Result << endl;
//		exit(-1);
//	}
//
//	//Gets core system / Used to handle lower level system
//	m_Result = pStudioSystem->getCoreSystem(&pLowLevelSystem);
//	if (m_Result != FMOD_OK)
//	{
//		std::cout << "ERROR GETTING CORE SYSTEM: " << m_Result << endl;
//		exit(-1);
//	}
//
//	
//}
// 
//
///// <summary>
///// Deleting and releasing memory
///// </summary>
//Init::~Init()
//{
//	pStudioSystem->unloadAll();
//	pStudioSystem->release();
//}
//
//
//
///// <summary>
///// Update Function for the initialization
///// ->Checks if a channel stopped playing, if yes, Destroy it
///// ->Call Fmod System update
///// </summary>
//void Init::InitUpdate()
//{
//	vector<pChannelMap::iterator> channelStopped;
//
//	// Loops channels map to check if channels stopped playing, if yes detroy it clearing up channel to use 
//	for (auto i = m_ChannelsMap.begin(), iEnd = m_ChannelsMap.end(); i != iEnd; i++)
//	{
//		bool isSoundPlaying = false;
//		i->second->isPlaying(&isSoundPlaying);
//
//		if (!isSoundPlaying)
//		{
//			channelStopped.push_back(i);
//		}
//	}
//	for (auto& i : channelStopped)
//	{
//		m_ChannelsMap.erase(i);
//	}
//
//	//Calls studio Update
//	m_Result = pStudioSystem->update();
//	if (m_Result != FMOD_OK)
//	{
//		std::cout << "ERROR UPDATING FMOD STUDIO SYSTEM: " << m_Result << endl;
//		exit(-1);
//	}
//
//	
//}
//
///// <summary>
///// Creating instance of the FMOD initialization
///// </summary>
//Init* pInit = nullptr;
//
//SoundEvent* pSoundEvent = nullptr;
//
////AudioEngine
//
////Create a new instance of the FMOD initialization
//void AudioEngine::Start()
//{
//	pInit = new Init();
//	pSoundEvent = new SoundEvent();
//
//	LoadBank("Master Bank.strings.bank");
//	LoadBank("Master Bank.bank");
//}
//
////Calls the update of the FMOD initialization
//void AudioEngine::Update()
//{
//
//	//Finding stopped events
//	std::vector<unsigned int> eventDone;
//	for (auto& i : pInit->m_EventInstanceMap)
//	{
//		FMOD::Studio::EventInstance* event = i.second;
//		//Getting state of the event
//		FMOD_STUDIO_PLAYBACK_STATE eventState;
//
//		event->getPlaybackState(&eventState);
//
//		if (eventState == FMOD_STUDIO_PLAYBACK_STOPPED)
//		{
//			//Releases evemt
//			event->release();
//			eventDone.emplace_back(i.first);
//		}
//
//	}
//	//Remove done events
//	for (auto i : eventDone)
//	{
//		pInit->m_EventInstanceMap.erase(i);
//	}
//
//	pInit->InitUpdate();
//	pInit->pStudioSystem->update();
//	//pInit->pLowLevelSystem->update();
//}
//
//void AudioEngine::Stop()
//{
//	delete pInit;
//	delete pSoundEvent;
//}
//
//
//void AudioEngine::LoadBank(const string& pathToSound)
//{
//	//Look for the sound in the map
//	auto foundSound = pInit->m_BankMap.find(pathToSound);
//
//	//Preventing double louading
//	if (foundSound != pInit->m_BankMap.end())
//	{
//		return;
//	}
//
//	//Loading Bank
//	FMOD::Studio::Bank* pBank = nullptr;
//
//	FMOD_RESULT m_result = pInit->pStudioSystem->loadBankFile(
//		pathToSound.c_str(), //File name of bank
//		FMOD_STUDIO_LOAD_BANK_NORMAL, // Normal Loading
//		&pBank // Saving pointer
//
//	);
//
//	//Needs to be constant
//	const int maxPathLenght = 64;
//
//	if (m_result == FMOD_OK)
//	{
//		//Adding bank to map
//		pInit->m_BankMap.emplace(pathToSound, pBank);
//		//Loading non-streaming sample data
//		pBank->loadSampleData();
//		//Number of events
//		int eventsNumber = 0;
//		pBank->getEventCount(&eventsNumber);
//
//		if (eventsNumber > 0)
//		{
//			//Getting list of event descriptions in this bank
//			std::vector<FMOD::Studio::EventDescription*> events(eventsNumber);
//			pBank->getEventList(events.data(), eventsNumber, &eventsNumber);
//			char eventName[maxPathLenght];
//
//			for (int i = 0; i < eventsNumber; i++)
//			{
//				FMOD::Studio::EventDescription* event = events[i];
//				//Getting path pf the event
//				event->getPath(
//					eventName, 
//					maxPathLenght, 
//					nullptr
//				);
//				//Add to map
//				pInit->m_EventMap.emplace(eventName, event);
//			}
//
//		}
//	}
//}
//
//void AudioEngine::UnloadingBank(const string& pathToSound)
//{
//	auto foundSound = pInit->m_BankMap.find(pathToSound);
//
//	//prevents double loading
//	if (foundSound == pInit->m_BankMap.end())
//	{
//		return;
//	}
//
//	m_EngineResult = foundSound->second->unload();
//	pInit->m_BankMap.erase(foundSound);
//}
//
//
//void AudioEngine::LoadSound(const string& pathToSound, bool isloop, bool is3D, bool isStream)
//{
//	//Look for the sound in the map
//	auto foundSound = pInit->m_SoundMap.find(pathToSound);
//	
//	//Prevents double loading
//	if (foundSound != pInit->m_SoundMap.end())
//	{
//		return;
//	}
//
//	FMOD_MODE mode = FMOD_DEFAULT;
//
//	mode = is3D ? FMOD_3D : FMOD_2D;
//	mode = isloop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
//	mode = isStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;
//
//	FMOD::Sound* pSound = nullptr;
//	m_EngineResult = pInit->pLowLevelSystem->createSound(
//		pathToSound.c_str(), // File name 
//		mode, // Mode
//		nullptr, //Extended information for creating the sound-> optinal 
//		&pSound // Save to pointer 
//	);
//	if (m_EngineResult != FMOD_OK)
//	{
//		std::cout << "ERROR CREATING SOUND: " << m_EngineResult << endl;
//	}
//	
//	if (pSound)
//	{
//		pInit->m_SoundMap[pathToSound] = pSound;
//	}
//	
//}
//
//void AudioEngine::UnloadingSound(const string& pathToSound)
//{
//	auto foundSound = pInit->m_SoundMap.find(pathToSound);
//	if (foundSound == pInit->m_SoundMap.end())
//	{
//		return;
//	}
//
//	foundSound->second->release();
//	pInit->m_SoundMap.erase(foundSound);
//}
//
//SoundEvent AudioEngine::PlayEvent(const string& eventName)
//{
//	unsigned int retID = 0;
//
//	auto foundEvent = pInit->m_EventMap.find(eventName);
//
//	if (foundEvent != pInit->m_EventMap.end())
//	{
//		//Instance of event 
//		FMOD::Studio::EventInstance* event = nullptr;
//
//		foundEvent->second->createInstance(&event);
//
//		if (event)
//		{
//			//start event instance
//			event->start();
//
//			//Get the next id, and add to map
//			int temp = pInit->m_NextID++;
//			
//			retID = temp;
//
//			pInit->m_EventInstanceMap.emplace(retID, event);
//
//			
//		}
//	}
//
//	return SoundEvent(this, retID);
//}
//
////Getters and Setters
//FMOD::Studio::EventInstance* AudioEngine::GetEventInstance(unsigned int ID)
//{
//	FMOD::Studio::EventInstance* eventInstance = nullptr;
//	auto it = pInit->m_EventInstanceMap.find(ID);
//	if (it != pInit->m_EventInstanceMap.end())
//	{
//		eventInstance = it->second;
//	}
//
//	return eventInstance;
//}
//
