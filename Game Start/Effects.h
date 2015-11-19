/*
*	Effects.h
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 11 November 2015
*
*/

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <list>

#include "Map.h"
#include "Hud.h"
#include "Character.h"
#include "projectile.h"
#include "Particle.h"

class Effects
{
public:
	Effects(sf::View &view, sf::RenderWindow &window, Map &map, Hud & HUD, Player & player, std::vector<Projectile> & projectiles);
	~Effects(void);

	void wait(int seconds);
	void zoomFreeze(float maxZoom, float seconds, float interval = 0.05);

	void screenShake(int power, float shakeFrames);
	void screenShakeUpdate();

	void fade(int red, int green, int blue, float alpha, float frames, int finalAlpha);
	void fadeUpdate();

	void blood(Character &target);
	void bloodUpdate(sf::Time TimePerFrame);

	void ambience();

	void weaponTrail();
	void weaponTrailUpdate(std::vector<Projectile> &weapon, Player &player);

private:
	sf::RenderWindow *_window;
	Player *_player;
	sf::View *_view;
	Map *_map;
	Hud *_hud;
	std::vector<Projectile> *_projectile;

	//SCREEN SHAKE
	bool shakeScreen;	//set to true to start shaking the screen
	int power;			//the amount the screen is shaken is multiplied by this, so the minimum is 1
	float shakeFrames;
	float shakeTimer;

	//FADE
	sf::RectangleShape transition;	//the rectangle that covers the screen
	float fadeIncrement;
	float alpha;
	float fadeFrames;
	float fadeTimer;
	bool fadeScreen; 
	int red;
	int green;
	int blue;
	int finalAlpha;

	//DRAW METHOD
	void draw();		//Set to private because it's just to be used in class methods as a shortcut
	sf::Texture dungeonMap;
	sf::Sprite dungeonStage;
	sf::Texture shopMap;
	sf::Sprite shopStage;
	sf::Texture lighting;
	sf::Sprite lightingSprite;

	//BLOOD
	Character *_target;		//The target of the blood spray
	sf::FloatRect rect;		//Boundary
	const static int BLOOD_SIZE = 10;
	const static int PARTICLE_RADIUS = 7;
	std::list<Particle> bloodParticles;	 
	bool bloodEffect;

	//AMBIENCE
	std::list<Particle> lightParticles;

	//WEAPON TRAIL
	std::list<Particle> weaponParticles;
	bool attacked;
};

