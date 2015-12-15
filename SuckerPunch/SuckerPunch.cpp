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
#include "Controller.h"



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
	p1Health.setPosition(20, 0);
	
	//Same for player 2
	Entity player2(800, 100);
	sf::Text p2Health;
	p2Health.setFont(font);
	p2Health.setString("player Two HP: " + std::to_string(player2.healthBar.getHealth()));
	p2Health.setPosition(680, 0);

	//Sound stuff
	SoundManager snd(player.GetVel(), player.GetPos(), player2.GetPos());
	snd.loopBGM(snd.getBGM());
	snd.threeDSound(snd.getThreeDS());
	bool sfxOn = true; //Sound effects
	bool tdsOn = true; //3D sound
	bool rvbOn = true; //Reverb

	//Controller stuff
	Controller c1(0);
	Controller c2(1);

	//gamestate stuff - D
	enum States { menu, game, pause };
	char gameState = menu;

	//animation timers - D
	int pauseTimer = 20;
	int p1AtkTimer = 0;
	int p2AtkTimer = 0;

	//BackGround Image
	sf::Texture btex;
	sf::Sprite backImg;
	btex.loadFromFile("../SuckerPunch/Sprites/back.png");
	backImg.setTexture(btex);

	// Start game loop 
	while (window.isOpen())
	{

	// Process events 
	sf::Event Event;

	if (gameState == menu)
	{

		sf::Texture titleTex;
		titleTex.loadFromFile("Title.png");
		sf::Sprite titleSpr = sf::Sprite(titleTex);
		titleSpr.setOrigin(279, 90);
		titleSpr.setPosition(window.getSize().x / 2, window.getSize().y / 2);
		window.draw(titleSpr);
		while (window.pollEvent(Event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Joystick::isButtonPressed(0, 7))
				gameState = game;
		}

		sf::Text subTitle;
		subTitle.setFont(font);
		subTitle.setString("Press Enter to Start");
		subTitle.setPosition(380, 600);
		window.draw(subTitle);
	}
	else if (gameState == pause)
	{

		window.clear();
		sf::Text pauseText;
		pauseText.setFont(font);
		pauseText.setString("Press Space to unpause");
		pauseText.setPosition(380, 600);
		window.draw(pauseText);
		if (pauseTimer > 0)
			pauseTimer--;
		if (pauseTimer < 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			pauseTimer = 20;
			gameState = game;
		}
	}
	else if (gameState == game)
	{

		if (pauseTimer > 0)
			pauseTimer--;
		if (p1AtkTimer > 0)
			p1AtkTimer--;
		if (p2AtkTimer > 0)
			p2AtkTimer--;

		//Flipping the bools on audio when key is pressed
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && pauseTimer < 1)
		{
			pauseTimer = 20;
			gameState = pause;
		}

		if (player.getHitbox().getCanMove() && player.healthBar.getHealth() > 0 && player2.healthBar.getHealth() > 0)
		{
			//PLAYER 1
			//Move Right
			if (((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || c1.getX() > 20) && player.GetVel().x < +player.MAXVEL)
				player.Accelerate(player.MOVESPEED, 0);
			//Move Left
			if (((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || c1.getX() < -20) && player.GetVel().x > -player.MAXVEL)
				player.Accelerate(-player.MOVESPEED, 0);
			//Attack 1
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::G)) || c1.b2Press())
			{
				player.Attack(sf::Vector2f(25, 200), 15, player.GetPos(), player2.GetPos(), player.getHitbox().getSize().x, 0, 0);
				if (sfxOn)
					snd.playSound(snd.getWoosh());
				p1AtkTimer = 15;
				player.spriteX = 0;
			}
			//Attack 2
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::F)) || c1.b3Press())
			{
				player.Attack(sf::Vector2f(100, 25), 40, player.GetPos(), player2.GetPos(), player.getHitbox().getSize().x , player.HEIGHT - 25 , 0);
				if (sfxOn)
					snd.playSound(snd.getWoosh());
				p1AtkTimer = 40;
				player.spriteX = 0;
			}
			//Attack 3
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::F)) || c1.b1Press())
			{
				player.Attack(sf::Vector2f(125, 225), 25, player.GetPos(), player2.GetPos(), player.getHitbox().getSize().x, -50, -100);
				if (sfxOn)
					snd.playSound(snd.getWoosh());
				p1AtkTimer = 25;
				player.spriteX = 0;
			}
			//JUMP
			if (c1.b0Press())
			{
				player.Jump(-100);
				if (sfxOn)
					snd.playSound(snd.getJump());
				player.spriteX = 0;
			}
		}

		if (player2.getHitbox().getCanMove() && player.healthBar.getHealth() > 0 && player2.healthBar.getHealth() > 0)
		{
			//PLAYER 2
			//Move Right
			if (((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || c2.getX() > 20) && player2.GetVel().x < +player2.MAXVEL)
				player2.Accelerate(player2.MOVESPEED, 0);
			//Move Left
			if (((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || c2.getX() < -20) && player2.GetVel().x > -player2.MAXVEL)
				player2.Accelerate(-player2.MOVESPEED, 0);
			//Attack 1
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::G)) || c2.b2Press())
			{
				player2.Attack(sf::Vector2f(25, 200), 15, player2.GetPos(), player.GetPos(), player2.getHitbox().getSize().x, 0, 0);
				if (sfxOn)
					snd.playSound(snd.getWoosh());
				p2AtkTimer = 15;
				player2.spriteX = 0;
			}
			//Attack 2
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::F)) || c2.b3Press())
			{
				player2.Attack(sf::Vector2f(100, 25), 40, player2.GetPos(), player.GetPos(), player2.getHitbox().getSize().x, player2.HEIGHT - 25, 0);
				if (sfxOn)
					snd.playSound(snd.getWoosh());
				p2AtkTimer = 40;
				player2.spriteX = 0;
			}
			//Attack 3
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::F)) || c2.b1Press())
			{
				player2.Attack(sf::Vector2f(125, 225), 25, player2.GetPos(), player2.GetPos(), player2.getHitbox().getSize().x, -50, -100);
				if (sfxOn)
					snd.playSound(snd.getWoosh());
				p1AtkTimer = 25;
				player2.spriteX = 0;
			}
			//JUMP
			if (c2.b0Press())
			{
				player2.Jump(-100);
				if (sfxOn)
					snd.playSound(snd.getJump());
				player2.spriteX = 0;
			}
		}


		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed || sf::Joystick::isButtonPressed(0,6))
				window.close();
			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();
		}

		//Collision for player 1's "hitbox"(the green one) and player 2's "hurtbox"(the red one)
		if (player.getHitbox().BoxCollision(player2.getHitbox().getHurtBox()) && player.getCooldown() == 60)
		{
			player.setCooldown(59); //Starts the cooldown.
			player.setHitboxCol(sf::Color(255, 255, 0, 128));
			player.healthBar.setHealth(player.healthBar.getHealth() - 1); //REdices the players total health by 1
			p1Health.setString("player One HP: " + std::to_string(player.healthBar.getHealth())); //Updates the text/healthbar
			if (sfxOn)
				snd.playSound(snd.getPunch());
		}
		//vice versa
		if (player2.getHitbox().BoxCollision(player.getHitbox().getHurtBox()) && player2.getCooldown() == 60)
		{
			player2.setCooldown(59);
			player2.setHitboxCol(sf::Color(255, 255, 0, 128));
			player2.healthBar.setHealth(player2.healthBar.getHealth() - 1);
			p2Health.setString("player Two HP: " + std::to_string(player2.healthBar.getHealth()));
			if (sfxOn)
				snd.playSound(snd.getPunch());
		}


		//Update methods
		player.Update();
		player2.Update();
		c1.update();
		c2.update();
		snd.update(player.GetVel(), player.GetPos(), player2.GetPos());

		//prepare frame
		window.clear();

		window.draw(backImg);

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
#pragma region Player1Animation
		player.playerImage.setPosition(player.GetPos());
		player.playerImage.setScale(sf::Vector2f(1, 1.6));

		if (p1AtkTimer > 0)
		{
			player.spriteY = 3;
			if (player.GetPos().x < player2.GetPos().x)
			{
				if (player.spriteX == 0)
					player.spriteX = 1;
				player.playerImage.setTextureRect(sf::IntRect(player.spriteX * player.sprWidth, player.spriteY * player.sprHight, -(player.sprWidth), player.sprHight));
				window.draw(player.playerImage);
			}
			else
				window.draw(player.playerImage);
			
			player.timer--;
			if (player.timer < 0)
			{
				player.spriteX++;
				if (player.spriteX > 10)
				{
					player.spriteX = 10; //set spritex to be 0 on jump button
				}
				player.timer = 4;
			}
		}
		else if (player.GetPos().y < 500)
		{
			player.spriteY = 2;
			if (player.GetPos().x < player2.GetPos().x)
			{
				if (player.spriteX == 0)
					player.spriteX = 1;
				player.playerImage.setTextureRect(sf::IntRect(player.spriteX * player.sprWidth, player.spriteY * player.sprHight, -(player.sprWidth), player.sprHight));
				window.draw(player.playerImage);
			}
			else
				window.draw(player.playerImage);
			player.timer--;
			if (player.timer < 0)
			{
				player.spriteX++;
				if (player.spriteX > 10)
				{
					player.spriteX = 10; //set spritex to be 0 on jump button
				}
				player.timer = 5;
			}
		}
		else if (player.GetVel().x < -0.2)
		{
			player.spriteY = 1;
			if (player.GetPos().x < player2.GetPos().x)
			{
				if (player.spriteX == 0)
					player.spriteX = 1;
				player.playerImage.setTextureRect(sf::IntRect(player.spriteX * player.sprWidth, player.spriteY * player.sprHight, -(player.sprWidth), player.sprHight));
				window.draw(player.playerImage);
			}
			else
				window.draw(player.playerImage);
			player.timer--;
			if (player.timer < 0)
			{
				player.spriteX++;
				if (player.spriteX > 10)
				{
					player.spriteX = 0;
				}
				player.timer = 5;
			}
			player.faceL = true;
		}
		else if (player.GetVel().x > 0.2)
		{
			player.spriteY = 1;
			if (player.GetPos().x < player2.GetPos().x)
			{
				if (player.spriteX == 0)
					player.spriteX = 1;
				player.playerImage.setTextureRect(sf::IntRect(player.spriteX * player.sprWidth, player.spriteY * player.sprHight, -(player.sprWidth), player.sprHight));
				window.draw(player.playerImage);
			}
			else
				window.draw(player.playerImage);
			player.timer--;
			if (player.timer < 0)
			{
				player.spriteX++;
				if (player.spriteX > 10)
				{
					player.spriteX = 1;
				}
				player.timer = 5;
			}
			player.faceL = false;
		}
		else
		{
			player.spriteY = 0;
			if (player.GetPos().x < player2.GetPos().x)
			{
				if (player.spriteX == 0)
					player.spriteX = 1;
				player.playerImage.setTextureRect(sf::IntRect(player.spriteX * player.sprWidth, player.spriteY * player.sprHight, -(player.sprWidth), player.sprHight));
				window.draw(player.playerImage);
			}
			else
				window.draw(player.playerImage);
			player.timer--;
			if (player.timer < 0)
			{
				player.spriteX++;
				if (player.spriteX > 9)
				{
					player.spriteX = 0;
				}
				player.timer = 5;
			}
		}
#pragma endregion

#pragma region Player2Animation
		player2.playerImage.setPosition(player2.GetPos());
		player2.playerImage.setScale(sf::Vector2f(1, 1.6));
		player2.playerImage.setColor(sf::Color::Cyan);

		if (p2AtkTimer > 0)
		{
			player2.spriteY = 3;
			if (player2.GetPos().x < player.GetPos().x)
			{
				if (player2.spriteX == 0)
					player2.spriteX = 1;
				player2.playerImage.setTextureRect(sf::IntRect(player2.spriteX * player2.sprWidth, player2.spriteY * player2.sprHight, -(player2.sprWidth), player2.sprHight));
				window.draw(player2.playerImage);
			}
			else
				window.draw(player2.playerImage);

			player2.timer--;
			if (player2.timer < 0)
			{
				player2.spriteX++;
				if (player2.spriteX > 10)
				{
					player2.spriteX = 10; //set spritex to be 0 on jump button
				}
				player2.timer = 4;
			}
		}
		else if (player2.GetPos().y < 500)
		{
			player2.spriteY = 2;
			if (player2.GetPos().x < player.GetPos().x)
			{
				if (player2.spriteX == 0)
					player2.spriteX = 1;
				player2.playerImage.setTextureRect(sf::IntRect(player2.spriteX * player2.sprWidth, player2.spriteY * player2.sprHight, -(player2.sprWidth), player2.sprHight));
				window.draw(player2.playerImage);
			}
			else
				window.draw(player2.playerImage);
			player2.timer--;
			if (player2.timer < 0)
			{
				player2.spriteX++;
				if (player2.spriteX > 10)
				{
					player2.spriteX = 10; //set spritex to be 0 on jump button
				}
				player2.timer = 5;
			}
		}
		else if (player2.GetVel().x < -0.2)
		{
			player2.spriteY = 1;
			if (player2.GetPos().x < player.GetPos().x)
			{
				if (player2.spriteX == 0)
					player2.spriteX = 1;
				player2.playerImage.setTextureRect(sf::IntRect(player2.spriteX * player2.sprWidth, player2.spriteY * player2.sprHight, -(player2.sprWidth), player2.sprHight));
				window.draw(player2.playerImage);
			}
			else
				window.draw(player2.playerImage);
			player2.timer--;
			if (player2.timer < 0)
			{
				player2.spriteX++;
				if (player2.spriteX > 10)
				{
					player2.spriteX = 0;
				}
				player2.timer = 5;
			}
			player2.faceL = true;
		}
		else if (player2.GetVel().x > 0.2)
		{
			player2.spriteY = 1;
			if (player2.GetPos().x < player.GetPos().x)
			{
				if (player2.spriteX == 0)
					player2.spriteX = 1;
				player2.playerImage.setTextureRect(sf::IntRect(player2.spriteX * player2.sprWidth, player2.spriteY * player2.sprHight, -(player2.sprWidth), player2.sprHight));
				window.draw(player2.playerImage);
			}
			else
				window.draw(player2.playerImage);
			player2.timer--;
			if (player2.timer < 0)
			{
				player2.spriteX++;
				if (player2.spriteX > 10)
				{
					player2.spriteX = 1;
				}
				player2.timer = 5;
			}
			player2.faceL = false;
		}
		else
		{
			player2.spriteY = 0;
			if (player2.GetPos().x < player.GetPos().x)
			{
				if (player2.spriteX == 0)
					player2.spriteX = 1;
				player2.playerImage.setTextureRect(sf::IntRect(player2.spriteX * player2.sprWidth, player2.spriteY * player2.sprHight, -(player2.sprWidth), player2.sprHight));
				window.draw(player2.playerImage);
			}
			else
				window.draw(player2.playerImage);
			player2.timer--;
			if (player2.timer < 0)
			{
				player2.spriteX++;
				if (player2.spriteX > 9)
				{
					player2.spriteX = 0;
				}
				player2.timer = 5;
			}
		}
#pragma endregion

	}
		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}