/*
*	Main.cpp
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 20 October 2015
*
*/

/*
TO DO: 
1. Hub area - interactable character (shopkeep)/shops - requires UI (for all menus), Item(?) and NPC classes
2. Particle effects - (multi-coloured) blood, glowing floating lights,  - Requires Effects or Blood class
3. Player - stats/levelling up; Resilience (HP), Endurance (stamina), Toughness (defence), Fastness (speed), Attack (Strength?) - Add to Player class
4. Enemy experience (based on level) - Add to enemy class
5. Stages - Collesseum, Forest Stage, Night City - Need resources and for these to be added to Main
6. Music, sound effects - Add to each necessary class (eg projectile for throwing sound, player or Hud for taking damage sound)
7. HUD completion - possibly add Crowd Meter - Hud class
8. Add character selection sprite (ie the mage if you select the mage) - Player class
9. Menu/Pause - save game/load game/new game/quit game/mode (eg survival) - Menu class
10. AI - Quad-tree - Enemy class
*/

/*NOTES:
Player size after 1.5 scaling: 24

*/

#include <SFML/Graphics.hpp>
#include "ChatBox.h"
#include "Map.h"
#include "Character.h"
#include "Projectile.h"
#include "Hud.h"
#include "Item.h"
#include "Store.h"

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
int health = 50;
int stamina = 30;
/*END*/

//SPEED OF THE GAME
const float GAME_SPEED = 60.0f; //The bigger this number is the more often frames are updated
sf::Time TimePerFrame = sf::seconds(1.0f / GAME_SPEED);
/*END*/

//**GAME STATE**//
int state = 0;
int characterSelection;
//**END**//

//**MAP TRANSITION STUFF**//
int curMap = 0;
//**END**//

//**MAPS**//
int mainMap[Map::ROW_COUNT][Map::COLUMN_COUNT] = { // The Arena
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1,10, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2,10, 1 },
	{ 1,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,11, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2,10, 0, 0, 0,10, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2,10, 0, 0, 0,10, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 9, 9, 0, 0, 0,11, 0, 0, 0,11, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,11, 0, 0, 0,11, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 2, 2,10, 0, 0, 0,10, 2, 2, 3, 3, 2, 2, 0, 0, 0, 2, 3, 2, 0, 0, 0, 2, 2, 3, 3, 2, 2,10, 0, 0, 0,10, 2, 2, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0,11, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 2 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 2,10, 0, 0, 0,10, 2, 2, 3, 3, 2, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 2, 3, 3, 2, 2,10, 0, 0, 0,10, 2, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0,11, 0, 0, 0,11, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0,11, 0, 0, 0,11, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 3, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 9, 9, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2,10, 0, 0, 0,10, 2, 2, 2, 3, 2, 2, 3, 2, 2, 2, 2, 2, 2,10, 0, 0, 0,10, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0, 0,11, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};


int secondMap[Map::ROW_COUNT][Map::COLUMN_COUNT] = { // Shop hub
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1,10, 2, 2, 2, 2, 2, 2, 3, 2,10,12,12,10, 7, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2,10,12,12,10, 8, 3, 2, 2, 2, 2, 2, 2,10, 1 },
	{ 1,11, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0,11, 9, 9, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,11, 0, 0,11, 0, 0, 0, 0, 0, 0, 0, 0,11, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 9, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

//int *maps[2] = {*mainMap,*secondMap}; // it'd be ideal to use a array like this of pointers to each map, and then just change a indexValue variable to change which map was being loaded,
//but having some issues being able to pass usable pointers, so I'm giving up for now, if anyone feels like trying to get this to work, go for it :D

//**END**//

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

void drawWallTiles(Map &map, sf::RenderWindow &window, sf::Texture *wall,sf::Texture *wallTorch, sf::Texture *itemWallFront, sf::Texture *statsWallFront, sf::Texture *aBarrel, sf::Texture *topPillar, sf::Texture *bottomPillar, sf::Texture *aDoor)
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

				if(tile == Map::Tile::TileWall || tile == Map::Tile::statStore || tile == Map::Tile::itemStore)
				{
					rectangle.setFillColor(sf::Color::Black);
				}
				else if(tile == Map::Tile::tileWallFront)
				{
					rectangle.setTexture(wall);
				}
				else if(tile == Map::Tile::tileWallFrontTorch)
				{
					rectangle.setTexture(wallTorch);
				}
				else if(tile == Map::Tile::itemFrontWall)
				{
					rectangle.setTexture(itemWallFront);
				}
				else if(tile == Map::Tile::statWallFront)
				{
					rectangle.setTexture(statsWallFront);
				}
				else if(tile == Map::Tile::barrel)
				{
					rectangle.setTexture(aBarrel);
				}
				else if(tile == Map::Tile::pillarTop)
				{
					rectangle.setTexture(topPillar);
				}
				else if(tile == Map::Tile::pillarBottom)
				{
					rectangle.setTexture(bottomPillar);
				}
				else if(tile == Map::Tile::door)
				{
					rectangle.setTexture(aDoor);
				}
					
				//Don't draw rectangles for empty cells, figuren this might reduce lag a little
				if(tile != Map::Tile::TileEmpty && tile != Map::Tile::transition)
				{
					window.draw(rectangle);
				}
			}
		}
	}
}

int main()
{
	//**LOAD STORE TEXTURES**//
	sf::Texture storeTexture;
	if(!storeTexture.loadFromFile("dungeonMap.jpg"))
	{
		//error
	}

	sf::Texture itemStoreBackground;
	if(!itemStoreBackground.loadFromFile("storeBackground.jpg"))
	{
		//error
	}
	//**END**//

	//**CREATE STORE OBJECTS**//
	Store itemStoreObject("Retro Computer_DEMO.ttf","Item Store",storeTexture,itemStoreBackground,winX,winY);
	//**END**//

	//**LOAD BACKGROUND TEXTURE MAPS**//
	sf::Texture dungeonMap;
	if(!dungeonMap.loadFromFile("dungeonMap.jpg"))
	{
		//error
	}
	sf::Sprite dungeonStage;
	dungeonStage.setTexture(dungeonMap);

	sf::Texture shopMap;
	if(!shopMap.loadFromFile("shopMap.jpg"))
	{
		//error
	}
	sf::Sprite shopStage;
	shopStage.setTexture(shopMap);
	//**END**//

	//**WALL SEGMENT LOAD**//
	sf::Texture wallFront;
	if(!wallFront.loadFromFile("wallFront.jpg"))
	{
		//error
	}




	sf::Texture door;
	if(!door.loadFromFile("door.png"))
	{
		//error
	}

	sf::Texture pillarTop;
	if(!pillarTop.loadFromFile("pillarTop.jpg"))
	{
		//error
		cout << "pillarTop.jpg can't load" << endl;
	}

	sf::Texture pillarBottom;
	if(!pillarBottom.loadFromFile("pillarBottom.png"))
	{
		//error
	}

	sf::Texture itemWallFront;
	if(!itemWallFront.loadFromFile("itemFrontWall.jpg"))
	{
		//error
	}

	sf::Texture barrel;
	if(!barrel.loadFromFile("barrel.png"))
	{
		//error
	}

	sf::Texture statsWallFront;
	if(!statsWallFront.loadFromFile("statsFrontWall.jpg"))
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
	lightingSprite.setOrigin(lighting.getSize().x/2,lighting.getSize().y/2);
	lightingSprite.scale(2,2);

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
	bool debug = false;

	//BOX TO TEST CHATBOX TRIGGERING
	sf::RectangleShape box(sf::Vector2f(24,24));
	box.setPosition(480,120);
	box.setFillColor(sf::Color::Transparent);

	//CREATE TEXTBOX
	ChatBox textBox = ChatBox(winX,winY);
	textBox.setTextSettings("Retro Computer_DEMO.ttf", 19, sf::Color::White);

	//NUMBER OF CHARCTERS PER LINE, WILL DIFFER DEPENDING ON FONT
	textBox.SetCharaterLineLimit(55);

	Map map(winX, winY, mainMap); //load main map by default when object is created
	map.setMap(mainMap); //pass it whatever map to load it

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

	sf::Clock timer;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	Player player(health, speed, stamina);
	player.setPosition(12,12);
	Hud HUD = Hud(player, window);

	sf::Event event;

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
			timer.restart();	// To fix a bug, where the clock was starting during character selection so timeSinceLastUpdate -= TimePerFrame was not reseting the clock (ie the game would go really fast)

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

				case (sf::Keyboard::P): //Spawn Enemy
					enemies.push_back(Enemy(10,4,sf::Vector2f(14,12)));
					break;

				case (sf::Keyboard::L): //Take damage for testing
					HUD.takeDamage(30);
					break;

				case (sf::Keyboard::Num1): //Use health potion
					HUD.useHealthPotion(1,player);
					break;

				case (sf::Keyboard::Num2): //Use stamina potion
					HUD.useStaminaPotion(1,player);
					break;
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				//Left as switch event incase we add more functionality, eg a right mouse click
				switch (event.key.code)
				{
					case (sf::Mouse::Button::Left): //Shoot event
						if(!HUD.getOutOfStamina())  //If not out of stamina you can shoot
						{
							projectiles.push_back( Projectile(true, player.getFacing(), 4.0f, player.getSprite().getPosition(), 9, missileTexture));
							HUD.takeStamina(8);
							break;
						}
						else
						{
							std::cout << "Out of stamina!" << std::endl;
							break;
						}
				}
			}
        }

		sf::Time elapsedTime = timer.restart();
		timeSinceLastUpdate += elapsedTime;
		if (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			HUD.updateStamina();

			if(event.type == sf::Event::MouseMoved)
			{
				sf::Vector2f mPos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
				sf::Vector2f pPos = sf::Vector2f(player.getSprite().getPosition().x, player.getSprite().getPosition().y);

				//works out the degrees of the vector between the player position and the mouse position
				float degrees = atan2f(mPos.y - pPos.y, mPos.x - pPos.x) * 180 / 3.14159 /* PI */;
				//std::cout<< "Degrees: " << degrees <<std::endl;

				if(degrees <= 140 && degrees > 35)
				{
					player.turn(2); //DOWN
				}
				if(degrees <= -40 && degrees > -140)
				{
					player.turn(0);//UP
				}
				if(degrees > -40 && degrees <= 35)
				{
					player.turn(1);//RIGHT
				}
				if(degrees <= -140 || degrees > 140)
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

				player.increaseGoldStash(5);
				/*
				std::cout << "Time since last update: " << timeSinceLastUpdate.asSeconds() << std::endl;
				std::cout << "Elapsed Time: " << elapsedTime.asSeconds() << std::endl;
				std::cout << "===============" << std::endl;
				std::cout << HUD.getGameOver() << std::endl;
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

			//Light halo follows player
			lightingSprite.setPosition(player.getSprite().getPosition().x,player.getSprite().getPosition().y);

			window.clear();
	
			//**MAP TRANSITIONS**/
			if( map.isTile(player.getRow(),player.getColumn(),Map::Tile::transition) )
			{
				if(curMap == 0)
				{
					map.setMap(secondMap);
					player.setPosition(1,17);
					curMap++;
				}
				else
				{
					map.setMap(mainMap);
					player.setPosition(44,17);
					curMap--;
				}
			}


			//TODO! For some reason trying to set the global state variable here just doesn't work.
			//New isTile method, takes row and col arguments like is Collision, but also takes tile type, so we can check for whatever tile we want. Thought it'd be handy.
			if( map.isTile( player.getRow()-1,player.getColumn(),Map::Tile::itemStore) ) //for item store
			{
				
				state = 2;
				textBox.setMessage("Welcome to the item store!",window);
				textBox.redrawChat(true);
				cout << state << endl;
			}
			else if( map.isTile( player.getRow()-1,player.getColumn(),Map::Tile::statStore) ) //for item store
			{
				state = 3;
				textBox.setMessage("Welcome to the vitamin store!",window);
				textBox.redrawChat(true);
				cout << state << endl;
			}
			
			//**END**//



			//DRAW GAME ELEMENTS
			window.draw(map.getSprite());

			//drawWallTiles(map,window,&wallFront,&wallTorch,&itemWallFront,&statsWallFront,&barrel,&pillarTop,&pillarBottom,&door); //uncomment this to edit stage layout

			//dungeon map/main stage

			if(curMap == 0)
			{
				window.draw(dungeonStage);
			}
			else
			{
				window.draw(shopStage);
			}
			
			window.draw(box);

			//window.draw(lightingSprite);
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


			//DISPLAY HUD LAST OVER TOP OF EVERYTHING ELSE EXCEPT CHATBOXES
			HUD.drawHUD();
			HUD.updateCoin();

			//DISPLAY CHATBOX IF REDRAWCHAT IS SET TO TRUE, IGNORE IF SET TO FALSE. REDRAW AUTOMATICALLY SET TO FALSE WHEN PLAYER CLOSES LAST CHATBOX
			textBox.displayMessage(window);
			


			//DISPLAY DRAW COMPONENTS
			window.display();
			
		}
    }
	else if (state == 2)//Item store
	{
		while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				else if (event.type == sf::Event::KeyPressed)
				{
					if(textBox.getRedraw() == false)
					{
						switch (event.key.code)
						{

						//Other Controls
						case (sf::Keyboard::D )://Change selection
							break;


						case (sf::Keyboard::Escape): //Chat box
							state = 1;
							textBox.redrawChat(false);
							player.setPosition(11,11);
							player.turn(2);
							break;
						}
					}
					switch (event.key.code)
					{
					case (sf::Keyboard::R): //Chat box
						textBox.setNext(true);
						break;
					}

					
				}
		}

		window.clear();

		itemStoreObject.displayStore(window,player.getGoldStash());
		textBox.displayMessage(window);

		
		window.display();
	}
	else if (state == 3)//stats store
	{
		while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				else if (event.type == sf::Event::KeyPressed)
				{
					if(textBox.getRedraw() == false)
					{
						switch (event.key.code)
						{
						//Other Controls
						case (sf::Keyboard::W || sf::Keyboard::Up)://Change selection
							break;

						case (sf::Keyboard::S)://Change selection
							break;

						case (sf::Keyboard::Down)://Change selection
							break;

						case (sf::Keyboard::Escape): //Chat box
							state = 1;
							textBox.redrawChat(false);
							player.setPosition(32,11);
							player.turn(2);
							break;
						}
					}
					switch (event.key.code)
					{
					case (sf::Keyboard::R): //Chat box
						textBox.setNext(true);
						break;
					}
				}
		}

		window.clear();

		itemStoreObject.displayStore(window,player.getGoldStash());
		textBox.displayMessage(window);
		
		window.display();
	}

	}
    return 0;
}