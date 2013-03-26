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

#include "Misc.h"


Misc::Misc(void)
{
	crashState = false;
	exitState = false;
}
Misc::~Misc(void){}


void Misc::setRandomSeed(int seed)
{
	srand(seed);
}


float Misc::getRandom(float randMin, float randMax)
{
	float randomNum = randMin + (float)rand()/((float)RAND_MAX/(randMax-(randMin)));

	return randomNum;
}


bool Misc::playerCollision(sf::CircleShape *circle1, sf::CircleShape *circle2)
{
	float hypotenuse = sqrt(pow(fabs(circle2->getPosition().x - circle1->getPosition().x), 2) + (pow(fabs(circle2->getPosition().y - circle1->getPosition().y), 2)));

	if (hypotenuse < circle1->getRadius() + circle2->getRadius()) return true;

	else return false;
}

bool Misc::spriteCollision(sf::Sprite *object1, sf::Sprite *object2)
{
	if (object1->getPosition().x + (object1->getLocalBounds().width / 2) > object2->getPosition().x		&& 
		object1->getPosition().x < object2->getPosition().x + object2->getLocalBounds().width			&&
		object1->getPosition().y + (object1->getLocalBounds().height / 2) > object2->getPosition().y	&&
		object1->getPosition().y - object1->getOrigin().y < object2->getPosition().y + object2->getLocalBounds().height) return true;
	
	return false;
}


void Misc::setCrashState(bool state)
{
	crashState = state;
}

bool Misc::getCrashState()
{
	return crashState;
}

void Misc::setExitState(bool state)
{
	exitState = state;
}

bool Misc::getExitState()
{
	return exitState;
}

void Misc::readSettingsFromFile()
{
	vSync = true;

	difficulty = 1;
	hardcore = false;

	showParticles = true;

	playSound = true;
	playMusic = true;

	int count = 0;;
	std::string string;

	std::string path(std::getenv("USERPROFILE"));
	path += "/Documents/SDSettings.txt";
	std::ifstream file(path, std::ifstream::in);

	if (file.good()){
		while (!file.eof()){
			if (count == 0){ //vSync
				std::getline(file, string);
				vSync = std::atoi(string.c_str());
			}
			else if (count == 1){ //Difficulty
				std::getline(file, string);
				difficulty = std::atoi(string.c_str());
			}
			else if (count == 2){ //Hardcore
				std::getline(file, string);
				hardcore = std::atoi(string.c_str());
			}
			else if (count == 3){ //Show particles
				std::getline(file, string);
				showParticles = std::atoi(string.c_str());
			}
			else if (count == 4){ //Play sound
				std::getline(file, string);
				playSound = std::atoi(string.c_str());
			}
			else if (count == 5){ //Play music
				std::getline(file, string);
				playMusic = std::atoi(string.c_str());
			}
			count++;
		}
	}
}
void Misc::writeSettingsToFile()
{
	std::string path(std::getenv("USERPROFILE"));
	path += "/Documents/SDSettings.txt";

	std::ofstream file;
	file.open(path);
	file << vSync << std::endl;	//vSync
	file << difficulty << std::endl;	//Difficulty
	file << hardcore << std::endl;		//HardCore
	file << showParticles << std::endl; //Show particles
	file << playSound << std::endl;		//Play sound
	file << playMusic;					//Play music
	file.close();
}