/*
*	Player.cpp
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 25 October 2015
*
*/

#include "Character.h"

Player::Player(int &health, float &speed, int &stamina) : Character(health, speed, stamina)
{
	spriteXPos = 0;
	spriteYPos = 0;
	SPRITEWIDTH = 16;
	SPRITEHEIGHT = 16;
	SPRITEMAX = 4;
	SPRITEGAP = 3;
	if (!texture.loadFromFile("characterSheet.png"))
	{
		std::cout << "Error loading resource characterSheet.png" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(SPRITEGAP,SPRITEGAP,SPRITEWIDTH,SPRITEHEIGHT));
	sprite.setScale(1.5, 1.5);
	facing = RIGHT;
}

Player::~Player()
{
}