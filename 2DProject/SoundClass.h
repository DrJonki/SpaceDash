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


#ifndef SOUNDCLASS
#define SOUNDCLASS

#include "Misc.h"
#include <ctime>

#include <SFML/Audio.hpp>

//namespace sd
//{
	class SoundClass : public Misc
	{
	public:
		SoundClass();
		~SoundClass();

		void updateMusic();
		void stopMusic();

		void updateMenuMusic();
		void stopMenuMusic();

		void updateAlarmSound();
		void stopAlarmSound();

		void updateCrashSound();
		void stopCrashSound();

		void playScoreSound();
		void playFuelSound();
		void playHealSound();
		void playShutdownSound();
		void playExplosionSound();
		void stopExplosionSound();
		void playExplosionSound2();

		void updateRocketSound();
		void stopRocketSound();

	private:
		Music music;
		Music menuMusic;

		SoundBuffer alarmSoundBuffer;
		Sound alarmSound;

		SoundBuffer scoreSoundBuffer;
		Sound scoreSound;

		SoundBuffer fuelSoundBuffer;
		Sound fuelSound;

		SoundBuffer healSoundBuffer;
		Sound healSound;

		SoundBuffer shutdownSoundBuffer;
		Sound shutdownSound;

		SoundBuffer rocketSoundBuffer;
		Sound rocketSound;

		SoundBuffer explosionSoundBuffer;
		Sound explosionSound;

		SoundBuffer explosionSoundBuffer2;
		Sound explosionSound2;

		SoundBuffer crashSoundBuffer;
		Sound crashSound;
	};
//}

#endif

