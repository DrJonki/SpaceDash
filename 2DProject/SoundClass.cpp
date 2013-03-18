#include <ctime>

#include "SoundClass.h"

#include <SFML/Audio.hpp>


SoundClass::SoundClass(void)
{
	srand(time(NULL));
}
SoundClass::~SoundClass(void){}


void SoundClass::updateMusic()
{
	if (music.getStatus() == sf::Music::Stopped){
		int number = 1 + (int)rand()/((int)RAND_MAX/(7-(1)));

		switch (number){
			case 1:
				music.openFromFile("Resources/Audio/Music1.wav");
				break;
			case 2:
				music.openFromFile("Resources/Audio/Music2.wav");
				break;
			case 3:
				music.openFromFile("Resources/Audio/Music3.wav");
				break;
			case 4:
				music.openFromFile("Resources/Audio/Music4.wav");
				break;
			case 5:
				music.openFromFile("Resources/Audio/Music5.wav");
				break;
			case 6:
				music.openFromFile("Resources/Audio/Music6.wav");
				break;
			case 7:
				music.openFromFile("Resources/Audio/Music7.wav");
				break;
			default:
				music.openFromFile("Resources/Audio/Music7.wav");
				break;
		}
		music.play();
	}
}

void SoundClass::stopMusic()
{
	music.stop();
}
