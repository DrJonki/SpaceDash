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

#include "Obstacle.h"

#include <Windows.h>
#include <SFML/Graphics.hpp>
using namespace sf;

//namespace sd
//{
	class OtherObjects : public Obstacle
	{
	public:

		OtherObjects(void);
		~OtherObjects(void);

		//Background
		void initBackground();
		void updateBackground();
		void drawBackground(RenderWindow &window);

		//Borders
		void initBorders();
		void updateBorders();
		void drawBorders(RenderWindow &window);

		//Bonus objects
		void initBonusObjects();
		void updateBonusObjects();
		void drawBonusObjects(RenderWindow &window);

		void initRedHue();
		void updateRedHue();
		void drawRedHue(RenderWindow &window);

		void initMeters();
		void updateMeters();
		void drawMeters(RenderWindow &window);

		//Star
		void resetStar();
		Sprite getStarSprite();
		void resetFuelSprite();
		Sprite getFuelSprite();
		void resetHealthSprite();
		Sprite getHealthSprite();

	private:
		//Resoures
		static const int numberOfStars = 300;
		RectangleShape backgroundStar[numberOfStars];
		int starSpeed[numberOfStars];

		Texture debrisTextureTop;
		Texture debrisTextureBottom;
		Texture starTexture;
		Texture redHueTexture;

		Sprite redHueSprite[4];

		Texture healthIconTexture;
		Texture fuelIconTexture;
		Sprite healthIconSprite[2];
		Sprite fuelIconSprite[2];
		RectangleShape healthMeter;
		RectangleShape fuelMeter;

		Sprite debrisSprite[4];

		Sprite starSprite;
	};
//}


#endif