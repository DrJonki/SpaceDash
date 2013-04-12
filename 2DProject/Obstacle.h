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

#ifndef OBSTACLE
#define OBSTACLE

#include "MenuClass.h"

class Obstacle : public MenuClass
{
public:
	Obstacle();
	~Obstacle();

	void initObstacles();
	void updateObstacles();
	void drawObstacles(RenderWindow &window);

	int getNumberOfObstacles();
	double getObstacleBaseSpeed();
	CircleShape getObstacleObject(int count);

private:
	sf::Texture obstacleTexture;
	
	int numberOfObstacles;
	std::vector<CircleShape> obstacle;
	std::vector<Vector2f> obstacleSpeedMod;
	const float obstacleRadiusMin;
	const float obstacleRadiusMax;

	const double obstacleBaseSpeed;
};

#endif

