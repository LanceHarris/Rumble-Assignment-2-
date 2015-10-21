#include "ChatBox.h"

ChatBox::ChatBox(int winX, int winY)
{
	renderWindowX = (float)winX;
	renderWindowY = (float)winY;
	width = renderWindowX*0.8f; //chatBox x axis spans 80% width of screen
	height = renderWindowY*0.15f; //chatBox y axis spans 20% width of screen

	textBox.setSize(sf::Vector2f(width,height));
	textBox.setFillColor(sf::Color::Black);
	textBox.setOutlineColor(sf::Color::White);
	textBox.setOutlineThickness(5);
	textBox.setPosition(sf::Vector2f( (renderWindowX - width) / 2, (renderWindowY - height) - 30));

	lineLimit = 72;

	//load default font
	if(!font.loadFromFile("arial.ttf"))
	{
		cout << "ERROR: FONT NOT FOUND" << endl;
	}
	text.setFont(font);
	text.setPosition(sf::Vector2f(width*0.15f,renderWindowY - height - (20)));

	textSpaceMessage.setString("Press R to continue...");
	textSpaceMessage.setPosition((float)(renderWindowX - (renderWindowX - width) - 45), (float)(renderWindowY - (height*0.4)));
	textSpaceMessage.setFont(font);
	textSpaceMessage.setCharacterSize(8);

	pageLimit = 3;
	start = 0;
	numOfBoxes = 0;
	boxesDone = 0;
	next = false;
}

ChatBox::~ChatBox(void)
{
}

void ChatBox::SetCharaterLineLimit(int limit)
{
	lineLimit = limit;
}


void ChatBox::setTextSettings(string fontTtf, int size, sf::Color Colour)
{
	text.setPosition(sf::Vector2f(width*0.15f,renderWindowY - height - (20)));
	if(!font.loadFromFile(fontTtf))
	{
		cout << "ERROR: FONT NOT FOUND" << endl;
	}

	text.setFont(font);
	text.setCharacterSize(size);
	text.setColor(Colour);
}

void ChatBox::setMessage(string aMessage, sf::RenderWindow &window)
{
	message = aMessage;
	messageLine = "";
	text.setString(aMessage);

	int count = 0;
	int lineCount = 0;
	numOfBoxes = 1;


	for(unsigned int i = 0; i < message.length();i++)
	{
		if(lineCount == 3)
		{
			messageLine += "(BREAK)";
			lineCount = 0;
			numOfBoxes++;
			i-=1;
		}
		else 
		{

			if(count >= lineLimit)
			{
				while(message[i] != ' ')
				{
					messageLine.erase(i,i);
					i-=1;
				}
				messageLine += "\n";
				lineCount++;
				count = 0;
			}
			else
			{
				messageLine+= message[i];
				count++;
			}
		}
	}
	boxesDone = numOfBoxes;
	message = messageLine;
}

void ChatBox::displayMessage(sf::RenderWindow &window)
{
	string::size_type loc;

	if(redraw == true)
	{
		window.draw(textBox);
		if(boxesDone > 1)
		{
				loc = message.find( "(BREAK)", 0 );
				text.setString(message.substr(0,loc));
				window.draw(text);

				if (next)
				{
					boxesDone-=1;
					cout << boxesDone << endl;
					message.erase(0,loc+7);
					next = false;
				}
		}
		else
		{
			text.setString(message);
			window.draw(text);

			if (next)
			{
				message = messageLine;
				boxesDone = numOfBoxes;
				next = false;
				redrawChat(false);
			}

		}
		window.draw(textSpaceMessage);

	}
}

void ChatBox::setNext(bool choice)
{
	next = choice;
}

void ChatBox::redrawChat(bool status)
{
	redraw = status;
}
