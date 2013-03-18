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


#include <Windows.h>

#include "OtherObjects.h"

#include <SFML/Graphics.hpp>
using namespace sf;


OtherObjects::OtherObjects(void)
{
	obstacleBaseSpeed = 8;
	obstacleScaleMin = 0.3;
	obstacleScaleMax = 0.4;

	if (!backgroundTexture.loadFromFile("Resources/Graphics/background_2.png")){
		setExitState(true);
		MessageBox(NULL, L"Failed to load background texture!", L"Error", MB_OK );
	}

	if (!debrisTextureTop.loadFromFile("Resources/Graphics/debrisfield_top.png")){
		setExitState(true);
		MessageBox(NULL, L"Failed to load the top debris texture!", L"Error", MB_OK );
	}

	if (!debrisTextureBottom.loadFromFile("Resources/Graphics/debrisfield_bottom.png")){
		setExitState(true);
		MessageBox(NULL, L"Failed to load the bottom debris texture!", L"Error", MB_OK );
	}

	if (!starTexture.loadFromFile("Resources/Graphics/star.png")){
		setExitState(true);
		MessageBox(NULL, L"Failed to load star object texture!", L"Error", MB_OK );
	}

	if (!obstacleTexture.loadFromFile("Resources/Graphics/debris_0.png")){
		setExitState(true);
		MessageBox(NULL, L"Failed to load obstacle texture!", L"Error", MB_OK );
	}
}
OtherObjects::~OtherObjects(void){}


void OtherObjects::initBackground()
{
	backgroundSprite[0].setTexture(backgroundTexture);
	backgroundSprite[0].setPosition(0, 0);

	backgroundSprite[1].setTexture(backgroundTexture);
	backgroundSprite[1].setPosition(backgroundSprite[0].getGlobalBounds().width, 0);
}

void OtherObjects::updateBackground()
{
	for (int i=0; i<2; i++){
		backgroundSprite[i].move(-1, 0);
		
		if (backgroundSprite[i].getPosition().x <= -(backgroundSprite[i].getGlobalBounds().width)){
			if (i == 0){
				backgroundSprite[0].setPosition(backgroundSprite[1].getGlobalBounds().width, 0);
			}

			else if (i == 1){
				backgroundSprite[1].setPosition(backgroundSprite[0].getGlobalBounds().width, 0);
			}
		}
	}
}


void OtherObjects::initBorders()
{
	debrisSprite[0].setTexture(debrisTextureTop);
	debrisSprite[0].setPosition(0, 0);

	debrisSprite[1].setTexture(debrisTextureTop);
	debrisSprite[1].setPosition(debrisSprite[0].getGlobalBounds().width, 0);


	debrisSprite[2].setTexture(debrisTextureBottom);
	debrisSprite[2].setPosition(0, VideoMode::getDesktopMode().height - 40);

	debrisSprite[3].setTexture(debrisTextureBottom);
	debrisSprite[3].setPosition(debrisSprite[2].getGlobalBounds().width, VideoMode::getDesktopMode().height - 40);
}

void OtherObjects::updateBorders()
{
	for (int i=0; i<2; i++){
		debrisSprite[i].move(-(obstacleBaseSpeed/4), 0);

		if (debrisSprite[i].getPosition().x <= -(debrisSprite[i].getGlobalBounds().width)){
			if (i == 0){
				debrisSprite[0].setPosition(debrisSprite[1].getGlobalBounds().width, 0);
			}

			else if (i == 1){
				debrisSprite[1].setPosition(debrisSprite[0].getGlobalBounds().width, 0);
			}
		}
	}

	for (int i=2; i<4; i++){
		debrisSprite[i].move(-(obstacleBaseSpeed/4), 0);

		if (debrisSprite[i].getPosition().x <= -(debrisSprite[i].getLocalBounds().width)){
			if (i == 2){
				debrisSprite[2].setPosition(debrisSprite[3].getLocalBounds().width, VideoMode::getDesktopMode().height - 40);
			}

			else if (i == 3){
				debrisSprite[3].setPosition(debrisSprite[2].getLocalBounds().width, VideoMode::getDesktopMode().height - 40);
			}
		}
	}
}


void OtherObjects::initObstacleObjects()
{
	//Init obstacle objects
	for (int i=0; i<numberOfObstacles; i++){
		obstacle[i].setTexture(obstacleTexture);
		obstacle[i].setOrigin(obstacle[i].getGlobalBounds().width / 2, obstacle[i].getGlobalBounds().height / 2);

		float ramNum = getRandom(obstacleScaleMin, obstacleScaleMax);
		obstacle[i].setScale(ramNum, ramNum);
		obstacle[i].setPosition(getRandom((VideoMode::getDesktopMode().width + 300), (VideoMode::getDesktopMode().width + 2500)), getRandom(100, 1100));
		obstacle[i].setRotation(0);
	}
}


void OtherObjects::updateObstacles()
{	
	//Obstacle movement
	for (int i=0; i<numberOfObstacles; i++){
		obstacle[i].move(-obstacleBaseSpeed, 0);
		obstacle[i].rotate(1);
		
		if (obstacle[i].getPosition().x < -100){
			float ramNum = getRandom(obstacleScaleMin, obstacleScaleMax);
			obstacle[i].setScale(ramNum, ramNum);
			obstacle[i].setPosition(getRandom((VideoMode::getDesktopMode().width + 300), (VideoMode::getDesktopMode().width + 2500)), getRandom(100, 1000));
		}
	}
}

void OtherObjects::initBonusObjects()
{
	starSprite.setTexture(starTexture);
	starSprite.setPosition(getRandom((VideoMode::getDesktopMode().width + 100),(VideoMode::getDesktopMode().width + 2500)),getRandom(100, VideoMode::getDesktopMode().height - 100));
}

void OtherObjects::updateBonusObjects()
{
	starSprite.move(-obstacleBaseSpeed, 0);
	if (starSprite.getPosition().x <= -50) starSprite.setPosition(getRandom((VideoMode::getDesktopMode().width + 100),(VideoMode::getDesktopMode().width + 2500)),getRandom(100, VideoMode::getDesktopMode().height - 100));
}

void OtherObjects::resetStar()
{
	starSprite.setPosition(getRandom((VideoMode::getDesktopMode().width + 100),(VideoMode::getDesktopMode().width + 2500)),getRandom(100, VideoMode::getDesktopMode().height - 100));
}


void OtherObjects::drawBackground(RenderWindow* window) 
{
	for (int i=0; i<2; i++){
		window->draw(backgroundSprite[i]);
	}
}

void OtherObjects::drawObstacles(RenderWindow* window)
{
	for (int i=0; i<numberOfObstacles; i++){
		if (obstacle[i].getPosition().x < VideoMode::getDesktopMode().width + 300){
			window->draw(obstacle[i]);
		}
	}
}

void OtherObjects::drawBorders(RenderWindow* window)
{
	for (int i=0; i<2; i++){
		window->draw(debrisSprite[i]);
	}
	for (int i=2; i<4; i++){
		window->draw(debrisSprite[i]);
	}
}

void OtherObjects::drawBonusObjects(RenderWindow* window)
{
	if (starSprite.getPosition().x < VideoMode::getDesktopMode().width + 300){
		window->draw(starSprite);
	}	
}


int OtherObjects::getNumberOfObstacles()
{
	return numberOfObstacles;
}
Sprite OtherObjects::getObstacleObject(int count)
{
	return obstacle[count];
}

Sprite OtherObjects::getStarSprite()
{
	return starSprite;
}