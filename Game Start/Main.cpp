/*
*	Main.cpp
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 20 October 2015
*
*/

/*TO DO: 
Create Player and Enemy class as subclasses of Character class
*/

/*NOTES:
Player size after 1.5 scaling: 24

*/

#include <SFML/Graphics.hpp>
#include "ChatBox.h"
#include "Map.h"
#include "Character.h"
#include "Projectile.h"

#include <list>
#include <cmath>


/*RENDERWINDOW SIZE*/
int winX = 1080; //45 cells
int winY = 840; //35 cells
/*END*/

/*PLAYER STATS*/
float speed = 6;
int attack = 1;
int toughness = 1;
int health = 1;
/*END*/

//SPEED OF THE GAME
const float GAME_SPEED = 60.0f; //The bigger this number is the more often frames are updated
sf::Time TimePerFrame = sf::seconds(1.0f / GAME_SPEED);
/*END*/

//**GAME STATE**//
bool state = 0;
int characterSelection;
//**END**//


//**MAPS**//
int mainMap[Map::ROW_COUNT][Map::COLUMN_COUNT] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 3, 2, 1, 0, 0, 1, 1, 0, 0, 1, 2, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 3, 2, 2, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};


int secondMap[Map::ROW_COUNT][Map::COLUMN_COUNT] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

//int *maps[2] = {*mainMap,*secondMap}; // it'd be ideal to use a array like this of pointers to each map, and then just change a indexValue variable to change which map was being loaded,
//but having some issues being able to pass usable pointers, so I'm giving up for now, if anyone feels like trying to get this to work, go for it :D

//**END**//
void drawGrid(sf::RenderWindow &window)
{
		int x = 0; //reset x to redraw grid
		int y = winY; //reset y to redraw grid
		for(int i = 0; i<winX/20;i++) //begin loop through to draw grid
		{
		
		//define vertical line vertexes
		x+=24;
		sf::Vertex lineVert[] = {

			sf::Vertex(sf::Vector2f(x, 0),sf::Color(0, 0, 0, 24)),
			sf::Vertex(sf::Vector2f(x, winY),sf::Color(40, 0, 0, 24)),

			};

		//define horizontal line vertexes
		y-=24;
		sf::Vertex lineHori[] = {

			sf::Vertex(sf::Vector2f(0, y),sf::Color(0, 0, 0, 24)),
			sf::Vertex(sf::Vector2f(winX,y),sf::Color(0, 0, 0, 24)),

			};

		window.draw(lineVert, 2, sf::Lines); //draw vertical lines
		window.draw(lineHori, 2, sf::Lines); //draw horizontal lines

		}
}

//COLOURS EMPTY TILES (or any others that you specify) CYAN FOR DEBUGGING PURPOSES
void drawEmptyTiles(Map &map, sf::RenderWindow &window)
{
	for (int row = 0; row < map.COLUMN_COUNT; row++)
	{
		for (int col = 0; col < map.ROW_COUNT; col++)
		{
			Map::Tile tile = map.getTile(col, row);
			if (tile == Map::Tile::TileEmpty)
			{
				sf::RectangleShape rectangle;
				rectangle.setPosition(row * 24, col * 24);
				rectangle.setSize(sf::Vector2f(24, 24));

				rectangle.setFillColor(sf::Color::Cyan);

				window.draw(rectangle);
			}
		}
	}
}

void drawWallTiles(Map &map, sf::RenderWindow &window, sf::Texture *wall,sf::Texture *wallTorch)
{

	for (int row = 0; row < map.COLUMN_COUNT; row++)
	{
		for (int col = 0; col < map.ROW_COUNT; col++)
		{
			Map::Tile tile = map.getTile(col, row);
			if (tile != Map::Tile::TileEmpty)
			{
				sf::RectangleShape rectangle;
				rectangle.setPosition(row * 24, col * 24);
				rectangle.setSize(sf::Vector2f(24, 24));

				if(tile == Map::Tile::TileWall)
					rectangle.setFillColor(sf::Color::Black);
				else if(tile == Map::Tile::tileWallFront)
					rectangle.setTexture(wall);
				else if(tile == Map::Tile::tileWallFrontTorch)
					rectangle.setTexture(wallTorch);

				window.draw(rectangle);
			}
		}
	}
}

int main()
{

	//**WALL SEGMENT LOAD**//
	sf::Texture wallFront;
	if(!wallFront.loadFromFile("wallFront.jpg"))
	{
		//error
	}

		sf::Texture wallTorch;
	if(!wallTorch.loadFromFile("wallFrontTorchOff.jpg"))
	{
		//error
	}
	//**END**//

	//**LIGHTING TEST**//
	sf::Texture lighting;
	if(!lighting.loadFromFile("lightingTest.png"))
	{
		//failed
	}
	sf::Sprite lightingSprite;
	lightingSprite.setTexture(lighting);
	lightingSprite.setOrigin(1500,1000);

	//**AMBIENT FROM TORCHES**//
	sf::Texture ambLighting;
	if(!ambLighting.loadFromFile("testAmbientLighting.png"))
	{
		//failed
	}
	sf::Sprite ambLightingSprite;
	ambLightingSprite.setTexture(ambLighting);

	//**END**//

    sf::RenderWindow window(sf::VideoMode(winX, winY), "Rumble!");

	//SET BOTH TO TRUE IF YOU WANT TO COLOUR IN THE EMPTY CELLS WITH CYAN
	bool drawGridCells = false;
	bool drawEmptyPath = false;

	//SET TO TRUE TO RUN DEBUGGING PRINT OUTS
	bool debug = true;

	//BOX TO TEST CHATBOX TRIGGERING
	sf::RectangleShape box(sf::Vector2f(24,24));
	box.setPosition(480,120);

	//CREATE TEXTBOX
	ChatBox textBox = ChatBox(winX,winY);
	textBox.setTextSettings("Retro Computer_DEMO.ttf", 19, sf::Color::White);

	//NUMBER OF CHARCTERS PER LINE, WILL DIFFER DEPENDING ON FONT
	textBox.SetCharaterLineLimit(55);

	sf::Clock timer;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	Map map(winX, winY, mainMap); //load main map by default when object is created
	map.setMap(mainMap); //pass it whatever map to load it

	Player player(health, speed);
	player.setPosition(12,12);

	sf::Event event;

	textBox.setMessage("Welcome to Rumble! Please select a character!",window);
	textBox.redrawChat(false);

	//**LOAD CHARACTER SELECT TEXUTRES**//
	sf::Texture wizardSelect;
	if(!wizardSelect.loadFromFile("wizardSelect.png"))
	{
		//error
	}

	sf::Texture warriorSelect;
	if(!warriorSelect.loadFromFile("warriorSelect.png"))
	{
		//error
	}

	sf::RectangleShape warriorBox(sf::Vector2f(234,378));
	warriorBox.setTexture(&warriorSelect);
	sf::Vector2f warriorLoc = sf::Vector2f(winX*0.8f-warriorBox.getSize().x,winY-600.0f);
	warriorBox.setPosition(warriorLoc);

	sf::RectangleShape wizardBox(sf::Vector2f(234,378));
	wizardBox.setTexture(&wizardSelect);
	sf::Vector2f wizardLoc = sf::Vector2f(winX*0.2f,winY-600.0f);
	wizardBox.setPosition(wizardLoc);

	sf::RectangleShape selectionOutline(sf::Vector2f(254,398));
	selectionOutline.setOutlineColor(sf::Color::White);
	selectionOutline.setOutlineThickness(10.0f);
	selectionOutline.setFillColor(sf::Color::Transparent);
	selectionOutline.setPosition(wizardLoc.x - 10, wizardLoc.y - 10);

	sf::Texture rumbleLogo;
	if(!rumbleLogo.loadFromFile("RumbleLogo.png"))
	{
		//error
	}

	sf::Sprite logo;
	logo.setTexture(rumbleLogo);
	logo.setOrigin(rumbleLogo.getSize().x/2,rumbleLogo.getSize().y/2);
	logo.setPosition(winX/2,winY*0.14);

	characterSelection = 1;
	//**END**/

	//**PROJECTILE TEXTURES**//
	sf::Texture missileTexture; //since allot of projectile objects are created all the time, I feel like it'd be more efficient to load this here only once, and pass it as an argument
	if(!missileTexture.loadFromFile("characterSheet.png"))
	{
		std::cout << "Error loading projectile texture" << std::endl;
	}

	//**END**//
	
	//**ARRAY LIST TO STORE PROJECTILES**//
	std::vector<Projectile> projectiles;
	//**END**//

	//**ARRAY LIST TO STORE ENEMIES**//
	std::vector<Enemy> enemies;
	//**END**//

    while (window.isOpen())
    {
		//STATE 0 - OPENING MENU SELECTION
		if(state == 0)
		{
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				else if (event.type == sf::Event::KeyPressed)
				{
					switch (event.key.code)
					{
					//Other Controls
					case (sf::Keyboard::D )://Change selection
						selectionOutline.setPosition(warriorLoc.x - 10, warriorLoc.y - 10);
						characterSelection = 2;
						break;

					case (sf::Keyboard::Right )://Change selection
						selectionOutline.setPosition(warriorLoc.x - 10, warriorLoc.y - 10);
						characterSelection = 2;
						break;

					case (sf::Keyboard::A ): //Change selection
						selectionOutline.setPosition(wizardLoc.x - 10, wizardLoc.y - 10);
						characterSelection = 1;
						break;

					case (sf::Keyboard::Left ): //Change selection
						selectionOutline.setPosition(wizardLoc.x - 10, wizardLoc.y - 10);
						characterSelection = 1;
						break;

					case (sf::Keyboard::Space): //Select character
						state = 1;
						break;

					case (sf::Keyboard::R): //Select character
						state = 1;
						break;
					}
				}
			}

			window.clear();

			window.draw(logo);
			window.draw(wizardBox);
			window.draw(warriorBox);
			window.draw(selectionOutline);
			textBox.displayConstantMessage(window);

			window.display();
		}

		//STATE 1 - GAME
		else if(state == 1)
		{
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
			{
                window.close();
			}

			else if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				//Other Controls
				case (sf::Keyboard::R): //Chat box
					textBox.setNext(true);
					break;

				case (sf::Keyboard::I): //Debug Information
					debug = true;
					break;
				case (sf::Keyboard::P):
					enemies.push_back( Enemy(10,4,sf::Vector2f(14,12)));
					break;
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				//Left as switch event incase we add more functionality, eg a right mouse click
				switch (event.key.code)
				{
					case (sf::Mouse::Button::Left): //Shoot event
						projectiles.push_back( Projectile(true, player.getFacing(), 4.0f, player.getSprite().getPosition(), 9, missileTexture));
						break;
				}
			}
        }

		sf::Time elapsedTime = timer.restart();
		timeSinceLastUpdate += elapsedTime;
		if (timeSinceLastUpdate > TimePerFrame)
		{
			if(event.type == sf::Event::MouseMoved)
			{
				//Rounding down the player's x and y position because the player can move 6 pixels at a time, whereas the mouse always returns whole integers when divided by 24
				//int x = floor(player.getSprite().getPosition().x/24);
				//int y = floor(player.getSprite().getPosition().y/24);

				sf::Vector2f a = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
				sf::Vector2f b = sf::Vector2f(player.getSprite().getPosition().x, player.getSprite().getPosition().y);

				//works out the degrees of the vector between the player position and the mouse position
				float degrees = atan2f(a.y - b.y, a.x - b.x) * 180 / 3.14159 /* PI */;
				//std::cout<< "Degrees: " << degrees <<std::endl;

				//Because it checks that the x and y axis' are aligned with the player, it means that when the mouse crosses over the tiles in a cross formation
				//with the player at the centre, the player's direction will be changed.
				if(degrees <= 140 && degrees > 35)//(event.mouseMove.x/24 == x && event.mouseMove.y/24 >= player.getSprite().getPosition().y/24)
				{
					player.turn(2); //DOWN
				}
				if(degrees <= -40 && degrees > -140)//event.mouseMove.x/24 == x && event.mouseMove.y/24 <= player.getSprite().getPosition().y/24)
				{
					player.turn(0);//UP
				}
				if(degrees > -40 && degrees <= 35)//event.mouseMove.y/24 == y && event.mouseMove.x/24 >= player.getSprite().getPosition().x/24)
				{
					player.turn(1);//RIGHT
				}
				if(degrees <= -140 || degrees > 140)//event.mouseMove.y/24 == y && event.mouseMove.x/24 <= player.getSprite().getPosition().x/24)
				{
					player.turn(3);//LEFT
				}
			}	

			//MOVEMENT
			//RIGHT
			if(((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))))
			{
				player.setFacing(Character::RIGHT);
				player.walk(map);
			}
			//LEFT
			else if(((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))))
			{
				player.setFacing(Character::LEFT);
				player.walk(map);
			}
			//UP
			else if(((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))))
			{
				player.setFacing(Character::UP);
				player.walk(map);
			}
			//DOWN
			else if(((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))))
			{
				player.setFacing(Character::DOWN);
				player.walk(map);
			}

			//DEBUG
			if(debug)
			{
				std::cout << "actual position: (" << player.getSprite().getPosition().x << ", " << player.getSprite().getPosition().y << ")" << std::endl;
				std::cout << "grid position: (" << player.getRow() << "," << player.getColumn() << ")" << std::endl;
				std::cout << "map tile: " << map.getTile(player.getRow(), player.getColumn()) << std::endl;
				std::cout << "Next tile right: " << (player.getColumn() + 1) << std::endl;
				std::cout << "Next tile left: " << (player.getColumn() - 1) << std::endl;
				std::cout << "Next tile up: " << (player.getRow() - 1) << std::endl;
				std::cout << "Next tile down: " << (player.getRow() + 1) << std::endl;
				std::cout << "Player facing: " << (player.getFacing()) << std::endl;
				std::cout << "===============" << std::endl;

				/*
				std::cout << "Time since last update: " << timeSinceLastUpdate.asSeconds() << std::endl;
				std::cout << "Elapsed Time: " << elapsedTime.asSeconds() << std::endl;
				std::cout << "===============" << std::endl;
				*/	

				if (drawGridCells)
				{
					if (drawEmptyPath)
					{
						drawEmptyTiles(map, window);
					}
				}
				debug = false;
			}

			timeSinceLastUpdate -= TimePerFrame;

			lightingSprite.setPosition(player.getSprite().getPosition().x,player.getSprite().getPosition().y);

			window.clear();

			
			//DRAW GAME ELEMENTS

			window.draw(map.getSprite());
			drawWallTiles(map,window,&wallFront,&wallTorch);
			window.draw(box);
			window.draw(lightingSprite);
			//window.draw(ambLightingSprite);
			window.draw(player.getSprite());

			//**DRAW PROJECTILES**//
			for(int i = 0; i < projectiles.size();i++)
			{
				projectiles[i].updateProjectileLocation(window);

				if(map.isCollision(projectiles[i].getRow(), projectiles[i].getColumn() ))
				{
					projectiles.erase(projectiles.begin()+i);
				}
				else if(projectiles[i].attackHit(enemies) != 1000){ //1000 = No hit
					projectiles.erase(projectiles.begin()+i);
					enemies[i].takeDamage(player.getAttack());
				}
				else if(projectiles[i].getPosX() > 1080 || projectiles[i].getPosX() < 0)
				{
					projectiles.erase(projectiles.begin()+i); //Since Projectile objects weren't allocated with new, erase should free the memory as well as removing the object from the array
				}
				else if(projectiles[i].getPosY() > 840 || projectiles[i].getPosY() < 0)
				{
					projectiles.erase(projectiles.begin()+i);
				}
			}
			//**END**//

			//**RUN / DRAW AI**//
			for(int i = 0; i < enemies.size();i++)
			{
				//enemies[i].walk(map);
				enemies[i].calcMovement(player, map);
				window.draw(enemies[i].getSprite());
			}
			//**END**//

			//drawGrid(window);
			
			//CHATBOX TEST EVENT
			if(box.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()))
			{
				textBox.redrawChat(true); //SET IF THE CHATBOX IS REDRAWN OR NOT
			}

			//DISPLAY CHATBOX IF REDRAWCHAT IS SET TO TRUE, IGNORE IF SET TO FALSE. REDRAW AUTOMATICALLY SET TO FALSE WHEN PLAYER CLOSES LAST CHATBOX
			textBox.displayMessage(window);
				
			//DISPLAY DRAW COMPONENTS
			window.display();
		}
    }
	}
    return 0;
}