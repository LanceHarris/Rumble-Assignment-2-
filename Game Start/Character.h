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
			LEFT,
			RIGHT,
			UP,
			DOWN
		};

		bool rowBoundary();
		bool columnBoundary();

		int getColumn();
		int getRow();

		void setHealth(int &health);
		void setSpeed(float &speed);
		void setAttack(int &attack);
		void setToughness(int &toughness);
		int getHealth();
		float getSpeed();
		int getAttack();
		int getToughness();

		void walk(Map map);
		sf::Sprite getSprite();
		void setFacing(Facing facing);
		void turn(int direction);
		void setPosition(int row, int column);

		int getFacing();

		Character(int &health, float &speed);
		~Character();

	private:
		Facing facing;

		int health;
		float speed;
		int attack;
		int toughness;
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

