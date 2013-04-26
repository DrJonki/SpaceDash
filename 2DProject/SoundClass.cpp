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

#include "SoundClass.h"


SoundClass::SoundClass()
{
	srand(time(NULL));

	music.setVolume(0);
	menuMusic.setVolume(0);

	alarmSoundBuffer.loadFromFile("Resources/Audio/alarm.wav");
	alarmSound.setBuffer(alarmSoundBuffer);
	alarmSound.setVolume(80);
	alarmSound.setPitch(1.4);

	scoreSoundBuffer.loadFromFile("Resources/Audio/scoresound.wav");
	scoreSound.setBuffer(scoreSoundBuffer);
	scoreSound.setVolume(70);
	scoreSound.setPitch(1.2);

	fuelSoundBuffer.loadFromFile("Resources/Audio/fuelsound.wav");
	fuelSound.setBuffer(fuelSoundBuffer);
	fuelSound.setVolume(99);
	fuelSound.setPitch(1.5);

	healSoundBuffer.loadFromFile("Resources/Audio/healsound.wav");
	healSound.setBuffer(healSoundBuffer);
	healSound.setVolume(99);
	healSound.setPitch(1.2);

	shutdownSoundBuffer.loadFromFile("Resources/Audio/shutdown.wav");
	shutdownSound.setBuffer(shutdownSoundBuffer);
	shutdownSound.setVolume(90);
	shutdownSound.setPitch(0.9);

	rocketSoundBuffer.loadFromFile("Resources/Audio/rocketsound.wav");
	rocketSound.setBuffer(rocketSoundBuffer);
	rocketSound.setVolume(90);

	explosionSoundBuffer.loadFromFile("Resources/Audio/explosion.wav");
	explosionSound.setBuffer(explosionSoundBuffer);
	explosionSound.setVolume(80);

	crashSoundBuffer.loadFromFile("Resources/Audio/crashsound.wav");
	crashSound.setBuffer(crashSoundBuffer);
	crashSound.setVolume(99);

	/*explosionSoundBuffer2.loadFromFile("Resources/Audio/bang.wav");
	explosionSound2.setBuffer(explosionSoundBuffer2);
	explosionSound2.setVolume(90);*/
}
SoundClass::~SoundClass(){}


void SoundClass::updateMusic()
{
	int number = 1 + (int)rand()/((int)RAND_MAX/(9-(1)));

	if (music.getStatus() == Music::Stopped && playMusic){

		switch (number){
			case 1:
				music.openFromFile("Resources/Audio/music1.wav");
				music.setVolume(70); //Set
				break;
			case 2:
				music.openFromFile("Resources/Audio/music2.wav");
				music.setVolume(85); //Set
				break;
			case 3:
				music.openFromFile("Resources/Audio/music3.wav");
				music.setVolume(45); //Set
				break;
			case 4:
				music.openFromFile("Resources/Audio/music4.wav");
				music.setVolume(37); //Set
				break;
			case 5:
				music.openFromFile("Resources/Audio/music5.wav");
				music.setVolume(57); //Set
				break;
			case 6:
				music.openFromFile("Resources/Audio/music6.wav");
				music.setVolume(47); //Set
				break;
			case 7:
				music.openFromFile("Resources/Audio/music7.wav");
				music.setVolume(37); //Set
				break;
			case 8:
				music.openFromFile("Resources/Audio/music8.wav");
				music.setVolume(60); //Set
				break;
			default:
				music.openFromFile("Resources/Audio/music7.wav");
				music.setVolume(37); //Set
				break;
		}
		music.play();
	}
}

void SoundClass::updateMenuMusic()
{
	if (menuMusic.getVolume() < 75) menuMusic.setVolume(menuMusic.getVolume() + 0.2);

	if (menuMusic.getStatus() == sf::Music::Stopped && playMusic){
		menuMusic.openFromFile("Resources/Audio/menumusic.wav");
		menuMusic.play();
	}
}

void SoundClass::stopMusic()
{
	music.stop();
	music.setVolume(0);
}
void SoundClass::stopMenuMusic()
{
	menuMusic.stop();
	menuMusic.setVolume(0);
}

void SoundClass::updateAlarmSound()
{
	if (alarmSound.getStatus() == sf::Sound::Stopped && playSound){
		alarmSound.play();
	}
}
void SoundClass::stopAlarmSound()
{
	alarmSound.stop();
}

void SoundClass::playScoreSound()
{
	if (playSound) scoreSound.play();
}
void SoundClass::playFuelSound()
{
	if (playSound){
		fuelSound.play();
		shutdownSound.stop();
	}
}
void SoundClass::playHealSound()
{
	if (playSound) healSound.play();
}
void SoundClass::playShutdownSound()
{
	if (playSound) shutdownSound.play();
}
void SoundClass::playExplosionSound()
{
	if (playSound) explosionSound.play();
}
void SoundClass::stopExplosionSound()
{
	explosionSound.stop();
}
void SoundClass::playExplosionSound2()
{
	if (playSound) explosionSound2.play();
}

void SoundClass::updateRocketSound()
{
	if (rocketSound.getStatus() == Sound::Stopped && playSound){
		rocketSound.play();
	}

	if (Keyboard::isKeyPressed(Keyboard::Space)){
		rocketSound.setVolume(50);
	}
	else {
		rocketSound.setVolume(20);
	}
}
void SoundClass::stopRocketSound()
{
	rocketSound.stop();
}

void SoundClass::updateCrashSound()
{
	if (crashSound.getStatus() == Sound::Stopped && playSound){
		crashSound.play();
	}
}
void SoundClass::stopCrashSound()
{
	crashSound.stop();
}