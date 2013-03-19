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

#include "TextClass.h"


TextClass::TextClass(void)
{
	score = 0;
	lastScore = 0;
	bestScore = 0;

	if (!defaultFont.loadFromFile("Resources/Misc/font.ttf")){
		MessageBox(NULL, L"Failed to load font!", L"Error", MB_OK );
	}
}
TextClass::~TextClass(void){}

void TextClass::initScoreText()
{
	lastScore = score;
	score = 0;
	
	initText.setFont(defaultFont);
	initText.setString("1234567890abcdefghijklmnstuvwxyz");
	initText.setCharacterSize(26);
	initText.setColor(Color::Cyan);
	initText.setPosition(10, 10);

	//Score
	scoreText.setFont(defaultFont);
	scoreText.setCharacterSize(26);
	scoreText.setColor(Color::Cyan);
	scoreText.setPosition(50, 50);

	//Last score
	lastScoreText.setFont(defaultFont);
	lastScoreText.setCharacterSize(26);
	lastScoreText.setColor(Color::Cyan);
	lastScoreText.setPosition(50, 100);

	//Best Score
	bestScoreText.setFont(defaultFont);
	bestScoreText.setCharacterSize(26);
	bestScoreText.setColor(Color::Cyan);
	bestScoreText.setPosition(50, 125);
}

void TextClass::updateText()
{
	std::stringstream ss;

	//Score
	score++;
	ss.str("");
	ss << "Current score: " << score / 10;
	scoreText.setString(ss.str());


	//Last score
	ss.str("");
	ss << "Last score: " << lastScore / 10;
	lastScoreText.setString(ss.str());


	//Best score
	if (bestScore < score) bestScore = score;
	ss.str("");
	ss << "Best score: " << bestScore / 10;
	bestScoreText.setString(ss.str());
}

void TextClass::drawText(RenderWindow* window)
{
	window->draw(scoreText);
	window->draw(lastScoreText);
	window->draw(bestScoreText);
}

void TextClass::addToScore(int scoreAdd)
{
	score += scoreAdd;
}

//void TextClass::readScoreFromFile() {
//	std::string Str;
//	std::ifstream Stream;
//	Stream.open("Scores.txt");
//	if (Stream.is_open()) {
//		int Len = Stream.tellg();
//		while (Stream.good()) {
//			WCHAR S[256];
//			Stream.getline(S, 256);
//			Str += S;
//			Str += L"\n";
//		};
//		Stream.close();
//	}
//	std::stringstream SS(Str);
//	SS >> bestScore;
//}
//
//void TextClass::writeScoreToFile() {
//	std::stringstream SS;
//	SS << bestScore;
//	std::ofstream Stream;
//	Stream.open("Scores.txt");
//	if (Stream.is_open()) {
//		Stream.write(SS.str(),SS.str().size());
//		Stream.close();
//	}
//}
