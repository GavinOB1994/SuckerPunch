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
#include "Entity.h"
#include "SoundManager.h"



////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

int main()
{
	//INITIALISATION
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(1000, 750, 64), "SFML First Program");

	//creating the clock
	sf::Clock clock;

	//Limiting the framerate
	window.setFramerateLimit(60);

	//Enable v-sync
	window.setVerticalSyncEnabled(true);

	//stopping the key buffer
	window.setKeyRepeatEnabled(false);

	//load a font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");

	//create a formatted text string
	sf::Text text;
	text.setFont(font);
	text.setString("Test text that tests things");
	text.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	text.setPosition(400, 40);
	text.setCharacterSize(40);

	//create a player & hitbox managers
	Entity player(100, 100);
	sf::Text p1Health;
	p1Health.setFont(font);
	p1Health.setString("player One HP: " + std::to_string(player.healthBar.getHealth()));
	p1Health.setPosition(20, 40);
	
	//Same for player 2
	Entity player2(800, 100);
	sf::Text p2Health;
	p2Health.setFont(font);
	p2Health.setString("player Two HP: " + std::to_string(player2.healthBar.getHealth()));
	p2Health.setPosition(780, 40);

	//Sound stuff
	SoundManager snd(player.GetVel(), player.GetPos(), player2.GetPos());
	snd.loopBGM(snd.bgm);
	snd.threeDSound(snd.threeDS);
	bool sfxOn = true; //Sound effects
	bool tdsOn = true; //3D sound
	bool rvbOn = true; //Reverb

	// Start game loop 
	while (window.isOpen())
	{

	// Process events 
	sf::Event Event;

	//Flipping the bools on audio 
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)))
	{
		sfxOn = !sfxOn;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)))
	{
		snd.pauseBGM();
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)))
	{
		snd.pauseTDS();
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)))
	{
		snd.pauseRVB();
	}

	if (player.getHitbox().getCanMove() && player.healthBar.getHealth() > 0 && player2.healthBar.getHealth() > 0)
	{
		//PLAYER 1
		//Move Right
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && player.GetVel().x < +player.MAXVEL)
			player.Accelerate(player.MOVESPEED, 0);
		//Move Left
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && player.GetVel().x > -player.MAXVEL)
			player.Accelerate(-player.MOVESPEED, 0);			
		//Attack
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::G)))
			player.Attack(sf::Vector2f(100, 100), 10, player.GetPos(), player2.GetPos(), player.getHitbox().getSize().x);
		//Attack
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::F)))
		{
			player.Attack(sf::Vector2f(200, 50), 20, player.GetPos(), player2.GetPos(), player.getHitbox().getSize().x);
			if (sfxOn)
			{
				snd.playSound(snd.punch);
			}
			
		}
			
	}

	if (player2.getHitbox().getCanMove() && player.healthBar.getHealth() > 0 && player2.healthBar.getHealth() > 0)
	{
		//PLAYER 2
		//Move Right
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && player2.GetVel().x < +player2.MAXVEL)
			player2.Accelerate(player2.MOVESPEED, 0);
		//Move Left
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && player2.GetVel().x > -player2.MAXVEL)
			player2.Accelerate(-player2.MOVESPEED, 0);
		//Attack
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::K)))
			player2.Attack(sf::Vector2f(100, 100), 10, player2.GetPos(), player.GetPos(), player2.getHitbox().getSize().x);
		}


		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();
			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();

			if (player.getHitbox().getCanMove() && player.healthBar.getHealth() > 0 && player2.healthBar.getHealth() > 0)
			{
				//Jump UP
				if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::W))
				{
					player.Jump(-100);
					if (sfxOn)
					{
						snd.playSound(snd.jump);
					}		
				}
					
			}
			if (player2.getHitbox().getCanMove() && player.healthBar.getHealth() > 0 && player2.healthBar.getHealth() > 0)
			{
				//Jump UP
				if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
					player2.Jump(-100);;
			}
		}

		//Collision for player 1's "hitbox"(the green one) and player 2's "hurtbox"(the red one)
		if (player.getHitbox().BoxCollision(player2.getHitbox().getHurtBox()) && player.getCooldown() == 60)
		{
			player.setCooldown(59); //Starts the cooldown.
			player.setHitboxCol(sf::Color(255,255,0,128));
			player.healthBar.setHealth(player.healthBar.getHealth() - 1); //REdices the players total health by 1
			p1Health.setString("player One HP: " + std::to_string(player.healthBar.getHealth())); //Updates the text/healthbar
		}
		//vice versa
		if (player2.getHitbox().BoxCollision(player.getHitbox().getHurtBox()) && player2.getCooldown() == 60)
		{
			player2.setCooldown(59);
			player2.setHitboxCol(sf::Color(255, 255, 0, 128));
			player2.healthBar.setHealth(player2.healthBar.getHealth() - 1);
			p2Health.setString("player Two HP: " + std::to_string(player2.healthBar.getHealth()));
		}

		player.Update();
		player2.Update();

		snd.update(player.GetVel(), player.GetPos(), player2.GetPos());

		//prepare frame
		window.clear();

		//draw frame items
		window.draw(p1Health);
		window.draw(p2Health);

		window.draw(player.getHitbox().getBox());
		if (player.getHitbox().getCanMove() == false)
		{
			window.draw(player.getHitbox().getHurtBox());
		}
		

		window.draw(player2.getHitbox().getBox());
		if (player2.getHitbox().getCanMove() == false)
		{
			window.draw(player2.getHitbox().getHurtBox());
		}

		if (player.healthBar.getHealth() <= 0)
		{
			text.setString("Player 2 Wins!");
		}
		if (player2.healthBar.getHealth() <= 0)
		{
			text.setString("Player 1 Wins!");
		}
		if (player2.healthBar.getHealth() <= 0 || player.healthBar.getHealth() <= 0)
		{
			window.draw(text);
		}
		


		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}