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
	regenSpeed = 0.5;
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
	maxLength = (max_HP*3);  //(window.getSize().x / 12) //if we remove the window calculation here it results in more acurately displayed health and stamina bars, in terms of the differences between them
	currLength = maxLength;							

	healthBar.setSize(sf::Vector2f(maxLength,20));
	healthBar.setPosition(10,10);
	healthBar.setFillColor(sf::Color(199,65,56,180));  //RGBA

	//STAMINA BAR
	current_Sta = player.getStamina();
	max_Sta = player.getStamina();
	maxSLength = (max_Sta*3); //(window.getSize().x / 12) //also added a *3 to the addition here to make the aditions to the health bar more exaggerated (if you don't like this Lance, feel free to change it back :) )
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

	//CROWD METER
	if(!meterTexture1.loadFromFile("crowdMeter1.png"))
	{
		std::cout << "Error masking image resource crowdMeter1.png" << std::endl;
	}

	if(!meterTexture2.loadFromFile("crowdMeter2.png"))
	{
		std::cout << "Error masking image resource crowdMeter2.png" << std::endl;
	}

	if(!meterTexture3.loadFromFile("crowdMeter3.png"))
	{
		std::cout << "Error masking image resource crowdMeter3.png" << std::endl;
	}

	if(!meterTexture4.loadFromFile("crowdMeter4.png"))
	{
		std::cout << "Error masking image resource crowdMeter4.png" << std::endl;
	}

	if(!dialTexture.loadFromFile("crowdDial.png"))
	{
		std::cout << "Error masking image resource crowdDial.png" << std::endl;
	}

	// - USEFUL IF THE BACKGROUND ISN'T TRANSPARENT
	sf::Image dialImage = dialTexture.copyToImage();
	dialImage.createMaskFromColor(sf::Color(255, 255, 255), 0);
	
	if (!dialTexture.loadFromImage(dialImage))
	{
		std::cout << "Error masking image resource crowdDial.png" << std::endl;
	}

	this->crowdMeterOverlay.setTexture(meterTexture1);
	this->crowdDial.setTexture(dialTexture);

	this->crowdMeterOverlay.setScale(0.25,0.25);
	this->crowdMeterOverlay.setPosition(((window.getSize().x - crowdMeterOverlay.getGlobalBounds().width) - 10), 7);

	this->crowdDial.setScale(0.45,0.45);
	this->crowdDial.setPosition((crowdMeterOverlay.getPosition().x + crowdMeterOverlay.getGlobalBounds().width/2), (crowdMeterOverlay.getPosition().y + crowdMeterOverlay.getGlobalBounds().height/2));
	this->crowdDial.setOrigin(crowdDial.getGlobalBounds().width, crowdDial.getGlobalBounds().height + 40); //40 centres it around the hilt gem
}

sf::Sprite & Hud::getCrowdDial()
{
	return this->crowdDial;
}

void Hud::updateCrowdMeter()
{
	float degrees = this->crowdDial.getRotation();

	if(degrees > 0.05 && degrees < 90)
	{
		this->crowdDial.rotate(-0.05);
		this->crowdMeterOverlay.setTexture(meterTexture1);
	}
	else if(degrees > 90 && degrees < 180)
	{
		this->crowdDial.rotate(-0.07);
		this->crowdMeterOverlay.setTexture(meterTexture2);
	}
	else if(degrees > 180 && degrees < 270)
	{
		this->crowdDial.rotate(-0.12);
		this->crowdMeterOverlay.setTexture(meterTexture3);
	}
	else if(degrees > 270 && degrees < 360)
	{
		this->crowdDial.rotate(-0.15);
		this->crowdMeterOverlay.setTexture(meterTexture4);
	}
	//std::cout << degrees << std::endl;
	//std::cout << crowdDial.getOrigin().x << ", " << crowdDial.getOrigin().y << std::endl;
}

void Hud::increaseCrowdMeter(int amount)
{
	float degrees = this->crowdDial.getRotation();
	int newAmount = 360-degrees;

	if(degrees+amount <= 360)
	{
		this->crowdDial.rotate(amount);
	}
	else
	{
		this->crowdDial.rotate(newAmount);
	}
}

float Hud::calculateMultiplier()
{
	float degrees = this->crowdDial.getRotation();
	float multiplier = 0;

	if(degrees > 0.05 && degrees < 90)
	{
		multiplier = 1.5;
	}
	else if(degrees > 90 && degrees < 180)
	{
		multiplier = 2.0;
	}
	else if(degrees > 180 && degrees < 270)
	{
		multiplier = 2.5;
	}
	else if(degrees > 270 && degrees < 360)
	{
		multiplier = 3.0;
	}
	return multiplier;
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
	current_HP = _player->getHealth();
	currLength = ((current_HP * maxLength) / max_HP); //Calculates the percentage of the bar that has been lost (eg. if you have lost 10% of your 100 HP, it will give you 90% of the bar's total length. In this case 243
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
	_window->draw(crowdMeterOverlay);
	_window->draw(crowdDial);
}

//CONSTANTLY INCREASES STAMINA AND CHECKS IF ALL STAMINA HAS BEEN USED UP
void Hud::updateStamina()
{
	if(current_Sta <= max_Sta)
	{
		if(currSLength > 0)
		{
			outOfStamina = false;
			if( (current_Sta+=regenSpeed) > max_Sta)
			{
				current_Sta = max_Sta;
			}
			else
			{
				current_Sta+=regenSpeed;
			}
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
	max_HP += newHP; //increase max HP
	current_HP = max_HP; //restore all HP

	maxLength = (max_HP*3); //update maxLength
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

	maxSLength = (max_Sta*3); //stamina regens on its own, no need to restore it :)

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

void Hud::setStaminaBarAttributes(int choice)
{
	//WARRIOR STAMINA
	if(choice == 0)
	{
		this->staminaBar.setFillColor(sf::Color(122,207,125,180));
	}

	//WIZARD MANA
	else if(choice == 1)
	{
		this->staminaBar.setFillColor(sf::Color(103,164,245,180));
	}
}

Hud::~Hud(void)
{
}
