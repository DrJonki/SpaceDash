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

#include "Player.h"


Player::Player(void)
{
	crashDebris.clear();
	damageParticle.clear();


	flameAnim = 0;
	flameScale = 0.5;
	animSteps = 10;
	animAscend = true;

	drawCollisionShapes = false;

	playerRotation = 0;
	playerSpeed = 0;
	
	baseClimingSpeed = -7;
	baseFallingSpeed = 10.5;

	if (!playerTexture.loadFromFile("Resources/Graphics/rocket.png")){
		setExitState(true);
		MessageBox(NULL, L"Failed to load player texture!", L"Error", MB_OK);
	}
	if (!flameTexture.loadFromFile("Resources/Graphics/flame_1.png")){
		setExitState(true);
		MessageBox(NULL, L"Failed to load player flame texture!", L"Error", MB_OK);
	}
}
Player::~Player(void){}


void Player::initPlayer()
{
	crashDebris.clear();
	damageParticle.clear();


	playerRotation = 0;
	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(360.0f, 250.0f);
	playerSprite.setOrigin(playerSprite.getLocalBounds().width / 2, playerSprite.getLocalBounds().height / 2);
	playerSprite.setRotation(playerRotation);

	flameAnim = 0;
	flameScale = 0.5;
	animSteps = 10;
	animAscend = true;

	//Flames
	flameSpriteTop.setTexture(flameTexture);
	flameSpriteTop.setScale(0.5f, 0.5f);
	flameSpriteTop.setOrigin(flameSpriteTop.getLocalBounds().width, flameSpriteTop.getLocalBounds().height);
	flameSpriteTop.setPosition(-100, -100);	

	flameSpriteBottom.setTexture(flameTexture);
	flameSpriteBottom.setScale(0.5f, 0.5f);
	flameSpriteBottom.setOrigin(flameSpriteBottom.getLocalBounds().width, flameSpriteBottom.getLocalBounds().height);
	flameSpriteBottom.setPosition(-100, -100);

	collisionCircle[0].setRadius(10);
	collisionCircle[0].setFillColor(Color::Green);
	collisionCircle[0].setOrigin(collisionCircle[0].getLocalBounds().width / 2, collisionCircle[0].getLocalBounds().height / 2);
	collisionCircle[1].setRadius(5);
	collisionCircle[1].setFillColor(Color::Green);
	collisionCircle[1].setOrigin(collisionCircle[1].getLocalBounds().width / 2, collisionCircle[1].getLocalBounds().height / 2);
	collisionCircle[2].setRadius(5);
	collisionCircle[2].setFillColor(Color::Green);
	collisionCircle[2].setOrigin(collisionCircle[2].getLocalBounds().width / 2, collisionCircle[2].getLocalBounds().height / 2);

	collisionCircle[0].setPosition(playerSprite.getPosition().x + 20, playerSprite.getPosition().y + ((playerRotation / 3) + 2));
	collisionCircle[1].setPosition(playerSprite.getPosition().x - 28, playerSprite.getPosition().y - (playerRotation + 14));
	collisionCircle[2].setPosition(playerSprite.getPosition().x - 28, playerSprite.getPosition().y - (playerRotation - 14));

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
	if ((playerSprite.getPosition().y <= playerSprite.getGlobalBounds().height / 2 ) || ((playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height / 2)) >= (VideoMode::getDesktopMode().height))){
		decreaseHealth(1);

		for (int i = 0; i < 2; i++){
			crashDebrisSpeed.push_back(getRandom(-2, 2));

			crashDebris.push_back(RectangleShape());
			short ramNum = getRandom(5, 8);
			crashDebris.back().setSize(Vector2f(ramNum, ramNum));
			crashDebris.back().setOrigin(ramNum / 2, ramNum / 2);
			ramNum = getRandom(50, 160);
			crashDebris.back().setFillColor(Color::Color(ramNum, ramNum, ramNum));
			crashDebris.back().setPosition(collisionCircle[0].getPosition().x + getRandom(-5, 5), collisionCircle[0].getPosition().y + (getRandom(-5, 5)));
		}

		if (getPlayerHealth() <= 0) setCrashState(true);
	}

	//Obstacles
	for (int i=0; i<getNumberOfObstacles(); i++){
		if (playerCollision(&collisionCircle[0], &getObstacleObject(i))){
			if (getPlayerHealth() > 0) decreaseHealth(1);
			if (getPlayerHealth() <= 0) setCrashState(true);

			crashDebrisSpeed.push_back(getRandom(-2, 2));
			
			crashDebris.push_back(RectangleShape());
			short ramNum = getRandom(5, 8);
			crashDebris.back().setSize(Vector2f(ramNum, ramNum));
			crashDebris.back().setOrigin(ramNum / 2, ramNum / 2);
			ramNum = getRandom(50, 160);
			crashDebris.back().setFillColor(Color::Color(ramNum, ramNum, ramNum));
			crashDebris.back().setPosition(collisionCircle[0].getPosition().x + getRandom(-5, 5), collisionCircle[0].getPosition().y + (getRandom(-5, 5)));
		}
		if (playerCollision(&collisionCircle[1], &getObstacleObject(i))){
			if (getPlayerHealth() > 0) decreaseHealth(1);
			if (getPlayerHealth() <= 0) setCrashState(true);
			
			crashDebrisSpeed.push_back(getRandom(-2, 2));

			crashDebris.push_back(RectangleShape());
			short ramNum = getRandom(4, 7);
			crashDebris.back().setSize(Vector2f(ramNum, ramNum));
			crashDebris.back().setOrigin(ramNum / 2, ramNum / 2);
			ramNum = getRandom(50, 160);
			crashDebris.back().setFillColor(Color::Color(ramNum, ramNum, ramNum));
			crashDebris.back().setPosition(collisionCircle[1].getPosition().x + getRandom(-3, 3), collisionCircle[1].getPosition().y + (getRandom(-3, 3)));
		}
		if (playerCollision(&collisionCircle[2], &getObstacleObject(i))){
			if (getPlayerHealth() > 0) decreaseHealth(1);
			if (getPlayerHealth() <= 0) setCrashState(true);
			
			crashDebrisSpeed.push_back(getRandom(-2, 2));

			crashDebris.push_back(RectangleShape());
			short ramNum = getRandom(4, 7);
			crashDebris.back().setSize(Vector2f(ramNum, ramNum));
			crashDebris.back().setOrigin(ramNum / 2.0f, ramNum / 2.0f);
			ramNum = getRandom(50, 160);
			crashDebris.back().setFillColor(Color::Color(ramNum, ramNum, ramNum));
			crashDebris.back().setPosition(collisionCircle[2].getPosition().x + getRandom(-3, 3), collisionCircle[2].getPosition().y + (getRandom(-3, 3)));
		}
	}

	if (1){
		crashDebrisSpeed.push_back(getRandom(-2, 2));

		crashDebris.push_back(RectangleShape());
		short ramNum = getRandom(5, 8);
		crashDebris.back().setSize(Vector2f(ramNum, ramNum));
		crashDebris.back().setFillColor(Color::Color(ramNum, ramNum, ramNum, 0));
		crashDebris.back().setPosition(collisionCircle[0].getPosition().x + getRandom(-5, 5), collisionCircle[0].getPosition().y + (getRandom(-5, 5)));
	}
	/*if (1){
		damageParticle.push_back(CircleShape(1));
		short ramNum = getRandom(5, 8);
		damageParticle.back().setSize(Vector2f(ramNum, ramNum));
		damageParticle.back().setFillColor(Color::Color(ramNum, ramNum, ramNum, 0));
		damageParticle.back().setPosition(collisionCircle[0].getPosition().x + getRandom(-5, 5), collisionCircle[0].getPosition().y + (getRandom(-5, 5)));
	}*/

	//Crash debris
	for (int i = 0; i < crashDebris.size(); i++){
		crashDebris[i].move(-(getObstacleBaseSpeed() / 2), crashDebrisSpeed[i]);
		
		if (i % 2 == 0) crashDebris[i].rotate(10);
		else crashDebris[i].rotate(-10);

		if (crashDebris[i].getPosition().x < -20){
			crashDebris.erase(crashDebris.begin() + i);
			crashDebrisSpeed.erase(crashDebrisSpeed.begin() + i);
		}
	}

	//Damage particles
	if (getPlayerHealth() > 0 && getPlayerHealth() <= 75){
		
		if (1 >= getRandom(0, 10)){
			damageParticle.push_back(CircleShape());

			damageParticle.back().setRadius(1);
			damageParticle.back().setFillColor(Color::Color(255, 153, 51));
			int i = getRandom(0, 2);
			damageParticle.back().setPosition(collisionCircle[i].getPosition().x + getRandom(-3, 3), collisionCircle[i].getPosition().y + (getRandom(-3, 3)));
		}
	}
	if (getPlayerHealth() > 0 && getPlayerHealth() <= 50){
		
		if (1 >= getRandom(0, 5)){
			damageParticle.push_back(CircleShape());
			
			damageParticle.back().setRadius(1);
			damageParticle.back().setFillColor(Color::Color(255, 153, 51));
			int i = getRandom(0, 2);
			damageParticle.back().setPosition(collisionCircle[i].getPosition().x + getRandom(-3, 3), collisionCircle[i].getPosition().y + (getRandom(-3, 3)));
		}
	}
	if (getPlayerHealth() > 0 && getPlayerHealth() <= 25){
		
		if (1 >= getRandom(0, 2)){
			damageParticle.push_back(CircleShape());
			
			damageParticle.back().setRadius(1);
			damageParticle.back().setFillColor(Color::Color(255, 153, 51));
			int i = getRandom(0, 2);
			damageParticle.back().setPosition(collisionCircle[i].getPosition().x + getRandom(-3, 3), collisionCircle[i].getPosition().y + (getRandom(-3, 3)));
		}
	}

	for (int i = 0; i < damageParticle.size(); i++){
		damageParticle[i].move(-(getObstacleBaseSpeed()), 0);

		if (damageParticle[i].getPosition().x < -10){
			damageParticle.erase(damageParticle.begin() + i);
		}
	}

	//Bonus objects
	if (spriteCollision(&playerSprite, &getStarSprite())){
		addToScore(500);
		playScoreSound();
		resetStar();
	}
	if (spriteCollision(&playerSprite, &getFuelSprite())){
		increaseFuel(25);
		playFuelSound();
		resetFuelSprite();
	}
	if (spriteCollision(&playerSprite, &getHealthSprite())){
		increaseHealth(10);
		playHealSound();
		resetHealthSprite();
	}


	if (getPlayerFuel() > 0){
		if (Keyboard::isKeyPressed(Keyboard::Space)){
			if (playerRotation >= -30){
				playerRotation -= 15;
				if (playerRotation < -30) playerRotation = playerRotation - (playerRotation + 30);
				playerSprite.setRotation(playerRotation);
			}

			playerSprite.move(0, baseClimingSpeed); //Climing speed is always constant
	
			playerSpeed = -(baseFallingSpeed +3); //Set speed value so that transition from climing to falling feels smooth
		}

		else {
			if (playerRotation <= 20){
				playerRotation += 5;
				playerSprite.setRotation(playerRotation);
			}

			playerSprite.move(0, baseFallingSpeed + playerSpeed);
		
			if (playerSpeed <= 0) playerSpeed = playerSpeed + 1;
			else if ((playerSpeed <= baseFallingSpeed) && (playerSpeed > 0)) playerSpeed = playerSpeed * 1.02;
		}
	}
	else{
		if (playerRotation < 0) playerSprite.move(0, playerRotation / 6);
		else if (playerRotation > 0) playerSprite.move(0, playerRotation / 3);

		if (playerRotation < 0) playerSprite.rotate(-1);
		else if (playerRotation > 0) playerSprite.rotate(1);
	}
	

	//Flame Sprite Bottom
	flameSpriteBottom.setPosition(playerSprite.getPosition().x - (41 - -(playerRotation / 2)), playerSprite.getPosition().y - (-20 - -(playerRotation)));
	flameSpriteBottom.setRotation(playerSprite.getRotation());

	if (animAscend){
		flameScale += 0.012;
		flameSpriteBottom.setScale(flameScale, flameSpriteBottom.getScale().y);
		flameAnim++;
	}
	else if (!animAscend){
		flameScale -= 0.012;
		flameSpriteBottom.setScale(flameScale, flameSpriteBottom.getScale().y);
		flameAnim--;
	}


	//Flame Sprite Top
	flameSpriteTop.setPosition(playerSprite.getPosition().x - (40 + -(playerRotation / 12)), playerSprite.getPosition().y - (10 - -(playerRotation)));
	flameSpriteTop.setRotation(playerSprite.getRotation());

	if (animAscend){
		flameScale += 0.012;
		flameSpriteTop.setScale(flameScale, flameSpriteBottom.getScale().y);
		flameAnim++;
	}
	else if (!animAscend){
		flameScale -= 0.012;
		flameSpriteTop.setScale(flameScale, flameSpriteBottom.getScale().y);
		flameAnim--;
	}

	collisionCircle[0].setPosition(playerSprite.getPosition().x + 20, playerSprite.getPosition().y + ((playerRotation / 3) + 2));
	collisionCircle[1].setPosition(playerSprite.getPosition().x - (24 - (playerRotation / 5)), playerSprite.getPosition().y - ((playerRotation / 2) + 12));
	collisionCircle[2].setPosition(playerSprite.getPosition().x - (24 + (playerRotation / 5)), playerSprite.getPosition().y - ((playerRotation / 2) - 14));
}

void Player::updateFlamesPaused()
{
	//Flame animation logic stuff
	if (flameAnim > animSteps){
		animAscend = false;
	}
	else if (flameAnim < -animSteps){
		animAscend = true;
	}

	//Flame Sprite Bottom
	flameSpriteBottom.setPosition(playerSprite.getPosition().x - 45, playerSprite.getPosition().y + 28);
	flameSpriteBottom.setRotation(playerSprite.getRotation());

	if (animAscend){
		flameScale += 0.012;
		flameSpriteBottom.setScale(flameScale, flameSpriteBottom.getScale().y);
		flameAnim++;
	}
	else if (!animAscend){
		flameScale -= 0.012;
		flameSpriteBottom.setScale(flameScale, flameSpriteBottom.getScale().y);
		flameAnim--;
	}
	//Flame Sprite Top
	flameSpriteTop.setPosition(playerSprite.getPosition().x - 45, playerSprite.getPosition().y - 7);
	flameSpriteTop.setRotation(playerSprite.getRotation());

	if (animAscend){
		flameScale += 0.012;
		flameSpriteTop.setScale(flameScale, flameSpriteBottom.getScale().y);
		flameAnim++;
	}
	else if (!animAscend){
		flameScale -= 0.012;
		flameSpriteTop.setScale(flameScale, flameSpriteBottom.getScale().y);
		flameAnim--;
	}
}

void Player::drawPlayer(RenderWindow &window)
{
	window.draw(playerSprite);

	if (drawCollisionShapes){
		window.draw(collisionCircle[0]);
		window.draw(collisionCircle[1]);
		window.draw(collisionCircle[2]);
	}
}

void Player::drawFlames(RenderWindow &window, bool paused)
{
	if(getPlayerFuel() > 0){
		window.draw(flameSpriteTop);

		if (Keyboard::isKeyPressed(Keyboard::Space) || paused){
			window.draw(flameSpriteBottom);
		}
	}
}

void Player::drawCrashDebris(RenderWindow &window)
{
	for (int i = 0; i < crashDebris.size(); i++){
		window.draw(crashDebris[i]);
	}
}
void Player::drawDamageParticles(RenderWindow &window)
{
	for (int i = 0; i < damageParticle.size(); i++){
		window.draw(damageParticle[i]);
	}
}