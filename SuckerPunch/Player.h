#pragma once

#include "Entity.h"


class Player : public Entity
{
public:
	Player(int x, int y);
	~Player();

	void Update();

	void MoveX(int x);
	void MoveY(int y);

	void Jump(float vel);

	const float DECELERATION = 0.75f;
	const float MOVESPEED = 5;

	int getCooldown();
	void setCooldown(int i);

private:

	int cooldown;



};

