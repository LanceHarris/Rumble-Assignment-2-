/*
*	Character.h
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 25 October 2015
*
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"

class Projectile
{


private:
	sf::Sprite attack;
	sf::Vector2f position;
	bool isPlayerProjectile;
	float damage;
	int direction;
	int speed;

	static const int FRAMES = 8;
	static const int FRAMEGAP = 1;
	static const int FRAMEXY = 10;
	static const int POSX = 82;

	int currentFrame;
	int axeYPos;

public:
	Projectile(bool aIsPlayerAttack, int aDirection, float aDamage, sf::Vector2f userPosition, int aSpeed, sf::Texture &missileTexture);
	~Projectile(void);
	void updateProjectileLocation(sf::RenderWindow &window);
	int attackHit(std::vector<Enemy> enemies);
	float getPosX();
	float getPosY();
	int getRow();
	int getColumn();
};

