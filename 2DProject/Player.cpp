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


Player::Player()
	: baseClimingSpeed(-7),
	  baseFallingSpeed(10.5)
{
	crashDebris.clear();
	crashDebrisSpeed.clear();
	damageParticle.clear();
	damageParticleSpeed.clear();
	crashDebris2.clear();
	crashDebrisSpeed2.clear();
	damageParticle2.clear();
	damageParticleSpeed2.clear();

	flameAnim = 0;
	flameScale = 0.5;
	animSteps = 10;
	animAscend = true;

	drawCollisionShapes = false;

	playerRotation = 0;
	playerSpeed = 0;
	

	if (!playerTexture.loadFromFile("Resources/Graphics/rocket.png")){
		setExitState(true);
		MessageBox(NULL, L"Failed to load player texture!", L"Error", MB_OK);
	}
	if (!flameTexture.loadFromFile("Resources/Graphics/flame_1.png")){
		setExitState(true);
		MessageBox(NULL, L"Failed to load player flame texture!", L"Error", MB_OK);
	}
}
Player::~Player(){}


void Player::initPlayer()
{
	playedShutdownSound = false;
	initExplosion = true;

	stopExplosionSound();

	crashDebris.clear();
	crashDebrisSpeed.clear();
	damageParticle.clear();
	damageParticleSpeed.clear();
	crashDebris2.clear();
	crashDebrisSpeed2.clear();
	damageParticle2.clear();
	damageParticleSpeed2.clear();

	setExplosionState(false);
	explosionSpeedCounter = 0.01;

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
	if (!getExplosionState()){
		if (playerSprite.getPosition().y <= (playerSprite.getGlobalBounds().height / 2) || playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height / 2) >= VideoMode::getDesktopMode().height){

			for (int i = 0; i < 2; i++){
				decreaseHealth(difficulty);
				if (getPlayerHealth() < 0){
					short num = -(getPlayerHealth());
					increaseHealth(num);
				}

				if (hardcore) setExplosionState(true);

				updateCrashSound();

				if (showParticles){
					crashDebrisSpeed.push_back(Vector2f(-(getObstacleBaseSpeed() / 2), getRandom(-2, 2)));
	
					crashDebris.push_back(RectangleShape());
					short ramNum = getRandom(5, 8);
					crashDebris.back().setSize(Vector2f(ramNum, ramNum));
					crashDebris.back().setOrigin(ramNum / 2, ramNum / 2);
					ramNum = getRandom(50, 160);
					crashDebris.back().setFillColor(Color::Color(ramNum, ramNum, ramNum));
					crashDebris.back().setPosition(collisionCircle[0].getPosition().x + getRandom(-5, 5), collisionCircle[0].getPosition().y + getRandom(-5, 5));
				}	
			}
		}

		//Obstacles
		for (int i=0; i<getNumberOfObstacles(); i++){
			if (playerCollision(&collisionCircle[0], &getObstacleObject(i))){
				if (getPlayerHealth() > 0) decreaseHealth(difficulty);
				if (getPlayerHealth() < 0){
					short num = -(getPlayerHealth());
					increaseHealth(num);
				}

				if (hardcore) setExplosionState(true);

				updateCrashSound();
	
				if (showParticles){
					crashDebrisSpeed.push_back(Vector2f(-(getObstacleBaseSpeed() / 2), getRandom(-2, 2)));
			
					crashDebris.push_back(RectangleShape());
					short ramNum = getRandom(5, 8);
					crashDebris.back().setSize(Vector2f(ramNum, ramNum));
					crashDebris.back().setOrigin(ramNum / 2, ramNum / 2);
					ramNum = getRandom(50, 160);
					crashDebris.back().setFillColor(Color::Color(ramNum, ramNum, ramNum));
					crashDebris.back().setPosition(collisionCircle[0].getPosition().x + getRandom(-5, 5), collisionCircle[0].getPosition().y + (getRandom(-5, 5)));
				}
			}

			if (playerCollision(&collisionCircle[1], &getObstacleObject(i))){
				if (getPlayerHealth() > 0) decreaseHealth(difficulty);
				if (getPlayerHealth() < 0){
					short num = -(getPlayerHealth());
					increaseHealth(num);
				}

				if (hardcore) setExplosionState(true);

				updateCrashSound();
			
				if (showParticles){
					crashDebrisSpeed.push_back(Vector2f(-(getObstacleBaseSpeed() / 2), getRandom(-2, 2)));

					crashDebris.push_back(RectangleShape());
					short ramNum = getRandom(4, 7);
					crashDebris.back().setSize(Vector2f(ramNum, ramNum));
					crashDebris.back().setOrigin(ramNum / 2, ramNum / 2);
					ramNum = getRandom(50, 160);
					crashDebris.back().setFillColor(Color::Color(ramNum, ramNum, ramNum));
					crashDebris.back().setPosition(collisionCircle[1].getPosition().x + getRandom(-3, 3), collisionCircle[1].getPosition().y + (getRandom(-3, 3)));
				}
			}

			if (playerCollision(&collisionCircle[2], &getObstacleObject(i))){
				if (getPlayerHealth() > 0) decreaseHealth(difficulty);
				if (getPlayerHealth() < 0){
					short num = -(getPlayerHealth());
					increaseHealth(num);
				}

				if (hardcore) setExplosionState(true);

				updateCrashSound();
			
				if (showParticles){
					crashDebrisSpeed.push_back(Vector2f(-(getObstacleBaseSpeed() / 2), getRandom(-2, 2)));

					crashDebris.push_back(RectangleShape());
					short ramNum = getRandom(4, 7);
					crashDebris.back().setSize(Vector2f(ramNum, ramNum));
					crashDebris.back().setOrigin(ramNum / 2.0f, ramNum / 2.0f);
					ramNum = getRandom(50, 160);
					crashDebris.back().setFillColor(Color::Color(ramNum, ramNum, ramNum));
					crashDebris.back().setPosition(collisionCircle[2].getPosition().x + getRandom(-3, 3), collisionCircle[2].getPosition().y + (getRandom(-3, 3)));
				}
			}
		}
	}

	//Explosion
	if (getPlayerHealth() <= 0 || getExplosionState()){
		setExplosionState(true);
		decreaseFuel(getPlayerFuel());
		updateExplosionText();
		stopRocketSound();
		stopAlarmSound();
		stopCrashSound();

		if (initExplosion){
			for (int i = 0; i < 200; i++){
				crashDebrisSpeed2.push_back(Vector2f(getRandom(-2, 2), getRandom(-2, 2)));

				crashDebris2.push_back(RectangleShape());
				short ramNum = getRandom(4, 7);
				crashDebris2.back().setSize(Vector2f(ramNum, ramNum));
				crashDebris2.back().setOrigin(ramNum / 2.0f, ramNum / 2.0f);
				ramNum = getRandom(50, 160);
				crashDebris2.back().setFillColor(Color::Color(ramNum, ramNum, ramNum));
				crashDebris2.back().setPosition(collisionCircle[0].getPosition().x + getRandom(-3, 3), collisionCircle[0].getPosition().y + (getRandom(-3, 3)));


				damageParticleSpeed2.push_back(Vector2f(getRandom(-3, 3), getRandom(-3, 3)));

				damageParticle2.push_back(CircleShape());
				damageParticle2.back().setRadius(getRandom(1, 2));
				damageParticle2.back().setFillColor(Color::Color(255, 153, 51));
				int j = getRandom(0, 2);
				damageParticle2.back().setPosition(collisionCircle[0].getPosition().x + getRandom(-3, 3), collisionCircle[0].getPosition().y + (getRandom(-3, 3)));
			}

			playExplosionSound();
		}

		for (int i = 0; i < crashDebris2.size(); i++){
			crashDebris2[i].move(crashDebrisSpeed2[i].x - explosionSpeedCounter, crashDebrisSpeed2[i].y);
			if (i % 2 == 0){
				crashDebris2[i].rotate(2);
			}
			else crashDebris2[i].rotate(-2);

			crashDebrisSpeed2[i].x = crashDebrisSpeed2[i].x * 0.985;
			crashDebrisSpeed2[i].y = crashDebrisSpeed2[i].y * 0.985;

			if (crashDebris2[i].getPosition().x < -10){
				crashDebris2.erase(crashDebris2.begin() + i);
				crashDebrisSpeed2.erase(crashDebrisSpeed2.begin() + i);
			}
		}
		for (int i = 0; i < damageParticleSpeed2.size(); i++){
			damageParticle2[i].move(damageParticleSpeed2[i].x - explosionSpeedCounter, damageParticleSpeed2[i].y);

			damageParticleSpeed2[i].x = damageParticleSpeed2[i].x * 0.985;
			damageParticleSpeed2[i].y = damageParticleSpeed2[i].y * 0.985;

			if (damageParticle2[i].getPosition().x < -10){
				damageParticle2.erase(damageParticle2.begin() + i);
				damageParticleSpeed2.erase(damageParticleSpeed2.begin() + i);
			}

		}

		if (explosionSpeedCounter <= 10.0){
			explosionSpeedCounter *= 1.03;
		}

		initExplosion = false;

		if (Keyboard::isKeyPressed(Keyboard::R)){
			setCrashState(true);
			setExplosionState(false);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Escape)) setExitState(true);
	}


	//Updates
	//Crash debris
	if (showParticles){
		for (int i = 0; i < crashDebris.size(); i++){
			crashDebris[i].move(crashDebrisSpeed[i].x, crashDebrisSpeed[i].y);
		
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
				damageParticleSpeed.push_back(Vector2f(-(getObstacleBaseSpeed()), 0));

				damageParticle.push_back(CircleShape());

				damageParticle.back().setRadius(1);
				damageParticle.back().setFillColor(Color::Color(255, 153, 51));
				int i = getRandom(0, 2);
				damageParticle.back().setPosition(collisionCircle[i].getPosition().x + getRandom(-3, 3), collisionCircle[i].getPosition().y + (getRandom(-3, 3)));
			}
		}
		if (getPlayerHealth() > 0 && getPlayerHealth() <= 50){
		
			if (1 >= getRandom(0, 5)){
				damageParticleSpeed.push_back(Vector2f(-(getObstacleBaseSpeed()), 0));

				damageParticle.push_back(CircleShape());
			
				damageParticle.back().setRadius(1);
				damageParticle.back().setFillColor(Color::Color(255, 153, 51));
				int i = getRandom(0, 2);
				damageParticle.back().setPosition(collisionCircle[i].getPosition().x + getRandom(-3, 3), collisionCircle[i].getPosition().y + (getRandom(-3, 3)));
			}
		}
		if (getPlayerHealth() > 0 && getPlayerHealth() <= 25){
		
			if (1 >= getRandom(0, 2)){
				damageParticleSpeed.push_back(Vector2f(-(getObstacleBaseSpeed()), 0));

				damageParticle.push_back(CircleShape());
			
				damageParticle.back().setRadius(1);
				damageParticle.back().setFillColor(Color::Color(255, 153, 51));
				int i = getRandom(0, 2);
				damageParticle.back().setPosition(collisionCircle[i].getPosition().x + getRandom(-3, 3), collisionCircle[i].getPosition().y + (getRandom(-3, 3)));
			}

			if (1 >= getRandom(0, 50)){

			}
		}

		for (int i = 0; i < damageParticle.size(); i++){
			damageParticle[i].move(damageParticleSpeed[i].x, damageParticleSpeed[i].y);

			if (damageParticle[i].getPosition().x < -10){
				damageParticle.erase(damageParticle.begin() + i);
				damageParticleSpeed.erase(damageParticleSpeed.begin() + i);
			}
		}
	}

	if (getPlayerFuel() > 0 && getPlayerHealth() > 0){
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

		if (getPlayerHealth() > 0) updateRocketSound();
	}
	else if (getPlayerFuel() <= 0){
		if (!playedShutdownSound){
			playShutdownSound();
			playedShutdownSound = true;
		}

		stopRocketSound();

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

void Player::bonusCollisionCheck()
{
	if (!getExplosionState()){
		//Bonus objects
		if (spriteCollision(&playerSprite, &getStarSprite())){
			addToScore((500 * difficulty) * (hardcore + 1));
			resetAdditionText(((500 * difficulty) * (hardcore + 1)) / 10, 0);
			playScoreSound();
			resetStar();
		}	
		if (spriteCollision(&playerSprite, &getFuelSprite())){
			increaseFuel(25);
			resetAdditionText(25, 2);
			playFuelSound();
			resetFuelSprite();
			playedShutdownSound = false;
		}
		if (spriteCollision(&playerSprite, &getHealthSprite())){
			increaseHealth(10);
			resetAdditionText(10, 1);
			playHealSound();
			resetHealthSprite();
		}
	}
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
	if (showParticles){
		for (int i = 0; i < crashDebris.size(); i++){
			window.draw(crashDebris[i]);
		}
		for (int i = 0; i < crashDebris2.size(); i++){
			window.draw(crashDebris2[i]);
		}
	}
}
void Player::drawDamageParticles(RenderWindow &window)
{
	if (showParticles){
		for (int i = 0; i < damageParticle.size(); i++){
			window.draw(damageParticle[i]);
		}
		for (int i = 0; i < damageParticle2.size(); i++){
			window.draw(damageParticle2[i]);
		}
	}
}