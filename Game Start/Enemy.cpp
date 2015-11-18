/*
*	Enemy.cpp
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 30 October 2015
*
*/

#include "Character.h"

Enemy::Enemy(int health, float speed, int attack, sf::Vector2f location): Character(health, speed, stamina)
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

	
	sprite.setPosition(location.x * 24, location.y * 24);
	moveColumn = 0;
	moveRow = 0;
	fullHealth = health;
	this->attack = attack;
}

bool Enemy::calcMovement(Player target, Map map){
	moveRow = getRow() - target.getRow();
	moveColumn = getColumn() - target.getColumn();

	if (moveRow == 0 && moveColumn == 0){
		//std::cout << "YOU LOSE" << std::endl;
		moveRow = 0;
		moveColumn = 0;
		return true;
	}else if (abs(moveRow/moveColumn) <= 1){
		moveRow = moveRow/abs(moveColumn);
		if (moveColumn > 0){
			moveColumn = 1;
		}
		else{
			moveColumn = -1;
		}
	}else{
		moveColumn = moveColumn/abs(moveRow);
		if (moveRow > 0){
			moveRow = 1;
		}
		else{
			moveRow = -1;
		}
	}
	this->moveColumn += moveColumn;
	this->moveRow += moveRow;
	
	/*std::cout << "Player location: " << target.getColumn() << ", " << target.getRow() << std::endl;
	std::cout << "Enemy Location: " << getColumn() << ", " << getRow() << std::endl;
	std::cout << "Movement Needed: " <<getColumn() - target.getColumn() << ", " << getRow() - target.getRow() << std::endl;
	std::cout << "Enemy movement: " << moveColumn << ", " << moveRow << std::endl;*/

	if (moveColumn >= 1){
		moveColumn -= 1;
		facing=LEFT;
	}else if (moveColumn <= -1){
		moveColumn += 1;
		facing=RIGHT;
	}
	if (moveRow >= 1){
		moveRow -= 1;
		facing=UP;
	}else if (moveRow <= -1){
		moveRow += 1;
		facing=DOWN;
	}
	return false;
}

int Enemy::getFHealth(){
	return fullHealth;
}

Enemy::~Enemy()
{
}