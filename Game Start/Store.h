#pragma once
#include <string.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#include "Item.h"

using namespace std;

class Store
{
public:
	int currentFrame;

	//textures
	sf::Texture aStoreKeeperTexture;
	sf::Texture aStoreKeeperBlinkTexture;

	sf::Texture aVitStoreKeeperTexture;
	sf::Texture aVitStoreKeeperBlinkTexture;

	sf::Texture aBackground;

	//item list array
	std::vector<Item> storeInventory;

	string storeName;
	std::ostringstream gold;

	sf::Sprite storeKeeperSprite;
	sf::Sprite background;

	sf::RectangleShape mainBox;
	sf::RectangleShape leftMenu;
	sf::RectangleShape rightMenu;

	sf::Text exitInfo;
	sf::Text moneyAmount;

	sf::Font font;

	Store(string fontTtf, string aStoreName, int winX, int winY);

	//Getters & Setters
	string getStoreName();

	//Other
	void displayStore(int storeType,sf::RenderWindow &window, int money);
	void blink(int storeType);
	void setStoreOwnerTexture(int storeType);
	~Store(void);
};

