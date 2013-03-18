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

#include "Player.h"
#include "OtherObjects.h"


#include <SFML/Graphics.hpp>
using namespace sf;


Player::Player(void)
{
	flameAnim = 0;
	flameScale = 0.5;
	animSteps = 10;
	animAscend = true;

	playerRotation = 0;
	playerSpeed = 0;

	topFlameCounter = 0;
	bottomFlameCounter = 0;
	
	baseClimingSpeed = -7;
	baseFallingSpeed = 10.5;

	if (!playerTexture.loadFromFile("Resources/Graphics/rocket.png")){
		setExitState(true);
		MessageBox(NULL, L"Failed to load player texture!", L"Error", MB_OK );
	}
	if (!flameTexture.loadFromFile("Resources/Graphics/flame_1.png")){
		setExitState(true);
		MessageBox(NULL, L"Failed to load player flame texture!", L"Error", MB_OK );
	}
}
Player::~Player(void){}


void Player::initPlayer()
{
	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(150, VideoMode::getDesktopMode().height/4);
	playerSprite.setOrigin(playerSprite.getGlobalBounds().width / 2, playerSprite.getGlobalBounds().height / 2);
	playerSprite.setRotation(0);

	//Flames
	flameSpriteTop.setTexture(flameTexture);
	flameSpriteTop.setScale(0.5f, 0.5f);
	flameSpriteTop.setOrigin(flameSpriteTop.getGlobalBounds().width, flameSpriteTop.getGlobalBounds().height);
	flameSpriteTop.setPosition(-100, -100);

	flameSpriteBottom.setTexture(flameTexture);
	flameSpriteBottom.setScale(0.5f, 0.5f);
	flameSpriteBottom.setOrigin(flameSpriteBottom.getGlobalBounds().width, flameSpriteBottom.getGlobalBounds().height);
	flameSpriteBottom.setPosition(-100, -100);
}

void Player::updatePlayer()
{
	//Animation logic stuff
	if (flameAnim > animSteps){
		animAscend = false;
	}
	else if (flameAnim < -animSteps){
		animAscend = true;
	}



	//Collision checks
	//Borders
	if ((playerSprite.getPosition().y <= playerSprite.getGlobalBounds().height / 2 ) || ((playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height / 2)) >= (VideoMode::getDesktopMode().height))) setCrashState(true);
	
	//Obstacles
	for (int i=0; i<getNumberOfObstacles(); i++){
		if (playerCollision(&playerSprite, &getObstacleObject(i))){
			setCrashState(true);
		}
	}

	//Bonus objects
	if (spriteCollision(&playerSprite, &getStarSprite())){
		addToScore(500);
		resetStar();
	}




	if (Keyboard::isKeyPressed(Keyboard::Space)){
		if (playerRotation > -30){
			playerRotation -= 10;
			playerSprite.setRotation(playerRotation);
		}

		playerSprite.move(0, baseClimingSpeed); //Climing speed is always constant
	
		playerSpeed = -(baseFallingSpeed +3); //Set speed value so that transition from climing to falling feels smooth
	}

	else {
		if (playerRotation < 20){
			playerRotation += 5;
			playerSprite.setRotation(playerRotation);
		}

		playerSprite.move(0, baseFallingSpeed + playerSpeed);
		
		if (playerSpeed <= 0) playerSpeed = playerSpeed + 1;
		else if ((playerSpeed <= baseFallingSpeed) && (playerSpeed > 0)) playerSpeed = playerSpeed * 1.02;
	}
	
		
	//Flame Sprite Bottom
	flameSpriteBottom.setPosition(playerSprite.getPosition().x - 80, playerSprite.getPosition().y + 20);
	flameSpriteBottom.setRotation(playerSprite.getRotation());

	if (animAscend){
		flameScale += 0.02;
		flameSpriteBottom.setScale(flameScale, flameSpriteBottom.getScale().y);
		flameAnim++;
	}
	else if (!animAscend){
		flameScale -= 0.02;
		flameSpriteBottom.setScale(flameScale, flameSpriteBottom.getScale().y);
		flameAnim--;
	}


	//Flame Sprite Top
	flameSpriteTop.setPosition(playerSprite.getPosition().x - 80, playerSprite.getPosition().y - 30);
	flameSpriteTop.setRotation(playerSprite.getRotation());

	if (animAscend){
		flameScale += 0.015;
		flameSpriteTop.setScale(flameScale, flameSpriteBottom.getScale().y);
		flameAnim++;
	}
	else if (!animAscend){
		flameScale -= 0.015;
		flameSpriteTop.setScale(flameScale, flameSpriteBottom.getScale().y);
		flameAnim--;
	}
}

void Player::drawPlayer(RenderWindow* window)
{
	window->draw(playerSprite);
}

void Player::drawFlames(RenderWindow* window)
{
	window->draw(flameSpriteTop);

	if (Keyboard::isKeyPressed(Keyboard::Space)){
		window->draw(flameSpriteBottom);
	}
}