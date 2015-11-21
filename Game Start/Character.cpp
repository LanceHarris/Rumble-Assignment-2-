/*
*	Character.cpp
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 25 October 2015
*
*/

#include "Character.h"
#include <cmath>

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

sf::Vector2f Character::getPosition()
{
	return sprite.getPosition();
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
int Character::getStamina()
{
	return stamina;
}


//Interesting note, if facing (enum) is returned as an int, or outputed with cout it displays as an integer value corresponding to it's position in the enum declartion (Up = 0; Right = 1; Down = 2; Left = 3;)
int Character::getFacing()
{
	return aiming;
}

Character::Character(int health, float speed, int stamina)
{
	this->health = health;
	this->speed = speed;
	this->stamina = stamina;
	if (!texture.loadFromFile("characterSheetCustom.png"))
	{
		std::cout << "Error loading resource characterSheetCustom.png" << std::endl;
	}
}

//GET HIT
bool Character::takeDamage(int Damage){
	health -= Damage;
	if (health <= 0){
		return true;
	}else{
		return false;
	}
}

void Character::knockback(Map &map, int &iterations, int Direction){
	int nextSpriteFrameEvery = 10; //used to determine how often the sprite is redrawn. Number represents number of frames. So 60 should equal 1 second.

	int height = SPRITEHEIGHT * sprite.getScale().y;
	int width = SPRITEWIDTH * sprite.getScale().x;

	sf::Vector2f pos = sprite.getPosition();
	switch (Direction)
	{
		case RIGHT:
			if (!map.isCollision( this->getRow(), this->getColumn() + ceil((float)width/24) ) && !map.isCollision( ((this->sprite.getPosition().y+height)/24) , this->getColumn() + ceil((float)width/24)))
			{
				pos.x += 12;

				if(iterations >= nextSpriteFrameEvery)
				{
					if(spriteXPos >= spriteXPosMax)
					{
					spriteXPos = spriteXPosMin;
					}
					else
					{
						spriteXPos+=1;
					}
					iterations = 0;
				}
			}
			//this->sprite.setTextureRect(sf::IntRect(right[frame] * 24, 0, 24, 24));
			break;
		case LEFT:
			if (!map.isCollision(this->getRow(), ((this->getSprite().getPosition().x+width)/24) - ceil((float)width/24) ) && !map.isCollision(((this->getSprite().getPosition().y+height)/24), ((this->getSprite().getPosition().x+width)/24) - ceil((float)width/24)))
			{
				pos.x -= 12;

				if(iterations >= nextSpriteFrameEvery)
				{
					if(spriteXPos >= spriteXPosMax)
					{
					spriteXPos = spriteXPosMin;
					}
					else
					{
						spriteXPos+=1;
					}
					iterations = 0;
				}
			}
			//this->sprite.setTextureRect(sf::IntRect(left[frame] * 24, 0, 24, 24));
			break;
		case UP:
			if (!map.isCollision( ((this->sprite.getPosition().y+height)/24) - ceil((float)height/24), this->getColumn()) && !map.isCollision( ((this->sprite.getPosition().y+height)/24) - ceil((float)height/24), ((this->sprite.getPosition().x+width)/24)))
			{
				pos.y -= 12;

				if(iterations >= nextSpriteFrameEvery)
				{
					if(spriteXPos >= spriteXPosMax)
					{
					spriteXPos = spriteXPosMin;
					}
					else
					{
						spriteXPos+=1;
					}
					iterations = 0;
				}
			}
			//this->sprite.setTextureRect(sf::IntRect(up[frame] * 24, 0, 24, 24)); - kept from the Pacman code
			break;
		case DOWN:
			if (!map.isCollision(this->getRow() + ceil((float)height/24), this->getColumn() ) && !map.isCollision(this->getRow() + ceil((float)height/24), (this->sprite.getPosition().x+width)/24))
			{
				pos.y += 12;

				if(iterations >= nextSpriteFrameEvery)
				{
					if(spriteXPos >= spriteXPosMax)
					{
					spriteXPos = spriteXPosMin;
					}
					else
					{
						spriteXPos+=1;
					}
					iterations = 0;
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

//MOVEMENT
void Character::walk(Map &map, int &iterations)
{
	int nextSpriteFrameEvery = 10; //used to determine how often the sprite is redrawn. Number represents number of frames. So 60 should equal 1 second.

	int height = floor(SPRITEHEIGHT * sprite.getScale().y);
	int width = floor(SPRITEWIDTH * sprite.getScale().x);

	sf::Vector2f pos = sprite.getPosition();
	switch (facing)
	{
		case RIGHT:
			if (!map.isCollision( this->getRow(), this->getColumn() + ceil((float)width/24) ) && !map.isCollision( ((this->sprite.getPosition().y+(height-2))/24) , this->getColumn() + ceil((float)width/24)))
			{
				pos.x += speed;

				if(iterations >= nextSpriteFrameEvery)
				{
					if(spriteXPos >= spriteXPosMax)
					{
						spriteXPos = spriteXPosMin;
					}
					else
					{
						spriteXPos+=1;
					}
					iterations = 0;
				}
			}
			//this->sprite.setTextureRect(sf::IntRect(right[frame] * 24, 0, 24, 24));
			break;
		case LEFT:
			if (!map.isCollision(this->getRow(), ((this->getSprite().getPosition().x+(width-2))/24) - ceil((float)width/24) ) && !map.isCollision(((this->getSprite().getPosition().y+(height-2))/24), ((this->getSprite().getPosition().x+(width-2))/24) - ceil((float)width/24)))
			{
				pos.x -= speed;

				if(iterations >= nextSpriteFrameEvery)
				{
					if(spriteXPos >= spriteXPosMax)
					{
						spriteXPos = spriteXPosMin;
					}
					else
					{
						spriteXPos+=1;
					}
					iterations = 0;
				}
			}
			//this->sprite.setTextureRect(sf::IntRect(left[frame] * 24, 0, 24, 24));
			break;
		case UP:
			if (!map.isCollision( ((this->sprite.getPosition().y+(height-2))/24) - ceil((float)height/24), this->getColumn()) && !map.isCollision( ((this->sprite.getPosition().y+(height-2))/24) - ceil((float)height/24), ((this->sprite.getPosition().x+(width-2))/24)))
			{
				pos.y -= speed;

				if(iterations >= nextSpriteFrameEvery)
				{
					if(spriteXPos >= spriteXPosMax)
					{
						spriteXPos = spriteXPosMin;
					}
					else
					{
						spriteXPos+=1;
					}
					iterations = 0;
				}
			}
			//this->sprite.setTextureRect(sf::IntRect(up[frame] * 24, 0, 24, 24)); - kept from the Pacman code
			break;
		case DOWN:
			if (!map.isCollision(this->getRow() + ceil((float)height/24), this->getColumn() ) && !map.isCollision(this->getRow() + ceil((float)height/24), (this->sprite.getPosition().x+(width-2))/24))
			{
				pos.y += speed;

				if(iterations >= nextSpriteFrameEvery)
				{
					if(spriteXPos >= spriteXPosMax)
					{
						spriteXPos = spriteXPosMin;
					}
					else
					{
						spriteXPos+=1;
					}
					iterations = 0;
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
 	this->sprite.setPosition(pos);
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

void Character::setStamina(int &stamina)
{
	this->stamina = stamina;
}

void Character::setSprite(sf::Sprite sprite)
{
	this->sprite = sprite;
}

Character::~Character()
{
}