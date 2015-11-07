#include "Store.h"


Store::Store(string fontTtf, string aStoreName, sf::Texture &aStoreKeeperTexture, sf::Texture &aBackground, int winX, int winY)
{
	
	if(!font.loadFromFile(fontTtf))
	{
		cout << "ERROR: FONT NOT FOUND" << endl;
	}
	exitInfo.setFont(font);
	exitInfo.setCharacterSize(12);
	exitInfo.setString("Press ESC to exit at any time");
	exitInfo.setPosition(40,winY-50);



	
	storeName = aStoreName;
	storeKeeperSprite.setTexture(aStoreKeeperTexture);

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
	background.setTexture(aBackground);


		//money text
	moneyAmount.setFont(font);
	moneyAmount.setCharacterSize(14);
	moneyAmount.setPosition(winX-rightMenuWidth+10,winY-50);
}

string Store::getStoreName()
{
	return storeName;
}

void Store::displayStore(sf::RenderWindow &window, int aMoney)
{
	ostringstream ss;
    ss << aMoney;

	moneyAmount.setString( "Gold: "+ss.str() );
	window.draw(background);
	window.draw(mainBox);
	window.draw(leftMenu);
	window.draw(rightMenu);
	window.draw(exitInfo);
	window.draw(moneyAmount);
}

Store::~Store(void)
{
}
