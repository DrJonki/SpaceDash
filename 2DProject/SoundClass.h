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

#include <ctime>

#include <SFML/Audio.hpp>

//namespace sd
//{
	class SoundClass
	{
	public:
		SoundClass(void);
		~SoundClass(void);

		void updateMusic();
		void stopMusic();

		void updateMenuMusic();
		void stopMenuMusic();

	private:
		sf::Music music;
		sf::Music menuMusic;
	};
//}

#endif

