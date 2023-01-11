#pragma once
#ifndef AUDIO_ENGINE_2D
#define AUDIO_ENGINE_2D

#include "fmod_studio.hpp"
#include "fmod.hpp"
#include "fmod_errors.h"
#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include <map>

#endif
using namespace std;

/// <summary>
/// Struct For FMOD Implementation, used to separete from audio engine, to prevent weird bugs
/// </summary>
struct FmodImplementation
{
	FmodImplementation();
	~FmodImplementation();

	//Maps
	typedef map<string, FMOD::Sound*> SoundMap;
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

	/// <summary>
	/// Function used to load sounds
	/// </summary>
	/// <param name="pathToSound"> ->Path to Sound e.g "StudioSim/Sounds/Quack.wav </param>
	/// <param name="isloop"> ->Is the sound going to loop ? used here for the FMOD_MODE</param>
	/// <param name="isStream"> ->Set to true if using a larger file</param>
	void LoadSound(const string& pathToSound, bool isloop, bool isStream);
	//
	/// <summary>
	/// Function used to play sound
	/// </summary>
	/// <param name="pathToSound"> ->Path to Sound e.g "StudioSim/Sounds/Quack.wav</param>
	/// <param name="isloop"> ->Should the sound loop when it ends ?</param>
	/// <param name="isStream"> ->Set to true if using a larger file</param>
	/// <param name="volumeDB"> ->Volume of the sound</param>
	/// <returns></returns>
	int PlaySound(const string& pathToSound, bool isloop, bool isStream, float volumeDB);


	/// <summary>
	/// Changes DB to volume
	/// </summary>
	/// <param name="DB"></param>
	/// <returns></returns>
	float ChangingDBToVolume(float DB);


};

//https://ebookcentral.proquest.com/lib/staffordshire/reader.action?docID=4717687&query=Getting+Started+with+C%2B%2B+Audio+Programming+for+Game+Development#
//https://www.programmer-books.com/wp-content/uploads/2018/08/Game-Programming-in-C-Creating-3D-Games.pdf
//https://www.fmod.com/docs/2.02/api/white-papers-getting-started.html
//https://www.codyclaborn.me/tutorials/making-a-basic-fmod-audio-engine-in-c/