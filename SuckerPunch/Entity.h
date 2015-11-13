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
#include "HitboxManager.h"

class Entity
{
public:
	Entity(int x, int y);

	//Consts
	const float MAXVEL = 20;
	const float GRAVITY = 3;
	const float DECELERATION = 0.75f;
	const float MOVESPEED = 5;

	//Updates
	void Update();

	//Player actions
	void Attack(sf::Vector2f size, int noOfFrames, sf::Vector2f playerPos, sf::Vector2f enemyPos);
	void Jump(float vel);
	void MoveX(int x);
	void MoveY(int y);
	void Accelerate(sf::Vector2f vec);
	void Accelerate(float x, float y);

	//Getters and setters for Position
	sf::Vector2f GetPos();
	void SetPos(float x, float y);
	void SetPos(sf::Vector2f p);

	//Getters and setters for Velocity
	sf::Vector2f GetVel();
	void SetVel(float x, float y);
	void SetVel(sf::Vector2f v);

	//Getters and setters for Hitbox
	HitboxManager getHitbox();
	void setHitboxCol(sf::Color col);

	//Getters and setters for Health
	int getHealth();
	void setHealth(int h);

	//Getters and setters for Cooldown
	int getCooldown();
	void setCooldown(int i);

private:
	HitboxManager hitbox;

	sf::Texture texture;

	sf::Vector2f pos;
	sf::Vector2f vel; //the x component if this is the speed variable

	int width;
	int height;
	int health;
	int speed;
	int cooldown;
};

