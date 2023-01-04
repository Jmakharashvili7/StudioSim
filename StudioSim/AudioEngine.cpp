#include "AudioEngine.h"

Init::Init()
{
	pSystem = nullptr;

	m_Result = FMOD::System_Create(&pSystem);

	//Error Check
	if (m_Result != FMOD_OK)
	{
		printf("Error initializing FMOD! (%d) %s\n", m_Result, FMOD_ERRORCALLBACK_INFO());
		exit(-1);
	}

	//Fmod Initialization
	m_Result = pSystem->init(512, FMOD_INIT_NORMAL, 0); 

	if(r)


}
