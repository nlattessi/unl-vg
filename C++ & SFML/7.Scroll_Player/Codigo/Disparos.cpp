#include "Disparos.h"

Disparo::Disparo( float x0, float y0, float velx )
{
	this->setPosition(x0, y0);
	this->setTexture( TextureManager::GetInstance().GetTexture( "Media/bullet1.png" ) );
	this->velx = velx;
}

ManejadorDisparos::ManejadorDisparos()
{
}

void ManejadorDisparos::updateDisparos(float dt, sf::FloatRect &r)
{
	std::list<Disparo>::iterator it = disparos.begin();
	float disparoX;
	while ( it != disparos.end() ) {
		disparoX = (*it).getPosition().x;
		if ( ( disparoX < r.left ) || ( disparoX > ( r.left + r.width ) ) ) {
			it = disparos.erase( it );
		} else {
			it->move( it->velx * dt, 0 );
			flipX( *it );
			it++;
		}
	}
}

void ManejadorDisparos::agregarDisparo( float x, float y, float vel )
{
	disparos.insert( disparos.end(), Disparo( x, y, vel ) );
}

void ManejadorDisparos::drawDisparos( sf::RenderWindow &w )
{
	std::list<Disparo>::iterator it = disparos.begin();
	while ( it != disparos.end() ) {
		w.draw( *it );
		it++;
	}
}

void ManejadorDisparos::flipX( Disparo& disparo )
{
	sf::IntRect rect = disparo.getTextureRect();
	if ( disparo.velx < 0 ) {
		disparo.setTextureRect(
			sf::IntRect(
			rect.left + rect.width,
			rect.top,
			-rect.width,
			rect.height
			)
		);
	}
}