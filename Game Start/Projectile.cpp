/*
*	projectile.h
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 30 October 2015
*
*/

#include "Projectile.h"


Projectile::Projectile(bool aIsPlayerAttack, int aDirection, float aDamage, sf::Vector2f userPosition, int aSpeed, sf::Texture &missileTexture)
{
	isPlayerProjectile = aIsPlayerAttack;
	damage = aDamage;
	direction = aDirection;
	position = userPosition;
	speed = aSpeed;
	currentFrame = 0;

	attack.setTexture(missileTexture);
	attack.setPosition(position.x,position.y);
	attack.setTextureRect(sf::IntRect(POSX,(FRAMEXY*currentFrame)+FRAMEGAP,10,10));
	attack.setScale(3,3);
}

Projectile::~Projectile(void)
{
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
