#include "stdafx.h"
#include "Entity.h"


Entity::Entity(float x, float y)
{
	pos = sf::Vector2f(2, 2);
	SetPos(x, y);
	healthBar.setHealth(healthBar.MAXHEALTH);
	cooldown = 60;
	hitbox = HitboxManager(80, 200);
	ptex.loadFromFile("ken-sprite-sheet.png");
	playerImage.setTexture(ptex);
	playerImage.setTextureRect(sf::IntRect(0, 0, sprWidth, sprHight));
	spriteX = 0;
	spriteY = 0;
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

	if (GetPos().y < 50)
	{
		SetPos(GetPos().x, 50);
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
	playerImage.setTextureRect(sf::IntRect(spriteX * sprWidth, spriteY * sprHight, sprWidth, sprHight));
	hitbox.Update(pos);

}

#pragma region Player actions

void Entity::Attack(sf::Vector2f size, int noOfFrames, sf::Vector2f playerPos, sf::Vector2f enemyPos, float playerWidth, int yOffset, int xOffset)
{
	hitbox.HurtBoxUse(size, noOfFrames, playerPos, enemyPos, playerWidth, yOffset, xOffset);
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
template <typename T, typename U>
void Entity::SetPos(T x, U y)
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
template <typename U, typename T>
void Entity::SetVel(T x, U y)
{
	vel.x = x;
	vel.y = y;
}

//Getters and setters for health
template <typename T>
T Entity::getSpeed()
{
	return speed;
}
template <typename T>
void Entity::setSpeed(T h)
{
	speed = h;
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


