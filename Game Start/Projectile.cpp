/*
*	projectile.h
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 30 October 2015
*
*/

#include "Projectile.h"
#include "Character.h"


Projectile::Projectile(bool aIsPlayerAttack, int aDirection, float aDamage, sf::Vector2f userPosition, int aSpeed, sf::Texture &missileTexture, int choice)
{
	isPlayerProjectile = aIsPlayerAttack;
	damage = aDamage;
	direction = aDirection;
	position = userPosition;
	speed = aSpeed;
	currentFrame = 0;
	this-> choice = choice;

	//WARRIOR
	if(choice == 0)
	{
		POSX = 97;
	}
	//WIZARD
	else if (choice == 1)
	{
		POSX = 207;
	}

	firelight.setFillColor(sf::Color(255,255,255,20));
	firelight.setRadius(25);

	attack.setTexture(missileTexture);
	attack.setPosition(position.x,position.y);
	attack.setTextureRect(sf::IntRect(POSX,(FRAMEXY*currentFrame)+FRAMEGAP,10,10));
	attack.setScale(3,3);
}

Projectile::~Projectile(void)
{
}

int Projectile::attackHit(std::vector<Enemy> enemies){
	for(int i = 0; i < enemies.size();i++)
			{
				std::cout << getRow() << " " << enemies[i].getRow() << std::endl;
				std::cout << getColumn() << " " << enemies[i].getColumn() << std::endl << std::endl;
				if ((getRow() == enemies[i].getRow()) && (getColumn() == enemies[i].getColumn())){
					return i;
				}
			}
	return 1000; //1000 = no hit
}

void Projectile::updateProjectileLocation(sf::RenderWindow &window)
{

	switch(direction)
	{
	case 0: //UP
		position.y -= speed;
		break;
	case 1: //RIGHT
		position.x += speed;
		break;
	case 2: //DOWN
		position.y += speed;
		break;
	case 3: //LEFT
		position.x -= speed;
		break;

	}

	attack.setPosition(position.x,position.y);
	window.draw(attack);

	if(choice == 1)
	{	
		firelight.setPosition(position.x - attack.getGlobalBounds().width/2 + 4,position.y - attack.getGlobalBounds().height/2 + 4);
		window.draw(firelight);
	}

	attack.setTextureRect(sf::IntRect(POSX,(FRAMEXY*currentFrame)+(currentFrame*FRAMEGAP)+FRAMEGAP,10,10));
	currentFrame++;
	if(currentFrame >= 8)
		currentFrame = 0;
}

float Projectile::getPosX()
{
	return position.x;
}

float Projectile::getPosY()
{
	return position.y;
}

int Projectile::getRow()
{
	return position.y / 24;
}

int Projectile::getColumn()
{
	return position.x / 24;
}
