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


#ifndef PLAYER
#define PLAYER

#include "OtherObjects.h"

#include <Windows.h>
#include <SFML/Graphics.hpp>
using namespace sf;

//namespace sd
//{
	class Player : public OtherObjects
	{
	public:
		Player(void);
		~Player(void);

		//Player
		void initPlayer();
		void updatePlayer();
		void drawPlayer(sf::RenderWindow* window);

		//Flames
		void drawFlames(sf::RenderWindow* window); 

	private:
		sf::Texture playerTexture;
		sf::Sprite playerSprite;

		CircleShape collisionCircle[3];

		sf::Texture flameTexture;
		sf::Sprite flameSpriteTop;
		sf::Sprite flameSpriteBottom;
	
		double playerRotation;
		double playerSpeed;

		double baseClimingSpeed;
		double baseFallingSpeed;

		int flameAnim;
		float flameScale;
		int animSteps;
		bool animAscend;

		bool drawCollisionShapes;
	};
//}

#endif