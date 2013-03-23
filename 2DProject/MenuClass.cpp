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

#include "MenuClass.h"


MenuClass::MenuClass(void)
{
	menuWindow = new RenderWindow;

	flameAnim = 0;
	flameScale = 0.5;
	animSteps = 10;
	animAscend = true;

	if (!rocketTexture.loadFromFile("Resources/Graphics/rocket.png")){
		MessageBox(NULL, L"Failed to load rocket texture!", L"Error", MB_OK);
	}
	if (!flameTexture.loadFromFile("Resources/Graphics/flame_1.png")){
		MessageBox(NULL, L"Failed to load flame texture!", L"Error", MB_OK);
	}
	if (!shadeTexture.loadFromFile("Resources/Graphics/menuShade.png")){
		MessageBox(NULL, L"Failed to load shade texture!", L"Error", MB_OK);
	}
	if (!logoTexture.loadFromFile("Resources/Graphics/menulogo.png")){
		MessageBox(NULL, L"Failed to load logo texture!", L"Error", MB_OK);
	}
	if (!defaultFont.loadFromFile("Resources/Misc/font.otf")){
		MessageBox(NULL, L"Failed to load font!", L"Error", MB_OK );
	}
}
MenuClass::~MenuClass(void)
{
	delete menuWindow;
}

bool MenuClass::showMenu()
{
	menuWindow->create(VideoMode(800, 400, 32), "Space Dash", Style::None);
	menuWindow->setPosition(Vector2i(VideoMode::getDesktopMode().width / 3.5, VideoMode::getDesktopMode().width / 5.5));
	menuWindow->setFramerateLimit(60);
	menuMusic.updateMenuMusic();
	initGraphics();

	bool start = false, exit = false;

	while (!start && !exit){
		menuMusic.updateMenuMusic();
		updateGraphics();
		drawGraphics();

		if (Keyboard::isKeyPressed(Keyboard::Space) || (Mouse::isButtonPressed(Mouse::Left) && mouseIsOnButton(&playButtonText))){
			start = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape) || (Mouse::isButtonPressed(Mouse::Left) && mouseIsOnButton(&exitButtonText))){
			exit = true;
		}

		sleep(milliseconds(1));
	}

	closeMenu();

	if (start) return true;
	else return false;
}

//Private

void MenuClass::closeMenu()
{
	menuMusic.stopMenuMusic();
	menuWindow->close();
}

void MenuClass::initGraphics()
{
	distanceLeftRocket = 225;
	rocketDestination = 125;

	for (int i = 0; i < numberOfStars; i++){
		starSpeed[i] = -(getRandom(1, 7));
	}

	playButtonText.setPosition(540, 50);
	playButtonText.setFont(defaultFont);
	playButtonText.setColor(Color::Color(0, 122, 243));
	playButtonText.setCharacterSize(55);
	playButtonText.setString("PLAY");

	exitButtonText.setPosition(540, 230);
	exitButtonText.setFont(defaultFont);
	exitButtonText.setColor(Color::Color(0, 122, 243));
	exitButtonText.setCharacterSize(35);
	exitButtonText.setString("EXIT");

	settingsButtonText.setPosition(540, 150);
	settingsButtonText.setFont(defaultFont);
	settingsButtonText.setColor(Color::Color(0, 122, 243));
	settingsButtonText.setCharacterSize(35);
	settingsButtonText.setString("SETTINGS");

	creditsButtonText.setPosition(540, 190);
	creditsButtonText.setFont(defaultFont);
	creditsButtonText.setColor(Color::Color(0, 122, 243));
	creditsButtonText.setCharacterSize(35);
	creditsButtonText.setString("CREDITS");

	shadeSprite.setTexture(shadeTexture);
	shadeSprite.setPosition(-50, 0);

	logoSprite.setTexture(logoTexture);
	logoSprite.setPosition(50, 50);

	rocketSprite.setTexture(rocketTexture);
	rocketSprite.setPosition(-100, 250);

	//Flames
	flameSpriteTop.setTexture(flameTexture);
	flameSpriteTop.setScale(0.5f, 0.5f);
	flameSpriteTop.setOrigin(flameSpriteTop.getGlobalBounds().width * 2, flameSpriteTop.getGlobalBounds().height * 2);
	flameSpriteTop.setPosition(-100, -100);	

	flameSpriteBottom.setTexture(flameTexture);
	flameSpriteBottom.setScale(0.5f, 0.5f);
	flameSpriteBottom.setOrigin(flameSpriteBottom.getGlobalBounds().width * 2, flameSpriteBottom.getGlobalBounds().height * 2);
	flameSpriteBottom.setPosition(-100, -100);

	for (int i = 0; i < numberOfStars; i++){
		float number = getRandom(1, 2);
		starShape[i].setSize(Vector2f(number, number));
		starShape[i].setPosition(getRandom(-2, 400), getRandom(0, menuWindow->getSize().y));
	}
}
void MenuClass::updateGraphics()
{
	if (rocketSprite.getPosition().x <= rocketDestination){
		float movement = 0.03 * distanceLeftRocket;
		rocketSprite.move(movement, 0);
		distanceLeftRocket -= movement;
	}

	if (mouseIsOnButton(&playButtonText)) playButtonText.setColor(Color::Color(255, 255, 0));
	else playButtonText.setColor(Color::Color(0, 122, 243));
	if (mouseIsOnButton(&exitButtonText)) exitButtonText.setColor(Color::Color(255, 255, 0));
	else exitButtonText.setColor(Color::Color(0, 122, 243));
	if (mouseIsOnButton(&settingsButtonText)) settingsButtonText.setColor(Color::Color(255, 255, 0));
	else settingsButtonText.setColor(Color::Color(0, 122, 243));
	if (mouseIsOnButton(&creditsButtonText)) creditsButtonText.setColor(Color::Color(255, 255, 0));
	else creditsButtonText.setColor(Color::Color(0, 122, 243));

	//Flame animation logic stuff
	if (flameAnim > animSteps){
		animAscend = false;
	}
	else if (flameAnim < -animSteps){
		animAscend = true;
	}

	//Flame Sprite Bottom
	flameSpriteBottom.setPosition(rocketSprite.getPosition().x - 5, rocketSprite.getPosition().y + 20);
	flameSpriteBottom.setRotation(rocketSprite.getRotation());

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
	flameSpriteTop.setPosition(rocketSprite.getPosition().x - 5, rocketSprite.getPosition().y + 50);
	flameSpriteTop.setRotation(rocketSprite.getRotation());

	if (animAscend){
		flameScale += 0.006;
		flameSpriteTop.setScale(flameScale, flameSpriteBottom.getScale().y);
		flameAnim++;
	}
	else if (!animAscend){
		flameScale -= 0.006;
		flameSpriteTop.setScale(flameScale, flameSpriteBottom.getScale().y);
		flameAnim--;
	}



	for (int i = 0; i < numberOfStars; i++){
		starShape[i].move(starSpeed[i], 0);

		if (starShape[i].getPosition().x <= -5) starShape[i].setPosition(getRandom(400, 400), getRandom(0, menuWindow->getSize().y));
	}
}
void MenuClass::drawGraphics()
{
	menuWindow->clear();

	for (int i = 0; i < numberOfStars; i++){
		menuWindow->draw(starShape[i]);
	}
	menuWindow->draw(shadeSprite);
	menuWindow->draw(logoSprite);
	menuWindow->draw(rocketSprite);
	menuWindow->draw(flameSpriteBottom);
	menuWindow->draw(flameSpriteTop);
	menuWindow->draw(playButtonText);
	menuWindow->draw(exitButtonText);
	menuWindow->draw(settingsButtonText);
	menuWindow->draw(creditsButtonText);

	menuWindow->display();
}

bool MenuClass::mouseIsOnMenu()
{
	if (menuWindow->getPosition().x < Mouse::getPosition().x &&
		menuWindow->getPosition().y < Mouse::getPosition().y &&
		menuWindow->getPosition().x + menuWindow->getSize().x > Mouse::getPosition().x &&
		menuWindow->getPosition().y + menuWindow->getSize().y > Mouse::getPosition().y) return true;

	return false;
}
bool MenuClass::mouseIsOnButton(Text *text)
{
	if (text->getPosition().x < Mouse::getPosition(*menuWindow).x &&
		text->getPosition().y + (text->getCharacterSize() / 3.6) < Mouse::getPosition(*menuWindow).y &&
		text->getPosition().x + text->getLocalBounds().width > Mouse::getPosition(*menuWindow).x &&
		text->getPosition().y + (text->getLocalBounds().height + (text->getCharacterSize() / 3.6)) > Mouse::getPosition(*menuWindow).y) return true;

	return false;
}