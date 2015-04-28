#include "Player.h"

//Player::Player( std::string spriteSheetFile, ManejadorDisparos *disparos )
Player::Player( std::string spriteSheetFile, ManejadorDisparos *disparos, Nivel *n )
: velX( 50.f )
, initJumpForce( -250.f ), gravity( 450.f )
, velDisparo( 100.f ), shoot_time( 1.f )
{
	this->setTexture( TextureManager::GetInstance().GetTexture( spriteSheetFile ) );
	ssm.Load( spriteSheetFile, 12, 6 );
	//ssm.loadFromJson( jsonFile );
	initAnimaciones();
	estado = ESTADO::QUIETO;
	direccion = 1;
	shootTime = 0.0f;
	this->disparos = disparos;
	this->n = n;
}

void Player::update( JOYSTICK j, float dt )
{
	// la distancia devuelta por ChocaraPared(), ChocaraSuelo(), etc
	float distAjuste;

	switch ( estado ) 
	{
		case ESTADO::QUIETO:
			if ( j.left ) {
				direccion = -1;

				if ( !ChocaraPared( dt, distAjuste ) )
					cambiarEstado( ESTADO::CORRIENDO );
				else
					this->move( distAjuste, 0 );

			} else if ( j.right ) {
				direccion = 1;

				if ( !ChocaraPared( dt, distAjuste ) )
					cambiarEstado( ESTADO::CORRIENDO );
				else
					this->move( distAjuste, 0 );

			}

			if ( checkDisparo( j ) ) {
				disparar();
				cambiarEstado( ESTADO::DISPARANDO );
			}

			// si no hay suelo debajo, empezamos a caer
			if ( !ChocaraSuelo( dt, distAjuste ) ) {
				velY = 0;
				cambiarEstado( ESTADO::SALTANDO );
			}

			if ( checkSalto( j ) ) {
				saltar();
				cambiarEstado( ESTADO::SALTANDO );
			}
			break;

		case ESTADO::CORRIENDO:
			if ( checkDisparo( j ) ) {
				disparar();
				cambiarEstado( ESTADO::DISPARANDO );
			}

			if ( checkQuieto( j ) ) {
				cambiarEstado( ESTADO::QUIETO );
			} else if ( j.left ) {
				direccion = -1;

				if ( ChocaraPared( dt, distAjuste ) ) {
					cambiarEstado( ESTADO::QUIETO );
					this->move( -distAjuste, 0 );
				}

			} else if ( j.right ) {
				direccion = 1;

				if ( ChocaraPared( dt, distAjuste ) ) {
					cambiarEstado( ESTADO::QUIETO );
					this->move( distAjuste, 0 );
				}

			}

			// si no hay suelo debajo, empezamos a caer
			if ( !ChocaraSuelo( dt, distAjuste ) ) {
				velY = 0;
				cambiarEstado( ESTADO::SALTANDO_CORRIENDO );
			}

			if ( checkSalto( j ) ) {
				saltar();
				cambiarEstado( ESTADO::SALTANDO_CORRIENDO );
			}
			break;

		case ESTADO::DISPARANDO:
			if ( secuenciaFinalizada( shootTime ) ) {
				cambiarEstado( ESTADO::QUIETO );
			}
			break;

		case ESTADO::SALTANDO:
			if ( j.left ) {
				direccion = -1;

				if ( !ChocaraPared( dt, distAjuste ) )
					cambiarEstado( ESTADO::SALTANDO_CORRIENDO );
				else
					this->move( distAjuste, 0 );

			} else if ( j.right ) {
				direccion = 1;
				
				if ( !ChocaraPared( dt, distAjuste ) )
					cambiarEstado( ESTADO::SALTANDO_CORRIENDO );
				else
					this->move( distAjuste, 0 );
			}

			//if ( checkDisparo( j ) ) {
			//	disparar();
			//	cambiarEstado( ESTADO::SALTANDO_DISPARANDO );
			//}
			
			//if ( colisionConSuelo() ) {
			//	cambiarEstado( ESTADO::QUIETO );
			//}
			
			if ( ChocaraSuelo( dt, distAjuste ) ) {
				velY = 0;
				cambiarEstado( ESTADO::QUIETO );
				this->move( 0, distAjuste );
			} else if ( ChocaraTecho( dt, distAjuste ) ) {
				velY = 0;
				this->move( 0, distAjuste );
			}

			break;

		case ESTADO::SALTANDO_CORRIENDO:
			if ( checkQuieto( j ) ) {
				cambiarEstado( ESTADO::SALTANDO );
			} else if ( j.left ) {
				direccion = -1;

				if ( ChocaraPared( dt, distAjuste ) ) {
					this->move( distAjuste, 0 );
					cambiarEstado( ESTADO::SALTANDO );
				}

			} else if ( j.right ) {
				direccion = 1;

				if ( ChocaraPared( dt, distAjuste ) ) {
					this->move( distAjuste, 0 );
					cambiarEstado( ESTADO::SALTANDO );
				}

			}
			
			//if ( checkDisparo( j ) ) {
			//	disparar();
			//	cambiarEstado( ESTADO::SALTANDO_DISPARANDO );
			//}
			
			//if ( colisionConSuelo() ) {
			//	cambiarEstado( ESTADO::QUIETO );
			//}

			if (  ChocaraSuelo( dt, distAjuste ) ) {
				velY = 0;
				this->move( 0, distAjuste );
				cambiarEstado( ESTADO::CORRIENDO );
			} else if ( ChocaraTecho( dt, distAjuste ) ) {
				velY = 0;
				this->move( 0, distAjuste );
			}

			break;

		default:
			break;
	}
	
	if ( estado == ESTADO::CORRIENDO || estado == ESTADO::SALTANDO_CORRIENDO ) {
		this->move( direccion * velX * dt, 0 );
	}

	if ( estado == ESTADO::SALTANDO || estado == ESTADO::SALTANDO_CORRIENDO ) {
		velY += gravity * dt;
		this->move( 0, velY * dt );
	}

	this->n->colisionItem(this->GetAABB());

	if ( !secuenciaFinalizada( shootTime ) ) shootTime -= dt;

	this->setTextureRect( animaciones[estado].Animate( dt ) );
	
	flipX();
}

void Player::cambiarEstado( ESTADO nuevoEstado, bool continueFromCurrent )
{
	ESTADO viejoEstado = estado;
	estado = nuevoEstado;
	animaciones[nuevoEstado].Reset();
	if( continueFromCurrent ) {
		// seteamos el frame de la nueva animacion
		animaciones[nuevoEstado].SetCurrentFrameNum( animaciones[viejoEstado].GetCurrentFrameNum() );
		// seteamos el tiempo del frame de la nueva animacion al mismo tiempo que tenia la anterior
		animaciones[nuevoEstado].Animate( animaciones[viejoEstado].GetCurrentFrameElapsedTime() );
	}
}

void Player::initAnimaciones()
{
	//QUIETO
	animaciones[ESTADO::QUIETO].AddFrame( ssm.GetRect( 0 ), 1.f );
	//animaciones[ESTADO::QUIETO].SetLoop( false );
	
	//CORRIENDO
	for ( int i = 1; i <= 8; i++ ) {
		animaciones[ESTADO::CORRIENDO].AddFrame( ssm.GetRect( i ), 0.2f );
	}
	//DISPARANDO
	for ( int i = 21; i <= 23; i++ ) {
		animaciones[ESTADO::DISPARANDO].AddFrame( ssm.GetRect( i ), 0.3f );
	//animaciones[ESTADO::DISPARANDO].SetLoop( false );
	}
	//SALTANDO
	animaciones[ESTADO::SALTANDO].AddFrame( ssm.GetRect( 8 ), 1.f );
	//SALTANDO_CORRIENDO
	animaciones[ESTADO::SALTANDO_CORRIENDO].AddFrame( ssm.GetRect( 8 ), 1.f );
}

void Player::flipX()
{
	sf::IntRect rect = this->getTextureRect();
	if ( direccion == -1 ) {
		this->setTextureRect( 
			sf::IntRect(
			rect.left + rect.width,
			rect.top,
			-rect.width,
			rect.height
			)
		);
	}
}

void Player::saltar()
{
	velY = initJumpForce;
	posY = this->getPosition().y;
}

bool Player::colisionConSuelo()
{
	float y = this->getPosition().y;

	if ( y >= posY ) {
		this->setPosition( this->getPosition().x, posY );
		return true;
	} else return false;
}

void Player::disparar()
{
	float x;
	if (direccion == 1) {
		x = this->getGlobalBounds().left + this->getGlobalBounds().width -1 * direccion;
	} else
		x = this->getGlobalBounds().left;
	
	float y = this->getGlobalBounds().top + 10;
	shootTime = shoot_time;
	disparos->agregarDisparo( x, y, velDisparo * direccion );
}

bool Player::secuenciaFinalizada( float time )
{
	return ( time < 0.f );
}

bool Player::checkDisparo( JOYSTICK j )
{
	if ( j.b && !j.pressingB && secuenciaFinalizada( shootTime ) ) {
		return true;
	} else {
		return false;
	}
}

bool Player::checkSalto( JOYSTICK j )
{
	if ( j.a && !j.pressingA ) {
		return true;
	} else {
		return false;
	}
}

bool Player::checkQuieto( JOYSTICK j )
{
	if ( !j.left && !j.right ) {
		return true;
	} else {
		return false;
	}
}

// saber si choca con alguna pared por derecha o por izquierda
bool Player::ChocaraPared(float dt, float &distAjuste){
	// creamos rectangulos para el bounding box actual
	// y el area de colision
	sf::FloatRect aabb, areaColision;
	
	// conseguimos el bounding box en la posicion actual
	aabb=GetAABB();
	bool chocaPared;
	
	// la distancia que nos moveriamos
	float despl=dt*velX*direccion;
	
	// buscamos el bounding box que tendriamos
	// si nos moviesemos, preguntamos si
	// colisionamos y la distancia
	// que nos podriamos mover sin colisionar (ajuste)
	aabb.left+=despl;
	//aabb.Right+=despl;
	// calculamos si habria colision
	chocaPared=n->HayColision(aabb, areaColision);
	distAjuste=direccion*(dt * velX - areaColision.width);

	if (distAjuste > 17.f ) std::cout<<distAjuste;

	return chocaPared;
}

// saber si choca con el techo
bool Player::ChocaraTecho(float dt, float &distAjuste){
	bool chocaConTecho;
	// calculamos la velocidad que tendriamos
	float newvy=velY+gravity*dt;
	// si estamos cayendo, no podemos chocar con
	// el suelo
	if(newvy>0) return false;
	else{
		sf::FloatRect aabb, areaColision;
		
		// la distancia que nos vamos a mover
		float despl=dt*newvy;
		
		// conseguimos el AABB actual y calculamos
		// el que tendriamos en un instante de tiempo
		aabb=GetAABB();
		aabb=aabb;
		aabb.top+=despl;
		//aabb.Bottom+=despl;
		// calculamos si habria colision
		chocaConTecho=n->HayColision(aabb, areaColision);
		distAjuste=despl+areaColision.height;

		if (distAjuste > 17.f ) std::cout<<distAjuste;
	}
	return chocaConTecho;
}

// saber si chocara con el suelo cuando esta cayendo,
// o si hay suelo debajo
bool Player::ChocaraSuelo(float dt, float &distAjuste){
	bool chocaConSuelo;
	// calculamos la velocidad que tendriamos
	float newvy=velY+gravity*dt;
	// si estamos subiendo, no podemos chocar con
	// el suelo
	if(newvy<0) return false;
	else{
		sf::FloatRect aabb, areaColision;
		aabb=GetAABB();
		// la distancia que nos vamos a mover
		float despl=dt*newvy;
		
		// conseguimos el AABB actual y calculamos
		// el que tendriamos en un instante de tiempo
		aabb.top+=despl;
		//aabb.Bottom+=despl;
		// calculamos si habria colision
		chocaConSuelo=n->HayColision(aabb, areaColision);
		distAjuste=despl-areaColision.height;

		if (distAjuste > 17.f ) std::cout<<distAjuste;
	}
	return chocaConSuelo;	
}

#ifndef round
 #define round(r) r-int(r)>=0.5?int(r)+1:int(r)
#endif
// devuelve el Axis-Aligned Bounding Box para megaman
sf::FloatRect Player::GetAABB(){
	//sf::Vector2f p = this->getPosition();
	//return sf::FloatRect(round(p.x-10), round(p.y-10), round(p.x+8), round(p.y+16));
	return this->getGlobalBounds();
}