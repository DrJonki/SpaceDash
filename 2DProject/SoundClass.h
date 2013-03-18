#ifndef SOUNDCLASS
#define SOUNDCLASS

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

	private:
		sf::Music music;
	};
//}

#endif

