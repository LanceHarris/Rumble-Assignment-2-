#include "menu.h"


Menu::Menu(float width, float hieght)
{
	if (font.loadFromFile("Retro Computer_DEMO.ttf"))
	{
		//error handel
	}
	selectedItemIndex = 0; 

	newGame.setColor(sf::Color::Yellow);
	newGame.setString("New Game");
	newGame.setCharacterSize(50);
	newGame.setPosition((width/2)-150, (hieght/2)-50);
	newGame.setFont(font);

	/*menu[1].setColor(sf::Color::White);
	menu[1].setString("Option");
	menu[1].setPosition(sf::Vector2f(width/2,hieght/(Max_Num+1)*2));*/

	Exit.setColor(sf::Color::White);
	Exit.setString("Exit");
	Exit.setCharacterSize(50);
	Exit.setPosition((width/2)-150, (hieght/2)+50);
	Exit.setFont(font);

}


Menu::~Menu(void)
{
}

void Menu::Move()
{
	if(selectedItemIndex == 1)
	{
		newGame.setColor(sf::Color::Yellow);
		Exit.setColor(sf::Color::White);
		selectedItemIndex = 0;
	}
	else
	{
		newGame.setColor(sf::Color::White);
		Exit.setColor(sf::Color::Yellow);
		selectedItemIndex = 1;
	}
}

void Menu::selectOption(int &state, sf::RenderWindow &window)
{
	if(selectedItemIndex == 0)
		state = 0;
	if(selectedItemIndex == 1)
		window.close();
}

void Menu::draw(sf::RenderWindow &window)
{
	window.clear();

	window.draw(newGame);
	window.draw(Exit);

	window.display();
}