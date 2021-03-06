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
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

class HitboxManager
{
private:
	sf::RectangleShape box;
	sf::RectangleShape hurtBox;
	sf::Vector2f size;
	int frameCount;
	bool canMove;

public:


	HitboxManager(float width = 50.0f, float height = 50.0f);
	bool BoxCollision(sf::RectangleShape enemyBox);
	//template <typename T, typename U>
	void HurtBoxUse(sf::Vector2f size, int noOfFrames, sf::Vector2f playerPos, sf::Vector2f enemyPos, float playerWidth, int yOffset, int xOffset);
	void IsHurtAcitve();
	void Update(sf::Vector2f pos);
	void setHitboxCol(sf::Color col);

	sf::RectangleShape getBox();
	sf::RectangleShape getHurtBox();
	sf::Vector2f getSize();
	bool getCanMove();

};

