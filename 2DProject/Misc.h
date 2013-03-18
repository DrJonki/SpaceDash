#ifndef MISC
#define MISC

#include <SFML/Graphics.hpp>

//namespace sd
//{
	class Misc
	{
	public:
		Misc(void);
		~Misc(void);

		void setRandomSeed(int seed);

		void setCrashState(bool state);
		bool getCrashState();
	
		void setExitState(bool state);
		bool getExitState();

		float getRandom(float randMin, float randMax);

		bool objectCollision(sf::RectangleShape *object1, sf::RectangleShape *object2);
		bool playerCollision(sf::Sprite *object1, sf::Sprite *object2);
		bool spriteCollision(sf::Sprite *object1, sf::Sprite *object2);

	private:
		bool crashState;
		bool exitState;

	};
//}

#endif