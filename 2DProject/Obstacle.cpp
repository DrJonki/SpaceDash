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

#include "Obstacle.h"


Obstacle::Obstacle(void)
{
	obstacleBaseSpeed = 8;
	obstacleRadiusMin = 25;
	obstacleRadiusMax = 50;

	if (!obstacleTexture.loadFromFile("Resources/Graphics/debris_0.png")){
		setExitState(true);
		MessageBox(NULL, L"Failed to load obstacle texture!", L"Error", MB_OK );
	}
}


Obstacle::~Obstacle(void)
{
}

void Obstacle::initObstacles()
{
	//Init obstacle objects
	for (int i=0; i<numberOfObstacles; i++){

		float ramNum = getRandom(obstacleRadiusMin, obstacleRadiusMax);
		obstacle[i].setRadius(ramNum);
		obstacle[i].setOrigin(ramNum, ramNum);
		obstacle[i].setPosition(getRandom((VideoMode::getDesktopMode().width + 300), (VideoMode::getDesktopMode().width + 2500)), getRandom(100, 1100));
		obstacle[i].setRotation(0);
		obstacle[i].setTexture(&obstacleTexture);
	}
}

void Obstacle::updateObstacles()
{	
	//Obstacle movement
	for (int i=0; i<numberOfObstacles; i++){
		obstacle[i].move(-obstacleBaseSpeed, 0);
		
		if (i % 2 == 0) obstacle[i].rotate(1);
		else obstacle[i].rotate(-1);
		
		if (obstacle[i].getPosition().x < -100){
			float ramNum = getRandom(obstacleRadiusMin, obstacleRadiusMax);
			obstacle[i].setRadius(ramNum);
			obstacle[i].setPosition(getRandom((VideoMode::getDesktopMode().width + 300), (VideoMode::getDesktopMode().width + 2500)), getRandom(100, 1000));
			obstacle[i].setRotation(0);
		}
	}
}

void Obstacle::drawObstacles(RenderWindow* window)
{
	for (int i=0; i<numberOfObstacles; i++){
		if (obstacle[i].getPosition().x < VideoMode::getDesktopMode().width + 300){
			window->draw(obstacle[i]);
		}
	}
}

double Obstacle::getObstacleBaseSpeed()
{
	return obstacleBaseSpeed;
}

int Obstacle::getNumberOfObstacles()
{
	return numberOfObstacles;
}
CircleShape Obstacle::getObstacleObject(int count)
{
	CircleShape &obstacleRef = obstacle[count];

	return obstacleRef;
}
