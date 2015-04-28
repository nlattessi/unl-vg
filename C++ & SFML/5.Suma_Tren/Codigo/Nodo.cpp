#include "Nodo.h"

Nodo::Nodo( int valor_, sf::Sprite sprite_, Nodo *sig_ )
{
	valor = valor_;
	sprite = sprite_;
	sig = sig_;
}

Nodo::~Nodo()
{
}

sf::Sprite Nodo::getSprite()
{
	return sprite;
}

void Nodo::setSpritePosition( float x, float y )
{
	sprite.setPosition( x, y );
}

int Nodo::getValor()
{
	return valor;
}