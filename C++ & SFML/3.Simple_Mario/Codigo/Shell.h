#ifndef SHELL_H
#define SHELL_H

#include <iostream>

#include <SFML\Graphics.hpp>

class Shell
{
	public:
		Shell();
		~Shell();

		sf::Sprite getSprite();
		void setPosicion( float x, float y );
		void setSprite( sf::Sprite sprite_ );
		void setTexture( const sf::Texture &textura);

		void Update( float delta_time_seconds );
		void cambiarDireccion();
		bool isLeft();

	private:
		sf::Sprite	sprite;
		float		speedX;
		bool		toLeft;
};

#endif