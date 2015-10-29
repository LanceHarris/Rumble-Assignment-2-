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

class Projectile
{


private:
	sf::Sprite attack;
	sf::Texture attackTexture;
	sf::Vector2f position;
	bool isPlayerProjectile;
	float damage;
	int direction;
	int speed;

public:
	Projectile(bool aIsPlayerAttack, int aDirection, float aDamage, sf::Vector2f userPosition, int aSpeed);
	~Projectile(void);
	void updateProjectileLocation(sf::RenderWindow &window);
	float getPosX();
	float getPosY();
	int getRow();
	int getColumn();
};

