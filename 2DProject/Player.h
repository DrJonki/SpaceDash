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
		void updateFlamesPaused();
		void drawPlayer(sf::RenderWindow &window);

		//Flames
		void drawFlames(sf::RenderWindow &window, bool paused); 

		void drawCrashDebris(RenderWindow &window);
		void drawDamageParticles(RenderWindow &window);

	private:
		std::vector<CircleShape> damageParticle;

		std::vector<RectangleShape> crashDebris;
		std::vector<float> crashDebrisSpeed;

		sf::Texture playerTexture;
		sf::Sprite playerSprite;

		CircleShape collisionCircle[3];

		sf::Texture flameTexture;
		sf::Sprite flameSpriteTop;
		sf::Sprite flameSpriteBottom;
	
		float playerRotation;
		float playerSpeed;

		float baseClimingSpeed;
		float baseFallingSpeed;

		int flameAnim;
		float flameScale;
		int animSteps;
		bool animAscend;

		bool drawCollisionShapes;
	};
//}

#endif