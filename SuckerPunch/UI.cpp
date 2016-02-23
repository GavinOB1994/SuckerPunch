#include "stdafx.h"
#include "UI.h"


UI::UI()
{
	for (int i = 0; i < 5; i++)
	{
		healthBar[i].setSize(sf::Vector2f(80, 50));
		healthBar[i].setPosition(sf::Vector2f(20 + 90 * i, 10));
		healthBar[i].setFillColor(sf::Color::Green);
	}
	for (int i = 0; i < 5; i++)
	{
		healthBar2[i].setSize(sf::Vector2f(80, 50));
		healthBar2[i].setPosition(sf::Vector2f(550 + (90 * i), 10));
		healthBar2[i].setFillColor(sf::Color::Red);
	}
	for (int i = 0; i < 2; i++)
	{
		winDots[i].setRadius(40.0f);
		winDots[i].setFillColor(sf::Color::Yellow);
		winDots[i].setPosition(sf::Vector2f(100 * i, 100));
	}
	for (int i = 0; i < 2; i++)
	{
		winDots2[i].setRadius(40.0f);
		winDots2[i].setFillColor(sf::Color::Yellow);
		winDots2[i].setPosition(sf::Vector2f(1000 - 100 * i, 100));
	}

	p1WinCount = 0;
	p2WinCount = 0;
}

UI::UI(sf::Color col1, sf::Color col2)
{
	for (int i = 0; i < 5; i++)
	{
		healthBar[i].setSize(sf::Vector2f(80, 50));
		healthBar[i].setPosition(sf::Vector2f(20 + 90 * i, 10));
		healthBar[i].setFillColor(col1);
	}
	for (int i = 0; i < 5; i++)
	{
		healthBar2[i].setSize(sf::Vector2f(80, 50));
		healthBar2[i].setPosition(sf::Vector2f(550 + (90 * i), 10));
		healthBar2[i].setFillColor(col2);
	}
}

void UI::Update()
{

}

void UI::Draw(sf::RenderWindow * window, int h1, int h2)
{
	for (int i = 0; i < h1; i++)
	{
		window->draw(healthBar[i]);
	}
	for (int i = 0; i < h2; i++)
	{
		window->draw(healthBar2[4 - i]);
	}
	for (int i = 0; i < p1WinCount; i++)
	{
		window->draw(winDots[i]);
	}
	for (int i = 0; i < p2WinCount; i++)
	{
		window->draw(winDots2[i]);
	}
}

void UI::SetColours(sf::Color c1, sf::Color c2)
{
	for (int i = 0; i < 5; i++)
	{
		healthBar[i].setFillColor(c1);
	}
	for (int i = 0; i < 5; i++)
	{
		healthBar2[i].setFillColor(c2);
	}
}

void UI::p1Win(bool whoWin)
{
	if (whoWin == true)
	{
		p1WinCount++;
	}
	else
	{
		p2WinCount++;
	}
}


