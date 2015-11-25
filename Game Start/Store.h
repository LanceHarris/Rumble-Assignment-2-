#pragma once
#include <string.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#include "Item.h"
#include "Character.h"

using namespace std;

class Store
{
public:
	int currentFrame;
	int maxItems;
	int currentItem;
	int storeType;

	static const int HEALTHPOTPRICE = 10;
	static const int STAMPOTPRICE = 10;

	static const int HEALTHVITPRICE = 100;
	static const int STRENGTHVITPRICE = 100;
	static const int STAMVITPRICE = 100;

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

	sf::Text firstItem;
	sf::Text secondItem;
	sf::Text thirdItem;

	sf::Text exitInfo;
	sf::Text moneyAmount;

	sf::Font font;

	Store(string fontTtf, string aStoreName, int winX, int winY, int storeType);

	//Getters & Setters
	string getStoreName();

	//Other
	void displayStore(int storeType,sf::RenderWindow &window, int money);
	void blink(int storeType);
	void setStoreOwnerTexture(int storeType);
	void setCurrentItem(int aValue);
	int getCurrentItem();
	int getMaxItems();
	void moveSelection(int direction);
	bool purchaseItem(Player &player);
	string getInfo();
	~Store(void); 
};

