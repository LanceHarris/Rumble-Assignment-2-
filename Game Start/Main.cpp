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
8. Menu/Pause - save game/load game/new game/quit game/mode (eg survival) - UI class
9. AI - Quad-tree - Enemy class
*/

/*NOTES:
Player size after 1.5 scaling: 24

*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ChatBox.h"
#include "Map.h"
#include "Character.h"
#include "Projectile.h"
#include "Hud.h"
#include "Item.h"
#include "Store.h"

#include <list>
#include <cmath>

//**CHATBOX MESSAGES**//
string introductionMessage = "Welcome to Rumble! \n\nPlease choose a character and press 'r' to confirm your \nselection."; //character select screen message
string itemNotificationMessage = "You recieved a "; //prefix for recieving an item

string oldManMessages[4] = {"Greetings, young one. What brings you down here?","Perhaps you're lost?","The only way out of here is to defeat all the enemies.","Here's a little something to help you with your efforts."};
int oldManMessagesIndex = 0; //used to determine which message is being displayed
bool oldManItemRecieved = false; //whether or not the player has recieved the old man's item (stamina vitamin)

string vitaminStoreMessages[5] = {"Well, hello! I haven't seen you around here before, it's very nice to meet you! Welcome to the vitamin store! My name Nibbles! Here you can buy vitamins to make you stronger!","Welcome to the vitamin store! My name Nibbles! Here you can buy vitamins to make you stronger!","Have you met my brother? He might seem a little grumpy, but he's really a big softy!","You're looking lively today! Feel free to browse my wares.","I heard the ceiling outside goes on forever! Can you imagine that? I think it sounds really scary if you ask me!"};
int vitStoreFirstVisit = true; //whether or not it's the player's first visit, used to display a unique greeting message at index 0

string itemStoreMessages[5] = {"Hello, stranger, it's unusual to see your kind around here... Whatever, This is the item store. Buy something or get out.","This is the item store. Buy something or get out.","My sister keeps bringing me over homemade sweets, I really don't like sweet things but I don't want to hurt her feelings.","You're looking a little beat up, how about buying a health potion?","What do you want?"};
int itemStoreFirstVisit = true; //whether or not it's the player's first visit, used to display a unique greeting message at index 0
//**END**//

/*RENDERWINDOW SIZE*/
int winX = 1080; //45 cells
int winY = 840; //35 cells
/*END*/

/*PLAYER STATS*/
float speed = 3;
int attack = 1;
int health = 50;
int stamina = 30;
int choice = 1;
/*END*/

//SPEED OF THE GAME
const float GAME_SPEED = 60.0f; //The bigger this number is the more often frames are updated
sf::Time TimePerFrame = sf::seconds(1.0f / GAME_SPEED);
/*END*/

//**SPRITE ITERATOR**//
int iterations; //used to control speed of animation
//**END**//

//**GAME STATE**//
int state = 0;
int characterSelection; //to record character choice
//**END**//

//**MUSIC AND SOUND**//
sf::Music music;
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
	{ 1,11, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0,11, 9, 9, 0, 0, 0, 9, 0,13, 0, 0, 0, 0, 0, 0, 0, 0, 9,11, 0, 0,11, 0, 0, 0, 0, 0, 0, 0, 0,11, 1 },
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


/*LOAD AND START ALL SOUND EFFECTS AND MUSIC*/
void startMusic()
{
		if(!(music.openFromFile("DST-Orchards.ogg"))) //load music file
		{
			printf("Could not load");
		}

		
		music.setVolume(20);         //set music volume
		music.setLoop(true);         //set music to loop
		//music.setPitch(1);		 //set music pitch
		music.play();				 //play the music

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

void drawWallTiles(Map &map, sf::RenderWindow &window, sf::Texture *wall,sf::Texture *wallTorch, sf::Texture *itemWallFront, sf::Texture *statsWallFront, sf::Texture *aBarrel, sf::Texture *topPillar, sf::Texture *bottomPillar, sf::Texture *aDoor, sf::Texture *oldMan)
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
				else if(tile == Map::Tile::oldMan)
				{
					rectangle.setTexture(oldMan);
					rectangle.setScale(1.2,1.2);
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

void talkToOldMan(Player &player, ChatBox &textBox, Map map, sf::RenderWindow &window, ChatBox &itemBox)
{
	int successful = false;
	switch(player.getFacing())
	{
						case 0:
							if(map.isTile( player.getRow()-1,(player.getSprite().getPosition().x+13)/24,Map::Tile::oldMan))
							{
								textBox.setMessage(oldManMessages[oldManMessagesIndex],window);
								successful = true;
							}
							break;
						case 1:
							if(map.isTile(player.getRow(),player.getColumn()+1,Map::Tile::oldMan))
							{
								textBox.setMessage(oldManMessages[oldManMessagesIndex],window);
								successful = true;
							}
							break;
						case 2:
							if(map.isTile(player.getRow()+1,player.getColumn(),Map::Tile::oldMan))
							{
								textBox.setMessage(oldManMessages[oldManMessagesIndex],window);
								successful = true;
							}
							break;
						case 3:
							if(map.isTile(player.getRow(),player.getColumn()-1,Map::Tile::oldMan))
							{
								textBox.setMessage(oldManMessages[oldManMessagesIndex],window);
								successful = true;
							}
							break;

	}
	if(successful)
	{
		textBox.redrawChat(true);
	
		if(oldManMessagesIndex == 3 && oldManItemRecieved == false)
		{
			player.giveStaminaVitamin();
			itemBox.setMessage(itemNotificationMessage + "Stamina Vitamin", window);
			itemBox.redrawChat(true);
			oldManItemRecieved = true;
			oldManMessagesIndex = 2;
		}

		if(oldManItemRecieved == false)
			oldManMessagesIndex++;
	}
		
}

int main()
{
	//**START MUSIC, FEEL FREE TO CHANGE THIS**//
	startMusic();
	//**END**//
	

	//**STORE STUFF**//
	sf::Time timePerBlink = sf::seconds(2);
	Store itemStore("Retro Computer_DEMO.ttf","Item Store",winX,winY,0);
	itemStore.setStoreOwnerTexture(0);	

	Store vitaminStore("Retro Computer_DEMO.ttf","Vitamin Store",winX,winY,1);
	vitaminStore.setStoreOwnerTexture(1);
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

	//**GOATFENNEC OLDMAN**//
	sf::Texture oldMan;
	if(!oldMan.loadFromFile("goatFennecOldMan.png"))
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
	//**END**//

    sf::RenderWindow window(sf::VideoMode(winX, winY), "Rumble!");

	
	// view for moving around, follows player
	sf::View view1;
	view1.reset(sf::FloatRect(0,0,winX,winY)); //view covers whole screen
	view1.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	view1.setSize(winX,winY); //size of view window */
	

	//SET BOTH TO TRUE IF YOU WANT TO COLOUR IN THE EMPTY CELLS WITH CYAN
	bool drawGridCells = false;
	bool drawEmptyPath = false;

	//SET TO TRUE TO RUN DEBUGGING PRINT OUTS
	bool debug = false;
	
	ChatBox itemNotificationBox = ChatBox(winX,winY);
	itemNotificationBox.setTextSettings("Retro Computer_DEMO.ttf", 19, sf::Color::Green);
	itemNotificationBox.SetCharaterLineLimit(55);

	//CREATE TEXTBOX FOR DISPLAYING DIALOGUE
	ChatBox textBox = ChatBox(winX,winY);
	textBox.setTextSettings("Retro Computer_DEMO.ttf", 19, sf::Color::White);

	//NUMBER OF CHARCTERS PER LINE, WILL DIFFER DEPENDING ON FONT
	textBox.SetCharaterLineLimit(55);
	textBox.setMessage(introductionMessage,window);
	textBox.redrawChat(false);//do not redraw textbox

	Map map(winX, winY, mainMap); //load main map by default when object is created
	map.setMap(mainMap,0); //pass it whatever map to load it

	

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

	sf::RectangleShape warriorBox(sf::Vector2f(250,250));
	warriorBox.setTexture(&warriorSelect);
	sf::Vector2f warriorLoc = sf::Vector2f(winX*0.8f-warriorBox.getSize().x,winY-550.0f);
	warriorBox.setPosition(warriorLoc);

	sf::RectangleShape wizardBox(sf::Vector2f(250,250));
	wizardBox.setTexture(&wizardSelect);
	sf::Vector2f wizardLoc = sf::Vector2f(winX*0.2f,winY-550.0f);
	wizardBox.setPosition(wizardLoc);

	sf::RectangleShape selectionOutline(sf::Vector2f(warriorBox.getSize().x,warriorBox.getSize().y));
	selectionOutline.setOutlineColor(sf::Color::White);
	selectionOutline.setOutlineThickness(10.0f);
	selectionOutline.setFillColor(sf::Color::Transparent);
	selectionOutline.setPosition(wizardLoc.x - 10, wizardLoc.y+7);

	sf::Texture rumbleLogo;
	if(!rumbleLogo.loadFromFile("RumbleLogo.png"))
	{
		//error
	}

	sf::Sprite logo;
	logo.setTexture(rumbleLogo);
	logo.setOrigin(rumbleLogo.getSize().x/2,rumbleLogo.getSize().y/2);
	logo.setPosition(winX/2,winY*0.14);
	logo.setScale(3.3,2.5);

	characterSelection = 1;
	//**END**/

	//**PROJECTILE TEXTURES**//
	sf::Texture missileTexture; //since allot of projectile objects are created all the time, I feel like it'd be more efficient to load this here only once, and pass it as an argument
	if(!missileTexture.loadFromFile("characterSheetCustom.png"))
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

	Player player(health, speed, stamina, choice);
	player.setPosition(23,17);//player starting position
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
						selectionOutline.setPosition(warriorLoc.x - 10, warriorLoc.y +7);
						characterSelection = 2;
						choice = 0;
						break;

					case (sf::Keyboard::Right )://Change selection
						selectionOutline.setPosition(warriorLoc.x - 10, warriorLoc.y +7);
						characterSelection = 2;
						choice = 0;
						break;

					case (sf::Keyboard::A ): //Change selection
						selectionOutline.setPosition(wizardLoc.x - 10, wizardLoc.y +7);
						characterSelection = 1;
						choice = 1;
						break;

					case (sf::Keyboard::Left ): //Change selection
						selectionOutline.setPosition(wizardLoc.x - 10, wizardLoc.y +7);
						characterSelection = 1;
						choice = 1;
						break;

					case (sf::Keyboard::R): //Select character
						state = 1;
						player.setSprite(choice);
						HUD.setStaminaBarAttributes(choice);
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
			window.setView(view1);
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
				case (sf::Keyboard::LShift):
					player.setSpeed(6);
					break;

				//Other Controls
				case (sf::Keyboard::R): //Chat box
					if(textBox.getRedraw() == true)//if textBox is being drawn, procede to next textBox
					{
						textBox.setNext(true);
					}
					else if(itemNotificationBox.getRedraw() == true)
					{
						itemNotificationBox.setNext(true);
					}
					else
					{
						talkToOldMan(player,textBox,map,window,itemNotificationBox);
					}
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

					//**VITAMIN USAGE KEYBINDINGS**//
				case (sf::Keyboard::Num3): //Use stamina potion
					if(player.getHealthVitaminNumber() > 0)
					{
						HUD.increaseMaxHP(10);
						player.useHealthVitamin();
						player.removeHealthVitamin();
					}
					else
					{
						//error sound
					}
					break;

				case (sf::Keyboard::Num4): //Use stamina potion
					if(player.getStaminaVitaminNumber() > 0)
					{
						HUD.increaseMaxSta(10);
						player.useStaminaVitamin();
						player.removeStaminaVitamin();
					}
					else
					{
						//error sound
					}
					break;

				case (sf::Keyboard::Num5): //Use stamina potion
					if(player.getStrengthVitaminNumber() > 0)
					{
						player.useStrengthVitamin();
						player.removeStrengthVitamin();
					}
					else
					{
						//error sound
					}
					break;
				}
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case (sf::Keyboard::LShift):
					player.setSpeed(3);
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
							projectiles.push_back( Projectile(true, player.getFacing(), player.getAttack(), player.getSprite().getPosition(), 9, missileTexture, choice));
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
			iterations++; //keeps track of how many screen draw iterations have happened
			
			view1.setCenter(player.getSprite().getPosition().x, player.getSprite().getPosition().y);
			
			HUD.updateStamina();
			HUD.updateCrowdMeter();

			//**PROCESS MOUSE MOVEMENT TO AIM**//
			if(event.type == sf::Event::MouseMoved)
			{
				sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
				sf::Vector2f mPos = window.mapPixelToCoords(pixel_pos);
				player.processMouseAiming(mPos);
			}

			//**PROCESS KEYBOARD MOVEMENT**//
			player.processDirectionalKeyPresses(map, iterations);


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
				HUD.increaseCrowdMeter(15);
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

			//**MAP TRANSITIONS**/
			if( map.isTile(player.getRow(),player.getColumn(),Map::Tile::transition) )
			{	
				projectiles.clear();//clear projectiles so they don't appear on the second map
				window.setView(window.getDefaultView()); //change view back to normal to display the stores properly
				if(map.getCurrentMap() == 0)
				{
					map.setMap(secondMap,1);
					player.setPosition(1,17);
				}
				else
				{
					map.setMap(mainMap,0);
					player.setPosition(44,17);
				}
			}

			window.clear();

			lightingSprite.setPosition(player.getSprite().getPosition().x,player.getSprite().getPosition().y); //move shadow/lighting sprite to follow player

		

			//Check to see if player is entering a store
			if( map.isTile( player.getRow()-1,player.getColumn(),Map::Tile::itemStore) ) //for item store
			{
				
				
				if(itemStoreFirstVisit == true)
				{
					textBox.setMessage(itemStoreMessages[0],window);
					itemStoreFirstVisit = false;
				}
				else
				{
					int randonNumber = rand()%(5-1)+1;
					textBox.setMessage(itemStoreMessages[randonNumber],window);
					
				}
				textBox.redrawChat(true);
				state = 2;
			}
			else if( map.isTile( player.getRow()-1,player.getColumn(),Map::Tile::statStore) ) //for item store
			{
				if(vitStoreFirstVisit == true)
				{
					textBox.setMessage(vitaminStoreMessages[0],window);
					vitStoreFirstVisit = false;
				}
				else
				{
					int randonNumber = rand()%(5-1)+1;
					textBox.setMessage(vitaminStoreMessages[randonNumber],window);
					
				}
				textBox.redrawChat(true);
				state = 3;
			}

			//**DRAW GAME ELEMENTS**//
			window.draw(map.getSprite());

			//drawWallTiles(map,window,&wallFront,&wallTorch,&itemWallFront,&statsWallFront,&barrel,&pillarTop,&pillarBottom,&door,&oldMan); //uncomment this to edit stage layout

			//dungeon map/main stage

			map.drawMap(window,dungeonStage,shopStage); //draw stage sprite overlay
			window.draw(lightingSprite); //draw lighting/shadow sprite
			window.draw(player.getSprite()); //draw player sprite

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

			window.setView(window.getDefaultView()); //change view back to normal so that chatBoxes and HUD elements don't scroll aswell

			//DISPLAY HUD LAST OVER TOP OF EVERYTHING ELSE EXCEPT CHATBOXES
			HUD.drawHUD();
			HUD.updateCoin();

			//DISPLAY CHATBOX IF REDRAWCHAT IS SET TO TRUE, IGNORE IF SET TO FALSE. REDRAW AUTOMATICALLY SET TO FALSE WHEN PLAYER CLOSES LAST CHATBOX

			if(textBox.getRedraw() == false)
			{
				itemNotificationBox.displayMessage(window);
			}
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
						case(sf::Keyboard::S):
							itemStore.moveSelection(1);
							break;

						case(sf::Keyboard::W):
							itemStore.moveSelection(0);
							break;

						case (sf::Keyboard::Escape): //exit shop, returns player to state 1 map
							state = 1;
							textBox.redrawChat(false);
							player.setPosition(11,11);
							player.turn(2);
							break;

						case (sf::Keyboard::R): //Chat box
							itemStore.purchaseItem(player);
							break;

						case (sf::Keyboard::X):
							textBox.setMessage(itemStore.getInfo(),window);
							textBox.redrawChat(true);
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
		

		sf::Time elapsedTime = timer.restart();
		timeSinceLastUpdate += elapsedTime;
		if (timeSinceLastUpdate > timePerBlink)
		{
			timeSinceLastUpdate -= timePerBlink;
			itemStore.blink(0);
		}

			window.clear();

			itemStore.displayStore(0,window,player.getGoldStash());
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
						case(sf::Keyboard::S):
							vitaminStore.moveSelection(1);
							break;

						case(sf::Keyboard::W):
							vitaminStore.moveSelection(0);
							break;

						case (sf::Keyboard::Escape): //exit shop, returns player to state 1 map
							state = 1;
							textBox.redrawChat(false);
							player.setPosition(32,11);
							player.turn(2);
							break;

						case (sf::Keyboard::R): //Chat box
							vitaminStore.purchaseItem(player);
							break;

						case (sf::Keyboard::X):
							textBox.setMessage(vitaminStore.getInfo(),window);
							textBox.redrawChat(true);
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


		sf::Time elapsedTime = timer.restart();
		timeSinceLastUpdate += elapsedTime;
		if (timeSinceLastUpdate > timePerBlink)
		{
			timeSinceLastUpdate -= timePerBlink;
			vitaminStore.blink(1); //store type, 0 = item store, 1 = vitamin store. Determines which sprite is drawn
		}

		window.clear();

		vitaminStore.displayStore(1,window,player.getGoldStash());
		textBox.displayMessage(window);
		
		window.display();
	}

	}
    return 0;
}