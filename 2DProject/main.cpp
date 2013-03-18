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
#include <ctime>

#include "Player.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace sf;

namespace
{
	//Global objects
	Player* object;

	RenderWindow* gameWindow;
	RenderWindow* menuWindow;
}

//Function protos
bool mainMenu();
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
	object = new Player;
	object->setRandomSeed(time(NULL));

	if (!mainMenu()) object->setExitState(true);

	sleep(milliseconds(200));

	if (!object->getExitState()){
		//Init music
		object->updateMusic();

		init();

		Thread renderThread(&render);
		renderThread.launch();

		while (!Keyboard::isKeyPressed(Keyboard::Space)){
			sleep(milliseconds(1));
		}

		update();

		renderThread.wait();
	}

	deInit();
	return 0;
}


bool mainMenu()
{
	menuWindow = new RenderWindow;

	menuWindow->create(VideoMode(VideoMode::getDesktopMode().width / 2, VideoMode::getDesktopMode().height / 2, 32), "Space Dash", Style::None);
	menuWindow->setPosition(Vector2i(VideoMode::getDesktopMode().width / 4, VideoMode::getDesktopMode().width / 8));

	RectangleShape background;
	background.setSize(Vector2f(menuWindow->getSize().x, menuWindow->getSize().y));
	background.setFillColor(Color::White);
	background.setPosition(menuWindow->getPosition().x, menuWindow->getPosition().y);

	menuWindow->display();

	bool start = false, exit = false;

	while (!start && !exit){
		
		menuWindow->draw(background);

		if (Keyboard::isKeyPressed(Keyboard::Space)){
			start = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)){
			exit = true;
		}

		sleep(milliseconds(1));

		menuWindow->clear();
	}

	menuWindow->close();

	delete menuWindow;

	if (start) return true;
	else return false;
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
	object->initObstacleObjects();

	return 1;
}

bool deInit(){
	object->stopMusic();
	delete object;

	return 1;
}


void update()
{	
	while (!object->getExitState() && !object->getExitState()){
		object->updatePlayer();
		object->updateBonusObjects();
		object->updateObstacles();
		object->updateBackground();
		object->updateBorders();
		object->updateText();
		object->updateMusic();

		sleep(microseconds(15000));

		if (object->getCrashState()){
			sleep(milliseconds(500));
			init();

			while (!Keyboard::isKeyPressed(Keyboard::Space) && !Keyboard::isKeyPressed(Keyboard::Space)){
				sleep(milliseconds(1));
			}
			
			if (Keyboard::isKeyPressed(Keyboard::Space)) object->setCrashState(false);
			else if(Keyboard::isKeyPressed(Keyboard::Escape)) object->setExitState(true);
		}
	}
}


void render()
{
	gameWindow = new RenderWindow;

	gameWindow->create(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height, 32), "Space Dash", Style::Fullscreen);
	gameWindow->setVerticalSyncEnabled(1);

	while ((!object->getExitState())){
		
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

	delete gameWindow;
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