#include <SFML\Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

#ifndef ENTIDAD_H
#define ENTIDAD_H

class Entidad
{
protected:
	Image imagen;
	Sprite sprite;

public:
	//Getters
	inline Sprite getSprite() { return sprite; };
};

#endif