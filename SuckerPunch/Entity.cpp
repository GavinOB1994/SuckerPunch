#include "stdafx.h"
#include "Entity.h"


Entity::Entity(int x, int y)
{
	pos = sf::Vector2f(2, 2);
	SetPos(x, y);
	setHealth(3);
	cooldown = 60;
}

void Entity::Update()
{
	if (hitbox.getCanMove())
	{
		SetPos(GetPos() + GetVel()); //Adds the velocity to the current position
		SetVel(GetVel().x * DECELERATION, GetVel().y * DECELERATION); //applying deceleration to the velocity
	}


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

	////Allows a whole second of cooldown between each hit
	if (getCooldown() < 60)
	{
		setCooldown(getCooldown() - 1);
		if (getCooldown() <= 0)
		{
			setCooldown(60);
			setHitboxCol(sf::Color(0, 255, 0, 128));
		}
	}

	hitbox.Update(pos);

}

#pragma region Player actions

void Entity::Attack(sf::Vector2f size, int noOfFrames, sf::Vector2f playerPos, sf::Vector2f enemyPos)
{
	hitbox.HurtBoxUse(size, noOfFrames, playerPos, enemyPos);
	vel = sf::Vector2f(0, 0);
}
void Entity::Jump(float vel)
{
	Accelerate(0, vel);
}
void Entity::MoveX(int x)
{
	SetPos(GetPos().x + x, GetPos().y);
}
void Entity::MoveY(int y)
{
	SetPos(GetPos().x, GetPos().y + y);
}
void Entity::Accelerate(float x, float y)//Adds to current momnetum
{
	vel.x += x;
	vel.y += y;
}
void Entity::Accelerate(sf::Vector2f vec)//Adds to current momnetum
{
	vel += vec;
}
#pragma endregion

#pragma region Getters And Setters
//Getters and setters for Hitbox colour
void Entity::setHitboxCol(sf::Color col)
{
	hitbox.setHitboxCol(col);
}

//Getters and setters for Position
sf::Vector2f Entity::GetPos()
{
	return pos;
}
void Entity::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}
void Entity::SetPos(sf::Vector2f p)
{
	pos = p;
}

//getters and setters for hitbox
HitboxManager Entity::getHitbox()
{
	return hitbox;
}


//Getters and setters for velocity
sf::Vector2f Entity::GetVel()
{
	return vel;
}
void Entity::SetVel(sf::Vector2f v)//overides current momentum
{
	vel = v;
}
void Entity::SetVel(float x, float y)
{
	vel.x = x;
	vel.y = y;
}

//Getters and setters for health
int Entity::getHealth()
{
	return health;
}
void Entity::setHealth(int h)
{
	health = h;
}

//Getters and setters for cooldown
int Entity::getCooldown()
{
	return cooldown;
}
void Entity::setCooldown(int i)
{
	cooldown = i;
}
#pragma endregion


