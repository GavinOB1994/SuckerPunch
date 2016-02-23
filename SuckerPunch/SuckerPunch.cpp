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
#include "UI.h"



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

	//Create UI
	UI ui;

	//create a player 
	Entity player(100, 100);

	//Same for player 2
	Entity player2(800, 100);

	//VAriables for character slect
	// Setting colour presets for character select
	sf::Color colours[3][3]; //Due to the shape of my colour select I chose a 2D array
	colours[0][0] = sf::Color::White;
	colours[0][1] = sf::Color::Black;
	colours[0][2] = sf::Color::Red;
	colours[1][0] = sf::Color::Blue;
	colours[1][1] = sf::Color::Transparent;
	colours[1][2] = sf::Color::Green;
	colours[2][0] = sf::Color::Yellow;
	colours[2][1] = sf::Color::Cyan;
	colours[2][2] = sf::Color::Magenta;
	int currentColX = 0;
	int currentColY = 0;
	int currentColX2 = 0;
	int currentColY2 = 0;
	sf::RectangleShape colBoxes[3][3]; //This is the array of colours for player 1
	sf::RectangleShape colBoxes2[3][3]; //Same for player 2
	sf::RectangleShape selectBox(sf::Vector2f(120, 120));
	selectBox.setFillColor(sf::Color::Color(255, 128, 0, 255));

	for (int i = 0; i < 3; i++) //Nested for loops to accomodate the 2D array
	{
		for (int j = 0; j < 3; j++)
		{
			colBoxes[i][j] = sf::RectangleShape(sf::Vector2f(100, 100)); //Here we set all of the starter variables for the colour select square
			colBoxes[i][j].setPosition(sf::Vector2f(i * 110 + 10, j * 110 + 200));
			colBoxes[i][j].setFillColor(colours[i][j]);
		}
	}
	for (int i = 0; i < 3; i++) //Same for player 2 squares
	{
		for (int j = 0; j < 3; j++)
		{
			colBoxes2[i][j] = sf::RectangleShape(sf::Vector2f(100, 100));
			colBoxes2[i][j].setPosition(sf::Vector2f(i * 110 + 670, j * 110 + 200));
			colBoxes2[i][j].setFillColor(colours[i][j]);
		}
	}

	//Sound stuff
	SoundManager snd(player.GetVel(), player.GetPos(), player2.GetPos());
	snd.loopBGM(snd.getBGM());
	snd.threeDSound(snd.getThreeDS());
	bool sfxOn = true; //Sound effects

	//Controller stuff
	Controller c1(0);
	Controller c2(1);

	//gamestate stuff - D
	enum States { menu, game, pause, charSelect };
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

	//Character select Images
	sf::Texture squidTex;
	sf::Texture eyeTex;
	sf::Sprite squid;
	sf::Sprite squid2;
	sf::Sprite eyes;
	sf::Sprite eyes2;
	squidTex.loadFromFile("../SuckerPunch/Sprites/Blank squid.png");
	eyeTex.loadFromFile("../SuckerPunch/Sprites/GlovesAndEyes.png");
	squid.setTexture(squidTex);
	squid2.setTexture(squidTex);
	eyes.setTexture(eyeTex);
	eyes2.setTexture(eyeTex);

	//Setting the position for the squid sprites in colour select
	eyes.setPosition(colBoxes[1][1].getPosition()); 
	eyes.setScale(4.762, 4.762);
	squid.setPosition(colBoxes[1][1].getPosition());
	squid.setScale(4.762, 4.762);
	eyes2.setPosition(colBoxes2[1][1].getPosition() + sf::Vector2f(100, 0));
	eyes2.setScale(-4.762, 4.762);
	squid2.setPosition(colBoxes2[1][1].getPosition() + sf::Vector2f(100, 0));
	squid2.setScale(-4.762, 4.762);

	//Title menu Variables
	sf::Texture titleTex; //Creating a texture for the title
	titleTex.loadFromFile("Title.png"); //loading
	sf::Sprite titleSpr = sf::Sprite(titleTex); //turining it into a sprite
	titleSpr.setOrigin(titleSpr.getTextureRect().width / 2, titleSpr.getTextureRect().height / 2); //setting the origin to the centre of the sprite
	titleSpr.setPosition(window.getSize().x / 2, window.getSize().y / 2); //putting it in the centre of the screen

	sf::Text subTitle; //Creating the title tooltip
	subTitle.setFont(font);
	subTitle.setString("Press Enter to Start");
	subTitle.setPosition(380, 600); //Hardcoding the postiton of the tooltip

	//Pause menu variables
	sf::Text pauseText;
	pauseText.setFont(font);
	pauseText.setString("Press Space OR Start to unpause \n Press R OR up to reset");
	pauseText.setPosition(380, 600);

	// Start game loop 
	while (window.isOpen())
	{

	// Process events 
	sf::Event Event;

//All of the regions for the different states updates

#pragma region Menu
	if (gameState == menu)
	{
		//prepare frame
		window.clear();
		window.draw(backImg); //Draw the background image
		window.draw(titleSpr); //Draw the game title sprite
		window.draw(subTitle); //Draw the tootltip text to the screen
		while (window.pollEvent(Event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || c1.startPress() || c2.startPress())
				gameState = charSelect;
		}		
	}
#pragma endregion

#pragma region CharSelect
	else if (gameState == charSelect)
	{
		//prepare frame
		window.clear();
		window.draw(backImg); //Draw the background

		for (int i = 0; i < 3; i++) //Nested for loops to accomodate the 2D array
		{
			for (int j = 0; j < 3; j++)
			{
				if (currentColX == i && currentColY == j)
				{
					selectBox.setPosition(sf::Vector2f(i * 110 + 0, j * 110 + 190));
					window.draw(selectBox);
				}
				window.draw(colBoxes[i][j]);
			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (currentColX2 == i && currentColY2 == j)
				{
					selectBox.setPosition(sf::Vector2f(i * 110 + 660, j * 110 + 190));
					window.draw(selectBox);
				}
				window.draw(colBoxes2[i][j]);
			}
		}


#pragma region Buttons

		while (window.pollEvent(Event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || c1.startPress() || c2.startPress())
			{
				player.playerImage.setColor(colours[currentColX][currentColY]);	//Setting the colour dor p1 based on the slected colour
				player2.playerImage.setColor(colours[currentColX2][currentColY2]);
				ui.SetColours(colours[currentColX][currentColY], colours[currentColX2][currentColY2]);
				gameState = game;
			}			

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || c1.upPress())
			{
				currentColY--;
				if (currentColY == 1 && currentColX == 1)
					currentColY = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Joystick::isButtonPressed(0, 20))
			{
				currentColY++;
				if (currentColY == 1 && currentColX == 1)
					currentColY = 2;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Joystick::isButtonPressed(0, 22))
			{
				currentColX++;
				if (currentColY == 1 && currentColX == 1)
					currentColX = 2;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Joystick::isButtonPressed(0, 24))
			{
				currentColX--;
				if (currentColY == 1 && currentColX == 1)
					currentColX = 0;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Joystick::isButtonPressed(1, 8))
			{
				currentColY2--;
				if (currentColY2 == 1 && currentColX2 == 1)
					currentColY2 = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Joystick::isButtonPressed(1, 9))
			{
				currentColY2++;
				if (currentColY2 == 1 && currentColX2 == 1)
					currentColY2 = 2;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Joystick::isButtonPressed(1, 9))
			{
				currentColX2++;
				if (currentColY2 == 1 && currentColX2 == 1)
					currentColX2 = 2;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Joystick::isButtonPressed(1, 9))
			{
				currentColX2--;
				if (currentColY2 == 1 && currentColX2 == 1)
					currentColX2 = 0;
			}
		}

#pragma endregion

#pragma region NumberManagement

		//This is all just number management for the Colour select box
		if (currentColX > 2)
		{
			currentColX = 0;
		}
		if (currentColX < 0)
		{
			currentColX = 2;
		}
		if (currentColY > 2)
		{
			currentColY = 0;
		}
		if (currentColY < 0)
		{
			currentColY = 2;
		}


		if (currentColX2 > 2)
		{
			currentColX2 = 0;
		}
		if (currentColX2 < 0)
		{
			currentColX2 = 2;
		}
		if (currentColY2 > 2)
		{
			currentColY2 = 0;
		}
		if (currentColY2 < 0)
		{
			currentColY2 = 2;
		}

#pragma endregion


		//Squid 1 draw code		
		window.draw(eyes);
		squid.setColor(colours[currentColX][currentColY]); //Set the colour of the squid
		window.draw(squid);

		window.draw(eyes2);
		squid2.setColor(colours[currentColX2][currentColY2]);
		window.draw(squid2);
	}
#pragma endregion

#pragma region Pause
	else if (gameState == pause)
	{

		window.clear();

		window.draw(pauseText);
		if (pauseTimer > 0)
			pauseTimer--;
		if (/*pauseTimer < 1 && */(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || c1.startPress() || c2.startPress()))
		{
			pauseTimer = 20;
			gameState = game;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			player.Reset(100, 100);
			player2.Reset(800, 100);
		}
	}
#pragma endregion

#pragma region Game
	else if (gameState == game)
	{

		if (pauseTimer > 0)
			pauseTimer--;
		if (p1AtkTimer > 0)
			p1AtkTimer--;
		if (p2AtkTimer > 0)
			p2AtkTimer--;
#pragma region boolFlips
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
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || c1.startPress() || c2.startPress()) && pauseTimer < 1)
		{
			pauseTimer = 20;
			gameState = pause;
		}
#pragma endregion

#pragma region playerInput
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
#pragma endregion

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
			player.healthBar.setHealth(player.healthBar.getHealth() - 1); //Reduces the players total health by 1
			if (sfxOn)
				snd.playSound(snd.getPunch());
		}
		//vice versa
		if (player2.getHitbox().BoxCollision(player.getHitbox().getHurtBox()) && player2.getCooldown() == 60)
		{
			player2.setCooldown(59);
			player2.setHitboxCol(sf::Color(255, 255, 0, 128));
			player2.healthBar.setHealth(player2.healthBar.getHealth() - 1);
			if (sfxOn)
				snd.playSound(snd.getPunch());
		}


		//Update methods for game
		player.Update();
		player2.Update();
		snd.update(player.GetVel(), player.GetPos(), player2.GetPos());

		//prepare frame
		window.clear();

		window.draw(backImg);

		//Drawing the UI
		ui.Draw(&window, player.healthBar.getHealth(), player2.healthBar.getHealth());


		//Toggle for Hitbox Mode ///////////////////////////////////////////////////
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

		if (player.healthBar.getHealth() <= 0 && text.getString() != "Player 2 Wins!")
		{
			text.setString("Player 2 Wins!");
			ui.p1Win(false);
		}
		if (player2.healthBar.getHealth() <= 0 && text.getString() != "Player 1 Wins!")
		{
			text.setString("Player 1 Wins!");
			ui.p1Win(true);
		}
		if (player2.healthBar.getHealth() <= 0 || player.healthBar.getHealth() <= 0)
		{
			window.draw(text);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || c1.startPress() || c2.startPress())
			{
				text.setString("");
				player.Reset(100, 100);
				player2.Reset(800, 100);
			}
		}

//Spreite animations - David
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
#pragma endregion

	//Global updates
	c1.update();
	c2.update();
		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}
