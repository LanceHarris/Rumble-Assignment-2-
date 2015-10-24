//*MIGHT BE A GOOD IDEA TO PUT ANY NOTES YOU WANT TO LEAVE UP HERE*//

//TO DO: sprite doesn't animate when moving in diagonals yet, if someone wants to go ahead and implement that, go for it :)

#include <SFML/Graphics.hpp>
#include "ChatBox.h"
#include "Map.h"

/*RENDERWINDOW SIZE*/
int winX = 1080; //45 cells
int winY = 840; //35 cells
/*END*/

/*PLAYER CORDS, CHANGE TO CHANGE STARTING POSITION*/
float playX = 200;
float playY = 200;
/*END*/

/*PLAYER STATS*/
int speed = 1;
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
void drawGrid(sf::RenderWindow &window)
{
		int x = 0; //reset x to redraw grid
		int y = winY; //reset y to redraw grid
		for(int i = 0; i<winX/20; i++) //begin loop through to draw grid
		{
		
		//define vertical line vertexes
		x+=24;
		sf::Vertex lineVert[] = {

			sf::Vertex(sf::Vector2f(x, 0),sf::Color(0, 0, 0, 24)),
			sf::Vertex(sf::Vector2f(x, winY),sf::Color(0, 0, 0, 24)),

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

//COLOURS EMPTY TILES CYAN FOR DEBUGGING PURPOSES
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
	window.setFramerateLimit(500);

	//SET BOTH TO TRUE IF YOU WANT TO COLOUR IN THE EMPTY CELLS WITH CYAN
	bool drawGridCells = false;
	bool drawEmptyPath = false;

	Map map(winX, winY);

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

	//TIMER NOT USED YET
	sf::Clock timer;

	//BACKGROUND TEXTURE
	/*
	sf::Texture ground;
	if(!ground.loadFromFile("sand.jpg"))
	{
	}
	ground.setRepeated(true);

	sf::Sprite background;
	background.setTexture(ground);
	background.setTextureRect(sf::IntRect(0, 0, winX, winY ));
	*/


	//CHARACTER TEXTURE AND SPRITE
	sf::Texture character;
	if(!character.loadFromFile("characterSheet.png"))
	{
	}
	sf::Sprite player;
	player.setTexture(character);
	player.setTextureRect(sf::IntRect(SPRITEGAP,SPRITEGAP,SPRITEWIDTH,SPRITEHEIGHT));
	player.setPosition(200,200);
	player.setScale(1.5,1.5);
	player.setOrigin(player.getGlobalBounds().height/2, player.getGlobalBounds().width/2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

			//PROGRESS OR CLOSE CHATBOX
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
				textBox.setNext(true);
        }

		//CHARACTER MOVEMENT EVENTS AND CHECK BOUNDS
		//RIGHT
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !(playX >= winX-SPRITEWIDTH-5))
		{
			//CHECK IF THE NEXT POSITION IN THE DIRECTION THE PLAYER IS HEADING ON THE MAP IS A COLLISION
			//Going by JC's example, player.getPosition.y/24 will eventually be replaced with something like player.getRow(); (referring to the object) etc etc
			if (!map.isCollision(player.getPosition().y / 24, player.getPosition().x / 24 + 1))
			{
				playX+=speed;

				spriteYPos = 1; //THE LEVEL OF THE SPRITE MAP THAT'S BEING USED, DIRECTION FACING: (Up = 0; Right = 1; Down = 2; Left = 3;)
				if(spriteXPos >= 3)
				{
					spriteXPos = 0;
				}
				else
				{
					spriteXPos+=1;
				}
			}
		}

		//LEFT
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !(playX <= 0))
		{
			if (!map.isCollision(player.getPosition().y / 24, player.getPosition().x / 24 - 1))
			{
				playX-=speed;

				spriteYPos = 3;
				if(spriteXPos >= 3)
				{
					spriteXPos = 0;
				}
				else
				{
					spriteXPos+=1;
				}
			}
		}

		//UP
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !(playY <= 0))
		{
			if (!map.isCollision(player.getPosition().y / 24 - 1, player.getPosition().x / 24))
			{
				playY-=speed;

				spriteYPos = 0;
				if(spriteXPos >= 3)
				{
					spriteXPos = 0;
				}
				else
				{
					spriteXPos+=1;
				}
			}
		}

		//DOWN
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !(playY >= winY-SPRITEWIDTH-5))
		{
			if (!map.isCollision(player.getPosition().y / 24 + 1, player.getPosition().x / 24))
			{
				playY+=speed;

				spriteYPos = 2;
				if(spriteXPos >= 3)
				{
					spriteXPos = 0;
				}
				else
				{
					spriteXPos+=1;
				}
			}
		}

		//SET CURRENT PLAYER SPRITE THAT'S BEING USED. SPRITEGAP IS THE GAP BETWEEN EACH SPRITE, SPRITEWIDTH IS THE WIDTH OF EACH SPRITE
		player.setTextureRect(sf::IntRect((spriteXPos * SPRITEWIDTH) + (SPRITEGAP * spriteXPos)+SPRITEGAP ,(spriteYPos * SPRITEWIDTH) + (SPRITEGAP * spriteYPos)+SPRITEGAP  ,SPRITEWIDTH,SPRITEHEIGHT));

		window.clear();

		//ACTUALLY MOVE PLAYER SPRITE BASED ON UPDATE POSITION VALUES
		player.setPosition(playX,playY);

		//DRAW GAME ELEMENTS
		window.draw(map.getSprite());
		//window.draw(background);

		if (drawGridCells)
		{
			if (drawEmptyPath)
			{
				drawEmptyTiles(map, window);
			}
		}

		window.draw(player);
		window.draw(box);

		//CHATBOX TEST EVENT
		if(box.getGlobalBounds().intersects(player.getGlobalBounds()))
			textBox.redrawChat(true); //SET IS THE CHATBOX IS REDRAWN OR NOT

		//DISPLAY CHATBOX IF REDRAWCHAT IS SET TO TRUE, IGNORE IF SET TO FALSE. REDRAW AUTOMATICALLY SET TO FALSE WHEN PLAYER CLOSES LAST CHATBOX
		textBox.displayMessage(window);

		drawGrid(window);
		//DISPLAY DRAW COMPONENTS
        window.display();

		

    }

    return 0;
}