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
#include "Map.h"

const int FRAMES = 4;

class Character
{
	public:
		enum Facing
		{
			UP,
			RIGHT,
			DOWN,
			LEFT
		};

		bool rowBoundary();
		bool columnBoundary();

		int getColumn();
		int getRow();

		enum Aiming
		{
			UPAIM,
			RIGHTAIM,
			DOWNAIM,
			LEFTAIM
		};

		void setHealth(int health);
		void setSpeed(float speed);
		void setAttack(int attack);
		void setToughness(int toughness);
		void setStamina(int &stamina);

		int getHealth();
		float getSpeed();
		int getAttack();
		int getToughness();
		int getStamina();

		void walk(Map &map);

		sf::Sprite getSprite();
		void setFacing(Facing facing);
		void turn(int direction);
		void setPosition(int row, int column);
		void takeDamage(int damage);

		int getFacing();

		Character(int health, float speed, int stamina);
		~Character();

	protected:
		Facing facing;
		Aiming aiming;

		int health;
		float speed;
		int attack;
		int toughness;
		int stamina;
		int frame;
		
		int spriteXPos;
		int spriteYPos;

		int SPRITEWIDTH;
		int SPRITEHEIGHT;
		int SPRITEMAX;
		int SPRITEGAP;

		static const int left[FRAMES];
		static const int right[FRAMES];
		static const int down[FRAMES];
		static const int up[FRAMES];

		sf::Sprite sprite;
		sf::Texture texture;
};


class Player: public Character{
public:
	Player(int &health, float &speed, int &stamina);
	~Player();
	int getGoldStash();

	//Potion stuff//
	int getHealthPotionNumber();
	int getStaminaPotionNumber();
	void removeHealthPotion();
	void removeStaminaPotion();

	int healthPotionNumber;
	int staminaPotionNumber;
	//End//

	void increaseGoldStash(int newGold);
	void useVitamin(char type);
};

class Enemy: public Character{
public:
	Enemy(int health, float speed, sf::Vector2f location);
	~Enemy();
	void calcMovement(Player target, Map map);
protected:
	enum Type
		{
			GHOST,
			ZOMBIE,
			SKELETON,
			HELLHOUND
		};
	float moveColumn;
	float moveRow;
};