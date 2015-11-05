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

	if(!music.openFromFile(""))// .ogg file this loads a compressed music file and allows it to play combat.
		std::cout << "Cant find" << std::endl;

	if(!soundBuffer.loadFromFile(""))// .wav file this allows a sound to be played such as buzzing for sword throughs or zap for magic
		std::cout << "Cant find" << std::endl;
		sound.setBuffer(soundBuffer);

	texture.loadFromFile("");// the path to the image.
	sf::Sprite sprite(texture);
	// Declare and load a texture
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(10, 10, 50, 30));
	sprite.setColor(sf::Color(255, 255, 255, 200));
	sprite.setPosition(100, 25);

	//window.draw(sprite);
	music.play();
	sound.play();
	system("pause");
	return 0;
}
};

