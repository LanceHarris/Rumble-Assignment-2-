/*
*	Main.cpp
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 20 October 2015
*
*/

/*TO DO: 
Tighten up collisions
Ensure the clock doesn't 'skip' when holding down movement
Ensure animations always play, and that they play slower when moving
Make it so that movement in another direction begins immediately when a key is pressed
Create Player and Enemy class as subclasses of Character class
*/

#include <SFML/Graphics.hpp>
#include "ChatBox.h"
#include "Map.h"
#include "Character.h"

/*RENDERWINDOW SIZE*/
int winX = 1080; //45 cells
int winY = 840; //35 cells
/*END*/

/*PLAYER CORDS, CHANGE TO STARTING POSITION*/
float playX = 200;
float playY = 200;
/*END*/

/*PLAYER STATS*/
int speed = 8; //8 looks smoother than 1
int attack = 1;
int toughness = 1;
int health = 1;
/*END*/

/*SPRITE INFO*/
const int SPRITEWIDTH = 16;
const int SPRITEHEIGHT = 16;
const int SPRITEMAX = 4;
const int SPRITEGAP = 3;

int spriteXPos = 0;
int spriteYPos = 0;
/*END*/

//SPEED OF THE GAME
const float GAME_SPEED = 60.0f; //The bigger this number is the more often frames are updated
sf::Time TimePerFrame = sf::seconds(1.0f / GAME_SPEED);
/*END*/

void drawGrid(sf::RenderWindow &window)
{
		int x = 0; //reset x to redraw grid
		int y = winY; //reset y to redraw grid
		for(int i = 0; i<winX/20;i++) //begin loop through to draw grid
		{
		
		//define vertical line vertexes
		x+=24;
		sf::Vertex lineVert[] = {

			sf::Vertex(sf::Vector2f(x, 0),sf::Color(0, 0, 0, 24)),
			sf::Vertex(sf::Vector2f(x, winY),sf::Color(40, 0, 0, 24)),

			};

		//define horizontal line vertexes
		y-=24;
		sf::Vertex lineHori[] = {

			sf::Vertex(sf::Vector2f(0, y),sf::Color(0, 0, 0, 24)),
			sf::Vertex(sf::Vector2f(winX,y),sf::Color(0, 0, 0, 24)),

			};

		window.draw(lineVert, 2, sf::Lines); //draw vertical lines
		window.draw(lineHori, 2, sf::Lines); //draw horizontal lines

		}
}

//COLOURS EMPTY TILES (or any others that you specify) CYAN FOR DEBUGGING PURPOSES
void drawEmptyTiles(Map &map, sf::RenderWindow &window)
{
	for (int row = 0; row < map.COLUMN_COUNT; row++)
	{
		for (int col = 0; col < map.ROW_COUNT; col++)
		{
			Map::Tile tile = map.getTile(col, row);
			if (tile == Map::Tile::TileEmpty)
			{
				sf::RectangleShape rectangle;
				rectangle.setPosition(row * 24, col * 24);
				rectangle.setSize(sf::Vector2f(24, 24));

				rectangle.setFillColor(sf::Color::Cyan);

				window.draw(rectangle);
			}
		}
	}
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(winX, winY), "Rumble!");

	//SET BOTH TO TRUE IF YOU WANT TO COLOUR IN THE EMPTY CELLS WITH CYAN
	bool drawGridCells = false;
	bool drawEmptyPath = false;

	//SET TO TRUE TO RUN DEBUGGING PRINT OUTS
	bool debug = true;

	//BOX TO TEST CHATBOX TRIGGERING
	sf::RectangleShape box(sf::Vector2f(24,24));
	box.setPosition(480,600);

	//CREATE TEXTBOX
	ChatBox textBox = ChatBox(winX,winY);
	textBox.setTextSettings("Retro Computer_DEMO.ttf", 19, sf::Color::White);

	//NUMBER OF CHARCTERS PER LINE, WILL DIFFER DEPENDING ON FONT
	textBox.SetCharaterLineLimit(55);

	//SET CHATBOX MESSAGE
	textBox.setMessage("Welcome to the Colloseum! Prepare to die! Nye hehheh hehheh hehheh hehheh *coughcough*! >_< Welcome to the Colloseum! Prepare to die! Nye hehheh hehheh hehheh hehheh *coughcough*! Welcome to the Colloseum! Prepare to die! Nye hehheh hehheh hehheh hehheh *coughcough*! Welcome to the Colloseum! Prepare to die! Nye hehheh hehheh hehheh hehheh *coughcough*! Welcome to the Colloseum! Prepare to die! Nye hehheh hehheh hehheh hehheh *coughcough*! ", window);

	sf::Clock timer;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	Map map(winX, winY);
	Character player(health, speed);
	player.setPosition(20,20);

	sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
			{
                window.close();
			}

			//PROGRESS OR CLOSE CHATBOX
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				textBox.setNext(true);
			}

			//CHARACTER MOVEMENT EVENTS AND CHECK BOUNDS
			//RIGHT
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !(player.getSprite().getPosition().x >= winX-SPRITEWIDTH-5))
			{
				//CHECK IF THE NEXT POSITION IN THE DIRECTION THE PLAYER IS HEADING ON THE MAP IS A COLLISION
				if (!map.isCollision(player.getRow(), player.getColumn() + 1))
				{
					player.setFacing(Character::RIGHT);
					player.walk(map);
				}
			}

			//LEFT
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !(player.getSprite().getPosition().x <= 0))
			{
				if (!map.isCollision(player.getRow(), player.getColumn() - 1))
				{
					player.setFacing(Character::LEFT);
					player.walk(map);
				}
			}

			//UP
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !(player.getSprite().getPosition().y <= 0))
			{
				if (!map.isCollision(player.getRow() - 1, player.getColumn()))
				{
					player.setFacing(Character::UP);
					player.walk(map);
				}
			}

			//DOWN
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !(player.getSprite().getPosition().y >= winY-SPRITEWIDTH-5))
			{
				if (!map.isCollision(player.getRow() + 1, player.getColumn()))
				{
					player.setFacing(Character::DOWN);
					player.walk(map);
				}
			}

			//FOR DEBUGGING
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)) //I = INFO
			{
				debug = true;
			}
        }

		sf::Time elapsedTime = timer.restart();
		timeSinceLastUpdate += elapsedTime;
		if (timeSinceLastUpdate > TimePerFrame)
		{
			//DEBUG
			if(debug)
			{
				std::cout << "actual position: (" << player.getSprite().getPosition().x << ", " << player.getSprite().getPosition().y << ")" << std::endl;
				std::cout << "grid position: (" << player.getRow() << "," << player.getColumn() << ")" << std::endl;
				std::cout << "map tile: " << map.getTile(player.getRow(), player.getColumn()) << std::endl;
				std::cout << "Next tile right: " << (player.getColumn() + 1) << std::endl;
				std::cout << "Next tile left: " << (player.getColumn() - 1) << std::endl;
				std::cout << "Next tile up: " << (player.getRow() - 1) << std::endl;
				std::cout << "Next tile down: " << (player.getRow() + 1) << std::endl;
				std::cout << "===============" << std::endl;

				std::cout << "Time since last update: " << timeSinceLastUpdate.asSeconds() << std::endl;
				std::cout << "Elapsed Time: " << elapsedTime.asSeconds() << std::endl;
				std::cout << "===============" << std::endl;

				if (drawGridCells)
				{
					if (drawEmptyPath)
					{
						drawEmptyTiles(map, window);
					}
				}
				debug = false;
			}

			timeSinceLastUpdate -= TimePerFrame;

			window.clear();
			//DRAW GAME ELEMENTS
			window.draw(map.getSprite());
			window.draw(player.getSprite());
			window.draw(box);
			drawGrid(window);

			//CHATBOX TEST EVENT
			if(box.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()))
			{
				textBox.redrawChat(true); //SET IF THE CHATBOX IS REDRAWN OR NOT
			}

			//DISPLAY CHATBOX IF REDRAWCHAT IS SET TO TRUE, IGNORE IF SET TO FALSE. REDRAW AUTOMATICALLY SET TO FALSE WHEN PLAYER CLOSES LAST CHATBOX
			textBox.displayMessage(window);

			//DISPLAY DRAW COMPONENTS
			window.display();
		}
    }
    return 0;
}