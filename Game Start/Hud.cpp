/*
*	Hud.cpp
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 2 November 2015
*
*/

#include <SFML\Graphics.hpp>
#include "Hud.h"

Hud::Hud(Character &player, sf::RenderWindow &window)
{
	gameOver = false;
	outOfStamina = false;
	regenSpeed = 0.3;
	repercussion = 0;
	_window = &window; //Can use this to reference the window used in the constructor parameter anywhere in the class (eg see drawHUD method)

	//HEALTH BAR
	current_HP = player.getHealth();				
	max_HP = player.getHealth();					
	maxLength = (window.getSize().x / 4) + max_HP; 
	currLength = maxLength;							

	healthBar.setSize(sf::Vector2f(maxLength,20));
	healthBar.setPosition(10,10);
	healthBar.setFillColor(sf::Color(199,65,56,180));  //RGBA

	//STAMINA BAR
	current_Sta = player.getStamina();
	max_Sta = player.getStamina();
	maxSLength = (window.getSize().x / 8) + max_Sta;
	currSLength = maxSLength;

	staminaBar.setSize(sf::Vector2f(maxSLength, 20));
	staminaBar.setPosition(10, 30);
	staminaBar.setFillColor(sf::Color(122,207,125,180)); //RGBA

	window.draw(healthBar);
	window.draw(staminaBar);
}

//This could be a double up with Character::takeDamage?
void Hud::takeDamage(int damage)
{
	current_HP -= damage;
	currLength = ((current_HP * maxLength) / max_HP); //Calculates the percentage of the bar that has been lost (eg. if you have lost 10% of your 100 HP, it will give you 90% of the bar's total length. In this case 243
}

void Hud::takeStamina(float stamina)
{
	if(current_Sta >= 1)
	{
		current_Sta -= stamina;
		currSLength = ((current_Sta * maxSLength) / max_Sta);
	}
}

void Hud::drawHUD()
{
	if(currSLength >= 1)
	{
		staminaBar.setSize(sf::Vector2f(currSLength, 20));
		_window->draw(staminaBar);
	}

	if(currLength >= 1)
	{
		healthBar.setSize(sf::Vector2f(currLength, 20));
		_window->draw(healthBar);
	}
	else
	{
		gameOver = true;
	}
}

void Hud::updateStamina()
{
	if(current_Sta <= max_Sta)
	{
		if(currSLength > 0)
		{
			outOfStamina = false;
			current_Sta+=regenSpeed;
			currSLength = ((current_Sta * maxSLength) / max_Sta);
			repercussion = 0;
			this->drawHUD();
		}
		//Repercussion for using up all your stamina
		else
		{
			outOfStamina = true;
			current_Sta = -60 + repercussion; //Couldn't think of a better way to force a cooldown on the player for using up all their stamina. But this effectively forces the player to wait a frame 
			repercussion++;					  //Could create an mutator for this value and reset it to 0 if the player keeps clicking after using up their stamina, forcing them to wait.
			currSLength = ((current_Sta * maxSLength) / max_Sta);
			this->drawHUD();
		}
	}
}

bool Hud::getGameOver()
{
	return gameOver;
}

bool Hud::getOutOfStamina()
{
	return outOfStamina;
}

void Hud::increaseMaxHP(int newHP)
{
	this->max_HP += newHP;
	this->current_HP += newHP;
	maxLength = (_window->getSize().x / 4) + max_HP;			//Update max length to reflect new values

	currLength = ((current_HP * maxLength) / max_HP);			//Update it on screen

	/*std::cout << "Max_HP: " << max_HP << std::endl;
	std::cout << "Current HP :" << current_HP << std::endl;
	std::cout << "Current Length :" << currLength << std::endl;
	std::cout << "Max Length :" << maxLength << std::endl;
	*/
}

void Hud::increaseMaxSta(int newSta)
{
	this->max_Sta += newSta;
	this->current_Sta += newSta;
	maxSLength = (_window->getSize().x / 8) + max_Sta;

	currSLength = ((current_Sta * maxSLength) / max_Sta);

	/*std::cout << "Max Sta: " << max_Sta << std::endl;
	std::cout << "Current Sta :" << current_Sta << std::endl;
	std::cout << "Current Length :" << currSLength << std::endl;
	std::cout << "Max Length :" << maxSLength << std::endl;
	*/
}

//This is here for when the character uses a potion?
void Hud::healHealth()
{

}

Hud::~Hud(void)
{
}
