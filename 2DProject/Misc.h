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


#ifndef MISC
#define MISC

#include <cstdlib>
#include <cmath>
#include <sstream>
#include <fstream>
#include <iostream>
#include <Windows.h>

#include <SFML/Graphics.hpp>
using namespace sf;


//namespace sd
//{
	class Misc
	{
	public:
		Misc();
		~Misc();

		void setRandomSeed(int seed);

		void setExplosionState(bool state);
		bool getExplosionState();

		void setCrashState(bool state);
		bool getCrashState();
	
		void setExitState(bool state);
		bool getExitState();

		float getRandom(float randMin, float randMax);

		bool playerCollision(CircleShape *object1, CircleShape *object2);
		bool spriteCollision(Sprite *object1, Sprite *object2);

		void readSettingsFromFile();
		void writeSettingsToFile();

		//Settings
		bool vSync;

		short difficulty;
		bool hardcore;

		bool showParticles;

		bool playSound;
		bool playMusic;

	private:
		bool explosionState;
		bool crashState;
		bool exitState;

	};
//}

#endif