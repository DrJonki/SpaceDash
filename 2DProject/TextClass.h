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
#include <SFML/Graphics.hpp>

//namespace sd
//{
	class TextClass : public Misc
	{
	public:
		TextClass(void);
		~TextClass(void);

		void initScoreText();

		void updateText();
		void drawText(sf::RenderWindow* window);
		void addToScore(int scoreAdd);

		//void readScoreFromFile();
		//void writeScoreToFile();

	private:
		sf::Font defaultFont;
		sf::Text scoreText;
		sf::Text lastScoreText;
		sf::Text bestScoreText;

		sf::Text initText;

		unsigned long score;
		unsigned long lastScore;
		unsigned long bestScore;

	};
//}

#endif

