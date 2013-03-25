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


#ifndef TEXTCLASS
#define TEXTCLASS

#include "Misc.h"
#include "SoundClass.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <Windows.h>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
using namespace sf;

//namespace sd
//{
	class TextClass : public Misc, public SoundClass
	{
	public:
		TextClass(void);
		~TextClass(void);

		void initScoreText();

		void updateText();
		void drawText(sf::RenderWindow &window);
		void drawPauseText(RenderWindow &window);
		void addToScore(int scoreAdd);

		short getPlayerHealth();
		int getPlayerFuel();
		void decreaseHealth(const unsigned short amount);
		void increaseHealth(const unsigned short amount);
		void decreaseFuel(const unsigned short amount);
		void increaseFuel(const unsigned short amount);

	private:
		sf::Font defaultFont;
		sf::Text scoreText;
		sf::Text lastScoreText;
		sf::Text bestScoreText;
		Text initText;
		Text healthText;
		Text fuelText;

		Text pauseText[2];
		Text infoText;

		short playerHealth;
		short playerFuel;

		unsigned long score;
		unsigned long lastScore;
		unsigned long bestScore;

		void readScoreFromFile();
		void writeScoreToFile();

		void readSettingsFromFile();
		void writeSettingsToFile();

		bool firstInit;

		short fuelCounter;
		short fuelWarningCounter;
		short healthWarningCounter;
	};
//}

#endif

