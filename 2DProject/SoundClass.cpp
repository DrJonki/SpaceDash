/*
Space Dash - A student project created with SFML
    Copyright (C) 2013  Joona Tiinanen

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/.
*/

#include "SoundClass.h"


SoundClass::SoundClass(void)
{
	srand(time(NULL));

	music.setVolume(0);
	menuMusic.setVolume(0);
}
SoundClass::~SoundClass(void){}


void SoundClass::updateMusic()
{
	if (music.getVolume() < 75) music.setVolume(music.getVolume() + 0.1);

	if (music.getStatus() == sf::Music::Stopped){
		int number = 1 + (int)rand()/((int)RAND_MAX/(7-(1)));

		switch (number){
			case 1:
				music.openFromFile("Resources/Audio/music1.wav");
				break;
			case 2:
				music.openFromFile("Resources/Audio/music2.wav");
				break;
			case 3:
				music.openFromFile("Resources/Audio/music3.wav");
				break;
			case 4:
				music.openFromFile("Resources/Audio/music4.wav");
				break;
			case 5:
				music.openFromFile("Resources/Audio/music5.wav");
				break;
			case 6:
				music.openFromFile("Resources/Audio/music6.wav");
				break;
			case 7:
				music.openFromFile("Resources/Audio/music7.wav");
				break;
			case 8:
				music.openFromFile("Resources/Audio/music.wav");
				break;
			default:
				music.openFromFile("Resources/Audio/music7.wav");
				break;
		}
		music.play();
	}
}

void SoundClass::updateMenuMusic()
{
	if (menuMusic.getVolume() < 75) menuMusic.setVolume(menuMusic.getVolume() + 0.05);

	if (menuMusic.getStatus() == sf::Music::Stopped){
		menuMusic.openFromFile("Resources/Audio/menumusic.wav");
		menuMusic.play();
	}
}

void SoundClass::stopMusic()
{
	music.stop();
	music.setVolume(0);
}
void SoundClass::stopMenuMusic()
{
	menuMusic.stop();
	menuMusic.setVolume(0);
}
