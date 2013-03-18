#ifndef TEXTCLASS
#define TEXTCLASS

#include "Misc.h"
#include <SFML/Graphics.hpp>

//namespace sd
//{
	class TextClass : public Misc
	{
	public:
		TextClass(void);
		~TextClass(void);

		void initScoreText();

		void updateText();
		void drawText(sf::RenderWindow* window);
		void addToScore(int scoreAdd);

		//void readScoreFromFile();
		//void writeScoreToFile();

	private:
		sf::Font defaultFont;
		sf::Text scoreText;
		sf::Text lastScoreText;
		sf::Text bestScoreText;

		sf::Text initText;

		unsigned long score;
		unsigned long lastScore;
		unsigned long bestScore;

	};
//}

#endif

