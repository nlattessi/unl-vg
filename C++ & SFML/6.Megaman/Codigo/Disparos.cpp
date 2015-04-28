#include "Disparos.h"

Disparo::Disparo(float x0, float y0, float velx, Animation anim)
{
	this->setPosition(x0, y0);
	this->setTexture( TextureManager::GetInstance().GetTexture( "Data/Disparos.png" ) );
	this->velx = velx;
	this->anim = anim;
}

ManejadorDisparos::ManejadorDisparos()
{
	//Cargo Sprite Sheet
	ssm.loadFromJson( "Data/Disparos.json" );

	//Cargo frames de animacion
	anim0.AddFrame( ssm[0], 1.f );

	anim1.AddFrame( ssm[1], 0.3f );
	anim1.AddFrame( ssm[2], 0.3f );

	anim2.AddFrame( ssm[3], 0.1f );
	anim2.AddFrame( ssm[4], 0.1f );
	anim2.AddFrame( ssm[5], 0.2f );
	anim2.AddFrame( ssm[6], 0.1f );
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
			//Animo el disparo
			it->setTextureRect( it->anim.animateNew( dt ) );
			it->setOrigin( it->anim.getOffset() );
			flipX( *it );
			it++;
		}
	}
}

void ManejadorDisparos::agregarDisparo( float x, float y, float vel, int arma )
{
	//Segun el arma creo el disparo con la animacion correspondiente
	switch ( arma ) {
		case 0:
			disparos.insert( disparos.end(), Disparo( x, y, vel, anim0 ) );
			break;
		case 1:
			disparos.insert( disparos.end(), Disparo( x, y, vel, anim1 ) );
			break;
		case 2:
			disparos.insert( disparos.end(), Disparo( x, y, vel, anim2 ) );
			break;
		default:
			break;
	}
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