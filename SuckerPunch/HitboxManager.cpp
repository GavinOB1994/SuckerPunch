#include "stdafx.h"
#include "HitboxManager.h"


HitboxManager::HitboxManager(float width, float height)
{
	size = sf::Vector2f(width, height);
	box = sf::RectangleShape(size);
	box.setFillColor(sf::Color(0,255,0,128));
	hurtBox = sf::RectangleShape(box);
	hurtBox.setFillColor(sf::Color(255,0,0,128));
	hurtBox.setPosition(-300, -300);
	canMove = true;
}

void HitboxManager::Update(sf::Vector2f pos)
{
	box.setPosition(pos);
	IsHurtAcitve();
}
//template <typename T, typename U>
void HitboxManager::HurtBoxUse(sf::Vector2f size, int noOfFrames, sf::Vector2f playerPos, sf::Vector2f enemyPos, float playerWidth, int yOffset, int xOffset)
{
	if (playerPos.x < enemyPos.x)
	{
		hurtBox.setPosition(sf::Vector2f(playerPos.x + playerWidth + xOffset, playerPos.y + yOffset));
	}
	else
	{
		hurtBox.setPosition(sf::Vector2f(playerPos.x - size.x - xOffset, playerPos.y + yOffset));
	}
	
	hurtBox.setSize(size);
	frameCount = noOfFrames;
	canMove = false;
}

void HitboxManager::IsHurtAcitve()
{
	if (frameCount == 0)
	{
		canMove = true;
		hurtBox.setPosition(-300, -300);
	}
	else if(canMove == false)
	{
		frameCount--;
	}

}

bool HitboxManager::BoxCollision(sf::RectangleShape enemyBox)
{
	if (enemyBox.getPosition().x > box.getPosition().x + box.getSize().x ||
		enemyBox.getPosition().x + enemyBox.getSize().x < box.getPosition().x ||
		enemyBox.getPosition().y > box.getPosition().y + box.getSize().y || 
		enemyBox.getPosition().y + enemyBox.getSize().y < box.getPosition().y)
	{
		return false;
	}
	else
	{
		return true;		
	}
}

#pragma region Getters and Setters
sf::RectangleShape HitboxManager::getBox()
{
	return box;
}
sf::RectangleShape HitboxManager::getHurtBox()
{
	return hurtBox;
}
bool HitboxManager::getCanMove()
{
	return canMove;
}
void HitboxManager::setHitboxCol(sf::Color col)
{
	box.setFillColor(col);
}
sf::Vector2f HitboxManager::getSize()
{
	return size;
}
#pragma endregion