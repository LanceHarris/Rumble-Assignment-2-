/*
*	Character.h
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 25 October 2015
*
*/

#include "Projectile.h"


Projectile::Projectile(bool aIsPlayerAttack, int aDirection, float aDamage, sf::Vector2f userPosition, int aSpeed)
{
	isPlayerProjectile = aIsPlayerAttack;
	damage = aDamage;
	direction = aDirection;
	position = userPosition;
	speed = aSpeed;

	if(!attackTexture.loadFromFile("sand.jpg"))
	{
		std::cout << "Error loading projectile texture" << std::endl;
	}
	attack.setTexture(attackTexture);
	attack.setPosition(position.x,position.y);
}

Projectile::~Projectile(void)
{
}

void Projectile::updateProjectileLocation(sf::RenderWindow &window)
{
	switch(direction)
	{
	case 0:
		position.x -= speed;
		break;
	case 1:
		position.x += speed;
		break;
	case 2:
		position.y -= speed;
		break;
	case 3:
		position.y += speed;
		break;

	}

	attack.setPosition(position.x,position.y);
	window.draw(attack);
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
