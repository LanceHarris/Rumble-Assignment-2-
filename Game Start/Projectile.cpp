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

	firelight.setFillColor(sf::Color(255,255,255,40));
	firelight.setRadius(25);

	attack.setTexture(missileTexture);
	attack.setPosition(position.x,position.y);
	attack.setTextureRect(sf::IntRect(POSX,(FRAMEXY*currentFrame)+FRAMEGAP,10,10));
	attack.setScale(3,3);
}

Projectile::~Projectile(void)
{
}

Enemy* Projectile::attackHit(QuadTree *enemyTree){
	std::vector<Enemy *> enemies;
	enemies.clear();
	enemies = enemyTree->retrieve(enemies, sf::Vector2f(attack.getPosition().x,attack.getPosition().y));
	int i = 0;
	while(i < enemies.size()){
		bool xCollision = (attack.getPosition().x + 20 >= enemies[i]->getPosition().x) && (attack.getPosition().x < enemies[i]->getPosition().x + 24);
		bool yCollision = (attack.getPosition().y + 20 >= enemies[i]->getPosition().y) && (attack.getPosition().y < enemies[i]->getPosition().y + 24);
		if (xCollision && yCollision){
			return enemies[i];
		}
		i++;
	}
	return NULL;
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

int Projectile::getDirection()
{
	return direction;
}