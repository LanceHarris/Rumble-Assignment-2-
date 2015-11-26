/*
*	Coin.h
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 24 November 2015
*
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Character.h"
#include "Hud.h"

#include <random>

class Coin
{
public:
	void updateCoinDrop(sf::RenderWindow &window, Player & player, int &iterations);
	void pickedUpCoin(Player & player, sf::Sound &sound, Hud & hud);
	bool getConsumed();

	Coin();
	Coin(Enemy &enemy, sf::Texture coinTexture);
	~Coin(void);

private:
	sf::Sprite coin;
	sf::Texture coinTexture;
	int amount;					//The amount of gold you get
	bool pickedUp, consumed; 
	int increment;				//To create the effect of adding gold over time
	int coinXPos, coinGap, coinWidth, coinHeight;

};

