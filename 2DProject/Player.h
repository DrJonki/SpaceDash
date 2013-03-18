#ifndef PLAYER
#define PLAYER

#include "OtherObjects.h"
#include <SFML/Graphics.hpp>

//namespace sd
//{
	class Player : public OtherObjects
	{
	public:
		Player(void);
		~Player(void);

		//Player
		void initPlayer();
		void updatePlayer();
		void drawPlayer(sf::RenderWindow & window);

		//Flames
		void drawFlames(sf::RenderWindow & window); 

	private:
		sf::Texture playerTexture;
		sf::Sprite playerSprite;

		sf::Texture flameTexture;
		sf::Sprite flameSpriteTop;
		sf::Sprite flameSpriteBottom;
	
		double playerRotation;
		double playerSpeed;

		int topFlameCounter;
		int bottomFlameCounter;

		double baseClimingSpeed;
		double baseFallingSpeed;

		int flameAnim;
		float flameScale;
		int animSteps;
		bool animAscend;
	};
//}

#endif