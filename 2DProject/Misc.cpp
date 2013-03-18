#include <cstdlib>

#include "Misc.h"

#include <SFML/Graphics.hpp>


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



bool Misc::objectCollision(sf::RectangleShape *object1, sf::RectangleShape *object2)
{
	if (object1->getPosition().x + object1->getSize().x > object2->getPosition().x &&
		object1->getPosition().x < object2->getPosition().x + object2->getSize().x &&
		object1->getPosition().y + object1->getSize().y > object2->getPosition().y &&
		object1->getPosition().y < object2->getPosition().y + object2->getSize().y) return true;

	return false;
}

bool Misc::playerCollision(sf::Sprite *object1, sf::Sprite *object2)
{
	/*if (object1->getPosition().x + object1->getOrigin().x > object2->getPosition().x - object2->getOrigin().x										&& 
		object1->getPosition().x - object1->getOrigin().x < object2->getPosition().x + (object2->getLocalBounds().width * object2->getScale().x)	&&
		object1->getPosition().y + object1->getOrigin().y > object2->getPosition().y - object2->getOrigin().y										&&
		object1->getPosition().y - object1->getOrigin().y < object2->getPosition().y + (object2->getLocalBounds().height * object2->getScale().y)) return true;

	return false;*/

	if (object1->getPosition().x - (object1->getGlobalBounds().width / 2) > (object2->getPosition().x - object2->getGlobalBounds().width)	&&
		object1->getPosition().x + (object1->getGlobalBounds().width / 2) < (object2->getPosition().x + object2->getGlobalBounds().width)  	&&
		object1->getPosition().y - (object1->getGlobalBounds().height / 2) > (object2->getPosition().y - object2->getGlobalBounds().height)	&&
		object1->getPosition().y + (object1->getGlobalBounds().height / 2) < (object2->getPosition().y + object2->getGlobalBounds().height)) return true;

	return false;
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