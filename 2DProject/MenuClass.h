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

#include "TextClass.h"

class MenuClass : public TextClass
{
public:
	MenuClass();
	~MenuClass();

	bool showMenu();

private:
	//Graphics
	Texture shadeTexture;
	Sprite shadeSprite;
	Texture logoTexture;
	Sprite logoSprite;
	Texture rocketTexture;
	Texture flameTexture;
	Sprite rocketSprite;
	Sprite flameSpriteTop;
	Sprite flameSpriteBottom;


	//Text stuff
	Font defaultFont;
	RectangleShape infoBackground;
	//Main menu text
	Text playButtonText;
	Text exitButtonText;
	Text scoreButtonText;
	Text optionsButtonText;
	Text creditsButtonText;
	Text backButtonText;
	//Sub menu texts
	Text scoreText[7];
	Text optionsText[13];
	Text creditsText[2];
	Text infoText;
	Text resetText;


	//Movement logic
	float distanceLeftRocket;
	float rocketDestination;
	float distanceLeftLogo;
	float logoDestination;


	//Star background
	static const int numberOfStars = 75;
	RectangleShape starShape[numberOfStars];
	float starSpeed[numberOfStars];


	//Functions
	void initGraphics(RenderWindow &menuWindow, bool firstInit);
	void updateGraphics(RenderWindow &menuWindow);
	void drawGraphics(RenderWindow &menuWindow);
	void closeMenu();
	bool mouseIsOnMenu(RenderWindow &menuWindow);
	bool mouseIsOnButton(RenderWindow &menuWindow, Text *text);
	void scoreMenu(RenderWindow &window, bool init);
	void optionsMenu(RenderWindow &window, bool init);
	void creditsMenu(RenderWindow &window, bool init);


	//System bools
	bool minimized;
	bool inSubMenu;
	
	bool inCreditsMenu;
	bool inOptionsMenu;
	bool inScoreMenu;


	//Animation
	int flameAnim;
	float flameScale;
	int animSteps;
	bool animAscend;
};

#endif