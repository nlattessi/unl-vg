#ifndef DISPAROS_H
#define DISPAROS_H

#include <list>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Sprite.hpp>

#include "TextureManager.h"
#include "Animation.h"

class Disparo : public sf::Sprite
{
	public:
		Disparo(float x0, float y0, float velx );
		friend class ManejadorDisparos;

	private:
		float velx;
};

class ManejadorDisparos
{
	public:
		void updateDisparos(float dt, sf::FloatRect &r);
		void agregarDisparo(float x, float y, float vel);
		void drawDisparos(sf::RenderWindow &w);
		
		ManejadorDisparos();

	private:
		std::list<Disparo> disparos;
		
		void flipX( Disparo& disparo );
};

#endif