/*
*	Main.cpp
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 20 October 2015
*
*/

/*
WOULD BE NICE TO HAVE: 
1. Hub area - interactable character (shopkeep)/shops - requires UI (for all menus), Item(?) and NPC classes
2. Player - stats/levelling up; Resilience (HP), Endurance (stamina), Toughness (defence), Fastness (speed), Attack (Strength?) - Add to Player class
3. Enemy experience (based on level) - Add to enemy class
4. Stages - Collesseum, Forest Stage, Night City - Need resources and for these to be added to Main
5. Music, sound effects - Add to each necessary class (eg projectile for throwing sound, player or Hud for taking damage sound)
6. Menu/Pause - save game/load game/new game/quit game/mode (eg survival) - UI class
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
#include "Store.h"
#include "Effects.h"
#include "Particle.h"
#include "Coin.h"
#include "menu.h"
#include <list>
#include <cmath>

//**CHATBOX MESSAGES**//
string introductionMessage = "Welcome to Rumble! \n\nPlease choose a character and press 'r' to confirm your \nselection."; //character select screen message
string itemNotificationMessage = "You recieved a "; //prefix for recieving an item
string gameOverMessages[10] = {"Black Knight: 'Tis but a scratch.\nKing Arthur: A scratch? Your arm's off!", "Your mother was a hamster and your father smelt\nof elderberries!","Bring out yer dead.","King Arthur: Look, you stupid bastard, you've got no arms!\nBlack Knight: Yes I have.\nKing Arthur: Look!\nBlack Knight: It's just a flesh wound.","Please! This is supposed to be a happy occasion.\nLet's not bicker and argue over who killed who.","Look, that rabbit's got a vicious streak a mile wide!\nIt's a killer!","Dennis: Come and see the violence inherent in the system.\nHelp! Help! I'm being repressed!\nKing Arthur: Bloody peasant!","We are now the Knights who say...\n\"Ekki-ekki-ekki-ekki-PTANG. Zoom-Boing, z'nourrwringmm.\"","King Arthur: Who are you who can summon fire\nwithout flint or tinder?\nTim: There are some who call me... Tim.","On second thought, let's not go to Camelot. It is a silly place."};

string oldManMessages[4] = {"Greetings, young one. What brings you down here?","Perhaps you're lost?","The only way out of here is to defeat all the enemies. Press [SPACE BAR] to spawn a new wave when in the other room.","Here's a little something to help you with your efforts."};
int oldManMessagesIndex = 0; //used to determine which message is being displayed
bool oldManItemRecieved = false; //whether or not the player has recieved the old man's item (stamina vitamin)

string vitaminStoreMessages[5] = {"Well, hello! I haven't seen you around here before, it's very nice to meet you! Welcome to the vitamin store! My name Nibbles! Here you can buy vitamins to make you stronger!","Welcome to the vitamin store! My name Nibbles! Here you can buy vitamins to make you stronger!","Have you met my brother? He might seem a little grumpy, but he's really a big softy!","You're looking lively today! Feel free to browse my wares.","I heard the ceiling outside goes on forever! Can you imagine that? I think it sounds really scary if you ask me!"};
int vitStoreFirstVisit = true; //whether or not it's the player's first visit, used to display a unique greeting message at index 0

string itemStoreMessages[5] = {"Hello, stranger, it's unusual to see your kind around here... Whatever, This is the item store. Buy something or get out.","This is the item store. Buy something or get out.","My sister keeps bringing me over homemade sweets, I really don't like sweet things but I don't want to hurt her feelings.","You're looking a little beat up, how about buying a health potion?","What do you want?"};
int itemStoreFirstVisit = true; //whether or not it's the player's first visit, used to display a unique greeting message at index 0

string victoryMessages[10] = {"Good job, Hero. But this is the first of many battles.","Your fight has only just begun, Hero. There are many more battles ahead. Many more opportunities for you to die.","You are powerful, Hero. I can admit that much, but no matter how powerful you are, all humans must grow weary.","Are you tiring of this yet, Hero?","Is it me, or are you slowing down? Nheheheh!","You're starting to annoy me, Hero. Why won't you just die?","Why do you struggle so? Wouldn't it be easier to just... Let go?","There is no end to my minions, Hero. Eventually, one of these times, you WILL fall.","DIE, HERO! JUST DIE! YOU WILL DIE EVEN IF I HAVE TO PUT YOU DOWN MYSELF!","How... Could you... Defeat... Everyone of my..."};
//**END**//

int roundMessages[10] = {0,0,0,0,0,0,0,0,0,0};
bool firstRoundDone = false;


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
int state = -1;
int characterSelection; //to record character choice
//**END**//

//**MUSIC AND SOUND**//
sf::Music musicAmbient;
sf::Music musicStore;
sf::Music musicGameOver;
sf::Music musicCombat;

sf::SoundBuffer bufferPotion;
sf::Sound soundPotion;

sf::SoundBuffer bufferCoin;
sf::Sound soundCoin;

sf::SoundBuffer bufferVitamin;
sf::Sound soundVitamin;

sf::SoundBuffer bufferError;
sf::Sound soundError;

sf::SoundBuffer bufferFireball;
sf::Sound soundFireball;

sf::SoundBuffer bufferAxe;
sf::Sound soundAxe;

sf::SoundBuffer bufferChangeSelection;
sf::Sound soundChangeSelection;

sf::SoundBuffer bufferNewGame;
sf::Sound soundNewGame;

sf::SoundBuffer bufferTakeDamage;
sf::Sound soundTakeDamage;

sf::SoundBuffer bufferDeathScream;
sf::Sound soundDeathScream;

sf::SoundBuffer bufferRoundStart;
sf::Sound soundRoundStart;

//Added but not implemented
sf::SoundBuffer bufferCrowdMeter;
sf::Sound soundCrowdMeter;

//**END**//

//**MAPS**//
int mainMap[Map::ROW_COUNT][Map::COLUMN_COUNT] = { // The Arena
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1,10, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2,10, 1 },
	{ 1,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,11, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1 },
	{ 1, 9, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

const int SPAWNLOACTIONS = 4;
sf::Vector2f spawnPoints[SPAWNLOACTIONS] = {
	sf::Vector2f(3,4),
	sf::Vector2f(3,30),
	sf::Vector2f(30,30),
	sf::Vector2f(30,4)};

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
		//if(!(music.openFromFile("DST-Orchards.ogg"))) //load music file
		if(!musicAmbient.openFromFile("ambientcave.ogg"))
		{
			printf("Could not load");
		}
		musicAmbient.setVolume(80);         //set music volume
		musicAmbient.setLoop(true);         //set music to loop

		if(!musicStore.openFromFile("store.ogg"))
		{
			printf("Could not load");
		}
		musicStore.setVolume(30);         //set music volume
		musicStore.setLoop(true);         //set music to loop

		if(!musicGameOver.openFromFile("DST-Xend.ogg"))
		{
			std::cout<<"Could not load DST-Xend.ogg"<<std::endl;
		}
		musicGameOver.setVolume(20);         //set music volume
		musicGameOver.setLoop(true);         //set music to loop

		if(!musicCombat.openFromFile("DST-TheDying.ogg"))
		{
			std::cout<<"Could not load DST-TheDying"<<std::endl;
		}
		musicCombat.setVolume(20);         //set music volume
		musicCombat.setLoop(true);         //set music to loop
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

void loadSounds()
{
	if(!bufferPotion.loadFromFile("potion.ogg"))
	{
		cout << "cannot load potion.ogg" << endl;
	}
	soundPotion.setBuffer(bufferPotion);

	if(!bufferVitamin.loadFromFile("pill.ogg"))
	{
		cout << "cannot load pill.ogg" << endl;
	}
	soundVitamin.setBuffer(bufferVitamin);

	if(!bufferCoin.loadFromFile("coin.ogg"))
	{
		cout << "cannot load coin.ogg" << endl;
	}
	soundCoin.setBuffer(bufferCoin);

	if(!bufferError.loadFromFile("error.ogg"))
	{
		cout << "cannot load error.ogg" << endl;
	}
	soundError.setBuffer(bufferError);
	soundError.setVolume(45);

	if(!bufferFireball.loadFromFile("fireball.ogg"))
	{
		cout << "cannot load fireball.ogg" << endl;
	}
	soundFireball.setBuffer(bufferFireball);
	soundFireball.setVolume(30);

	if(!bufferAxe.loadFromFile("axe.ogg"))
	{
		cout << "cannot load axe.ogg" << endl;
	}
	soundAxe.setBuffer(bufferAxe);

	if(!bufferChangeSelection.loadFromFile("changeSelection.ogg"))
	{
		cout << "cannot load axe.ogg" << endl;
	}
	soundChangeSelection.setBuffer(bufferChangeSelection);

	if(!bufferNewGame.loadFromFile("newGame.ogg"))
	{
		cout << "cannot load axe.ogg" << endl;
	}
	soundNewGame.setBuffer(bufferNewGame);
	soundNewGame.setVolume(30);

	if(!bufferDeathScream.loadFromFile("deathscream.ogg"))
	{
		cout << "cannot load deathscream.ogg" << endl;
	}

	soundDeathScream.setBuffer(bufferDeathScream);
	soundDeathScream.setVolume(30);

	if(!bufferTakeDamage.loadFromFile("takedamage.ogg"))
	{
		cout << "cannot load takedamage.ogg" <<endl;
	}
	soundTakeDamage.setBuffer(bufferTakeDamage);
	soundTakeDamage.setVolume(30);

	if(!bufferRoundStart.loadFromFile("roundstart.ogg"))
	{
		cout << "cannot load roundstart.ogg" <<endl;
	}
	soundRoundStart.setBuffer(bufferRoundStart);
	soundRoundStart.setVolume(30);

	if(!bufferCrowdMeter.loadFromFile("crowdmeterprogress.ogg"))
	{
		cout << "cannot load crowdmeterprogress.ogg" <<endl;
	}
	soundCrowdMeter.setBuffer(bufferCrowdMeter);
	soundCrowdMeter.setVolume(30);
}

int main()
{
	std::srand(time(NULL));

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
		std::cout<<"Error loading resource dungeonMap.jpg"<<std::endl; //error
	}
	sf::Sprite dungeonStage;
	dungeonStage.setTexture(dungeonMap);

	sf::Texture shopMap;
	if(!shopMap.loadFromFile("shopMap.jpg"))
	{
		std::cout<<"Error loading resource shopMap.jpg"<<std::endl; //error
	}
	sf::Sprite shopStage;
	shopStage.setTexture(shopMap);
	//**END**//

	//**LIGHTING TEST**//
	sf::Texture lighting;
	if(!lighting.loadFromFile("lightingTest.png"))
	{
		std::cout<<"Error loading resource lightingTest.png"<<std::endl; //error
	}
	sf::Sprite lightingSprite;
	lightingSprite.setTexture(lighting);
	lightingSprite.setOrigin(lighting.getSize().x/2,lighting.getSize().y/2);
	lightingSprite.scale(2,2);
	
	sf::Texture spriteTexture;
	if (!spriteTexture.loadFromFile("characterSheetCustom.png"))
	{
		std::cout << "Error loading resource characterSheetCustom.png" << std::endl;
	}
	//**END**//

    sf::RenderWindow window(sf::VideoMode(winX, winY), "Rumble!");

	// view for moving around, follows player
	sf::View view1;
	view1.reset(sf::FloatRect(0,0,winX,winY)); //view covers whole screen
	view1.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	view1.setSize(winX,winY); //size of view window */
	
	//SET TO TRUE TO RUN DEBUGGING PRINT OUTS
	bool debug = false;
	
	ChatBox itemNotificationBox = ChatBox(winX,winY);
	itemNotificationBox.setTextSettings("Retro Computer_DEMO.ttf", 19, sf::Color::Green);
	itemNotificationBox.SetCharaterLineLimit(55);

	//GAME OVER TEXT BOX & FONT
	ChatBox textBox2 = ChatBox(winX,winY);
	sf::Font gameOverFont;
	if(!gameOverFont.loadFromFile("8-BIT WONDER.ttf"))
	{
		std::cout << "Error masking image resource 8-BIT WONDER.ttf" << std::endl;
	}
	sf::Text yesText("Yes", gameOverFont, 50);
	sf::Text noText("No", gameOverFont, 50);
	sf::Text continueText("Continue", gameOverFont, 50);
	int retryChoice = 1;
	int randomMessage = 0;

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
		std::cout<<"Error loading resource wizardSelect.png"<<std::endl; //error
	}

	sf::Texture warriorSelect;
	if(!warriorSelect.loadFromFile("warriorSelect.png"))
	{
		std::cout<<"Error loading resource warriorSelect.png"<<std::endl; //error
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
		std::cout<<"Error loading resource RumbleLogo.png"<<std::endl; //error
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
		std::cout<<"Error loading resource characterSheetCustom.png - projectile sheet."<<std::endl; //error
	}
	//**END**//
	
	//**ARRAY LIST TO STORE PROJECTILES**//
	std::vector<Projectile> projectiles;
	//**END**//

	//**ARRAY LIST TO STORE ENEMIES**//
	std::vector<Enemy> enemies;

	sf::RectangleShape fullScreen(sf::Vector2f(winX,winY));
	fullScreen.setPosition(0,0);
	QuadTree enemyTree(0, fullScreen);

	int eLoop;
	//Enemy Health Bars
	sf::RectangleShape healthBar(sf::Vector2f(24,7));
	sf::RectangleShape healthGauge(sf::Vector2f(20,3));

	healthBar.setFillColor(sf::Color(20,20,20,240));
	healthGauge.setFillColor(sf::Color::Red);
	
	//**END**//

	//**Rounds**//
	int currentRound = 0;
	int rounds[10][2] = {
		{0,0}, //Placeholder
		{2,0}, //Wave 1
		{4,0}, //Wave 2
		{6,0}, //Wave 3
		{8,0}, //Wave 4
		{4,1}, //Wave 5
		{8,1}, //Wave 6
		{10,2}, //Wave 7
		{15,4}, //Wave 8
		{20,4}, //Wave 9
	};

	int thisRound[2];

	sf::Clock spawnTimer;
	int SPAWNWAIT = 2000;

	bool roundActive = false;
	bool store = false; //is Player in store

	bool infinite = false; //infinite spawn mode
	int infWait = 5000;
	int infRound = 1;

	//**END**//

	sf::Clock timer;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	Player player(health, speed, stamina, choice, spriteTexture);
	player.setPosition(23,16);//player starting position
	
	//Create enemies
	Enemy newEnemy_Zombie(10,2,10,Enemy::ZOMBIE,sf::Vector2f(14,16), spriteTexture);
	Enemy newEnemy_Boss(25,1,20,Enemy::BOSS,sf::Vector2f(14,16), spriteTexture);

	Hud HUD = Hud(player, window);
	Effects effect (view1, window, map, HUD, player, projectiles);

	//COIN DROP TEXTURE
	sf::Texture dropCoinTexture;
	if (!dropCoinTexture.loadFromFile("spinning_coin_gold.png"))
	{
		std::cout << "Error loading resource spinning_coin_gold.png" << std::endl;
	}
	std::vector<Coin> droppedCoins;

	//store mangement variables
	Store *currentStore;
	int storeType;

	//load sounds and start music
	loadSounds();
	musicAmbient.play();

	sf::Event event;

	//main menu object (new game, exit)
	Menu menu(winX, winY);

    while (window.isOpen())
    {
		//STATE -1 - OPENING MENU
		if(state == -1)
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
					case (sf::Keyboard::W )://Change selection
						menu.Move();
						soundChangeSelection.play();
						break;

					case (sf::Keyboard::Up )://Change selection
						menu.Move();
						soundChangeSelection.play();
						break;

					case (sf::Keyboard::S): //Change selection
						menu.Move();
						soundChangeSelection.play();
						break;

					case (sf::Keyboard::Down ): //Change selection
						menu.Move();
						soundChangeSelection.play();
						break;

					case (sf::Keyboard::R): //Select character
						menu.selectOption(state, window);
						soundNewGame.play();
						break;

					}
				}
			}
			menu.draw(window);
		}
		//STATE 0 - SELECTION
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
						soundChangeSelection.play();
						choice = 0;
						break;

					case (sf::Keyboard::Right )://Change selection
						selectionOutline.setPosition(warriorLoc.x - 10, warriorLoc.y +7);
						characterSelection = 2;
						soundChangeSelection.play();
						choice = 0;
						break;

					case (sf::Keyboard::A ): //Change selection
						selectionOutline.setPosition(wizardLoc.x - 10, wizardLoc.y +7);
						characterSelection = 1;
						soundChangeSelection.play();
						choice = 1;
						break;

					case (sf::Keyboard::Left ): //Change selection
						selectionOutline.setPosition(wizardLoc.x - 10, wizardLoc.y +7);
						characterSelection = 1;
						soundChangeSelection.play();
						choice = 1;
						break;

					case (sf::Keyboard::R): //Select character
						soundNewGame.play();
						state = 1;
						player.setSprite(choice);
						player.setChoice(choice);
						HUD.setStaminaBarAttributes(choice);
						/*
						if(choice == 0)
						{
							health = 60;
							stamina = 30;
						}
						else
						{
							health = 40;
							stamina = 50;
						}
						player.setStamina(stamina);
						player.setHealth(health);
						*/

						//intial greeting message
						textBox.setMessage("Welcome to my dungeon. The only way to escape here is to defeat all my minions! Press [SPACE BAR] to spawn a new wave of enemies when you are ready to begin. You will find stores to the right where you can spend the gold you gather from vaquishing foes. I'm nothing if not sporting. Nyheheheh.",window);
						textBox.redrawChat(true);
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
						soundChangeSelection.play();
					}
					else if(itemNotificationBox.getRedraw() == true)
					{
						soundChangeSelection.play();
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
					enemies.push_back(newEnemy_Zombie);
					break;

				case (sf::Keyboard::Space):
					
					if (!(store && roundActive)){
						soundRoundStart.play();
						//musicCombat.play();
						roundActive = true;
						if (currentRound < 10){
							currentRound ++;
							thisRound[1] = rounds[currentRound][1];
							thisRound[0] = rounds[currentRound][0];
						}else{
							infinite = true;
						}
					}
					break;
				
				case (sf::Keyboard::B): //Spawn Enemy
					enemies.push_back(newEnemy_Boss);
					break;

				case (sf::Keyboard::Num1): //Use health potion
					if(HUD.useHealthPotion(1,player))
						soundPotion.play();
					else
						soundError.play();
					break;

				case (sf::Keyboard::Num2): //Use stamina potion
					if(HUD.useStaminaPotion(1,player))
						soundPotion.play();
					else
						soundError.play();
					break;

					//**VITAMIN USAGE KEYBINDINGS**//
				case (sf::Keyboard::Num3): //Use health vitamin
					if(player.useHealthVitamin())
					{
						HUD.increaseMaxHP(10);
						soundVitamin.play();
					}
					else
					{
						soundError.play();
					}
					break;

				case (sf::Keyboard::Num4): //Use stamina vitamin
					if(player.useStaminaVitamin())
					{
						HUD.increaseMaxSta(10);
						soundVitamin.play();
					}
					else
					{
						soundError.play();
					}
					break;

				case (sf::Keyboard::Num5): //Use strength vitamin
					if(player.useStrengthVitamin())
					{
						soundVitamin.play();
					}
					else
					{
						soundError.play();
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
							effect.weaponTrail();
							if(choice == 0)
								soundAxe.play();
							else
								soundFireball.play();
							break;
						}
						else
						{
							//std::cout << "Out of stamina!" << std::endl;
							break;
						}
				}
			}
        }


		//**SPAWN ENEMIES**//
		int spawnAt = std::rand() % SPAWNLOACTIONS;
		if (!infinite){
			if (spawnTimer.getElapsedTime().asMilliseconds() > SPAWNWAIT && roundActive ) {
				int i = 0;
				while (i < SPAWNLOACTIONS && thisRound[0] > 0){
					if (spawnAt == SPAWNLOACTIONS){spawnAt = 0;}
					newEnemy_Zombie.setPosition(spawnPoints[spawnAt].x,spawnPoints[spawnAt].y);
					enemies.push_back(newEnemy_Zombie);
					thisRound[0] --;
					i++;
					spawnAt ++;
				}
				while (i < SPAWNLOACTIONS && thisRound[1] > 0){
					if (spawnAt == SPAWNLOACTIONS){spawnAt = 0;}
					newEnemy_Boss.setPosition(spawnPoints[spawnAt].x,spawnPoints[spawnAt].y);
					enemies.push_back(newEnemy_Boss);
					thisRound[1] --;
					i++;
					spawnAt ++;
				}
				spawnTimer.restart();
			}
			if (enemies.size() == 0 && thisRound[1] == 0 && thisRound[1] == 0){
				roundActive = false;
			}
		}else{
			//zombies
			if (spawnTimer.getElapsedTime().asMilliseconds() > infWait) {
				if (spawnAt == SPAWNLOACTIONS){spawnAt = 0;}
				newEnemy_Zombie.setPosition(spawnPoints[spawnAt].x,spawnPoints[spawnAt].y);
				enemies.push_back(newEnemy_Zombie);
				spawnAt ++;
			}
			if (spawnTimer.getElapsedTime().asMilliseconds() > infWait && infWait % ((((int)40/infRound)+1)*50) == 0 && infWait < 4750){
				if (spawnAt == SPAWNLOACTIONS){spawnAt = 0;}
				newEnemy_Boss.setPosition(spawnPoints[spawnAt].x,spawnPoints[spawnAt].y);
				enemies.push_back(newEnemy_Boss);
				rounds[currentRound][1] --;
				spawnAt ++;
			}
			if (spawnTimer.getElapsedTime().asMilliseconds() > infWait){
				spawnTimer.restart();
				infRound ++;
				if (infWait > 500){infWait -= 50;}; //speed things up :)
			}
		}
		//**END**//

		sf::Time elapsedTime = timer.restart();
		timeSinceLastUpdate += elapsedTime;
		if (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			iterations++; //keeps track of how many screen draw iterations have happened
			
			view1.setCenter(player.getSprite().getPosition().x, player.getSprite().getPosition().y); //make view follow player
			
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

				debug = false;
			}

			//**MAP TRANSITIONS**/
			//If you're not currently in a round then you can transition
			if(!roundActive)
			{
				if( map.isTile(player.getRow(),player.getColumn(),Map::Tile::transition)  && !(roundActive))
				{	
					projectiles.clear();//clear projectiles so they don't appear on the second map
					window.setView(window.getDefaultView()); //change view back to normal to display the stores properly
					if(map.getCurrentMap() == 0)
					{
						store = true;
						map.setMap(secondMap,1);
						player.setPosition(1,17);
					}
					else
					{
						store = false;
						map.setMap(mainMap,0);
						player.setPosition(44,17);
					}
				}
			}
			//**END**//

			window.clear();

			lightingSprite.setPosition(player.getSprite().getPosition().x,player.getSprite().getPosition().y); //move shadow/lighting sprite to follow player

			//**CHECK IF ENTERING STORE**//
			if( map.isTile( player.getRow()-1,player.getColumn(),Map::Tile::itemStore) || map.isTile( player.getRow()-1,player.getColumn(),Map::Tile::statStore)) //for item store
			{
				//determine what store type is being entered
				if(map.isTile( player.getRow()-1,player.getColumn(),Map::Tile::itemStore))
				{
					currentStore = &itemStore;
					storeType = 0;
				}
				else
				{
					currentStore = &vitaminStore;
					storeType = 1;
				}

				//stop ambient music and start store music
				musicAmbient.stop();
				musicStore.play();

				//check if first visit to store, if so display unique one time message, if not display random message from array not including first message at 0 index
				if(itemStoreFirstVisit == true && storeType == 0)
				{
					textBox.setMessage(itemStoreMessages[0],window);
					itemStoreFirstVisit = false;
				}
				else if(vitStoreFirstVisit == true && storeType == 1)
				{
					textBox.setMessage(vitaminStoreMessages[0],window);
					vitStoreFirstVisit = false;
				}
				else
				{
					int randonNumber = rand()%(5-1)+1;
					if(storeType == 0)
						textBox.setMessage(itemStoreMessages[randonNumber],window);
					else
						textBox.setMessage(vitaminStoreMessages[randonNumber],window);
					
				}
				textBox.redrawChat(true); //set textBox to be redrawn by game loop
				state = 2; //switch to store state
			}
			//**END**//

			//**DRAW GAME ELEMENTS**//
			window.draw(map.getSprite());

			//dungeon map/main stage
			map.drawMap(window,dungeonStage,shopStage); //draw stage sprite overlay

			//Victory messages stuff
			if(!firstRoundDone && roundActive) //whether or not first round has begun
				firstRoundDone = true;

			//if no enemies, roundMessages message at current index hasn't been displayed (not 1) and the first round has already happened, display message
			if(enemies.size() == 0 && roundMessages[currentRound] == 0 && firstRoundDone)
			{
				textBox.setMessage(victoryMessages[currentRound],window);
				textBox.redrawChat(true);
				roundMessages[currentRound] = 1;
			}

			//**ENEMY DROPS**//
			for(int i = 0; i < droppedCoins.size(); i ++)
			{
				if(droppedCoins.size() > 0)
				{
					if (droppedCoins[i].getConsumed())
					{
						droppedCoins.erase(droppedCoins.begin()+i);				
					}
					else
					{
						if(!store)
						{
							droppedCoins[i].updateCoinDrop(window, player, iterations);		//Draws the coins if you aren't in the store area
						}
						droppedCoins[i].pickedUpCoin(player,soundCoin, HUD);				//adds the amount to your stash over time * multiplier
					}
				}
			}
			//**END**//

			window.draw(player.getSprite()); //draw player sprite
			effect.bloodUpdate(TimePerFrame);
			effect.weaponTrailUpdate(projectiles, player);
			effect.screenShakeUpdate();

			//**RUN / DRAW AI**//
			enemyTree.clear();
			if (enemies.size() > 0)
			{
				if (eLoop >= enemies.size())
				{
					eLoop = 0;
				}
				for(int i = 0; eLoop < enemies.size() && i < 2; i ++)
				{
					if (enemies[eLoop].getHealth() <= 0)
					{
						Coin newCoin = Coin(enemies[eLoop], dropCoinTexture);
						enemies.erase(enemies.begin()+eLoop);
						HUD.increaseCrowdMeter(30);
						droppedCoins.push_back(newCoin);
					}
					else
					{
						enemies[eLoop].calcMovement(player, map, iterations);
						enemyTree.insert(&enemies[eLoop]);
						eLoop ++;
					}
				}
				
				for(int i = 0; i < enemies.size();i++)
				{
					//Enemy Health
					sf::Vector2f ePosition = enemies[i].getPosition();
					healthBar.setPosition(ePosition.x, ePosition.y - 14);
					healthGauge.setPosition(ePosition.x + 2, ePosition.y - 12);
					
					if (enemies[i].type == Enemy::ZOMBIE)
					{
						healthBar.setFillColor(sf::Color::Black);
						healthGauge.setFillColor(sf::Color::Red);
						
						healthBar.setSize(sf::Vector2f(24,7));
						healthGauge.setSize(sf::Vector2f(((float)20/(float)enemies[i].getFHealth())*enemies[i].getHealth(),3));

					}
					else if (enemies[i].type == Enemy::BOSS)
					{
						healthBar.setFillColor(sf::Color::Yellow);
						healthGauge.setFillColor(sf::Color::Magenta);

						healthBar.setSize(sf::Vector2f(42,7));
						healthGauge.setSize(sf::Vector2f(((float)38/(float)enemies[i].getFHealth())*enemies[i].getHealth(),3));
					}

					enemies[i].walk(map,iterations);
					enemies[i].attackTimer --;

					window.draw(healthBar);
					window.draw(healthGauge);
					window.draw(enemies[i].getSprite());
				}
			}

			std::vector<Enemy *> playerCollision;
			playerCollision.clear();
			playerCollision = enemyTree.retrieve(playerCollision, sf::Vector2f(player.getPosition().x,player.getPosition().y));
			int i = 0;

			while(i < playerCollision.size()){
				bool xCollision = (player.getPosition().x + 20 >= playerCollision[i]->getPosition().x) && (player.getPosition().x < playerCollision[i]->getPosition().x + 24);
				bool yCollision = (player.getPosition().y + 20 >= playerCollision[i]->getPosition().y) && (player.getPosition().y < playerCollision[i]->getPosition().y + 24);
				if (xCollision && yCollision){
					if (playerCollision[i]->attackTimer <= 0){
						if (player.takeDamage(playerCollision[i]->getAttack()))
						{
							//GAME OVER

							musicAmbient.stop();
							soundDeathScream.play();
							musicGameOver.play();

							player.setDead(choice);
							if(effect.zoomFreeze(40,5))
							{
								view1.reset(sf::FloatRect(0,0,winX,winY));
						
								textBox2.setTextSettings("Retro Computer_DEMO.ttf", 19, sf::Color::White);
							
								int prevNum = randomMessage;
								randomMessage = rand()%9;

								//To fix an annoying bug where if the same number was chosen twice, no message would show
								while(randomMessage == prevNum)
								{
									randomMessage = rand()%9; //if it's the same generate a new number
								}

								//NUMBER OF CHARCTERS PER LINE, WILL DIFFER DEPENDING ON FONT
								textBox2.SetCharaterLineLimit(55);
								textBox2.setMessage(gameOverMessages[randomMessage],window);
								textBox2.redrawChat(false);//do not redraw textbox
							
								yesText.setPosition(sf::Vector2f(winX*0.2f, winY-450.0f));
								noText.setPosition(sf::Vector2f(winX*0.8f - 150, winY-450.0f));
								continueText.setPosition(sf::Vector2f(winX*0.33f, winY-750.0f));
								selectionOutline.setSize(sf::Vector2f(yesText.getGlobalBounds().width+10, yesText.getGlobalBounds().height+5));
								selectionOutline.setPosition(yesText.getPosition().x - 7, yesText.getPosition().y + 7);
							
								retryChoice = 1;
								state = 4;	
							}
						}
						else
						{
							soundTakeDamage.play();
							std::cout << "ouch!!   Player Health: "<< player.getHealth() << std::endl;
							effect.blood(player);
							player.knockback(map,iterations,playerCollision[i]->getFacing());
							playerCollision[i]->attackTimer = 30;
						}

					}	
				}
				i++;
			}
			//**END**//

			//**DRAW PROJECTILES**//
			for(int i = 0; i < projectiles.size();i++)
			{
				projectiles[i].updateProjectileLocation(window);
				Enemy* hitCheck = projectiles[i].attackHit(&enemyTree);

				if(map.isCollision(projectiles[i].getRow(), projectiles[i].getColumn() ))
				{
					projectiles.erase(projectiles.begin()+i);
				}
				else if(hitCheck != NULL){
 					hitCheck->knockback(map,iterations,projectiles[i].direction);
					projectiles.erase(projectiles.begin()+i);
					hitCheck->takeDamage(player.getAttack());
					effect.screenShake(1, 10);
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

			window.draw(lightingSprite); //draw lighting/shadow sprite
			effect.ambience();

			window.setView(window.getDefaultView()); //change view back to normal so that chatBoxes and HUD elements don't scroll aswell

			//DISPLAY HUD LAST OVER TOP OF EVERYTHING ELSE EXCEPT CHATBOXES
			HUD.drawHUD();
			HUD.updateCoin(iterations);
			HUD.updateActionbar(player.getHealthPotionNumber(),player.getStaminaPotionNumber(),player.getHealthVitaminNumber(),player.getStaminaVitaminNumber(),player.getStrengthVitaminNumber());

			//DISPLAY CHATBOX IF REDRAWCHAT IS SET TO TRUE, IGNORE IF SET TO FALSE. REDRAW AUTOMATICALLY SET TO FALSE WHEN PLAYER CLOSES LAST CHATBOX

			if(textBox.getRedraw() == false)
			{
				itemNotificationBox.displayMessage(window);
			}
			textBox.displayMessage(window);

			//effect.fadeUpdate();

			//DISPLAY DRAW COMPONENTS
			window.display();

			if(iterations >= 10)
			{
				iterations = 0;
			}		
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
							currentStore->moveSelection(1);
							soundChangeSelection.play();
							break;

						case(sf::Keyboard::W):
							currentStore->moveSelection(0);
							soundChangeSelection.play();
							break;

						case (sf::Keyboard::Escape): //exit shop, returns player to state 1 map
							state = 1;
							textBox.redrawChat(false);

							if(storeType == 0)
								player.setPosition(11,11);
							else
								player.setPosition(32,11);

							player.turn(2);

							//stop store music and resume ambient music on exit
							musicStore.stop();
							musicAmbient.play();
							break;

						case (sf::Keyboard::R): //Chat box
							if(currentStore->purchaseItem(player))
								soundNewGame.play();
							else
								soundError.play();
							break;

						case (sf::Keyboard::X):
							textBox.setMessage(currentStore->getInfo(),window);
							textBox.redrawChat(true);
							break;

						}
					}
					else
					{
						switch (event.key.code)
						{
						case (sf::Keyboard::R): //Chat box
							soundChangeSelection.play();
							textBox.setNext(true);
							break;
						}		
					}
				}
			}
		
			sf::Time elapsedTime = timer.restart();
			timeSinceLastUpdate += elapsedTime;
			if (timeSinceLastUpdate > timePerBlink)
			{
				timeSinceLastUpdate -= timePerBlink;
				currentStore->blink(storeType);
			}

			window.clear();

			currentStore->displayStore(storeType,window,player.getGoldStash());
			textBox.displayMessage(window);
		
			window.display();
		
	}

	else if(state == 4)//GAME OVER
	{
		window.clear();
		window.draw(selectionOutline);
		window.draw(yesText);
		window.draw(noText);
		window.draw(continueText);
		textBox2.displayConstantMessage(window);
		window.display();

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
				case (sf::Keyboard::D )://Change selection - NO
					selectionOutline.setPosition(noText.getPosition().x - 30, noText.getPosition().y + 7);
					soundChangeSelection.play();
					retryChoice = 0;
					break;

				case (sf::Keyboard::Right )://Change selection - NO
					selectionOutline.setPosition(noText.getPosition().x - 30, noText.getPosition().y + 7);
					soundChangeSelection.play();
					retryChoice = 0;
					break;

				case (sf::Keyboard::A ): //Change selection - YES
					selectionOutline.setPosition(yesText.getPosition().x - 7, noText.getPosition().y + 7);
					soundChangeSelection.play();
					retryChoice = 1;
					break;

				case (sf::Keyboard::Left ): //Change selection - YES
					selectionOutline.setPosition(yesText.getPosition().x - 7, noText.getPosition().y + 7);
					soundChangeSelection.play();
					retryChoice = 1;
					break;

				case (sf::Keyboard::R): //Select character
					if(retryChoice == 1)
					{
						soundNewGame.play();
						//will need to reset more values than this

						speed = 3;
						attack = 1;
						health = 50;
						stamina = 30;
						choice = 1;

						roundActive = false;
						store = false; //is Player in store

						infinite = false; //infinite spawn mode
						infWait = 5000;
						infRound = 1;

						player.setPosition(23,16);//player starting position
						player.setGoldStash(0);
						HUD.getCrowdDial().setRotation(0.06);
						player.fullHealth(health);
						player.setHealthPotionNumber(1);

						selectionOutline.setSize(sf::Vector2f(warriorBox.getSize().x,warriorBox.getSize().y));
						selectionOutline.setPosition(wizardLoc.x - 10, wizardLoc.y+7);

						enemies.clear();
						droppedCoins.clear();
						projectiles.clear();

						currentRound = 0;
						textBox.setNext(true);

						musicAmbient.play();
						musicGameOver.stop();
						
						state=-1;
					}
					//Go back to main menu??
					else
					{
						window.close();
					}					
					break;
				}
			}
			window.clear();
			window.draw(selectionOutline);
			window.draw(yesText);
			window.draw(noText);
			window.draw(continueText);
			textBox2.displayConstantMessage(window);
			window.display();
			}
		}
	}
    return 0;
}