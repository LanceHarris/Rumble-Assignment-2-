/*
*	Enemy.cpp
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 30 October 2015
*
*/

#include "Character.h"

Enemy::Enemy(int health, float speed, int attack, Type type, sf::Vector2f location, sf::Texture enemyTexture): Character(health, speed, stamina)
{
	this->texture = enemyTexture;

	spriteXPos = 14;
	spriteYPos = 0;
	SPRITEWIDTH = 16;
	SPRITEHEIGHT = 16;
	SPRITEMAX = 4;
	SPRITEGAP = 1;

	spriteXPosMax = 16;
	spriteXPosMin = 14;

	sprite.setTexture(texture);

	switch(type)
	{
		case ZOMBIE:
			sprite.setTextureRect(sf::IntRect(SPRITEGAP,SPRITEGAP,SPRITEWIDTH,SPRITEHEIGHT));
			sprite.setScale(1.5, 1.5);
			break;
		case BOSS:
			sprite.setTextureRect(sf::IntRect(SPRITEGAP,SPRITEGAP,SPRITEWIDTH,SPRITEHEIGHT));
			sprite.setScale(2.6, 2.6);
			break;
	}
	
	sprite.setPosition(location.x * 24, location.y * 24);
	facing = RIGHT;

	moveColumn = 0;
	moveRow = 0;

	attackTimer = 0;
	fullHealth = health;
	this->attack = attack;
	this->type = type;
}

bool Enemy::calcMovement(Player target, Map &map, int &iterations){

	moveRow = getRow() - target.getRow();
	moveColumn = getColumn() - target.getColumn();

	if (moveRow == 0 && moveColumn == 0){
		if (attackTimer <= 0){
			//take damage
			target.knockback(map,iterations,facing);
			attackTimer = 30;
			return true;
		}
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

	if (moveColumn >= 1)
	{
		moveColumn -= 1;
		facing=LEFT;
	}
	else if (moveColumn <= -1)
	{
		moveColumn += 1;
		facing=RIGHT;
	}
	if (moveRow >= 1)
	{
		moveRow -= 1;
		facing=UP;
	}
	else if (moveRow <= -1)
	{
		moveRow += 1;
		facing=DOWN;
	}

	//This is making the enemies animate really fast
	if(spriteXPos >= spriteXPosMax)
	{
		spriteXPos = spriteXPosMin;
	}
	else
	{
		spriteXPos+=1;
	}

	this->turn(facing); //sets the enemy facing the right way
	return false;
}

int Enemy::getFHealth(){
	return fullHealth;
}

Enemy::~Enemy()
{
}