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

#include "OtherObjects.h"


OtherObjects::OtherObjects()
{
	if (!debrisTextureTop.loadFromFile("Resources/Graphics/debrisfield_top.png")){
		setExitState(true);
		MessageBox(NULL, L"Failed to load the top debris texture!", L"Error", MB_OK );
	}

	if (!debrisTextureBottom.loadFromFile("Resources/Graphics/debrisfield_bottom.png")){
		setExitState(true);
		MessageBox(NULL, L"Failed to load the bottom debris texture!", L"Error", MB_OK );
	}

	if (!starTexture.loadFromFile("Resources/Graphics/star.png")){
		setExitState(true);
		MessageBox(NULL, L"Failed to load star object texture!", L"Error", MB_OK );
	}

	if (!healthIconTexture.loadFromFile("Resources/Graphics/healthicon.png")){
		setExitState(true);
		MessageBox(NULL, L"Failed to load health icon texture!", L"Error", MB_OK );
	}
	if (!fuelIconTexture.loadFromFile("Resources/Graphics/fuelicon.png")){
		setExitState(true);
		MessageBox(NULL, L"Failed to load fuel icon texture!", L"Error", MB_OK );
	}
}
OtherObjects::~OtherObjects(){}


void OtherObjects::initBackground()
{
	for (int i = 0; i < numberOfStars; i++){
		float ramNum = getRandom(1, 3);
		backgroundStar[i].setSize(Vector2f(ramNum, ramNum));
		backgroundStar[i].setPosition(getRandom(-1, VideoMode::getDesktopMode().width + 1), getRandom(0, VideoMode::getDesktopMode().height));

		starSpeed[i] = -(getRandom(1.0f, 5.0f));
	}
}

void OtherObjects::updateBackground()
{
	for (int i = 0; i < numberOfStars; i++){
		backgroundStar[i].move(starSpeed[i], 0);

		if (backgroundStar[i].getPosition().x < -2) backgroundStar[i].setPosition(VideoMode::getDesktopMode().width + 1, getRandom(0, VideoMode::getDesktopMode().height));
	}
}


void OtherObjects::initBorders()
{
	debrisSprite[0].setTexture(debrisTextureTop);
	debrisSprite[0].setPosition(0, 0);

	debrisSprite[1].setTexture(debrisTextureTop);
	debrisSprite[1].setPosition(debrisSprite[0].getGlobalBounds().width, 0);


	debrisSprite[2].setTexture(debrisTextureBottom);
	debrisSprite[2].setPosition(0, VideoMode::getDesktopMode().height - 40);

	debrisSprite[3].setTexture(debrisTextureBottom);
	debrisSprite[3].setPosition(debrisSprite[2].getGlobalBounds().width, VideoMode::getDesktopMode().height - 40);
}

void OtherObjects::updateBorders()
{
	for (int i=0; i<2; i++){
		debrisSprite[i].move(-(getObstacleBaseSpeed() / 1.5), 0);

		if (debrisSprite[i].getPosition().x <= -(debrisSprite[i].getGlobalBounds().width)){
			if (i == 0){
				debrisSprite[0].setPosition(debrisSprite[1].getGlobalBounds().width, 0);
			}

			else if (i == 1){
				debrisSprite[1].setPosition(debrisSprite[0].getGlobalBounds().width, 0);
			}
		}
	}

	for (int i=2; i<4; i++){
		debrisSprite[i].move(-(getObstacleBaseSpeed() / 1.5), 0);

		if (debrisSprite[i].getPosition().x <= -(debrisSprite[i].getLocalBounds().width)){
			if (i == 2){
				debrisSprite[2].setPosition(debrisSprite[3].getLocalBounds().width, VideoMode::getDesktopMode().height - 40);
			}

			else if (i == 3){
				debrisSprite[3].setPosition(debrisSprite[2].getLocalBounds().width, VideoMode::getDesktopMode().height - 40);
			}
		}
	}
}


void OtherObjects::initBonusObjects()
{
	starSprite.setTexture(starTexture);
	starSprite.setPosition(getRandom(VideoMode::getDesktopMode().width + 100, VideoMode::getDesktopMode().width + (2500 / difficulty)), getRandom(100, VideoMode::getDesktopMode().height - 100));

	fuelIconSprite[1].setTexture(fuelIconTexture);
	fuelIconSprite[1].setPosition(getRandom(VideoMode::getDesktopMode().width + 100, VideoMode::getDesktopMode().width + (6000 / difficulty)), getRandom(100, VideoMode::getDesktopMode().height - 100));

	healthIconSprite[1].setTexture(healthIconTexture);
	healthIconSprite[1].setPosition(getRandom(VideoMode::getDesktopMode().width + 100, VideoMode::getDesktopMode().width + (15000 / difficulty)), getRandom(100, VideoMode::getDesktopMode().height - 100));
}

void OtherObjects::updateBonusObjects()
{
	if (starSprite.getPosition().x <= VideoMode::getDesktopMode().width + 100 || !getExplosionState()) starSprite.move(-getObstacleBaseSpeed(), 0);
	if (starSprite.getPosition().x <= -50) starSprite.setPosition(getRandom(VideoMode::getDesktopMode().width + 100, VideoMode::getDesktopMode().width + (2500 / difficulty)), getRandom(100, VideoMode::getDesktopMode().height - 100));

	if (fuelIconSprite[1].getPosition().x <= VideoMode::getDesktopMode().width + 100 || !getExplosionState()) fuelIconSprite[1].move(-getObstacleBaseSpeed(), 0);
	if (fuelIconSprite[1].getPosition().x <= -50) fuelIconSprite[1].setPosition(getRandom(VideoMode::getDesktopMode().width + 100, VideoMode::getDesktopMode().width + (6000 / difficulty)), getRandom(100, VideoMode::getDesktopMode().height - 100));

	if (!hardcore && (healthIconSprite[1].getPosition().x <= VideoMode::getDesktopMode().width + 100 || !getExplosionState())) healthIconSprite[1].move(-getObstacleBaseSpeed(), 0);
	if (healthIconSprite[1].getPosition().x <= -50) healthIconSprite[1].setPosition(getRandom(VideoMode::getDesktopMode().width + 100, VideoMode::getDesktopMode().width + (15000 / difficulty)), getRandom(100, VideoMode::getDesktopMode().height - 100));
}

void OtherObjects::resetStar()
{
	starSprite.setPosition(getRandom(VideoMode::getDesktopMode().width + 100, VideoMode::getDesktopMode().width + (2500 / difficulty)), getRandom(100, VideoMode::getDesktopMode().height - 100));
}
void OtherObjects::resetFuelSprite()
{
	fuelIconSprite[1].setPosition(getRandom(VideoMode::getDesktopMode().width + 100, VideoMode::getDesktopMode().width + (6000 / difficulty)), getRandom(100, VideoMode::getDesktopMode().height - 100));
}
void OtherObjects::resetHealthSprite()
{
	healthIconSprite[1].setPosition(getRandom(VideoMode::getDesktopMode().width + 100, VideoMode::getDesktopMode().width + (15000 / difficulty)), getRandom(100, VideoMode::getDesktopMode().height - 100));
}


void OtherObjects::drawBackground(RenderWindow &window) 
{
	for (int i=0; i<numberOfStars; i++){
		window.draw(backgroundStar[i]);
	}
}

void OtherObjects::drawBorders(RenderWindow &window)
{
	for (int i=0; i<2; i++){
		window.draw(debrisSprite[i]);
	}
	for (int i=2; i<4; i++){
		window.draw(debrisSprite[i]);
	}
}

void OtherObjects::drawBonusObjects(RenderWindow &window)
{
	if (starSprite.getPosition().x < VideoMode::getDesktopMode().width + 300){
		window.draw(starSprite);
	}

	window.draw(fuelIconSprite[1]);
	if (!hardcore) window.draw(healthIconSprite[1]);
}


Sprite OtherObjects::getStarSprite()
{
	Sprite &ref = starSprite;

	return ref;
}
Sprite OtherObjects::getFuelSprite()
{
	Sprite &ref = fuelIconSprite[1];

	return ref;
}
Sprite OtherObjects::getHealthSprite()
{
	Sprite &ref = healthIconSprite[1];

	return ref;
}


void OtherObjects::initMeters()
{
	healthMeter.setSize(Vector2f(200, 25));
	healthMeter.setFillColor(Color::Color(0, 255, 0));
	healthMeter.setScale(1, 1);
	healthMeter.setPosition(540, 68);
	healthIconSprite[0].setTexture(healthIconTexture);
	healthIconSprite[0].setPosition(healthMeter.getPosition().x - 35, healthMeter.getPosition().y);

	fuelMeter.setSize(Vector2f(200, 25));
	fuelMeter.setFillColor(Color::Color(0, 255, 0));
	fuelMeter.setScale(1, 1);
	if (hardcore) fuelMeter.setPosition(540, 75);
	else fuelMeter.setPosition(540, 118);
	fuelIconSprite[0].setTexture(fuelIconTexture);
	fuelIconSprite[0].setPosition(fuelMeter.getPosition().x - 35, fuelMeter.getPosition().y);
}
void OtherObjects::updateMeters()
{
	float tempHealth = getPlayerHealth() * 2.55;
	healthMeter.setFillColor(Color::Color(255 - tempHealth, tempHealth, 0));
	healthMeter.setScale(getPlayerHealth() / 100.0f, 1);

	float tempFuel = getPlayerFuel() * 2.55;
	fuelMeter.setFillColor(Color::Color(255 - tempFuel, tempFuel, 0));
	fuelMeter.setScale(getPlayerFuel() / 100.0f, 1);
}
void OtherObjects::drawMeters(RenderWindow &window)
{
	if (!hardcore){
		window.draw(healthMeter);
		window.draw(healthIconSprite[0]);
	}
	
	window.draw(fuelMeter);
	window.draw(fuelIconSprite[0]);
}