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
void Character::setHealth(int health)
{
	this->health = health;
}
void Character::setSpeed(float speed)
{
	this->speed = speed;
}
void Character::setAttack(int attack)
{
	this->attack = attack;
}
void Character::setToughness(int toughness)
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

//Interesting note, if facing (enum) is returned as an int, or outputed with cout it displays as an integer value corresponding to it's position in the enum declartion (Up = 0; Right = 1; Down = 2; Left = 3;)
int Character::getFacing()
{
	return aiming;
}

Character::Character(int health, float speed)
{
	this->health = health;
	this->speed = speed;
}

//GET HIT
void Character::takeDamage(int Damage){
	setHealth(health - Damage);
}

//MOVEMENT
void Character::walk(Map &map)
{
	sf::Vector2f pos = sprite.getPosition();
	switch (facing)
	{
		case RIGHT:
			if (!map.isCollision( this->getRow(), this->getColumn() + 1 ) && !map.isCollision( ((this->sprite.getPosition().y+18)/24) , this->getColumn() + 1))
			{
				pos.x += speed;

				
				if(spriteXPos >= 3)
				{
					spriteXPos = 0;
				}
				else
				{
					spriteXPos+=1;
				}
			}
			//this->sprite.setTextureRect(sf::IntRect(right[frame] * 24, 0, 24, 24));
			break;
		case LEFT:
			if (!map.isCollision(this->getRow(), ((this->getSprite().getPosition().x+18)/24) - 1 ) && !map.isCollision(((this->getSprite().getPosition().y+18)/24), ((this->getSprite().getPosition().x+18)/24) - 1 ))
			{
				pos.x -= speed;

				
				if(spriteXPos >= 3)
				{
					spriteXPos = 0;
				}
				else
				{
					spriteXPos+=1;
				}
			}
			//this->sprite.setTextureRect(sf::IntRect(left[frame] * 24, 0, 24, 24));
			break;
		case UP:
			if (!map.isCollision( ((this->sprite.getPosition().y+18)/24) - 1, this->getColumn()) && !map.isCollision( ((this->sprite.getPosition().y+18)/24) - 1, ((this->sprite.getPosition().x+18)/24)))
			{
				pos.y -= speed;

				
				if(spriteXPos >= 3)
				{
					spriteXPos = 0;
				}
				else
				{
					spriteXPos+=1;
				}
			}
			//this->sprite.setTextureRect(sf::IntRect(up[frame] * 24, 0, 24, 24)); - kept from the Pacman code
			break;
		case DOWN:
			if (!map.isCollision(this->getRow() + 1, this->getColumn() ) && !map.isCollision(this->getRow() + 1, (this->sprite.getPosition().x+18)/24))
			{
				pos.y += speed;

				
				if(spriteXPos >= 3)
				{
					spriteXPos = 0;
				}
				else
				{
					spriteXPos+=1;
				}
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
//END OF MOVEMENT

//Turns the player the direction they want to go regardless of whether it's into a wall
void Character::turn(int direction)
{
	//(Up = 0; Right = 1; Down = 2; Left = 3;)
	if (direction == 0)
	{
		this->aiming = UPAIM;
		spriteYPos = 0;
	}
	else if (direction == 1)
	{
		this->aiming = RIGHTAIM;
		spriteYPos = 1; //THE LEVEL OF THE SPRITE MAP THAT'S BEING USED, DIRECTION FACING: (Up = 0; Right = 1; Down = 2; Left = 3;)
	}
	else if (direction == 2)
	{
		this->aiming = DOWNAIM;
		spriteYPos = 2;
	}
	else //must be 3
	{
		this->aiming = LEFTAIM;
		spriteYPos = 3;
	}

	spriteYPos = direction;
	this->sprite.setTextureRect(sf::IntRect((spriteXPos * SPRITEWIDTH) + (SPRITEGAP * spriteXPos)+SPRITEGAP ,(spriteYPos * SPRITEWIDTH) + (SPRITEGAP * spriteYPos)+SPRITEGAP  ,SPRITEWIDTH,SPRITEHEIGHT));
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

Character::~Character()
{
}