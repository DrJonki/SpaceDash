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
}
MenuClass::~MenuClass(void)
{
	delete menuWindow;
}

bool MenuClass::showMenu()
{
	menuWindow->create(VideoMode(800, 400, 32), "Space Dash", Style::None);
	menuWindow->setPosition(Vector2i(VideoMode::getDesktopMode().width / 3.5, VideoMode::getDesktopMode().width / 5));
	menuMusic.updateMenuMusic();

	bool start = false, exit = false;

	while (!start && !exit){
		menuMusic.updateMenuMusic();
		menuWindow->clear();
		menuWindow->display();

		if (Keyboard::isKeyPressed(Keyboard::Space)){
			start = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)){
			exit = true;
		}

		sleep(milliseconds(1));
	}

	menuWindow->close();
	closeMenu();

	if (start) return true;
	else return false;
}

//Private

void MenuClass::closeMenu()
{
	menuMusic.stopMenuMusic();
}

bool MenuClass::mouseIsOnMenu()
{
	if (menuWindow->getPosition().x < Mouse::getPosition().x &&
		menuWindow->getPosition().y < Mouse::getPosition().y &&
		menuWindow->getPosition().x + menuWindow->getSize().x > Mouse::getPosition().x &&
		menuWindow->getPosition().y + menuWindow->getSize().y > Mouse::getPosition().y) return true;

	return false;
}