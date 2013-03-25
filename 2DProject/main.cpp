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
#include "MenuClass.h"

#include <SFML/System.hpp>

namespace
{
	Player* object;
	MenuClass menu;

	RenderWindow gameWindow;

	bool gamePaused = true;
	bool firstInit = true;

	Event e;
}

//Function protos
bool init(bool initBackgroundAndBorders, bool resetScore);
bool deInit();
void update();
void render();
void network();


int WINAPI WinMain(HINSTANCE hInstance, 
				   HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, 
				   int nCmdShow)
{
	while (menu.showMenu()){
		object = new Player;
		object->setRandomSeed(time(NULL));

		while (gameWindow.pollEvent(e));

		gameWindow.create(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height, 32), "Space Dash", Style::Fullscreen);
		//gameWindow->setFramerateLimit(60);
		gameWindow.setVerticalSyncEnabled(1);
		gameWindow.setMouseCursorVisible(0);

		sleep(milliseconds(200));

		if (!object->getExitState()){
			//Init music
			object->updateMusic();
			gamePaused = true;
			firstInit = true; 

			init(1, 1);
			render();
			update();
		}
		
		gameWindow.close();
		deInit();
	}

	return 0;
}


bool init(bool initBackgroundAndBorders, bool resetScore)
{
	//Set the seed for randomizer
	object->setRandomSeed(time(NULL));

	//Init text
	if (resetScore) object->initScoreText();

	//Init background
	if (initBackgroundAndBorders) object->initBackground();

	//Init player object
	object->initPlayer();

	//Init borders
	if (initBackgroundAndBorders) object->initBorders();

	//Bonus objects
	object->initBonusObjects();

	//Init obstacles
	object->initObstacles();

	//Meters
	object->initMeters();

	return 1;
}

bool deInit(){
	object->stopMusic();
	delete object;

	return 1;
}


void update()
{
	Clock clock;
	Time time;

	while (!object->getExitState()){

		if (Keyboard::isKeyPressed(Keyboard::Escape) || gamePaused){
			gamePaused = true;
			while (Keyboard::isKeyPressed(Keyboard::Escape) || Keyboard::isKeyPressed(Keyboard::R)){
				if (firstInit){
					object->updateBackground();
					object->updateBorders();
					object->updateFlamesPaused();
				}
				render();
				object->updateMusic();

				while (gameWindow.pollEvent(e));

			}
			do{
				if (firstInit){
					object->updateBackground();
					object->updateBorders();
					object->updateFlamesPaused();
				}
				render();
				object->updateMusic();

				while (gameWindow.pollEvent(e));

			}while (!Keyboard::isKeyPressed(Keyboard::Space) && !Keyboard::isKeyPressed(Keyboard::R) && !Keyboard::isKeyPressed(Keyboard::Escape));

			if (Keyboard::isKeyPressed(Keyboard::Space));
			else if (Keyboard::isKeyPressed(Keyboard::Escape)) object->setExitState(true);
		}

		if (Keyboard::isKeyPressed(Keyboard::R)){
			if (firstInit) init(0, 0);
			else init(0, 1);
			gamePaused = true;
			firstInit = true;
		}
		else{
			gamePaused = false;
			firstInit = false;
		}

		if (!object->getExitState() && !gamePaused){
			clock.restart();
			object->updatePlayer();
			object->updateBonusObjects();
			object->updateObstacles();
			object->updateBackground();
			object->updateBorders();
			object->updateMeters();
			object->updateText();
			object->updateMusic();

			render();

			time = clock.getElapsedTime();
			sleep(milliseconds(14 - time.asMilliseconds()));

			if (object->getCrashState()){
				sleep(milliseconds(750));
				init(0, 1);
				gamePaused = true;
				firstInit = true;
				object->setCrashState(false);
			}
		}
		while (gameWindow.pollEvent(e));
	}
}


void render()
{
	gameWindow.clear();
	gameWindow.pushGLStates();

	//Draw objects
	//Background
	object->drawBackground(gameWindow);

	//Borders
	object->drawBorders(gameWindow);
	
	//Obstacles
	object->drawObstacles(gameWindow);
	
	//Bonus objects
	object->drawBonusObjects(gameWindow);

	//Player
	if (!object->getCrashState()) object->drawPlayer(gameWindow);
	//Flames
	if (!object->getCrashState()) object->drawFlames(gameWindow, gamePaused && firstInit);

	//Crash debris
	object->drawCrashDebris(gameWindow);
	object->drawDamageParticles(gameWindow);

	//Meters
	object->drawMeters(gameWindow);

	//Text
	object->drawText(gameWindow);

	if (gamePaused) object->drawPauseText(gameWindow);
			
	gameWindow.popGLStates();
	gameWindow.display();
}


void network()
{
	//Reason: -NO! You're not doing this! Just make the damn game.
	//Me: -But I want to do internet multiplayer! It'll be so aweso...
	//Reason: -Forget it! It's just going to screw everything up!
	//Me: -But I'm just gonna...
	//Reason: -NO!
	//Me: -okay...
}