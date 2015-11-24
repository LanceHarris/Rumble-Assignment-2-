#include "Coin.h"

//Constructor
Coin::Coin(Enemy &enemy, sf::Texture coinTexture)
{
	coinXPos = 0;
	coinGap = 2;
	coinWidth = 30;
	coinHeight = 32;

	this->coinTexture = coinTexture;
	coin.setTexture(coinTexture);
	coin.setScale(0.5,0.5);
	coin.setPosition(sf::Vector2f(enemy.getPosition().x, enemy.getPosition().y));
	coin.setTextureRect(sf::IntRect((coinXPos * coinWidth) + (coinGap * coinXPos)+coinGap, 0, coinWidth, coinHeight));
	
	pickedUp = false;
	consumed = false;
	increment = 0;

	if(enemy.type == Enemy::ZOMBIE)
	{
		amount = (rand()%50)+25; //Between 25 and 75
	}

	//Bosses give you more gold!
	else if(enemy.type == Enemy::BOSS)
	{
		amount = (rand()%300)+50; //Between 50 and 350
	}
}

Coin::~Coin(void)
{
}

//Used to update the animation for the coin and check if there is a collision
void Coin::updateCoinDrop(sf::RenderWindow & window, Player & player, int &iterations)
{
	//Don't draw the coin if it has been picked up (ie pickedUp = true)
	if(!pickedUp)
	{
		coin.setTexture(coinTexture);

		//Keeps the animation in time with the game loop
		if(iterations >= 10)
		{
			if(coinXPos >= 7)
			{
				coinXPos = 0;
			}
			else
			{
				coinXPos+=1;
			}
		}

		coin.setTextureRect(sf::IntRect((coinXPos * coinWidth) + (coinGap * coinXPos)+coinGap,0,coinWidth,coinHeight));
	
		window.draw(coin);

		//Simple collision check
		if(player.getSprite().getGlobalBounds().intersects(coin.getGlobalBounds()))
		{
			pickedUp = true;
			//Add sound effect here methinks!
		}
	}
}

//Adds the effect of coins being added to your stash over time then marks the coin as consumed so the vector can erase it
void Coin::pickedUpCoin(Player & player)
{
	//If the coin has been pickedUp...
	if(pickedUp)
	{
		if(increment < amount)
		{
			player.increaseGoldStash(1);
			increment++;
		}
		else
		{
			pickedUp = false;
			increment = 0;
			consumed = true;
		}
	}
}

//For the vector to check if the coin has been consumed (ie it has been collided with and the amount has finished adding to your stash)
bool Coin::getConsumed()
{
	return consumed;
}