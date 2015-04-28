#ifndef FRAME_H
#define FRAME_H

#include <SFML\Graphics\Rect.hpp>

class Frame
{
	public:
		Frame(sf::IntRect rect, sf::Vector2f offset);

	private:
		sf::IntRect rect;
		sf::Vector2f offset;
		// Para que las clases SpriteSheetManager y Animation puedan acceder a sus atributos
		friend class SpriteSheetManager;
		friend class Animation;
};

#endif