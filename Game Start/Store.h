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

	Store(string fontTtf, string aStoreName, sf::Texture &aStoreKeeperTexture, sf::Texture &aBackground, int winX, int winY);

	//Getters & Setters
	string getStoreName();

	//Other
	void displayStore(sf::RenderWindow &window, int money);

	~Store(void);
};

