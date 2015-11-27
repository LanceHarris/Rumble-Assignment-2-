/*
*	Hud.h
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 2 November 2015
*
*/

#pragma once

#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Character.h"

using namespace std;

class Hud
{
private:
	bool gameOver;
	bool outOfStamina;
	float repercussion;
	sf::RenderWindow *_window;
	Player *_player;

	//====HEALTH BAR=====
	int max_HP;					//The maximum player hitpoints
	int current_HP;				//The current player HP
	int maxLength;				//The maximum length of the HP bar
	int currLength;				//The current length of the HP bar
	sf::RectangleShape healthBar;

	//====STAMINA BAR====
	int max_Sta;
	float current_Sta;
	int maxSLength;
	float currSLength;
	float regenSpeed;
	sf::RectangleShape staminaBar;

	//====CROWD METER====
	sf::Sprite crowdDial;
	sf::Sprite crowdMeterOverlay;

	sf::Texture meterTexture1;
	sf::Texture meterTexture2;
	sf::Texture meterTexture3;
	sf::Texture meterTexture4;

	sf::Texture actionBar;
	sf::Sprite actionBarSprite;
	sf::Text itemAmountsHealthPot;
	sf::Text itemAmountsStamPot;
	sf::Text itemAmountsHealthVit;
	sf::Text itemAmountsStamVit;
	sf::Text itemAmountsStrVit;
	sf::Font font;

	sf::Texture dialTexture;

	//====GOLD COUNT====
	sf::Sprite coin;
	int coinXPos;
	int coinGap;
	int coinWidth;
	int coinHeight;
	sf::Texture coinTexture;
	sf::Text goldCount;
	sf::Font goldFont;

	//====SCORE====
	sf::Text playerScore;
	int red, green, blue;

public:
	Hud(Player &player, sf::RenderWindow &window);

	void takeStamina(float stamina);
	void drawHUD();
	void updateStamina();
	void updateCoin(int &iterations);
	void healHealth();
	bool getGameOver();
	bool getOutOfStamina();
	void setStaminaBarAttributes(int choice);

	void increaseMaxHP(int newHP);
	void increaseMaxSta(int newSta);

	//Potions
	bool useHealthPotion(int potionLevel, Player &player);
	bool useStaminaPotion(int potionLevel, Player &player);

	//Crowd Meter
	sf::Sprite & getCrowdDial();
	void updateCrowdMeter();
	void increaseCrowdMeter(int amount);
	float calculateMultiplier();

	string NumberToString( int Number); //for conversion of int to strings
	void updateActionbar(int healthPot, int stamPot, int healthVit, int stamVit, int strVit);

	//Player Score
	void updatePlayersScore(Player &player, sf::RenderWindow &window);
	void popPlayerScore();

	~Hud(void);
};

