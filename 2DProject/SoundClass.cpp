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
