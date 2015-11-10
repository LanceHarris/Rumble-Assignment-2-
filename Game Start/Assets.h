//#pragma once
//#include <iostream>
//#include "SFML/Audio.hpp"
//#include "SFML/Graphics.hpp"
//#include <Windows.h>
//#include "MMSystem.h"
//using namespace std;
//class Assets
//{
//public:
//	Assets(void);
//	~Assets(void);
//
//int main()
//{
//	sf::Texture texture;
//	sf::SoundBuffer soundBuffer;
//	sf::Sound sound;
//	sf::Music music;
//	//
//	//SOUND and Textures//
//	//spond and textures need to be loaded from the same location as the cpp file//
//
//	if(!music.openFromFile("DST-Orchards.ogg"))// .ogg file this loads a compressed music file and allows it to play combat.
//		std::cout << "Cant find" << std::endl;
//
//	if(!soundBuffer.loadFromFile(""))// .wav file this allows a sound to be played such as buzzing for sword throughs or zap for magic
//		std::cout << "Cant find" << std::endl;
//		sound.setBuffer(soundBuffer);
///*========================================================
//					Textures 
//=======================================================*/
//	texture.loadFromFile("barrel.png");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//
//	texture.loadFromFile("characterSheet.png");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//
//	texture.loadFromFile("characterSheetCustom.png");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//
//	texture.loadFromFile("door.png");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//
//	texture.loadFromFile("fennecGoalOldMan.png");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//
//	texture.loadFromFile("goatFennecOldMan.png");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//
//	texture.loadFromFile("dungeonMap.jpg");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//
//	texture.loadFromFile("itemFrontWall.jpg");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//
//	texture.loadFromFile("itemStoreOwner.png");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//
//	texture.loadFromFile("itemStoreOwnerBlink.png");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//
//	texture.loadFromFile("ligthningTest.png");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//
//	texture.loadFromFile("pillarTop.jpg");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//
//	texture.loadFromFile("pillarBottom.png");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//
//	texture.loadFromFile("RumbleLogo.png");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//	
//	texture.loadFromFile("shopMap.jpg");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//
//	texture.loadFromFile("shopOverlay.png");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//
//	texture.loadFromFile("spinning_coin_gold.png");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//	
//	texture.loadFromFile("statsFrontWall.jpg");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//	
//	texture.loadFromFile("storeBackground.jpg");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//	
//	texture.loadFromFile("title2,jpg");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//	
//	texture.loadFromFile("VitamenStorOwner.png");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//	
//	texture.loadFromFile("VitamenStorOwnerBlink.png");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//	
//	texture.loadFromFile("wallFront.jpg");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//		
//	texture.loadFromFile("wallFrontTourchOff.jpg");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//		
//	texture.loadFromFile("warriorSelect.png");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//		
//	texture.loadFromFile("wizardSelect.png");// the path to the image.
//	sf::Sprite sprite(texture);
//	// Declare and load a texture
//	sprite.setTexture(texture);
//	sprite.setPosition(100, 25);
//
///////////////////////////////////////////////////////////////////////
//	//window.draw(sprite);
//	music.play();
//	sound.play();
//	system("pause");
//	return 0;
//}
//};
//
