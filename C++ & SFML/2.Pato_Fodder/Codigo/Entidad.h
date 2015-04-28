#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <sstream>

#ifndef ENTIDAD_H
#define ENTIDAD_H

class Entidad
{
protected:
	sf::Sprite sprite;

public:
	inline sf::Sprite getSprite() { return sprite; };
};

#endif