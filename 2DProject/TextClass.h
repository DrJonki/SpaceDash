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

#include "SoundClass.h"

#include <SFML/OpenGL.hpp>

//namespace sd
//{
	class TextClass : public SoundClass
	{
	public:
		TextClass(void);
		~TextClass(void);

		void initScoreText();
		void readScoreFromFile();
		void writeScoreToFile();

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
		
		unsigned long bestScoreEasy;
		unsigned long bestScoreMedium;
		unsigned long bestScoreHard;
		unsigned long bestScoreEasyHC;
		unsigned long bestScoreMediumHC;
		unsigned long bestScoreHardHC;

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

		//Scores
		unsigned long score;
		unsigned long lastScore;
		unsigned long bestScore;

		bool firstInit;

		short fuelCounter;
		short fuelWarningCounter;
		short healthWarningCounter;
	};
//}

#endif

