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

	RenderWindow* gameWindow;
}

//Function protos
bool init();
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

		gameWindow = new RenderWindow;

		gameWindow->create(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height, 32), "Space Dash", Style::Fullscreen);
		gameWindow->setVerticalSyncEnabled(1);
		gameWindow->setMouseCursorVisible(0);

		sleep(milliseconds(200));

		if (!object->getExitState()){
			//Init music
			object->updateMusic();

			init();
			render();

			while (!Keyboard::isKeyPressed(Keyboard::Space) && !Keyboard::isKeyPressed(Keyboard::Escape)){
				sleep(milliseconds(1));
				object->updateMusic();
			}

			update();
		}
		
		gameWindow->close();
		deInit();
	}

	return 0;
}


bool init()
{
	//Set the seed for randomizer
	object->setRandomSeed(time(NULL));

	//Init text
	object->initScoreText();

	//Init background
	object->initBackground();

	//Init player object
	object->initPlayer();

	//Init borders
	object->initBorders();

	//Bonus objects
	object->initBonusObjects();

	//Init obstacles
	object->initObstacles();

	return 1;
}

bool deInit(){
	object->stopMusic();
	delete gameWindow;
	delete object;

	return 1;
}


void update()
{
	Clock clock;
	Time time;

	while (!object->getExitState()){
		clock.restart();
		object->updatePlayer();
		object->updateBonusObjects();
		object->updateObstacles();
		object->updateBackground();
		object->updateBorders();
		object->updateText();
		object->updateMusic();

		render();

		time = clock.getElapsedTime();
		sleep(milliseconds(14 - time.asMilliseconds()));

		if (object->getCrashState()){
			sleep(milliseconds(500));
			init();

			do{
				sleep(milliseconds(1));

				if (Keyboard::isKeyPressed(Keyboard::Space)){
					object->setCrashState(false);
				}
				object->updateMusic();
				render();
			}while (!object->getExitState() && object->getCrashState());
		}
	}
}


void render()
{
	gameWindow->clear();
	gameWindow->pushGLStates();

	//Draw objects
	//Background
	object->drawBackground(gameWindow);

	//Player
	object->drawPlayer(gameWindow);
	//Flames
	if (!object->getCrashState()) object->drawFlames(gameWindow);

	//Bonus objects
	object->drawBonusObjects(gameWindow);

	//Borders
	object->drawBorders(gameWindow);

	//Obstacles
	object->drawObstacles(gameWindow);

	//Text
	object->drawText(gameWindow);
			
	gameWindow->popGLStates();
	gameWindow->display();

	if ((Keyboard::isKeyPressed(Keyboard::Escape))) object->setExitState(true);
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