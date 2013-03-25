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

#ifndef MENUCLASS
#define MENUCLASS

#include "SoundClass.h"
#include "Misc.h"

#include <Windows.h>
#include <SFML/Graphics.hpp>
using namespace sf;

class MenuClass : private Misc, private SoundClass
{
public:
	MenuClass(void);
	~MenuClass(void);

	bool showMenu();

private:
	Texture shadeTexture;
	Sprite shadeSprite;

	Texture logoTexture;
	Sprite logoSprite;

	Font defaultFont;
	Text playButtonText;
	Text exitButtonText;
	Text settingsButtonText;
	Text creditsButtonText;

	Text craditsText;

	Texture rocketTexture;
	Texture flameTexture;
	Sprite rocketSprite;
	Sprite flameSpriteTop;
	Sprite flameSpriteBottom;
	float distanceLeftRocket;
	float rocketDestination;

	static const int numberOfStars = 50;
	RectangleShape starShape[numberOfStars];
	float starSpeed[50];

	void initGraphics(RenderWindow &menuWindow);
	void updateGraphics(RenderWindow &menuWindow);
	void drawGraphics(RenderWindow &menuWindow);

	void closeMenu();
	bool mouseIsOnMenu(RenderWindow &menuWindow);
	bool mouseIsOnButton(RenderWindow &menuWindow, Text *text);

	bool firstInit;
	bool creditsRolling;
	bool settingsMenu;

	//Animation
	int flameAnim;
	float flameScale;
	int animSteps;
	bool animAscend;
};

#endif