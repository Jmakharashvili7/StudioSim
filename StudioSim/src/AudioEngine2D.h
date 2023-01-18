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
	FMOD::ChannelGroup* pSoundsGroup;
	FMOD::ChannelGroup* pTracksGroup;
	
	
	

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


/// <summary>
/// Function used to load sounds
/// </summary>
/// <param name="pathToSound"> ->Path to Sound e.g "StudioSim/Sounds/Quack.wav </param>
/// <param name="isloop"> ->Is the sound going to loop ? used here for the FMOD_MODE</param>
/// <param name="isStream"> ->Set to true if using a larger file</param>
	static void LoadSound(const string& pathToSound,
		bool is3D , bool isloop, bool isStream );
	
	static void UnloadSound(const string& pathToSound);
	
/// <summary>
/// Function used to play sound
/// </summary>
/// <param name="pathToSound">->File path: "Sounds/quackOuter.wav"  </param>
/// <param name="vectorPos">->Position of sound in game space: set to 0,0,0 for 2D </param>
/// <param name="is3D">->Does the sound need to be 3D </param>
/// <param name="isloop">->Is the sound looping</param>
/// <param name="isStream">->Set to true if it is a large sound</param>
/// <param name="volumeDB">->Change the volume </param>
/// <param name="pitch">->0.5: half pitch slow /1.0: unmodified pitch /2.0: dobule the pitch fast </param>
/// <returns></returns>
	static int PlaySound(const string& pathToSound, 
		const Vector3& vectorPosition,bool is3D , bool isloop, bool isStream, float volumeDB, float pitch);

	/// <summary>
	/// Use it for soundtrack
	/// </summary>
	/// <param name="pathToSound"></param>
	/// <param name="vectorPosition"></param>
	/// <param name="is3D"></param>
	/// <param name="isloop"></param>
	/// <param name="isStream"></param>
	/// <param name="volumeDB"></param>
	/// <param name="pitch"></param>
	/// <returns></returns>
	static int PlaySoundTrack(const string& pathToSound,
		const Vector3& vectorPosition, bool is3D, bool isloop, bool isStream, float volumeDB, float pitch);
/// <summary>
/// Convert DB to linear Volume
/// </summary>
/// <param name="DB"> -> Logarithmic unit used to measure sound level </param>
/// <returns> Returns the value of X to the power of Y </returns>
	static float ChangingDBToVolume(float DB);
/// <summary>
/// Convert Vector3 struct to FMOD vector 3
/// Used to set 3D position on the word
/// </summary>
/// <param name="vectorPos"></param>
/// <returns></returns>
	static FMOD_VECTOR VectorToFmod(const Vector3& vectorPos);
	static void StopTrackGroup();

	//Varaibles
	AudioEngine2D* pAudioEngine;



	//Helpers
	static int GetSoundID();

};

//https://ebookcentral.proquest.com/lib/staffordshire/reader.action?docID=4717687&query=Getting+Started+with+C%2B%2B+Audio+Programming+for+Game+Development#
//https://www.programmer-books.com/wp-content/uploads/2018/08/Game-Programming-in-C-Creating-3D-Games.pdf
//https://www.fmod.com/docs/2.02/api/white-papers-getting-started.html
//https://www.codyclaborn.me/tutorials/making-a-basic-fmod-audio-engine-in-c/