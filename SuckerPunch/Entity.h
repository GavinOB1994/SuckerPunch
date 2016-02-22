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
#include "HealthBar.h"

class Entity
{
public:
	Entity(float x, float y);

	HealthBar<float> healthBar; //It is crucial that you delclare the type inside the angle brackets e.g. <int> , <float> , <double>

	//Consts
	const float MAXVEL = 20;
	const float GRAVITY = 3;
	const float DECELERATION = 0.75f;
	const float MOVESPEED = 5;
	const float WIDTH = 100;
	const float HEIGHT = 200;

	//Updates
	void Update();

	//Player actions
	void Attack(sf::Vector2f size, int noOfFrames, sf::Vector2f playerPos, sf::Vector2f enemyPos, float playerWidth, int yOffset, int xOffset);
	void Jump(float vel);
	void MoveX(int x);
	void MoveY(int y);
	void Accelerate(sf::Vector2f vec);
	void Accelerate(float x, float y);
	void Reset(int x, int y);

	//Getters and setters for Position
	sf::Vector2f GetPos();
	template <typename T, typename U> //using template func
	void SetPos(T x, U y);
	void SetPos(sf::Vector2f p);

	//Getters and setters for Velocity 
	sf::Vector2f GetVel();
	template <typename U, typename T> //using template func
	void SetVel(T x, U y);
	void SetVel(sf::Vector2f v);

	//Getters and setters for Hitbox
	HitboxManager getHitbox();
	void setHitboxCol(sf::Color col);

	//Getters and setters for Speed using template functions
	template <typename T>
	T getSpeed();
	template <typename T>
	void setSpeed(T h);

	//Getters and setters for Cooldown
	int getCooldown();
	void setCooldown(int i);


	//Textures by David
	sf::Texture ptex;
	sf::Sprite playerImage;
	int spriteX;
	int spriteY;
	const int sprWidth = 100;
	const int sprHight = 120;
	void Draw();
	int timer = 5;
	bool faceL = true;
	/////////////////

private:
	HitboxManager hitbox;
	
	sf::Texture texture;

	sf::Vector2f pos;
	sf::Vector2f vel; //the x component if this is the speed variable

	int width;
	int height;
	int speed;
	int cooldown;
};

