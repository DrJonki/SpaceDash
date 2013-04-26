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


Obstacle::Obstacle()
	: obstacleBaseSpeed(8),
	  obstacleRadiusMin(25),
	  obstacleRadiusMax(50)
{
	if (!obstacleTexture.loadFromFile("Resources/Graphics/debris_0.png")){
		setExitState(true);
		MessageBox(NULL, L"Failed to load obstacle texture!", L"Error", MB_OK );
	}
}
Obstacle::~Obstacle(){}

void Obstacle::initObstacles()
{
	obstacle.clear();
	obstacleSpeedMod.clear();

	numberOfObstacles = 35 + (difficulty * 15);

	for (int i = 0; i < numberOfObstacles; i++){
		obstacle.push_back(CircleShape());
		obstacleSpeedMod.push_back(Vector2f(getRandom(-3.0f, 3.0f), getRandom(-0.6f, 0.6f)));
	}

	//Init obstacle objects
	for (int i=0; i<numberOfObstacles; i++){

		float ramNum = getRandom(obstacleRadiusMin, obstacleRadiusMax);
		obstacle[i].setRadius(ramNum);
		obstacle[i].setOrigin(ramNum, ramNum);
		obstacle[i].setPosition(getRandom((VideoMode::getDesktopMode().width + 300), (VideoMode::getDesktopMode().width + 3000)), getRandom(100, 1200));
		obstacle[i].setRotation(0);
		obstacle[i].setTexture(&obstacleTexture);
	}
}

void Obstacle::updateObstacles()
{	
	//Obstacle movement
	for (int i=0; i<numberOfObstacles; i++){
		obstacle[i].move(-(obstacleBaseSpeed + obstacleSpeedMod[i].x), obstacleSpeedMod[i].y);
		
		if (i % 2 == 0) obstacle[i].rotate(1);
		else obstacle[i].rotate(-1);
		
		if (obstacle[i].getPosition().x < -100 || obstacle[i].getPosition().y < -100 || obstacle[i].getPosition().y > 1300){
			float ramNum = getRandom(obstacleRadiusMin, obstacleRadiusMax);
			obstacle[i].setRadius(ramNum);
			obstacle[i].setOrigin(ramNum, ramNum);
			obstacle[i].setPosition(getRandom((VideoMode::getDesktopMode().width + 300), (VideoMode::getDesktopMode().width + 3000)), getRandom(100, 1200));
			obstacle[i].setRotation(0);
		}
	}
}

void Obstacle::drawObstacles(RenderWindow &window)
{
	for (int i=0; i<numberOfObstacles; i++){
		if (obstacle[i].getPosition().x < VideoMode::getDesktopMode().width + 300){
			window.draw(obstacle[i]);
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