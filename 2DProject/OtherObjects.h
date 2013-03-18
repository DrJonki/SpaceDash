#ifndef OTHER_OBJECTS
#define OTHER_OBJECTS

#include "TextClass.h"
#include "SoundClass.h"
#include <SFML/Graphics.hpp>

//namespace sd
//{
	class OtherObjects : public TextClass, public SoundClass
	{
	public:

		OtherObjects(void);
		~OtherObjects(void);

		//Background
		void initBackground();
		void updateBackground();
		void drawBackground(sf::RenderWindow* window);

		//Borders
		void initBorders();
		void updateBorders();
		void drawBorders(sf::RenderWindow* window);

		//Obstacles
		void initObstacleObjects();
		void updateObstacles();
		void drawObstacles(sf::RenderWindow* window);
		int getNumberOfObstacles();
		sf::Sprite getObstacleObject(int count);

		//Bonus objects
		void initBonusObjects();
		void updateBonusObjects();
		void drawBonusObjects(sf::RenderWindow* window);

		//Star
		void resetStar();
		sf::Sprite getStarSprite();

	private:
		//Resoures
		sf::Texture backgroundTexture;
		sf::Texture debrisTextureTop;
		sf::Texture debrisTextureBottom;
		sf::Texture starTexture;
		sf::Texture obstacleTexture;

		sf::Sprite backgroundSprite[2];
		sf::Sprite debrisSprite[4];

		sf::Sprite starSprite;

		static const int numberOfObstacles = 20;
		sf::Sprite obstacle[numberOfObstacles];
		float obstacleScaleMin;
		float obstacleScaleMax;

	protected:
		double obstacleBaseSpeed;
	};
//}


#endif