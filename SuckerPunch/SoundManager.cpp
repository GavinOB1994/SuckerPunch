#include "stdafx.h"
#include "SoundManager.h"
#include <iostream>


SoundManager::SoundManager(sf::Vector2f vel, sf::Vector2f listnerPos, sf::Vector2f source)
{
	//setup FMOD
	result = FMOD::System_Create(&FMODsys);         // Create the main system object.
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error!" << result << FMOD_ErrorString(result);
		exit(-1);
	}

	result = FMODsys->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.

	if (result != FMOD_OK)
	{
		std::cout << "FMOD error!" << result << FMOD_ErrorString(result);
		exit(-1);
	}

	//Load PUNCH sound
	result = FMODsys->createSound("../SuckerPunch/Sound/punch.wav", FMOD_DEFAULT, 0, &punch);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (%d) %s\n" << result;
		exit(-1);
	}
	//Load JUMP sound
	result = FMODsys->createSound("../SuckerPunch/Sound/jump.wav", FMOD_DEFAULT, 0, &jump);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (%d) %s\n" << result;
		exit(-1);
	}
	//Load BGM
	result = FMODsys->createSound("../SuckerPunch/Sound/bgm.mp3", FMOD_DEFAULT, 0, &bgm);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (%d) %s\n" << result;
		exit(-1);
	}
	//Load 3D sound
	result = FMODsys->createSound("../SuckerPunch/Sound/threed.mp3", FMOD_LOOP_NORMAL | FMOD_3D, 0, &threeDS);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (%d) %s\n" << result;
		exit(-1);
	}


	//STUFF FOR LISTNER
	listenervel = { vel.x, 0.0f, vel.y };
	//update position & velocity of listener
	//position of listener needed for spatial & reverb effects
	//velocity of listener needed for dopper effects
	listenerpos = { listnerPos.x, 0.0f, listnerPos.y };
	//final pair of parameters are forward direction and up direction of listener (not needed in 2D)
	FMODsys->set3DListenerAttributes(0, &listenerpos, &listenervel, 0, 0);

	//update position of sound
	if (threeD)
	{
		FMOD_VECTOR  sourcePos = { source.x, 0.0f, source.y };
		//the source is fixed so velocity is 0
		threeD->set3DAttributes(&sourcePos, 0);
	}

	
	result = FMODsys->createReverb(&reverb);
	FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_SEWERPIPE;
	reverb->setProperties(&prop);
	FMOD_VECTOR pos = { source.x, 0.0f, source.y };
	float mindist = 100.0f;
	float maxdist = 150.0f;
	reverb->set3DAttributes(&pos, mindist, maxdist);

	reverb->setActive(true);

	bgmPaused = false;
	tdsPaused = false;
	rvbPaused = false;
}

void SoundManager::playSound(FMOD::Sound *snd)
{
	FMOD::Channel *channel;

	FMODsys->playSound(FMOD_CHANNEL_FREE, snd, true, &channel);
	channel->setVolume(0.5f);           // Set the volume while it is paused
	channel->setPaused(false);          // This is where the sound really starts.
}

void SoundManager::loopBGM(FMOD::Sound *snd)
{
	FMODsys->playSound(FMOD_CHANNEL_FREE, snd, true, &background);
	background->setVolume(0.1f);           // Set the volume while it is paused
	background->setPaused(false);          // This is where the sound really starts.
	background->setMode(FMOD_LOOP_NORMAL);
}

void SoundManager::threeDSound(FMOD::Sound *snd)
{
	FMODsys->playSound(FMOD_CHANNEL_FREE, snd, true, &threeD);
	threeD->setPaused(false);          // This is where the sound really starts.
	threeD->setMode(FMOD_LOOP_NORMAL);
	//need this for sound fall off
	threeD->set3DMinMaxDistance(30, 1000);
}

void SoundManager::pauseBGM()
{
	if (bgmPaused)
	{
		background->setPaused(false);
		bgmPaused = false;
	}
	else
	{
		background->setPaused(true);
		bgmPaused = true;
	}
}

void SoundManager::pauseTDS()
{
	if (tdsPaused)
	{
		threeD->setPaused(false);
		tdsPaused = false;
	}
	else
	{
		threeD->setPaused(true);
		tdsPaused = true;
	}
}

void SoundManager::pauseRVB()
{
	if (rvbPaused)
	{
		reverb->setActive(false);
	}
	else
	{
		reverb->setActive(true);
	}
	rvbPaused = !rvbPaused;
}

void SoundManager::update(sf::Vector2f vel, sf::Vector2f listnerPos, sf::Vector2f source)
{
	//STUFF FOR LISTNER
	listenervel = { vel.x, 0.0f, vel.y };
	listenerpos = { listnerPos.x, 0.0f, listnerPos.y };
	FMODsys->set3DListenerAttributes(0, &listenerpos, &listenervel, 0, 0);
	if (threeD)
	{
		FMOD_VECTOR  sourcePos = { source.x, 0.0f, source.y };
		threeD->set3DAttributes(&sourcePos, 0);
	}

	FMOD_VECTOR pos = { source.x, 0.0f, source.y };
	float mindist = 100.0f;
	float maxdist = 150.0f;
	reverb->set3DAttributes(&pos, mindist, maxdist);

	FMODsys->update();
}