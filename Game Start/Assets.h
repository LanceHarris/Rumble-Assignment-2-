#pragma once
#include <iostream>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include <Windows.h>
#include "MMSystem.h"
using namespace std;
class Assets
{
public:
	Assets(void);
	~Assets(void);

int main()
{
	sf::Texture texture;
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
	sf::Music music;
	//
	//SOUND and Textures//
	//spond and textures need to be loaded from the same location as the cpp file//

	if(!music.openFromFile("DST-Orchards.ogg"))// .ogg file this loads a compressed music file and allows it to play combat.
		std::cout << "Cant find" << std::endl;

	if(!soundBuffer.loadFromFile(""))// .wav file this allows a sound to be played such as buzzing for sword throughs or zap for magic
		std::cout << "Cant find" << std::endl;
		sound.setBuffer(soundBuffer);
/*========================================================
					Textures 
=======================================================*/
	texture.loadFromFile("barrel.png");// the path to the image.
	sf::Sprite barrel(texture);
	// Declare and load a texture
	barrel.setTexture(texture);
	barrel.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////

	texture.loadFromFile("characterSheet.png");// the path to the image.
	sf::Sprite character(texture);
	// Declare and load a texture
	character.setTexture(texture);
	character.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////

	texture.loadFromFile("characterSheetCustom.png");// the path to the image.
	sf::Sprite characterCustom(texture);
	// Declare and load a texture
	characterCustom.setTexture(texture);
	characterCustom.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////

	texture.loadFromFile("door.png");// the path to the image.
	sf::Sprite door(texture);
	// Declare and load a texture
	door.setTexture(texture);
	door.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////

	texture.loadFromFile("fennecGoalOldMan.png");// the path to the image.
	sf::Sprite fennec(texture);
	// Declare and load a texture
	fennec.setTexture(texture);
	fennec.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////

	texture.loadFromFile("goatFennecOldMan.png");// the path to the image.
	sf::Sprite goat(texture);
	// Declare and load a texture
	goat.setTexture(texture);
	goat.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////

	texture.loadFromFile("dungeonMap.jpg");// the path to the image.
	sf::Sprite dungeon(texture);
	// Declare and load a texture
	dungeon.setTexture(texture);
	dungeon.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////

	texture.loadFromFile("itemFrontWall.jpg");// the path to the image.
	sf::Sprite itemFront(texture);
	// Declare and load a texture
	itemFront.setTexture(texture);
	itemFront.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////

	texture.loadFromFile("itemStoreOwner.png");// the path to the image.
	sf::Sprite itemStore(texture);
	// Declare and load a texture
	itemStore.setTexture(texture);
	itemStore.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////

	texture.loadFromFile("itemStoreOwnerBlink.png");// the path to the image.
	sf::Sprite itemStoreB(texture);
	// Declare and load a texture
	itemStoreB.setTexture(texture);
	itemStoreB.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////

	texture.loadFromFile("ligthningTest.png");// the path to the image.
	sf::Sprite ligthning(texture);
	// Declare and load a texture
	ligthning.setTexture(texture);
	ligthning.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////

	texture.loadFromFile("pillarTop.jpg");// the path to the image.
	sf::Sprite pillar(texture);
	// Declare and load a texture
	pillar.setTexture(texture);
	pillar.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////

	texture.loadFromFile("pillarBottom.png");// the path to the image.
	sf::Sprite pillarB(texture);
	// Declare and load a texture
	pillarB.setTexture(texture);
	pillarB.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////

	texture.loadFromFile("RumbleLogo.png");// the path to the image.
	sf::Sprite RumbleLogo(texture);
	// Declare and load a texture
	RumbleLogo.setTexture(texture);
	RumbleLogo.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////
	
	texture.loadFromFile("shopMap.jpg");// the path to the image.
	sf::Sprite shopMap(texture);
	// Declare and load a texture
	shopMap.setTexture(texture);
	shopMap.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////

	texture.loadFromFile("shopOverlay.png");// the path to the image.
	sf::Sprite shopOverlay(texture);
	// Declare and load a texture
	shopOverlay.setTexture(texture);
	shopOverlay.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////

	texture.loadFromFile("spinning_coin_gold.png");// the path to the image.
	sf::Sprite spinning(texture);
	// Declare and load a texture
	spinning.setTexture(texture);
	spinning.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////
	
	texture.loadFromFile("statsFrontWall.jpg");// the path to the image.
	sf::Sprite statsFront(texture);
	// Declare and load a texture
	statsFront.setTexture(texture);
	statsFront.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////
	
	texture.loadFromFile("storeBackground.jpg");// the path to the image.
	sf::Sprite storeB(texture);
	// Declare and load a texture
	storeB.setTexture(texture);
	storeB.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////
	
	texture.loadFromFile("title2.jpg");// the path to the image.
	sf::Sprite title2(texture);
	// Declare and load a texture
	title2.setTexture(texture);
	title2.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////
	
	texture.loadFromFile("VitamenStorOwner.png");// the path to the image.
	sf::Sprite VitamenS(texture);
	// Declare and load a texture
	VitamenS.setTexture(texture);
	VitamenS.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////
	
	texture.loadFromFile("VitamenStorOwnerBlink.png");// the path to the image.
	sf::Sprite VitamenSB(texture);
	// Declare and load a texture
	VitamenSB.setTexture(texture);
	VitamenSB.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////
	
	texture.loadFromFile("wallFront.jpg");// the path to the image.
	sf::Sprite wallF(texture);
	// Declare and load a texture
	wallF.setTexture(texture);
	wallF.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////
		
	texture.loadFromFile("wallFrontTourchOff.jpg");// the path to the image.
	sf::Sprite wallFT(texture);
	// Declare and load a texture
	wallFT.setTexture(texture);
	wallFT.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////
		
	texture.loadFromFile("warriorSelect.png");// the path to the image.
	sf::Sprite warriorS(texture);
	// Declare and load a texture
	warriorS.setTexture(texture);
	warriorS.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////
		
	texture.loadFromFile("wizardSelect.png");// the path to the image.
	sf::Sprite wizardS(texture);
	// Declare and load a texture
	wizardS.setTexture(texture);
	wizardS.setPosition(100, 25);

/////////////////////////////////////////////////////////////////////
	//window.draw(sprite);
	music.play();
	sound.play();
	system("pause");
	return 0;
}
};

