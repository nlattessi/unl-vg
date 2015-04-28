#ifndef NODO_H
#define NODO_H

#include <iostream>

#include <SFML\Graphics.hpp>

class Nodo 
{
	public:
		Nodo( int valor_, sf::Sprite sprite_, Nodo *sig_ = NULL );
		~Nodo();

		sf::Sprite	getSprite();
		void		setSpritePosition( float x, float y );
		int			getValor();

	private:
		int			valor;
		sf::Sprite	sprite;
		Nodo*		sig;

	friend class Lista;
	friend class Game;
};

#endif