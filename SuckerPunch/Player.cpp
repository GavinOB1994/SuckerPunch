#include "stdafx.h"
#include "Player.h"


Player::Player(int x, int y)
{
	SetPos(x, y);
	setHealth(3);
	cooldown = 60;
}


Player::~Player()
{
}

void Player::MoveX(int x)
{
	SetPos(GetPos().x + x, GetPos().y);
}

void Player::MoveY(int y)
{
	SetPos(GetPos().x, GetPos().y + y);
}




void Player::Update()
{
	SetPos(GetPos() + GetVel()); //Adds the velocity to the current position
	SetVel(GetVel().x * DECELERATION, GetVel().y * DECELERATION); //applying deceleration to the velocity

	if (GetPos().y < 500)
	{
		Accelerate(0, GRAVITY);//Acceleration due to gravity
	}
	else
	{
		SetPos(GetPos().x, 500);//Setting a hard floor TEMPORARY
	}

	if (GetPos().x < 0)
	{
		SetPos(0, GetPos().y);
	}
	if (GetPos().x > 900)
	{
		SetPos(900, GetPos().y);
	}

	UpdateHitbox();
	
}

void Player::Jump(float vel)
{
	Accelerate(0, vel);
}

int Player::getCooldown()
{
	return cooldown;
}
void Player::setCooldown(int i)
{
	cooldown = i;
}