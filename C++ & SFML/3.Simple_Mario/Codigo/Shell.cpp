#include "Shell.h"

Shell::Shell()
{
	// Randomizo la velocidad de cada Shell para hacerlo mas desafiante.
	speedX = (float)(100 + rand()%(401 - 100));
	toLeft = false;
}

Shell::~Shell()
{
}

sf::Sprite Shell::getSprite()
{
	return sprite;
}

void Shell::setPosicion( float x, float y )
{
	sprite.setPosition( x, y );
}

void Shell::setSprite( sf::Sprite sprite_ )
{
	sprite = sprite_;
}

void Shell::setTexture( const sf::Texture &textura )
{
	sprite.setTexture( textura );
}

void Shell::Update( float delta_time_seconds )
{
	if ( toLeft ) {
		sprite.move( -1.0f * speedX * delta_time_seconds, 0.0f );
	} else {
		sprite.move( 1.0f * speedX * delta_time_seconds, 0.0f );
	}
}

void Shell::cambiarDireccion()
{
	if ( toLeft )
		toLeft = false;
	else { 
		toLeft = true;
	}
}

bool Shell::isLeft()
{
	if ( toLeft ) {
		return true;
	} else {
		return false;
	}
}