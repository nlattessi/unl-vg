#ifndef DISPAROS_H
#define DISPAROS_H

#include <list>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include "TextureManager.h"
#include "Animation.h"
#include "SpriteSheetManager.h"

class Disparo : public sf::Sprite
{
	public:
		Disparo(float x0, float y0, float velx, Animation anim );
		friend class ManejadorDisparos;

	private:
		float velx;
		Animation anim;
};

class ManejadorDisparos
{
	public:
		void updateDisparos(float dt, sf::FloatRect &r);
		void agregarDisparo(float x, float y, float vel);
		void agregarDisparo(float x, float y, float vel, int arma );
		void drawDisparos(sf::RenderWindow &w);
		
		ManejadorDisparos();

	private:
		std::list<Disparo> disparos;
		SpriteSheetManager ssm;
		
		/*
		anim0: Normal
		anim1: Buster
		anim2: Mega Buster
		*/
		Animation anim0, anim1, anim2;

		void flipX( Disparo& disparo );
};

#endif