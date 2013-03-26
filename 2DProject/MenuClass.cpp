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

namespace{
	Event e;
}

MenuClass::MenuClass(void)
{
	minimized = false;

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
MenuClass::~MenuClass(void){}

bool MenuClass::showMenu()
{
	readSettingsFromFile();
	readScoreFromFile();

	inSubMenu = false;
	inCreditsMenu = false;
	inOptionsMenu = false;
	inScoreMenu = false;

	RenderWindow menuWindow;
	menuWindow.create(VideoMode(800, 400, 32), "Space Dash", Style::None);
	menuWindow.setPosition(Vector2i((VideoMode::getDesktopMode().width / 2) - (menuWindow.getSize().x / 2), (VideoMode::getDesktopMode().height / 2) - (menuWindow.getSize().y / 2)));
	if (!vSync) menuWindow.setFramerateLimit(60);
	menuWindow.setVerticalSyncEnabled(vSync);
	updateMenuMusic();
	initGraphics(menuWindow, 1);

	bool start = false, exit = false;

	while (!start && !exit){
		if (!minimized){
			menuWindow.clear();
			updateMenuMusic();
			updateGraphics(menuWindow);
			drawGraphics(menuWindow);
			infoText.setString("");
		
			
			if (Keyboard::isKeyPressed(Keyboard::Space) || (Mouse::isButtonPressed(Mouse::Left) && mouseIsOnButton(menuWindow, &playButtonText))){
				start = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape) || (Mouse::isButtonPressed(Mouse::Left) && mouseIsOnButton(menuWindow, &exitButtonText))){
				exit = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::S) || (Mouse::isButtonPressed(Mouse::Left) && mouseIsOnButton(menuWindow, &scoreButtonText))){
				inSubMenu = true;
				inCreditsMenu = false;
				inOptionsMenu = false;
				inScoreMenu = true;
				scoreMenu(menuWindow, 1);
			}
			if (Keyboard::isKeyPressed(Keyboard::O) || (Mouse::isButtonPressed(Mouse::Left) && mouseIsOnButton(menuWindow, &optionsButtonText))){
				inSubMenu = true;
				inCreditsMenu = false;
				inOptionsMenu = true;
				inScoreMenu = false;
				optionsMenu(menuWindow, 1);
			}
			if (Keyboard::isKeyPressed(Keyboard::C) || (Mouse::isButtonPressed(Mouse::Left) && mouseIsOnButton(menuWindow, &creditsButtonText))){
				inSubMenu = true;
				inCreditsMenu = true;
				inOptionsMenu = false;
				inScoreMenu = false;
				creditsMenu(menuWindow, 1);
			}
			if ((Keyboard::isKeyPressed(Keyboard::BackSpace) && inSubMenu) || (Mouse::isButtonPressed(Mouse::Left) && mouseIsOnButton(menuWindow, &backButtonText))){
				inSubMenu = false;
				inCreditsMenu = false;
				inOptionsMenu = false;
				inScoreMenu = false;
				initGraphics(menuWindow, 0);
			}
			
			if (inScoreMenu) scoreMenu(menuWindow, 0);
			else if (inOptionsMenu) optionsMenu(menuWindow, 0);
			else if (inCreditsMenu) creditsMenu(menuWindow, 0);
			else {
				inSubMenu = false;
				inCreditsMenu = false;
				inOptionsMenu = false;
				inScoreMenu = false;
			}

			menuWindow.display();
		}

		if (minimized || !inSubMenu){
			while (menuWindow.pollEvent(e)){
				if (e.type == Event::LostFocus) minimized = true;
				else if (e.type == Event::GainedFocus) minimized = false;
			}
			sleep(milliseconds(10));
		}
	}
	
	menuWindow.close();
	closeMenu();

	if (start) return true;
	else return false;
}

//Private

void MenuClass::closeMenu()
{
	writeSettingsToFile();
	writeScoreToFile();
	stopMenuMusic();
}

void MenuClass::initGraphics(RenderWindow &menuWindow, bool firstInit)
{
	rocketDestination = 200;
	logoDestination = 133;

	infoText.setFont(defaultFont);
	infoText.setColor(Color::Color(255, 128, 0));
	infoText.setCharacterSize(13);
	infoText.setString("");

	if (firstInit){
		for (int i = 0; i < numberOfStars; i++){
			starSpeed[i] = -(getRandom(1, 7));
		}

		playButtonText.setPosition(540, 50);
		playButtonText.setFont(defaultFont);
		playButtonText.setColor(Color::Color(0, 122, 243));
		playButtonText.setCharacterSize(55);
		playButtonText.setString("PLAY");

		scoreButtonText.setPosition(540, 150);
		scoreButtonText.setFont(defaultFont);
		scoreButtonText.setColor(Color::Color(0, 122, 243));
		scoreButtonText.setCharacterSize(35);
		scoreButtonText.setString("SCORES");

		optionsButtonText.setPosition(540, 190);
		optionsButtonText.setFont(defaultFont);
		optionsButtonText.setColor(Color::Color(0, 122, 243));
		optionsButtonText.setCharacterSize(35);
		optionsButtonText.setString("OPTIONS");

		creditsButtonText.setPosition(540, 230);
		creditsButtonText.setFont(defaultFont);
		creditsButtonText.setColor(Color::Color(0, 122, 243));
		creditsButtonText.setCharacterSize(35);
		creditsButtonText.setString("CREDITS");

		exitButtonText.setPosition(540, 270);
		exitButtonText.setFont(defaultFont);
		exitButtonText.setColor(Color::Color(0, 122, 243));
		exitButtonText.setCharacterSize(35);
		exitButtonText.setString("EXIT");

		backButtonText.setPosition(350, 350);
		backButtonText.setFont(defaultFont);
		backButtonText.setColor(Color::Green);
		backButtonText.setCharacterSize(28);
		backButtonText.setString("BACK >>");


		shadeSprite.setTexture(shadeTexture);
		shadeSprite.setPosition(25, 0);
	}

	logoSprite.setTexture(logoTexture);
	logoSprite.setPosition(-250, 50);

	rocketSprite.setTexture(rocketTexture);
	rocketSprite.setPosition(-500, 250);

	//Flames
	flameSpriteTop.setTexture(flameTexture);
	flameSpriteTop.setScale(0.5f, 0.5f);
	flameSpriteTop.setOrigin(flameSpriteTop.getGlobalBounds().width * 2, flameSpriteTop.getGlobalBounds().height * 2);
	flameSpriteTop.setPosition(-100, -100);	

	flameSpriteBottom.setTexture(flameTexture);
	flameSpriteBottom.setScale(0.5f, 0.5f);
	flameSpriteBottom.setOrigin(flameSpriteBottom.getGlobalBounds().width * 2, flameSpriteBottom.getGlobalBounds().height * 2);
	flameSpriteBottom.setPosition(-100, -100);

	if (firstInit){
		for (int i = 0; i < numberOfStars; i++){
			float number = getRandom(1, 2);
			starShape[i].setSize(Vector2f(number, number));
			starShape[i].setPosition(getRandom(-2, 600), getRandom(0, menuWindow.getSize().y));
		}
	}
	
	distanceLeftRocket = rocketDestination + -(rocketSprite.getPosition().x);
	distanceLeftLogo = logoDestination + -(logoSprite.getPosition().x);

	firstInit = false;
	inSubMenu = false;
}
void MenuClass::updateGraphics(RenderWindow &menuWindow)
{
	//Rocket
	if (rocketDestination > rocketSprite.getPosition().x){
		float movement = 0.03 * distanceLeftRocket;
		rocketSprite.move(movement, 0);
		distanceLeftRocket -= movement;
	}
	else if (rocketDestination < rocketSprite.getPosition().x){
		float movement = 0.03 * distanceLeftLogo;
		logoSprite.move(-movement, 0);
		distanceLeftLogo += movement;
	}
	//Logo
	if (logoDestination > logoSprite.getPosition().x){
		float movement = 0.03 * distanceLeftLogo;
		logoSprite.move(movement, 0);
		distanceLeftLogo -= movement;
	}
	else if (logoDestination < logoSprite.getPosition().x){
		float movement = 0.03 * distanceLeftLogo;
		logoSprite.move(-movement, 0);
		distanceLeftLogo += movement;
	}

	infoText.setPosition(Mouse::getPosition(menuWindow).x + 50, Mouse::getPosition(menuWindow).y);
	

	if (mouseIsOnButton(menuWindow, &playButtonText)) playButtonText.setColor(Color::Color(255, 255, 0));
	else playButtonText.setColor(Color::Color(0, 122, 243));
	if (mouseIsOnButton(menuWindow, &scoreButtonText)) scoreButtonText.setColor(Color::Color(255, 255, 0));
	else scoreButtonText.setColor(Color::Color(0, 122, 243));
	if (mouseIsOnButton(menuWindow, &optionsButtonText)) optionsButtonText.setColor(Color::Color(255, 255, 0));
	else optionsButtonText.setColor(Color::Color(0, 122, 243));
	if (mouseIsOnButton(menuWindow, &creditsButtonText)) creditsButtonText.setColor(Color::Color(255, 255, 0));
	else creditsButtonText.setColor(Color::Color(0, 122, 243));
	if (mouseIsOnButton(menuWindow, &exitButtonText)) exitButtonText.setColor(Color::Color(255, 255, 0));
	else exitButtonText.setColor(Color::Color(0, 122, 243));
	if (mouseIsOnButton(menuWindow, &backButtonText)) backButtonText.setColor(Color::Color(255, 255, 0));
	else backButtonText.setColor(Color::Green);

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
	flameSpriteTop.setPosition(rocketSprite.getPosition().x - 5, rocketSprite.getPosition().y + 50);
	flameSpriteTop.setRotation(rocketSprite.getRotation());

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



	for (int i = 0; i < numberOfStars; i++){
		starShape[i].move(starSpeed[i], 0);

		if (starShape[i].getPosition().x <= -3) starShape[i].setPosition(600, getRandom(1, menuWindow.getSize().y));
	}
}
void MenuClass::drawGraphics(RenderWindow &menuWindow)
{
	for (int i = 0; i < numberOfStars; i++){
		menuWindow.draw(starShape[i]);
	}
	
	menuWindow.draw(shadeSprite);
	if (!inSubMenu){
		menuWindow.draw(logoSprite);
		menuWindow.draw(rocketSprite);
		menuWindow.draw(flameSpriteBottom);
		menuWindow.draw(flameSpriteTop);
	}
	menuWindow.draw(playButtonText);
	menuWindow.draw(exitButtonText);
	menuWindow.draw(optionsButtonText);
	menuWindow.draw(creditsButtonText);
	menuWindow.draw(scoreButtonText);
	if (inSubMenu) menuWindow.draw(backButtonText);
}

bool MenuClass::mouseIsOnMenu(RenderWindow &menuWindow)
{
	if (menuWindow.getPosition().x < Mouse::getPosition().x &&
		menuWindow.getPosition().y < Mouse::getPosition().y &&
		menuWindow.getPosition().x + menuWindow.getSize().x > Mouse::getPosition().x &&
		menuWindow.getPosition().y + menuWindow.getSize().y > Mouse::getPosition().y) return true;

	return false;
}
bool MenuClass::mouseIsOnButton(RenderWindow &menuWindow, Text *text)
{
	if (text->getPosition().x < Mouse::getPosition(menuWindow).x &&
		text->getPosition().y + (text->getCharacterSize() / 3.6) < Mouse::getPosition(menuWindow).y &&
		text->getPosition().x + text->getLocalBounds().width > Mouse::getPosition(menuWindow).x &&
		text->getPosition().y + (text->getLocalBounds().height + (text->getCharacterSize() / 3.6)) > Mouse::getPosition(menuWindow).y) return true;

	return false;
}

void MenuClass::scoreMenu(RenderWindow &window, bool init)
{
	if (init){
		std::stringstream ss;

		scoreText[0].setPosition(25, 14);
		scoreText[0].setFont(defaultFont);
		scoreText[0].setColor(Color::White);
		scoreText[0].setCharacterSize(40);
		scoreText[0].setString("High Scores");

		
		ss.str("");
		ss << "Easy << " << bestScoreEasy / 10;
		scoreText[1].setPosition(50, 100);
		scoreText[1].setFont(defaultFont);
		scoreText[1].setColor(Color::Green);
		scoreText[1].setCharacterSize(20);
		scoreText[1].setString(ss.str());
		ss.str("");
		ss << "Medium << " << bestScoreMedium / 10;
		scoreText[2].setPosition(50, 125);
		scoreText[2].setFont(defaultFont);
		scoreText[2].setColor(Color::Yellow);
		scoreText[2].setCharacterSize(20);
		scoreText[2].setString(ss.str());
		ss.str("");
		ss << "Hard << " << bestScoreHard / 10;
		scoreText[3].setPosition(50, 150);
		scoreText[3].setFont(defaultFont);
		scoreText[3].setColor(Color::Red);
		scoreText[3].setCharacterSize(20);
		scoreText[3].setString(ss.str());
		ss.str("");
		ss << "Easy HC << " << bestScoreEasyHC / 10;
		scoreText[4].setPosition(50, 200);
		scoreText[4].setFont(defaultFont);
		scoreText[4].setColor(Color::Green);
		scoreText[4].setCharacterSize(20);
		scoreText[4].setString(ss.str());
		ss.str("");
		ss << "Medium HC << " << bestScoreMediumHC / 10;
		scoreText[5].setPosition(50, 225);
		scoreText[5].setFont(defaultFont);
		scoreText[5].setColor(Color::Yellow);
		scoreText[5].setCharacterSize(20);
		scoreText[5].setString(ss.str());
		ss.str("");
		ss << "Hard HC << " << bestScoreHardHC / 10;
		scoreText[6].setPosition(50, 250);
		scoreText[6].setFont(defaultFont);
		scoreText[6].setColor(Color::Red);
		scoreText[6].setCharacterSize(20);
		scoreText[6].setString(ss.str());
	}

	if (!init){
		for (int i = 0; i < 7; i++) window.draw(scoreText[i]);
		window.draw(infoText);
	}

	while (window.pollEvent(e));
}
void MenuClass::optionsMenu(RenderWindow &window, bool init)
{
	if (init){
		optionsText[0].setPosition(25, 14);
		optionsText[0].setFont(defaultFont);
		optionsText[0].setColor(Color::White);
		optionsText[0].setCharacterSize(40);
		optionsText[0].setString("OPTIONS");

		//Vsync
		optionsText[1].setPosition(25, 75);
		optionsText[1].setFont(defaultFont);
		optionsText[1].setCharacterSize(20);
		if (vSync){
			optionsText[1].setColor(Color::Yellow);
			optionsText[1].setString("V-Sync (ON)");
		}
		else{
			optionsText[1].setColor(Color::Cyan);
			optionsText[1].setString("V-Sync (OFF)");
		}
		//Sounds
		optionsText[2].setPosition(25, optionsText[1].getPosition().y + 35);
		optionsText[2].setFont(defaultFont);
		optionsText[2].setCharacterSize(20);
		if (playSound){
			optionsText[2].setColor(Color::Yellow);
			optionsText[2].setString("Sound (ON)");
		}
		else{
			optionsText[2].setColor(Color::Cyan);
			optionsText[2].setString("Sound (OFF)");
		}
		//Music
		optionsText[3].setPosition(25, optionsText[2].getPosition().y + 25);
		optionsText[3].setFont(defaultFont);
		optionsText[3].setCharacterSize(20);
		if (playMusic){
			optionsText[3].setColor(Color::Yellow);
			optionsText[3].setString("Music (ON)");
		}
		else{
			optionsText[3].setColor(Color::Cyan);
			optionsText[3].setString("Music (OFF)");
		}
		//Easy
		optionsText[4].setPosition(25,  optionsText[3].getPosition().y + 50);
		optionsText[4].setFont(defaultFont);
		optionsText[4].setCharacterSize(20);
		if (difficulty == 1){
			optionsText[4].setColor(Color::Green);
			optionsText[4].setString("Easy <--");
		}
		else{
			optionsText[4].setColor(Color::Green);
			optionsText[4].setString("Easy");
		}
		//Medium
		optionsText[5].setPosition(25, optionsText[4].getPosition().y + 25);
		optionsText[5].setFont(defaultFont);
		optionsText[5].setCharacterSize(20);
		if (difficulty == 2){
			optionsText[5].setColor(Color::Yellow);
			optionsText[5].setString("Medium <--");
		}
		else{
			optionsText[5].setColor(Color::Yellow);
			optionsText[5].setString("Medium");
		}
		//Hard
		optionsText[6].setPosition(25,  optionsText[5].getPosition().y + 25);
		optionsText[6].setFont(defaultFont);
		optionsText[6].setCharacterSize(20);
		if (difficulty == 3){
			optionsText[6].setColor(Color::Red);
			optionsText[6].setString("Hard <--");
		}
		else{
			optionsText[6].setColor(Color::Red);
			optionsText[6].setString("Hard");
		}
		//Hardcore
		optionsText[7].setPosition(25,  optionsText[6].getPosition().y + 35);
		optionsText[7].setFont(defaultFont);
		optionsText[7].setCharacterSize(20);
		if (hardcore){
			optionsText[7].setColor(Color::Magenta);
			optionsText[7].setString("Hardcore (ON)");
		}
		else{
			optionsText[7].setColor(Color::Cyan);
			optionsText[7].setString("Hardcore (OFF)");
		}
	}

	std::stringstream ss;

	if (!init){
		//Vsync
		if (mouseIsOnButton(window, &optionsText[1])){
			infoText.setString("Enable/disable vertical\nsynchronization");
			while (window.pollEvent(e)){
				if (e.type == Event::MouseButtonPressed){
					if (vSync){
						vSync = false;
						optionsText[1].setColor(Color::Cyan);
						optionsText[1].setString("V-Sync (OFF)");

					}
					else{
						vSync = true;
						optionsText[1].setColor(Color::Yellow);
						optionsText[1].setString("V-Sync (ON)");
					}
				}
			}
		}
		//Sound
		if (mouseIsOnButton(window, &optionsText[2])){
			infoText.setString("Enable/disable sound");
			while (window.pollEvent(e)){
				if (e.type == Event::MouseButtonPressed){
					if (playSound){
						playSound = false;
						optionsText[2].setColor(Color::Cyan);
						optionsText[2].setString("Sound (OFF)");

					}
					else{
						playSound = true;
						optionsText[2].setColor(Color::Yellow);
						optionsText[2].setString("Sound (ON)");
					}
				}
			}
		}
		//Music
		if (mouseIsOnButton(window, &optionsText[3])){
			infoText.setString("Enable/disable music");
			while (window.pollEvent(e)){
				if (e.type == Event::MouseButtonPressed){
					if (playMusic){
						playMusic = false;
						stopMenuMusic();
						optionsText[3].setColor(Color::Cyan);
						optionsText[3].setString("Music (OFF)");

					}
					else{
						playMusic = true;
						updateMenuMusic();
						optionsText[3].setColor(Color::Yellow);
						optionsText[3].setString("Music (ON)");
					}
				}
			}
		}
		//Easy
		if (mouseIsOnButton(window, &optionsText[4])){
			infoText.setString("- Standard number of meteorites\n- Standard fuel consumption\n- You're not that fragile\n- Standard score gain");
			while (window.pollEvent(e)){
				if (e.type == Event::MouseButtonPressed){
					if (difficulty == 2 || difficulty == 3){
						difficulty = 1;
						optionsText[4].setString("Easy <--");
						optionsText[5].setString("Medium");
						optionsText[6].setString("Hard");
					}
				}
			}
		}
		//Medium
		if (mouseIsOnButton(window, &optionsText[5])){
			infoText.setString("- There are more meteorites\n- Increased fuel consumption\n- You're more fragile\n- Score increases faster");
			while (window.pollEvent(e)){
				if (e.type == Event::MouseButtonPressed){
					if (difficulty == 1 || difficulty == 3){
						difficulty = 2;
						optionsText[4].setString("Easy");
						optionsText[5].setString("Medium <--");
						optionsText[6].setString("Hard");
					}
				}
			}
		}
		//Hard
		if (mouseIsOnButton(window, &optionsText[6])){
			infoText.setString("- There are even moremeteorites\n- Increased fuel consumption\n- You're more fragile\n- Score increases faster");
			while (window.pollEvent(e)){
				if (e.type == Event::MouseButtonPressed){
					if (difficulty == 1 || difficulty == 2){
						difficulty = 3;
						optionsText[4].setString("Easy");
						optionsText[5].setString("Medium");
						optionsText[6].setString("Hard <--");
					}
				}
			}
		}
		//Hardcore
		if (mouseIsOnButton(window, &optionsText[7])){
			infoText.setString("In hardcore mode\nyou'll die from\na single hit.\nScore gain is doubled.");
			while (window.pollEvent(e)){
				if (e.type == Event::MouseButtonPressed){
					if (hardcore){
						hardcore = false;
						optionsText[7].setColor(Color::Cyan);
						optionsText[7].setString("Hardcore (OFF)");

					}
					else{
						hardcore = true;
						optionsText[7].setColor(Color::Magenta);
						optionsText[7].setString("Hardcore (ON)");
					}
				}
			}
		}
		while (window.pollEvent(e)){
			if (e.type == Event::LostFocus) minimized = true;
			else if (e.type == Event::GainedFocus) minimized = false;
		}

		for (int i = 0; i < 8; i++) window.draw(optionsText[i]);
		window.draw(infoText);
	}
}
void MenuClass::creditsMenu(RenderWindow &window, bool init)
{
	if (init){
		creditsText[0].setPosition(25, 400);
		creditsText[0].setFont(defaultFont);
		creditsText[0].setColor(Color::White);
		creditsText[0].setCharacterSize(40);
		creditsText[0].setString("Credits");

		std::stringstream ss;
		ss << "Creator\n";
		ss << "    Joona \"Jonki\" Tiinanen\n\n";
		ss << "Programming\n";
		ss << "    Joona \"Jonki\" Tiinanen\n\n";
		ss << "Art\n";
		ss << "    Joona \"Jonki\" Tiinanen\n\n";
		ss << "Music\n";
		ss << "    Machinima Sound\n    Kevin MacLeod\n\n";
		ss << "Sound\n";
		ss << "    \n    \n\n\n";
		ss << "Special thanks!\n";
		ss << "    Ilari \"Ilgoth\" Nikkarikoski\n";
		ss << "    Nooobody\n";
		ss << "    Students and teachers\n";
		ss << "    of Kajaani UAS\n";

		creditsText[1].setPosition(25, creditsText[0].getPosition().y + 50);
		creditsText[1].setFont(defaultFont);
		creditsText[1].setColor(Color::Cyan);
		creditsText[1].setCharacterSize(15);
		creditsText[1].setString(ss.str());
	}

	if (!init){
		creditsText[0].move(0, -0.5);
		creditsText[1].setPosition(25, creditsText[0].getPosition().y + 50);

		window.draw(creditsText[0]);
		window.draw(creditsText[1]);
		window.draw(infoText);

		if (creditsText[0].getPosition().y < -480){
			inSubMenu = false;
			inCreditsMenu = false;
			initGraphics(window, 0);
		}
	}
	while (window.pollEvent(e));
}