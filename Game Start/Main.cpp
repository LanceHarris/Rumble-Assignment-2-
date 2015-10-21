//*MIGHT BE A GOOD IDEA TO PUT ANY NOTES YOU WANT TO LEAVE UP HERE*//

//TO DO: sprite doesn't animate when moving in diagonals yet, if someone wants to go ahead and implement that, go for it :)

#include <SFML/Graphics.hpp>
#include "ChatBox.h"

/*RENDERWINDOW SIZE*/
int winX = 1000;
int winY = 800;
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

int main()
{
    sf::RenderWindow window(sf::VideoMode(winX, winY), "SFML works!");
	window.setFramerateLimit(500);

	//BOX TO TEST CHATBOX TRIGGERING
	sf::RectangleShape box(sf::Vector2f(30,30));
	box.setPosition(500,600);

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
	sf::Texture ground;
	if(!ground.loadFromFile("sand.jpg"))
	{
	}
	ground.setRepeated(true);

	sf::Sprite background;
	background.setTexture(ground);
	background.setTextureRect(sf::IntRect(0, 0, winX, winY ));

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

		//CHARACTER MOVEMENT EVENTS AND CHECK BOUDNS
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !(playX >= winX-SPRITEWIDTH-5))
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

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !(playX <= 0))
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

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !(playY <= 0))
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

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !(playY >= winY-SPRITEWIDTH-5))
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

		//SET CURRENT PLAYER SPRITE THAT'S BEING USED. SPRITEGAP IS THE GAP BETWEEN EACH SPRITE, SPRITEWIDTH IS THE WIDTH OF EACH SPRITE
		player.setTextureRect(sf::IntRect((spriteXPos * SPRITEWIDTH) + (SPRITEGAP * spriteXPos)+SPRITEGAP ,(spriteYPos * SPRITEWIDTH) + (SPRITEGAP * spriteYPos)+SPRITEGAP  ,SPRITEWIDTH,SPRITEHEIGHT));

		window.clear();

		//ACTUALLY MOVE PLAYER SPRITE BASED ON UPDATE POSITION VALUES
		player.setPosition(playX,playY);

		//DRAW GAME ELEMENTS
		window.draw(background);
		window.draw(player);
		window.draw(box);

		//CHATBOX TEST EVENT
		if(box.getGlobalBounds().intersects(player.getGlobalBounds()))
			textBox.redrawChat(true); //SET IS THE CHATBOX IS REDRAWN OR NOT

		//DISPLAY CHATBOX IF REDRAWCHAT IS SET TO TRUE, IGNORE IF SET TO FALSE. REDRAW AUTOMATICALLY SET TO FALSE WHEN PLAYER CLOSES LAST CHATBOX
		textBox.displayMessage(window);

		//DISPLAY DRAW COMPONENTS
        window.display();

		

    }

    return 0;
}