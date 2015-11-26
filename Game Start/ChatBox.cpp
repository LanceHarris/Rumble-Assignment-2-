/*
*	Character.h
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 25 October 2015
*
*/

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
	numOfBoxes = 0;

	for(unsigned int i = 0; i < message.length();i++)
	{
		//IF STRING CONTAINS 3 LINES, INSERT (BREAK) SO THEY CAN BE BROKEN INTO SEPARATE CHATBOXES LATER
		if(lineCount == 3)
		{
			messageLine += "^";
			lineCount = 0;
			i-=1;
			numOfBoxes+=1;
		}
		//LINECOUNT STILL LESS THAN MAXIMUM OF 3
		else 
		{
			//MAX NUMBER OF ALLOWED CHARACTERS PER LINE IS REACHED, INCREMENT LINECOUNT AND IF LINE END IS NOT AT A SPACE, ERASE CHARACTERS UNTIL ONE IS REACHED
			if(count >= lineLimit)
			{
				while(message[i] != ' ')
				{
					messageLine.erase(i+numOfBoxes,i+numOfBoxes);
					i-=1;
				}

				messageLine += "\n";
				lineCount++;
				count = 0;
			}
			//LINELIMIT NOT REACHED, CONTINUE WRITING CHARACTERS INTO MESSAGELINE
			else
			{
				messageLine+= message[i];
				count++;
			}
		}
	}

	//SET MESSAGE TO MESSAGELINE. "\n and (BREAK)" ADDED
	message = messageLine;
	cout << message << endl;
}

void ChatBox::displayMessage(sf::RenderWindow &window)
{
	

	//IF REDRAW IS SET TO TRUE, DRAW CHATBOX(S)
	if(redraw == true)
	{
		boxesDone = count(message.begin(),message.end(),'^')+1;
		
		//VARIABLE TO STORE LOCATINO OF FOUND (BREAK)'S IN CHATBOX STRING
		string::size_type loc;

		//DRAW BLACK BOX WITH WHITE OUTLINE UDNER CHATBOX TEXT
		window.draw(textBox);

		//IF THERE IS MORE THAN 1 BOX WORTH OF TEXT (EG: (BREAK)'S INSERTED
		if(boxesDone > 1)
		{
				//FIND LOCATION OF INSERTED (BREAK)'S
				loc = message.find( "^", 0 );

				//SET TEXT TO SUBSTR OF TEXT FROM BEGINNING TO FIRST (BREAK)
				text.setString(message.substr(0,loc));
				window.draw(text);

				//IF PLAYER CLICKS "R", NEXT IS SET TO TRUE
				if (next)
				{
					boxesDone-=1;
					cout << boxesDone << endl;

					//ERASE PREVIOUSLY DRAWN TEXT AND MOVE ONTO NEXT ONE (+7 IS TO ALSO DELETE THE (BREAK) )
					message.erase(0,loc+1);
					next = false;
				}
		}
		//IF ONLY ONE BOX LEFT, OR ONE BOX TO BEGIN WITH
		else
		{
			text.setString(message);
			window.draw(text);

			//IF PLAYER CLICKS "R", NEXT IS SET TO TRUE
			if (next)
			{
				message = messageLine;
				boxesDone = numOfBoxes;
				next = false;
				redrawChat(false);
			}

		}
		//DRAW TEXT
		window.draw(textSpaceMessage);
	}
}

void ChatBox::displayConstantMessage(sf::RenderWindow &window)
{
	//DRAW BLACK BOX WITH WHITE OUTLINE UDNER CHATBOX TEXT
	window.draw(textBox);

	//IF ONLY ONE BOX LEFT, OR ONE BOX TO BEGIN WITH
	window.draw(text);
}

void ChatBox::setNext(bool choice)
{
	next = choice;
}

void ChatBox::redrawChat(bool status)
{
	redraw = status;
}

bool ChatBox::getRedraw()
{
	return redraw;
}
