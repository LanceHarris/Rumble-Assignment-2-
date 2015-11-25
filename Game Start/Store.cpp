#include "Store.h"


Store::Store(string fontTtf, string aStoreName, int winX, int winY, int aStoreType)
{
	storeType = aStoreType;

	//**LOAD ITEM STORE TEXTURES**//
	if(!aStoreKeeperTexture.loadFromFile("itemStoreOwner.png"))
	{
		//error
	}

	if(!aStoreKeeperBlinkTexture.loadFromFile("itemStoreOwnerBlink.png"))
	{
		//error
	}

	//**LOAD VITAMIN STORE TEXTURES**//
	if(!aVitStoreKeeperTexture.loadFromFile("vitaminStoreOwner.png"))
	{
		//error
	}

	if(!aVitStoreKeeperBlinkTexture.loadFromFile("vitaminStoreOwnerBlink.png"))
	{
		//error
	}

	//LOAD BACKGROUND
	if(!aBackground.loadFromFile("storeBackground.jpg"))
	{
		//error
	}

	if(!font.loadFromFile(fontTtf))
	{
		cout << "ERROR: FONT NOT FOUND" << endl;
	}
	exitInfo.setFont(font);
	exitInfo.setCharacterSize(12);
	exitInfo.setString("ESC: Exit          R: Confirm          X: Info");
	exitInfo.setPosition(40,winY-50);



	
	

	float mainBoxWidth = winX * 0.98f;
	float mainBoxHeight = winY * 0.4f;;

	mainBox.setFillColor(sf::Color::Black);
	mainBox.setOutlineColor(sf::Color::White);
	mainBox.setOutlineThickness(5);

	mainBox.setSize( sf::Vector2f(mainBoxWidth,mainBoxHeight) );
	mainBox.setPosition((winX-mainBoxWidth)/2,winY-mainBoxHeight - 10);

	//left menu where items appear
	int leftMenuWidth = winX * 0.8f;
	int leftMenuHeight = winY * 0.4f - 20;

	leftMenu.setFillColor(sf::Color::Black);
	leftMenu.setOutlineColor(sf::Color::White);
	leftMenu.setOutlineThickness(5);

	leftMenu.setSize( sf::Vector2f(leftMenuWidth,leftMenuHeight) );
	leftMenu.setPosition( ((winX-mainBoxWidth)/2)+10,winY-leftMenuHeight - 20);

	//right menu where money and details appear
	int rightMenuWidth = winX * 0.15f;
	int rightMenuHeight = winY * 0.4f - 20;

	rightMenu.setFillColor(sf::Color::Black);
	rightMenu.setOutlineColor(sf::Color::White);
	rightMenu.setOutlineThickness(5);

	rightMenu.setSize( sf::Vector2f(rightMenuWidth,rightMenuHeight) );
	rightMenu.setPosition( (winX-rightMenuWidth)-20,winY-rightMenuHeight - 20);

	//Store background
	//background.setTexture(aBackground);


		//money text
	moneyAmount.setFont(font);
	moneyAmount.setCharacterSize(14);
	moneyAmount.setPosition(winX-rightMenuWidth+10,winY-50);

	
	storeName = aStoreName;

	//store owner sprite
	storeKeeperSprite.setScale(4,4);
	storeKeeperSprite.setTexture(aStoreKeeperTexture);
	storeKeeperSprite.setPosition(sf::Vector2f( (winX/2)-(storeKeeperSprite.getGlobalBounds().width/2),(winY-mainBoxHeight)-storeKeeperSprite.getGlobalBounds().height ));
	
	currentFrame = 0;
	currentItem = 1;

	//max number of items for stores
	if(storeType == 0)
	{
		maxItems = 2; //item store
		firstItem.setString("Health Potion... 10G");
		secondItem.setString("Stamina Potion... 10G");
	}
	else
	{
		maxItems = 3; //vitamin store
		firstItem.setString("Health Vitamin... 100G");
		secondItem.setString("Stamina Vitamin... 100G");
		thirdItem.setString("Strength Vitamin... 100G");
	}
	firstItem.setFont(font);
	firstItem.setCharacterSize(20);
	firstItem.setPosition( ((winX-mainBoxWidth)/2)+15,winY-leftMenuHeight - 15 );
	firstItem.setColor(sf::Color::Yellow);

	secondItem.setFont(font);
	secondItem.setCharacterSize(20);
	secondItem.setPosition( ((winX-mainBoxWidth)/2)+15,winY-leftMenuHeight + 15 );

	thirdItem.setFont(font);
	thirdItem.setCharacterSize(20);
	thirdItem.setPosition( ((winX-mainBoxWidth)/2)+15,winY-leftMenuHeight + 45 );
}

string Store::getStoreName()
{
	return storeName;
}

void Store::blink(int storeType)
{
	if(currentFrame == 0)
	{
		if(storeType == 0)
		{
			storeKeeperSprite.setTexture(aStoreKeeperTexture);
		}
		else
		{
			storeKeeperSprite.setTexture(aVitStoreKeeperTexture);
		}
		
		currentFrame = 1;
	}
	else
	{
		if(storeType == 0)
		{
			storeKeeperSprite.setTexture(aStoreKeeperBlinkTexture);
		}
		else
		{
			storeKeeperSprite.setTexture(aVitStoreKeeperBlinkTexture);
		}
		
		currentFrame = 0;
	}
}


//0 = item, 1 = vitamin
void Store::displayStore(int storeType, sf::RenderWindow &window, int aMoney)
{

	ostringstream ss;
    ss << aMoney;

	moneyAmount.setString( "Gold: "+ss.str() );
	window.draw(background);



	window.draw(storeKeeperSprite);
	window.draw(mainBox);
	window.draw(leftMenu);
	window.draw(rightMenu);
	window.draw(exitInfo);
	window.draw(moneyAmount);

	window.draw(firstItem);
	window.draw(secondItem);
	if(storeType == 1)
		window.draw(thirdItem);
}

void Store::setStoreOwnerTexture(int storeType)
{
	if(storeType == 0)
		storeKeeperSprite.setTexture(aStoreKeeperTexture);
	else
		storeKeeperSprite.setTexture(aVitStoreKeeperTexture);
}

void Store::setCurrentItem(int value)
{
	currentItem = value;
}

int Store::getCurrentItem()
{
	return currentItem;
}

int Store::getMaxItems()
{
	return maxItems;
}

void Store::moveSelection(int direction) 
{

	if(direction == 0)
		currentItem-=1; //up
	else if(direction == 1)
		currentItem+=1; //down

	if(currentItem > maxItems)
		currentItem = 1;
	else if(currentItem <= 0)
		currentItem = maxItems;

	firstItem.setColor(sf::Color::White);
	secondItem.setColor(sf::Color::White);
	thirdItem.setColor(sf::Color::White);

	if(currentItem == 1)
		firstItem.setColor(sf::Color::Yellow);
	else if(currentItem == 2)
		secondItem.setColor(sf::Color::Yellow);
	else if(currentItem == 3)
		thirdItem.setColor(sf::Color::Yellow);
}

bool Store::purchaseItem(Player &player)
{
	if(storeType == 0)
	{
		switch(currentItem)
		{
		case 1:
			if(player.getGoldStash() >= HEALTHPOTPRICE)
			{
				player.giveHealthPotion();
				player.decreaseGoldStash(HEALTHPOTPRICE);
				cout << "You purchased a Health Potion" << endl;
				return true;
			}
			else
			{
				cout << "Not enough gold";
				return false;
			}
			break;
		case 2:
			if(player.getGoldStash() >= STAMPOTPRICE)
			{
				player.giveStaminaPotion();
				player.decreaseGoldStash(STAMPOTPRICE);
				cout << "You purchased a Stamina Potion" << endl;
				return true;
			}
			else
			{
				cout << "Not enough gold";
				return false;
			}
			break;
		}
	}
	else
	{
		switch(currentItem)
		{
		case 1:
			if(player.getGoldStash() >= HEALTHVITPRICE)
			{
				player.giveHealthVitamin();
				player.decreaseGoldStash(HEALTHVITPRICE);
				cout << "You purchased a Health Vitamin" << endl;
				return true;
			}
			else
			{
				cout << "Not enough gold";
				return false;
			}
			break;
		case 2:
			if(player.getGoldStash() >= STAMVITPRICE)
			{
				player.giveStaminaVitamin();
				player.decreaseGoldStash(STAMVITPRICE);
				cout << "You purchased a Stamina Vitamin" << endl;
				return true;
			}
			else
			{
				cout << "Not enough gold";
				return false;
			}
			break;
		case 3:
			if(player.getGoldStash() >= STRENGTHVITPRICE)
			{
				player.giveStrengthVitamin();
				player.decreaseGoldStash(STRENGTHVITPRICE);
				cout << "You purchased a Strength Vitamin" << endl;
				return true;
			}
			else
			{
				cout << "Not enough gold";
				return false;
			}
			break;
		}
	}
}

string Store::getInfo()
{
	if(storeType == 0)
	{
		switch(currentItem)
		{
		case 1:
			return "That's a health potion... It restores your health, do I really need to go over this?";
			break;
		case 2:
			return "A stamina potion, for when you're tired.";
			break;
		}
	}
	else
	{
		switch(currentItem)
		{
		case 1:
			return "That's a health vitamin, it improves your healthiness permanently!";
			break;
		case 2:
			return "This item will make you fitter so you can fight for longer!";
			break;
		case 3:
			return "If you drink a Strength Vitamin, you'll get stronger!... Not that you aren't strong enough already!";
			break;
		}
	}
}

Store::~Store(void)
{
}
