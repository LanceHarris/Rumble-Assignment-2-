/*
*	Character.cpp
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 25 October 2015
*
*/

#include "Character.h"

//These FRAMES are currently not used to determine which frame to display, just kept in from the Pacman code
const int Character::left[FRAMES] = { 12,13,14,15 };
const int Character::right[FRAMES] = { 4,5,6,7 };
const int Character::down[FRAMES] = { 8,9,10,11 };
const int Character::up[FRAMES] = { 0,1,2,3 };

/*
bool Character::rowBoundary()
{
	return ((int)sprite.getPosition().y % 24 == 0);
}
bool Character::columnBoundary()
{
	return ((int)sprite.getPosition().x % 24 == 0);
}
*/

int Character::getColumn()
{
	return sprite.getPosition().x / 24;
}
int Character::getRow()
{
	return sprite.getPosition().y / 24;
}

//Mutator and accessor methods for character attributes (NB: some of these may need to be moved to the Player or Enemy classes at a later date)
void Character::setHealth(int &health)
{
	this->health = health;
}
void Character::setSpeed(float &speed)
{
	this->speed = speed;
}
void Character::setAttack(int &attack)
{
	this->attack = attack;
}
void Character::setToughness(int &toughness)
{
	this->toughness = toughness;
}
int Character::getHealth()
{
	return health;
}
float Character::getSpeed()
{
	return speed;
}
int Character::getAttack()
{
	return attack;
}
int Character::getToughness()
{
	return toughness;
}

//Interesting note, if facing (enum) is returned as an int, or outputed with cout it displays as an integer value corresponding to it's position in the enum declartion (left = 0, right = 1, down = 2, up = 3)
int Character::getFacing()
{
	return facing;
}

Character::Character(int &health, float &speed)
{
	spriteXPos = 0;
	spriteYPos = 0;
	SPRITEWIDTH = 16;
	SPRITEHEIGHT = 16;
	SPRITEMAX = 4;
	SPRITEGAP = 3;
	this->health = health;
	this->speed = speed;

	if (!texture.loadFromFile("characterSheet.png"))
	{
		std::cout << "Error loading resource characterSheet.png" << std::endl;
	}

	/*
	sf::Image characterImage = texture.copyToImage();
	//Create a transparency mask from a specified color-key. This function sets the alpha value of every pixel matching the given color to alpha (0 by default), 
	//so that they become transparent.
	characterImage.createMaskFromColor(sf::Color(0, 0, 0), 0);

	if (!texture.loadFromImage(characterImage))
	{
		std::cout << "Error masking image resource characterSheet.png" << std::endl;
	}
	*/

	this->sprite.setTexture(texture);
	//this->sprite.setTextureRect(sf::IntRect(right[frame]*16, 0,16,16));
	this->sprite.setTextureRect(sf::IntRect(SPRITEGAP,SPRITEGAP,SPRITEWIDTH,SPRITEHEIGHT));
	this->sprite.setScale(1.5, 1.5);
	this->facing = RIGHT;
}

void Character::walk(Map map)
{
	sf::Vector2f pos = sprite.getPosition();
	switch (facing)
	{
		case RIGHT:
			pos.x += speed;

			spriteYPos = 1; //THE LEVEL OF THE SPRITE MAP THAT'S BEING USED, DIRECTION FACING: (Up = 0; Right = 1; Down = 2; Left = 3;)
			if(spriteXPos >= 3)
			{
				spriteXPos = 0;
			}
			else
			{
				spriteXPos+=1;
			}
			//this->sprite.setTextureRect(sf::IntRect(right[frame] * 24, 0, 24, 24));
			break;
		case LEFT:
			pos.x -= speed;

			spriteYPos = 3;
			if(spriteXPos >= 3)
			{
				spriteXPos = 0;
			}
			else
			{
				spriteXPos+=1;
			}
			//this->sprite.setTextureRect(sf::IntRect(left[frame] * 24, 0, 24, 24));
			break;
		case UP:
			pos.y -= speed;

			spriteYPos = 0;
			if(spriteXPos >= 3)
			{
				spriteXPos = 0;
			}
			else
			{
				spriteXPos+=1;
			}
			//this->sprite.setTextureRect(sf::IntRect(up[frame] * 24, 0, 24, 24)); - kept from the Pacman code
			break;
		case DOWN:
			pos.y += speed;

			spriteYPos = 2;
			if(spriteXPos >= 3)
			{
				spriteXPos = 0;
			}
			else
			{
				spriteXPos+=1;
			}
			//this->sprite.setTextureRect(sf::IntRect(down[frame] * 24, 0, 24, 24));
			break;
		default:
			std::cout << "this is an error";
			break;
	}
	//frame = (frame + 1) % 2; - kept from the Pacman code

	//SET CURRENT PLAYER SPRITE THAT'S BEING USED. SPRITEGAP IS THE GAP BETWEEN EACH SPRITE, SPRITEWIDTH IS THE WIDTH OF EACH SPRITE
	this->sprite.setTextureRect(sf::IntRect((spriteXPos * SPRITEWIDTH) + (SPRITEGAP * spriteXPos)+SPRITEGAP ,(spriteYPos * SPRITEWIDTH) + (SPRITEGAP * spriteYPos)+SPRITEGAP  ,SPRITEWIDTH,SPRITEHEIGHT));
	sprite.setPosition(pos);
}

sf::Sprite Character::getSprite()
{
	return sprite;
}

void Character::setFacing(Facing facing)
{
	this->facing = facing;
}

//Overrides setPosition to take a cell location (instead of a pixel location)
void Character::setPosition(int row, int column)
{
	sprite.setPosition(row * 24, column * 24);
}

//Turns the player the direction they want to go regardless of whether it's into a wall
void Character::turn(int direction)
{
	spriteYPos = direction;
	this->sprite.setTextureRect(sf::IntRect((spriteXPos * SPRITEWIDTH) + (SPRITEGAP * spriteXPos)+SPRITEGAP ,(spriteYPos * SPRITEWIDTH) + (SPRITEGAP * spriteYPos)+SPRITEGAP  ,SPRITEWIDTH,SPRITEHEIGHT));
}

Character::~Character()
{
}