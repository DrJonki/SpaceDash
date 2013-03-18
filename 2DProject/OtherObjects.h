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


#ifndef OTHER_OBJECTS
#define OTHER_OBJECTS

#include "TextClass.h"
#include "SoundClass.h"
#include <SFML/Graphics.hpp>

//namespace sd
//{
	class OtherObjects : public TextClass, public SoundClass
	{
	public:

		OtherObjects(void);
		~OtherObjects(void);

		//Background
		void initBackground();
		void updateBackground();
		void drawBackground(sf::RenderWindow* window);

		//Borders
		void initBorders();
		void updateBorders();
		void drawBorders(sf::RenderWindow* window);

		//Obstacles
		void initObstacleObjects();
		void updateObstacles();
		void drawObstacles(sf::RenderWindow* window);
		int getNumberOfObstacles();
		sf::Sprite getObstacleObject(int count);

		//Bonus objects
		void initBonusObjects();
		void updateBonusObjects();
		void drawBonusObjects(sf::RenderWindow* window);

		//Star
		void resetStar();
		sf::Sprite getStarSprite();

	private:
		//Resoures
		sf::Texture backgroundTexture;
		sf::Texture debrisTextureTop;
		sf::Texture debrisTextureBottom;
		sf::Texture starTexture;
		sf::Texture obstacleTexture;

		sf::Sprite backgroundSprite[2];
		sf::Sprite debrisSprite[4];

		sf::Sprite starSprite;

		static const int numberOfObstacles = 20;
		sf::Sprite obstacle[numberOfObstacles];
		float obstacleScaleMin;
		float obstacleScaleMax;

	protected:
		double obstacleBaseSpeed;
	};
//}


#endif