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

Hud::Hud(Player &player, sf::RenderWindow &window)
{
	gameOver = false;
	outOfStamina = false;
	regenSpeed = 0.3;
	repercussion = 0;

	coinXPos = 0;
	coinGap = 2;
	coinWidth = 30;
	coinHeight = 32;

	_window = &window; //Can use this to reference the window used in the constructor parameter anywhere in the class (eg see drawHUD method)
	_player = &player; //Same as above but for Player object

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

	//COIN COUNTER
	if (!coinTexture.loadFromFile("spinning_coin_gold.png"))
	{
		std::cout << "Error loading resource spinning_coin_gold.png" << std::endl;
	}
	
	/* - USEFUL IF THE BACKGROUND STOPS BEING TRANSPARENT (EG IF YOU TRY TO EDIT IT IN SOMETHING LIKE PAINT...) 
	sf::Image coinImage = coinTexture.copyToImage();
	coinImage.createMaskFromColor(sf::Color(255, 255, 255), 0);
	
	if (!coinTexture.loadFromImage(coinImage))
	{
		std::cout << "Error masking image resource spinning_coin_gold.png" << std::endl;
	}*/

	this->coin.setTexture(coinTexture);
	this->coin.setPosition(10, (window.getSize().y - 32) - 10); //Subtract the height of the coin and another 10 to get it 10 pixels from the bottom
	this->coin.setTextureRect(sf::IntRect((coinXPos * coinWidth) + (coinGap * coinXPos)+coinGap, 0, coinWidth, coinHeight));

	if(!goldFont.loadFromFile("8-BIT WONDER.ttf"))
	{
		std::cout << "Error masking image resource 8-BIT WONDER.ttf" << std::endl;
	}

	this->goldCount.setFont(goldFont);
	this->goldCount.setColor(sf::Color::White);
	this->goldCount.setPosition(((coin.getPosition().x + coinWidth) + 10), coin.getPosition().y);

	std::ostringstream buff;
	buff << player.getGoldStash();
	this->goldCount.setString(buff.str());
}

//This could be a double up with Character::takeDamage?
void Hud::takeDamage(int damage)
{
	current_HP -= damage;
	currLength = ((current_HP * maxLength) / max_HP); //Calculates the percentage of the bar that has been lost (eg. if you have lost 10% of your 100 HP, it will give you 90% of the bar's total length. In this case 243
}

//USE THIS TO DECREASE THE STAMINA (EG WHEN AN AXE IS THROWN)
void Hud::takeStamina(float stamina)
{
	if(current_Sta >= 1)
	{
		current_Sta -= stamina;
		currSLength = ((current_Sta * maxSLength) / max_Sta);
	}
}

//DRAWS HEALTH AND STAMINA BARS, CHECKS LOSE CONDITION
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

//CONSTANTLY INCREASES STAMINA AND CHECKS IF ALL STAMINA HAS BEEN USED UP
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
		}
		//Repercussion for using up all your stamina
		else
		{
			outOfStamina = true;
			current_Sta = -60 + repercussion; //Couldn't think of a better way to force a cooldown on the player for using up all their stamina. But this effectively forces the player to wait a frame 
			repercussion++;					  //Could create an mutator for this value and reset it to 0 if the player keeps clicking after using up their stamina, forcing them to wait.
			currSLength = ((current_Sta * maxSLength) / max_Sta);
		}
	}
}

//INCREMENTS THE SPRITE INTRECT AND UPDATES COIN AMOUNT
void Hud::updateCoin()
{
	if(coinXPos >= 7)
	{
		coinXPos = 0;
	}
	else
	{
		coinXPos+=1;
	}

	this->coin.setTextureRect(sf::IntRect((coinXPos * coinWidth) + (coinGap * coinXPos)+coinGap,0,coinWidth,coinHeight));

	std::ostringstream buff;
	buff << _player->getGoldStash();

	this->goldCount.setString(buff.str());

	_window->draw(coin);
	_window->draw(goldCount);
}

bool Hud::getGameOver()
{
	return gameOver;
}

bool Hud::getOutOfStamina()
{
	return outOfStamina;
}

//USE WHEN PERMANENTLY INCREASING MAX HP
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

//USE WHEN PERMANENTLY INCREASING STAMINA
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

void Hud::useHealthPotion(int potionLevel, Player &player)
{
	if(current_HP == max_HP)
	{
		cout<<"Health already full"<<endl; //full health
	}
	else if(player.getHealthPotionNumber() > 0)
	{
		int healAmount = 40 * potionLevel;
		int missingHP = max_HP - current_HP;

		if( healAmount < missingHP )
			current_HP += healAmount;
		else
			current_HP = max_HP;

		player.removeHealthPotion();
		currLength = ((current_HP * maxLength) / max_HP);
		cout<<"Potion used"<<endl; //remove this later and add drinking sound
	}
	else//for both having no health potions and having full health
	{
		cout<<"No health potions"<<endl; //remove this later and add an error sound "EH-EH!!" or something :P
	}
	
}

void Hud::useStaminaPotion(int potionLevel, Player &player)
{
	if(current_Sta == max_Sta)
	{
		cout<<"Stamina already full"<<endl; //full health
	}
	else if(player.getStaminaPotionNumber() > 0)
	{	
		int healAmount = 40 * potionLevel;
		int missingSta = max_Sta - current_Sta;

		if( healAmount < missingSta )
			current_Sta += healAmount;
		else
			current_Sta = max_Sta;

		player.removeStaminaPotion();
		currSLength = ((current_Sta * maxSLength) / max_Sta);
		cout<<"Stamina used"<<endl;//remove this later and add drinking sound
	}
	else//for having no stamina potions and full stamina
	{
		cout<<"No Stamina potions"<<endl; //remove this later and add an error sound "EH-EH!!" or something :P
	}
}

//This is here for when the character uses a potion?
void Hud::healHealth()
{

}

Hud::~Hud(void)
{
}
