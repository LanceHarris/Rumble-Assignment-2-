#include <SFML/Graphics.hpp>
#include "ChatBox.h"

/*CONSTANTS*/
int winX = 1000;
int winY = 800;
/*END*/

/*PLAYER CORDS*/
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
int spriteWidth = 16;
int spriteHeight = 16;
int spriteMax = 4;

int spriteXPos = 0;
int spriteYPos = 0;

int spriteGap = 3;
/*END*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(winX, winY), "SFML works!");
    sf::CircleShape shape(10.f);
    shape.setFillColor(sf::Color::Black);

	window.setFramerateLimit(500);

	sf::RectangleShape box(sf::Vector2f(30,30));
	box.setPosition(500,600);

	//ARGS = window x axis size, window y axis size, padding/gap below chatBox
	ChatBox textBox = ChatBox(winX,winY,30);
	textBox.setTextSettings("Retro Computer_DEMO.ttf", 19, sf::Color::White,35);
	textBox.SetCharaterLineLimit(55);

	sf::Clock timer;
	textBox.setMessage("Welcome to the Colloseum! Prepare to die! Nye hehheh hehheh hehheh hehheh *coughcough*! >_< Welcome to the Colloseum! Prepare to die! Nye hehheh hehheh hehheh hehheh *coughcough*! Welcome to the Colloseum! Prepare to die! Nye hehheh hehheh hehheh hehheh *coughcough*! Welcome to the Colloseum! Prepare to die! Nye hehheh hehheh hehheh hehheh *coughcough*! Welcome to the Colloseum! Prepare to die! Nye hehheh hehheh hehheh hehheh *coughcough*! ", window);

	sf::Texture ground;
	if(!ground.loadFromFile("sand.jpg"))
	{
	}
	ground.setRepeated(true);

	sf::Sprite background;
	background.setTexture(ground);
	background.setTextureRect(sf::IntRect(0, 0, winX, winY ));

	sf::Texture character;
	if(!character.loadFromFile("characterSheet.png"))
	{
	}
	sf::Sprite player;
	player.setTexture(character);
	player.setTextureRect(sf::IntRect(spriteGap,spriteGap,spriteWidth,spriteHeight));
	player.setPosition(200,200);
	player.setScale(1.5,1.5);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
				textBox.setNext(true);
        }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			playX+=speed;

			spriteYPos = 1;
			if(spriteXPos >= 3)
			{
				spriteXPos = 0;
			}
			else
			{
				spriteXPos+=1;
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
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

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
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

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
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

		player.setTextureRect(sf::IntRect((spriteXPos * spriteWidth) + (spriteGap * spriteXPos)+spriteGap ,(spriteYPos * spriteWidth) + (spriteGap * spriteYPos)+spriteGap  ,spriteWidth,spriteHeight));
		//Check bounds
		if(playX>=1016)
			playX = 0;
		else if(playX <= -32)
			playX = 1000;
		else if(playY >= 816)
			playY = 0;
		else if (playY <= -32)
			playY = 800;


		window.clear();
		player.setPosition(playX,playY);
		//Display message with text
		window.draw(background);
		window.draw(player);
		window.draw(box);

		if(box.getGlobalBounds().intersects(player.getGlobalBounds()))
			textBox.redrawChat(true);

		textBox.displayMessage(window);


        window.display();

		

    }

    return 0;
}