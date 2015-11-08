/*
*	Player.cpp
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 25 October 2015
*
*/

#include "Character.h"

int goldStash = 0;


Player::Player(int &health, float &speed, int &stamina) : Character(health, speed, stamina)
{
	spriteXPos = 0;
	spriteYPos = 0;
	SPRITEWIDTH = 16;
	SPRITEHEIGHT = 16;
	SPRITEMAX = 4;
	SPRITEGAP = 1;

	//potions
	healthPotionNumber = 1; //to test
	staminaPotionNumber = 0;

	//vitamins
	strengthVitaminNumber = 0;
	healthVitaminNumber = 0;
	staminaVitaminNumber = 0;

	//gold
	goldStash = 10;

	if (!texture.loadFromFile("characterSheetCustom.png"))
	{
		std::cout << "Error loading resource characterSheet.png" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(SPRITEGAP,SPRITEGAP,SPRITEWIDTH,SPRITEHEIGHT));
	sprite.setScale(1.6, 1.6);
	facing = RIGHT;
}

void Player::processDirectionalKeyPresses(Map &map, int &iterations)
{
			if(((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))))
			{

				setFacing(Character::RIGHT);
				walk(map,iterations);
			}
			//LEFT
			else if(((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))))
			{

				setFacing(Character::LEFT);
				walk(map,iterations);
			}
			//UP
			else if(((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))))
			{

				setFacing(Character::UP);
				walk(map,iterations);
			}
			//DOWN
			else if(((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))))
			{

				setFacing(Character::DOWN);
				walk(map,iterations);
			}
}

//determines vector aiming and allows player to shoot projectiles where the mouse is (limited to 4 directions)
	void Player::processMouseAiming(sf::Vector2f mPos)
	{
		sf::Vector2f pPos = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y);

				//works out the degrees of the vector between the player position and the mouse position
				float degrees = atan2f(mPos.y - pPos.y, mPos.x - pPos.x) * 180 / 3.14159 /* PI */;
				//std::cout<< "Degrees: " << degrees <<std::endl;

				if(degrees <= 140 && degrees > 35)
				{
					turn(2); //DOWN
				}
				if(degrees <= -40 && degrees > -140)
				{
					turn(0);//UP
				}
				if(degrees > -40 && degrees <= 35)
				{
					turn(1);//RIGHT
				}
				if(degrees <= -140 || degrees > 140)
				{
					turn(3);//LEFT
				}	
}

int Player::getGoldStash()
{
	return goldStash;
}

void Player::increaseGoldStash(int newGold)
{
	goldStash += newGold;
}

void Player::useStrengthVitamin()
{
	attack += 1;
}

void Player::useHealthVitamin()
{
	health += 10;
}

void Player::useStaminaVitamin()
{
	stamina += 10;
}

//Potion methods
int Player::getHealthPotionNumber()
{
	return healthPotionNumber;
}

int Player::getStaminaPotionNumber()
{
	return staminaPotionNumber;
}

void Player::removeHealthPotion()
{
	healthPotionNumber-=1;
}

void Player::removeStaminaPotion()
{
	staminaPotionNumber-=1;
}

void Player::giveStaminaPotion()
{
	staminaPotionNumber+=1;
}

void Player::giveHealthPotion()
{
	healthPotionNumber+=1;
}

void Player::giveStrengthVitamin()
{
	strengthVitaminNumber+=1;
}

void Player::giveHealthVitamin()
{
	healthVitaminNumber+=1;
}
	
void Player::giveStaminaVitamin()
{
	staminaVitaminNumber+=1;
}

void Player::removeStrengthVitamin()
{
	strengthVitaminNumber-=1;
}

void Player::removeHealthVitamin()
{
	healthVitaminNumber-=1;
}
	
void Player::removeStaminaVitamin()
{
	staminaVitaminNumber-=1;
}

int Player::getStrengthVitaminNumber()
{
	return strengthVitaminNumber;
}

int Player::getStaminaVitaminNumber()
{
	return staminaVitaminNumber;
}

int Player::getHealthVitaminNumber()
{
	return healthVitaminNumber;
}

Player::~Player()
{
}