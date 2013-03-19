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

#include "TextClass.h"
#include "SoundClass.h"

#include <Windows.h>
#include <SFML/Graphics.hpp>
using namespace sf;

class Obstacle : public TextClass, public SoundClass
{
public:
	Obstacle(void);
	~Obstacle(void);

	void initObstacles();
	void updateObstacles();
	void drawObstacles(sf::RenderWindow* window);

	int getNumberOfObstacles();
	double getObstacleBaseSpeed();
	sf::Sprite getObstacleObject(int count);

private:
	sf::Texture obstacleTexture;
	
	static const int numberOfObstacles = 20;
	sf::Sprite obstacle[numberOfObstacles];
	float obstacleScaleMin;
	float obstacleScaleMax;

	double obstacleBaseSpeed;
};

#endif

