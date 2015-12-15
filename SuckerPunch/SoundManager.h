#pragma once
#include "stdafx.h"
#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-network-d.lib")
#else
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-audio.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-network.lib")
#endif
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
//FMOD includes
#pragma comment(lib,"fmodex_vc.lib")
#include "fmod.hpp"
#include "fmod_errors.h"

class SoundManager
{
private:
	FMOD::Sound *punch;
	FMOD::Sound *jump;
	FMOD::Sound *bgm;
	FMOD::Sound *threeDS;
	FMOD::Sound *woosh;

	FMOD::Reverb *reverb;

	FMOD_VECTOR  listenervel;
	FMOD_VECTOR  listenerpos;

	FMOD::Channel *background;
	FMOD::Channel *threeD;

	FMOD::System *FMODsys; //will point to the FMOD system
	FMOD_RESULT result;

	bool bgmPaused;
	bool tdsPaused;
	bool rvbPaused;

public:
	SoundManager(sf::Vector2f vel, sf::Vector2f listnerPos, sf::Vector2f source);
	void playSound(FMOD::Sound *snd);
	void threeDSound(FMOD::Sound *snd);
	void loopBGM(FMOD::Sound *snd);
	void pauseBGM();
	void pauseTDS();
	void pauseRVB();
	void update(sf::Vector2f vel, sf::Vector2f listnerPos, sf::Vector2f source);

	FMOD::Sound* getPunch();
	FMOD::Sound* getJump();
	FMOD::Sound* getBGM();
	FMOD::Sound* getThreeDS();
	FMOD::Sound* getWoosh();
};

