#pragma once

#include "BasicIncludes.h"
#include "fmod_studio.hpp"
#include "fmod.hpp"
#include "fmod_errors.h"


using namespace std;

struct Vector3
{
	float x;
	float y;
	float z;
};

/// <summary>
/// Struct For FMOD Implementation, used to separete from audio engine, to prevent weird bugs
/// </summary>
struct FmodImplementation
{
	FmodImplementation();
	~FmodImplementation();

	//Maps

	typedef map<string, FMOD::Sound*> SoundMap;
	//Channel is a playing instance of a Sound
	typedef map<int, FMOD::Channel*> ChannelMap;

	//Functions
	void Update();

	//Pointers and variables
	FMOD::System* pFmodSystem;

	SoundMap	m_SoundMap;
	ChannelMap	m_ChannelMap;

	int			m_NextChannelID;
};


/// <summary>
/// 2D Audio Engine Class
/// </summary>
class AudioEngine2D
{
public:

	static void Initialization();
	static void Update();
	static void Shutdown();
	static void LoadSound(const string& pathToSound,
		bool is3D , bool isloop, bool isStream );
	
	static int PlaySound(const string& pathToSound, 
		const Vector3& vectorPosition,bool is3D , bool isloop, bool isStream, float volumeDB);

	static float ChangingDBToVolume(float DB);

	static FMOD_VECTOR VectorToFmod(const Vector3& vectorPos);

	//Varaibles
	AudioEngine2D* pAudioEngine;




};

//https://ebookcentral.proquest.com/lib/staffordshire/reader.action?docID=4717687&query=Getting+Started+with+C%2B%2B+Audio+Programming+for+Game+Development#
//https://www.programmer-books.com/wp-content/uploads/2018/08/Game-Programming-in-C-Creating-3D-Games.pdf
//https://www.fmod.com/docs/2.02/api/white-papers-getting-started.html
//https://www.codyclaborn.me/tutorials/making-a-basic-fmod-audio-engine-in-c/