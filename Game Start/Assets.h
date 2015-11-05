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

	music.play();
	sound.play();
	system("pause");
	return 0;
}
};

