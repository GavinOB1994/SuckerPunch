#pragma once
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
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

class Controller
{
private:
	int cIndex;

	int xAxis;

	bool b0curr;
	bool b0prev;

	bool b1curr;
	bool b1prev;

	bool b2curr;
	bool b2prev;

	bool b3curr;
	bool b3prev;

public:
	Controller(int contIndex);
	void update();

	bool b0Press();
	bool b1Press();
	bool b2Press();
	bool b3Press();

	int getX();
};

