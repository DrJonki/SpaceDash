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

	bestScoreEasy = 0;
	bestScoreMedium = 0;
	bestScoreHard = 0;
	bestScoreEasyHC = 0;
	bestScoreMediumHC = 0;
	bestScoreHardHC = 0;

	firstInit = true;

	playerHealth = 100;
	playerFuel = 100;

	fuelCounter = 0;
	fuelWarningCounter = 0;
	healthWarningCounter = 0;

	if (!defaultFont.loadFromFile("Resources/Misc/font.otf")){
		MessageBox(NULL, L"Failed to load font!", L"Error", MB_OK );
	}
}
TextClass::~TextClass(void)
{
	writeScoreToFile();
}

void TextClass::initScoreText()
{
	if (!firstInit) lastScore = score;
	score = 0;
	playerHealth = 100;
	playerFuel = 100;

	fuelCounter = 0;
	fuelWarningCounter = 0;
	healthWarningCounter = 0;

	stopAlarmSound();

	initText.setFont(defaultFont);
	initText.setString("1234567890abcdefghijklmnstuvwxyz");
	initText.setCharacterSize(26);
	initText.setColor(Color::Cyan);
	initText.setPosition(10, 10);

	healthText.setFont(defaultFont);
	healthText.setCharacterSize(26);
	healthText.setColor(Color::Color(0, 255, 0));
	healthText.setPosition(520 + (playerHealth * 2), 63);

	fuelText.setFont(defaultFont);
	fuelText.setCharacterSize(26);
	fuelText.setColor(Color::Color(0, 255, 0));
	fuelText.setPosition(520 + (playerHealth * 2), 114);

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

	pauseText[0].setFont(defaultFont);
	pauseText[0].setString("PAUSED");
	pauseText[0].setCharacterSize(80);
	pauseText[0].setColor(Color::Yellow);
	pauseText[0].setPosition(450, 300);
	pauseText[1].setFont(defaultFont);
	pauseText[1].setString("SPACE - Start/Continue\nR - Restart\nEscape - Exit");
	pauseText[1].setCharacterSize(40);
	pauseText[1].setColor(Color::Color(255, 153, 0));
	pauseText[1].setPosition(pauseText[0].getPosition().x, pauseText[0].getPosition().y + 120);
	infoText.setFont(defaultFont);
	infoText.setString("------------------------------------------------------\nUSE SPACE BAR TO\nCONTROL THE ROCKET\n\nPRESS ESCAPE DURING\nGAMEPLAY TO PAUSE THE GAME\n\nSCORES WILL BE\nSAVED UPON EXIT\n------------------------------------------------------");
	infoText.setCharacterSize(20);
	infoText.setColor(Color::Cyan);
	infoText.setPosition(50, pauseText[0].getPosition().y + 23);

	updateText();

	firstInit = false;
}

void TextClass::updateText()
{
	std::stringstream ss;

	//Health
	ss.str("");
	if (playerHealth <= 10){
		healthWarningCounter++;
		ss << "!!! " << playerHealth << " !!!";
	}
	else ss << playerHealth;
	healthText.setString(ss.str());
	float tempHealth = playerHealth * 2.55;
	healthText.setColor(Color::Color(255 - tempHealth, tempHealth, 0));

	healthText.setPosition(520 + (playerHealth * 2), 63);

	if (healthWarningCounter <= 5 && playerHealth <= 10) healthText.setColor(Color::Color(236, 20, 20));
	else if(healthWarningCounter > 5 && healthWarningCounter <= 10 && playerHealth <= 10) healthText.setColor(Color::Color(238, 232, 67));

	//Fuel
	if (Keyboard::isKeyPressed(Keyboard::Space)) fuelCounter += difficulty * 2;
	else fuelCounter += difficulty;
	if (fuelCounter >= 60){
		if (playerFuel > 0) playerFuel -= 1;
		fuelCounter = 0;
	}
	ss.str("");
	if (playerFuel <= 10){
		fuelWarningCounter++;
		ss << "!!! " << playerFuel << " !!!";
	}
	else ss << playerFuel;
	fuelText.setString(ss.str());
	float tempFuel = playerFuel * 2.55;
	fuelText.setColor(Color::Color(255 - tempFuel, tempFuel, 0));
	
	if (hardcore) fuelText.setPosition(520 + (playerFuel * 2), 70);
	else fuelText.setPosition(520 + (playerFuel * 2), 114);

	if (fuelWarningCounter <= 5 && playerFuel <= 10) fuelText.setColor(Color::Color(236, 20, 20));
	else if(fuelWarningCounter > 5 && fuelWarningCounter <= 10 && playerFuel <= 10) fuelText.setColor(Color::Color(238, 232, 67));


	//Score
	score += (difficulty * (hardcore + 1));
	ss.str("");
	ss << "Current score: " << score / 10;
	scoreText.setString(ss.str());


	//Last score
	if (lastScore < score) lastScore = score;
	ss.str("");
	ss << "Last score: " << lastScore / 10;
	lastScoreText.setString(ss.str());


	//Best score
	if (bestScore < score) bestScore = score;
	ss.str("");
	ss << "Best score: " << bestScore / 10;
	bestScoreText.setString(ss.str());

	if (fuelWarningCounter >= 10) fuelWarningCounter = 0;
	if (healthWarningCounter >= 10) healthWarningCounter = 0;

	if (playerHealth <= 10 || playerFuel <= 10) updateAlarmSound();
	else stopAlarmSound();

	glFlush();
}

void TextClass::drawText(RenderWindow &window)
{
	window.draw(scoreText);
	window.draw(lastScoreText);
	window.draw(bestScoreText);
	if (!hardcore) window.draw(healthText);
	window.draw(fuelText);
}
void TextClass::drawPauseText(RenderWindow &window)
{
	window.draw(pauseText[0]);
	window.draw(pauseText[1]);
	window.draw(infoText);
}

void TextClass::addToScore(int scoreAdd)
{
	score += scoreAdd;
}

void TextClass::readScoreFromFile()
{
	int count = 0;;
	std::string string;

	std::string path(std::getenv("USERPROFILE"));
	path += "/Documents/SDScores.txt";
	std::ifstream file(path, std::ifstream::in);

	if (file.good()){
		while (!file.eof()){
			if (count == 0){
				std::getline(file, string);
				bestScoreEasy = std::atoi(string.c_str());
				bestScoreEasy *= 10;
			}
			if (count == 1){
				std::getline(file, string);
				bestScoreMedium = std::atoi(string.c_str());
				bestScoreMedium *= 10;
			}
			if (count == 2){
				std::getline(file, string);
				bestScoreHard = std::atoi(string.c_str());
				bestScoreHard *= 10;
			}
			if (count == 3){
				std::getline(file, string);
				bestScoreEasyHC = std::atoi(string.c_str());
				bestScoreEasyHC *= 10;
			}
			if (count == 4){
				std::getline(file, string);
				bestScoreMediumHC = std::atoi(string.c_str());
				bestScoreMediumHC *= 10;
			}
			if (count == 5){
				std::getline(file, string);
				bestScoreHardHC = std::atoi(string.c_str());
				bestScoreHardHC *= 10;
			}
			count++;
		}
	}

	if (difficulty == 1 && !hardcore) bestScore = bestScoreEasy;
	else if (difficulty == 2 && !hardcore) bestScore = bestScoreMedium;
	else if (difficulty == 3 && !hardcore) bestScore = bestScoreHard;
	else if (difficulty == 1 && hardcore) bestScore = bestScoreEasyHC;
	else if (difficulty == 2 && hardcore) bestScore = bestScoreMediumHC;
	else if (difficulty == 3 && hardcore) bestScore = bestScoreHardHC;
}
void TextClass::writeScoreToFile()
{
	if ((difficulty == 1 && !hardcore) && bestScore > bestScoreEasy) bestScoreEasy = bestScore;
	else if ((difficulty == 2 && !hardcore) && bestScore > bestScoreMedium) bestScoreMedium = bestScore;
	else if ((difficulty == 3 && !hardcore) && bestScore > bestScoreHard) bestScoreHard = bestScore;
	else if ((difficulty == 1 && hardcore) && bestScore > bestScoreEasyHC) bestScoreEasyHC = bestScore;
	else if ((difficulty == 2 && hardcore) && bestScore > bestScoreMediumHC) bestScoreMediumHC = bestScore;
	else if ((difficulty == 3 && hardcore) && bestScore > bestScoreHardHC) bestScoreHardHC = bestScore;

	std::string path(std::getenv("USERPROFILE"));
	path += "/Documents/SDScores.txt";

	std::ofstream file;
	file.open(path);
	file << bestScoreEasy / 10 << std::endl;
	file << bestScoreMedium / 10 << std::endl;
	file << bestScoreHard / 10 << std::endl;
	file << bestScoreEasyHC / 10 << std::endl;
	file << bestScoreMediumHC / 10 << std::endl;
	file << bestScoreHardHC / 10;
	file.close();
}

//Health functions
short TextClass::getPlayerHealth()
{
	return playerHealth;
}
void TextClass::decreaseHealth(const unsigned short amount)
{
	playerHealth -= amount;
}
void TextClass::increaseHealth(const unsigned short amount)
{
	playerHealth += amount;

	if (playerHealth > 100){
		playerHealth = playerHealth - (playerHealth - 100);
	}
}

//Fuel functions
int TextClass::getPlayerFuel()
{
	return playerFuel;
}
void TextClass::decreaseFuel(const unsigned short amount)
{
	playerFuel -= amount;
}
void TextClass::increaseFuel(const unsigned short amount)
{
	playerFuel += amount;
	
	if (playerFuel > 100){
		playerFuel = playerFuel - (playerFuel - 100);
	}
}
