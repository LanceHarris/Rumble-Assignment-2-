#pragma once
#include <string.h>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class ChatBox
{
public:
	sf::RectangleShape textBox;
	sf::Font font;
	sf::Text text;
	sf::Text textSpaceMessage;
	float renderWindowX;
	float renderWindowY;
	float width;
	float height;
	int bottomPadding;
	int lineLimit;
	int pageLimit;
	int messageLength;
	string message;
	string messageLine;
	bool redraw;
	int numOfBoxes;
	int start;
	int boxesDone;
	bool next;

public:
	ChatBox(int winX, int winY, int botPadding);
	~ChatBox(void);
	void displayMessage(sf::RenderWindow &window);
	void setTextSettings(string fontTtf, int size, sf::Color Colour, int botPadding);
	void SetCharaterLineLimit(int limit);
	void setMessage(string message, sf::RenderWindow &window);
	void redrawChat(bool status);
	void setPageLineLimit(int Limit);
	void setNext(bool choice);

};

