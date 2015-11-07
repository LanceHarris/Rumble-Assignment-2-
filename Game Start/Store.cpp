#include "Store.h"


Store::Store(string fontTtf, string aStoreName, int winX, int winY)
{
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
	exitInfo.setString("Press ESC to exit at any time");
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
}

void Store::setStoreOwnerTexture(int storeType)
{
	if(storeType == 0)
		storeKeeperSprite.setTexture(aStoreKeeperTexture);
	else
		storeKeeperSprite.setTexture(aVitStoreKeeperTexture);
}

Store::~Store(void)
{
}
