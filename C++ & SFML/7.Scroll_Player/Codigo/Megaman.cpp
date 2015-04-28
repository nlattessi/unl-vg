#include "Megaman.h"

Megaman::Megaman( std::string spriteSheetFile, std::string jsonFile, ManejadorDisparos *disparos ) :
	/*ANIM*/ busterLvlChangeTime( 1.2f ), busterAnimChangeTime( 0.4f ), 
	/*MOVX*/ velX( 60.f ),
	/*MOVY*/ initJumpForce( -250.f ), gravity( 450.f ),
	/*SLID*/ slide_time( 1.f ),
	/*DISP*/ velDisparo( 180.f ), shoot_time( 1.f )
{
	this->setTexture( TextureManager::GetInstance().GetTexture( spriteSheetFile ) );
	ssm.loadFromJson( jsonFile );
	initAnimaciones();
	estado = ESTADO::QUIETO;
	busterLvl = BUSTER_LVL::NORMAL;
	busterAnim = BUSTER_ANIM::NORMAL_0;
	busterLvlClock = 0.f; busterAnimClock = 0.f;
	direccion = 1;
	velY = 0.f;
	isFalling = false;
	slideTime = 0.f;
	shootTime = 0.f;
	this->disparos = disparos;
}

void Megaman::update( JOYSTICK j, float dt )
{
	//ESTADO (switch grande)
	switch ( estado )
	{
		case ESTADO::QUIETO:
			if ( j.left ) {
				direccion = -1;
				cambiarEstado( ESTADO::CORRIENDO );
			} else if ( j.right ) {
				direccion = 1;
				cambiarEstado( ESTADO::CORRIENDO );
			}
			if ( checkDisparo( j ) ) {
				disparar();
				cambiarEstado( ESTADO::DISPARANDO );
			} else  if ( checkDisparoBuster( j ) ) {
				dispararBuster();
				cambiarEstado( ESTADO::DISPARANDO );
			}			
			if ( checkSalto( j ) ) {
				if ( j.down ) {
					cambiarEstado( ESTADO::DESLIZANDO );
					slideTime = slide_time;
				} else {
					cambiarEstado( ESTADO::SALTANDO );
					saltar();
				}
			}
			break;

		case ESTADO::CORRIENDO:
			if ( checkDisparo( j ) ) {
				disparar();
				cambiarEstado( ESTADO::CORRIENDO_DISPARANDO, true );
			} else if ( checkDisparoBuster( j ) ) {
				dispararBuster();
				cambiarEstado( ESTADO::CORRIENDO_DISPARANDO, true );
			}
			if ( checkQuieto( j ) ) {
				cambiarEstado( ESTADO::QUIETO );
			} else if ( j.left ) {
				direccion = -1;
			} else if ( j.right ) {
				direccion = 1;
			}
			if ( checkSalto( j ) ) {
				cambiarEstado( ESTADO::SALTANDO_CORRIENDO );
				saltar();
			}
			break;

		case ESTADO::DESLIZANDO:
			if ( checkDisparoBuster( j ) ) {
				dispararBuster();
				cambiarEstado( ESTADO::DISPARANDO );
			}
			if ( secuenciaFinalizada( slideTime ) ) {
				cambiarEstado( ESTADO::QUIETO );
			}
			break;

		case ESTADO::SALTANDO:
			if ( j.left ) {
				direccion = -1;
				cambiarEstado( ESTADO::SALTANDO_CORRIENDO );
			} else if ( j.right ) {
				direccion = 1;
				cambiarEstado( ESTADO::SALTANDO_CORRIENDO );
			}
			if ( checkDisparo( j ) ) {
				disparar();
				cambiarEstado( ESTADO::SALTANDO_DISPARANDO );
			} else if ( checkDisparoBuster( j ) ) {
				dispararBuster();
				cambiarEstado( ESTADO::SALTANDO_DISPARANDO );
			}
			if ( colisionConSuelo() ) {
				cambiarEstado( ESTADO::QUIETO );
			}
			break;

		case ESTADO::DISPARANDO:
			if ( j.left ) {
				direccion = -1;
				cambiarEstado( ESTADO::CORRIENDO_DISPARANDO, true );
			} else if ( j.right ) {
				direccion = 1;
				cambiarEstado( ESTADO::CORRIENDO_DISPARANDO, true );
			}
			if ( secuenciaFinalizada( shootTime ) ) {
				cambiarEstado( ESTADO::QUIETO );
			}
			if ( checkSalto( j ) ) {
				cambiarEstado( ESTADO::SALTANDO );
				saltar();
			}
			break;

		case ESTADO::CORRIENDO_DISPARANDO:
			if ( checkQuieto( j ) ) {
				cambiarEstado( ESTADO::DISPARANDO );
			} else if ( j.left ) {
				direccion = -1;
			} else if ( j.right ) {
				direccion = 1;
			}
			if ( checkSalto( j ) ) {
				cambiarEstado( ESTADO::SALTANDO_CORRIENDO_DISPARANDO );
				saltar();
			}
			if ( secuenciaFinalizada( shootTime ) ) {
				cambiarEstado ( ESTADO::CORRIENDO, true );
			}
			break;

		case ESTADO::SALTANDO_DISPARANDO:
			if ( secuenciaFinalizada( shootTime ) ) {
				cambiarEstado( ESTADO::SALTANDO );
			}
			if ( j.left ) {
				direccion = -1;
				cambiarEstado( ESTADO::SALTANDO_CORRIENDO_DISPARANDO );
			} else if ( j.right ) {
				direccion = 1;
				cambiarEstado( ESTADO::SALTANDO_CORRIENDO_DISPARANDO );
			}
			if ( colisionConSuelo() ) {
				cambiarEstado( ESTADO::DISPARANDO );
			}
			break;

		case ESTADO::SALTANDO_CORRIENDO:
			if ( checkDisparo( j ) ) {
				disparar();
				cambiarEstado( ESTADO::SALTANDO_CORRIENDO_DISPARANDO );
			} else if ( checkDisparoBuster( j ) ) {
				dispararBuster();
				cambiarEstado( ESTADO::SALTANDO_CORRIENDO_DISPARANDO );
			}
			if ( checkQuieto( j ) ) {
				cambiarEstado( ESTADO::SALTANDO );
			} else if ( j.left ) {
				direccion = -1;
			} else if ( j.right ) {
				direccion = 1;
			}
			if ( colisionConSuelo() ) {
				cambiarEstado( ESTADO::CORRIENDO );
			}
			break;

		case ESTADO::SALTANDO_CORRIENDO_DISPARANDO:
			if ( secuenciaFinalizada( shootTime ) ) {
				cambiarEstado ( ESTADO::SALTANDO_DISPARANDO );
			}
			if ( checkQuieto( j ) ) {
				cambiarEstado( ESTADO::SALTANDO_DISPARANDO );
			} else if ( j.left ) {
				direccion = -1;
			} else if ( j.right ) {
				direccion = 1;
			}
			if ( colisionConSuelo() ) {
				cambiarEstado( ESTADO::CORRIENDO_DISPARANDO );
			}
			break;

		default:
			break;
	}
	
	// Según el estado movemos horizontalmente
	if ( 
		( estado == ESTADO::CORRIENDO ) || ( estado == ESTADO::CORRIENDO_DISPARANDO ) ||
		( estado == ESTADO::DESLIZANDO ) || ( estado == ESTADO::SALTANDO_CORRIENDO ) ||
		( estado == ESTADO::SALTANDO_CORRIENDO_DISPARANDO ) || ( estado == ESTADO::SALTANDO_CORRIENDO_DISPARANDO ) 
		) {
			this->move( direccion * velX * dt, 0 );
		}

	// Según el estado movemos verticalmente
	if ( 
		( estado == ESTADO::SALTANDO ) || ( estado == ESTADO::SALTANDO_CORRIENDO ) ||
		( estado == ESTADO::SALTANDO_CORRIENDO_DISPARANDO ) || ( estado == ESTADO::SALTANDO_DISPARANDO )
		) {
			velY += gravity * dt;
			this->move( 0, velY * dt ); 
		}

	// Decrementamos tiempo a la secuencia de SLIDE y de DISPARO
	if ( !secuenciaFinalizada( slideTime ) ) slideTime -= dt;
	if ( !secuenciaFinalizada( shootTime ) ) shootTime -= dt;

	// Animamos y aplicamos el offset al sprite
	this->setTextureRect( anim[estado][busterAnim].animateNew( dt ) );
	this->setOrigin( anim[estado][busterAnim].getOffset() );

	//Updateo la animacion según el nivel del arma
	updateBusterAnim( j, dt );

	// Según la dirección le avisamos si debe dibujar el sprite invertido
	flipX();
}

void Megaman::cambiarEstado( ESTADO nuevoEstado, bool continueFromCurrent )
{
	ESTADO viejoEstado = estado;
	estado = nuevoEstado;
	anim[nuevoEstado][busterAnim].Reset();
	if( continueFromCurrent ) {
		// seteamos el frame de la nueva animacion
		anim[nuevoEstado][busterAnim].SetCurrentFrameNum( anim[viejoEstado][busterAnim].GetCurrentFrameNum() );
		// seteamos el tiempo del frame de la nueva animacion al mismo tiempo que tenia la anterior
		anim[nuevoEstado][busterAnim].animateNew( anim[viejoEstado][busterAnim].GetCurrentFrameElapsedTime() );
	}
}

void Megaman::cambiarBusterAnim( BUSTER_ANIM nuevoBusterAnim, bool continueFromCurrent )
{
	BUSTER_ANIM viejoBusterAnim = busterAnim;
	busterAnim = nuevoBusterAnim;
	anim[estado][nuevoBusterAnim].Reset();
	if ( continueFromCurrent ) {
		// seteamos el frame de la nueva animacion
		anim[estado][nuevoBusterAnim].SetCurrentFrameNum( anim[estado][viejoBusterAnim].GetCurrentFrameNum() );
		// seteamos el tiempo del frame de la nueva animacion al mismo tiempo que tenia la anterior
		anim[estado][nuevoBusterAnim].animateNew( anim[estado][viejoBusterAnim].GetCurrentFrameElapsedTime() );
	}
}

void Megaman::updateBusterAnim( JOYSTICK j, float dt )
{
	//BUSTER
	if ( j.pressingB && secuenciaFinalizada( shootTime ) ) {
		//LVL
		if ( busterLvl < BUSTER_LVL::MEGA_BUSTER ) {
			busterLvlClock += dt;
			if ( busterLvlClock > busterLvlChangeTime ) {
				if ( busterLvl == BUSTER_LVL::NORMAL ) {
					busterLvl = BUSTER_LVL::BUSTER;
					cambiarBusterAnim( BUSTER_ANIM::BUSTER_0 );
				} else if ( busterLvl == BUSTER_LVL::BUSTER ) {
					busterLvl = BUSTER_LVL::MEGA_BUSTER;
					cambiarBusterAnim( BUSTER_ANIM::MEGA_BUSTER_0 );
				}
				busterLvlClock = 0.f;
			}
		}
		//ANIM
		if ( busterLvl == BUSTER_LVL::BUSTER ) {
			busterAnimClock += dt;
			if ( busterAnimClock > busterAnimChangeTime ) {
				if ( busterAnim == BUSTER_ANIM::BUSTER_0 ) cambiarBusterAnim( BUSTER_ANIM::BUSTER_1 );
				else if ( busterAnim == BUSTER_ANIM::BUSTER_1 ) cambiarBusterAnim( BUSTER_ANIM::BUSTER_2 );
				busterAnimClock = 0.f;
			}
		} else if ( busterLvl == BUSTER_LVL::MEGA_BUSTER ) {
			busterAnimClock += dt;
			if ( busterAnimClock > busterAnimChangeTime ) {
				if ( busterAnim == BUSTER_ANIM::MEGA_BUSTER_0 ) cambiarBusterAnim( BUSTER_ANIM::MEGA_BUSTER_1 );
				else if ( busterAnim == BUSTER_ANIM::MEGA_BUSTER_1 ) cambiarBusterAnim( BUSTER_ANIM::MEGA_BUSTER_0 );
				busterAnimClock = 0.f;
			}
		}
	}
}

void Megaman::initAnimaciones()
{
	//QUIETO
	anim[ESTADO::QUIETO][BUSTER_ANIM::NORMAL_0].AddFrame( ssm[0], 1.2f );
	anim[ESTADO::QUIETO][BUSTER_ANIM::NORMAL_0].AddFrame( ssm[1], 0.3f );
	//
	anim[ESTADO::QUIETO][BUSTER_ANIM::BUSTER_0].AddFrame( ssm[2], 1.0f );
	anim[ESTADO::QUIETO][BUSTER_ANIM::BUSTER_1].AddFrame( ssm[3], 1.0f );
	anim[ESTADO::QUIETO][BUSTER_ANIM::BUSTER_2].AddFrame( ssm[4], 1.0f );
	//
	anim[ESTADO::QUIETO][BUSTER_ANIM::MEGA_BUSTER_0].AddFrame( ssm[5], 1.f );
	anim[ESTADO::QUIETO][BUSTER_ANIM::MEGA_BUSTER_1].AddFrame( ssm[6], 1.f );
	
	//CORRIENDO
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::NORMAL_0].AddFrame( ssm[7], 0.3f );
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::NORMAL_0].AddFrame( ssm[8], 0.3f );
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::NORMAL_0].AddFrame( ssm[9], 0.3f );
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::NORMAL_0].AddFrame( ssm[8], 0.3f );
	//
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::BUSTER_0].AddFrame( ssm[10], 0.3f );
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::BUSTER_0].AddFrame( ssm[11], 0.3f );
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::BUSTER_0].AddFrame( ssm[12], 0.3f );
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::BUSTER_0].AddFrame( ssm[11], 0.3f );
	//
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::BUSTER_1].AddFrame( ssm[13], 0.3f );
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::BUSTER_1].AddFrame( ssm[14], 0.3f );
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::BUSTER_1].AddFrame( ssm[15], 0.3f );
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::BUSTER_1].AddFrame( ssm[14], 0.3f );
	//
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::BUSTER_2].AddFrame( ssm[16], 0.3f );
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::BUSTER_2].AddFrame( ssm[17], 0.3f );
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::BUSTER_2].AddFrame( ssm[18], 0.3f );
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::BUSTER_2].AddFrame( ssm[17], 0.3f );
	//
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::MEGA_BUSTER_0].AddFrame( ssm[19], 0.3f );
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::MEGA_BUSTER_0].AddFrame( ssm[20], 0.3f );
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::MEGA_BUSTER_0].AddFrame( ssm[21], 0.3f );
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::MEGA_BUSTER_0].AddFrame( ssm[20], 0.3f );
	//
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::MEGA_BUSTER_1].AddFrame( ssm[22], 0.3f );
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::MEGA_BUSTER_1].AddFrame( ssm[23], 0.3f );
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::MEGA_BUSTER_1].AddFrame( ssm[24], 0.3f );
	anim[ESTADO::CORRIENDO][BUSTER_ANIM::MEGA_BUSTER_1].AddFrame( ssm[23], 0.3f );

	//DISPARANDO
	anim[ESTADO::DISPARANDO][BUSTER_ANIM::NORMAL_0].AddFrame( ssm[25], 1.f );

	//SALTANDO
	anim[ESTADO::SALTANDO][BUSTER_ANIM::NORMAL_0].AddFrame( ssm[26], 1.f );
	//
	anim[ESTADO::SALTANDO][BUSTER_ANIM::BUSTER_0].AddFrame( ssm[27], 1.f );
	anim[ESTADO::SALTANDO][BUSTER_ANIM::BUSTER_1].AddFrame( ssm[28], 1.f );
	anim[ESTADO::SALTANDO][BUSTER_ANIM::BUSTER_2].AddFrame( ssm[29], 1.f );
	//
	anim[ESTADO::SALTANDO][BUSTER_ANIM::MEGA_BUSTER_0].AddFrame( ssm[30], 1.f );
	anim[ESTADO::SALTANDO][BUSTER_ANIM::MEGA_BUSTER_1].AddFrame( ssm[31], 1.f );

	//DESLIZANDO
	anim[ESTADO::DESLIZANDO][BUSTER_ANIM::NORMAL_0].AddFrame( ssm[32], 1.f );
	//
	anim[ESTADO::DESLIZANDO][BUSTER_ANIM::BUSTER_0].AddFrame( ssm[33], 1.f );
	anim[ESTADO::DESLIZANDO][BUSTER_ANIM::BUSTER_1].AddFrame( ssm[34], 1.f );
	anim[ESTADO::DESLIZANDO][BUSTER_ANIM::BUSTER_2].AddFrame( ssm[35], 1.f );
	//
	anim[ESTADO::DESLIZANDO][BUSTER_ANIM::MEGA_BUSTER_0].AddFrame( ssm[36], 1.f );
	anim[ESTADO::DESLIZANDO][BUSTER_ANIM::MEGA_BUSTER_1].AddFrame( ssm[37], 1.f );
	
	//CORRIENDO_DISPARANDO
	anim[ESTADO::CORRIENDO_DISPARANDO][BUSTER_ANIM::NORMAL_0].AddFrame( ssm[38], 0.3f );
	anim[ESTADO::CORRIENDO_DISPARANDO][BUSTER_ANIM::NORMAL_0].AddFrame( ssm[39], 0.3f );
	anim[ESTADO::CORRIENDO_DISPARANDO][BUSTER_ANIM::NORMAL_0].AddFrame( ssm[40], 0.3f );
	anim[ESTADO::CORRIENDO_DISPARANDO][BUSTER_ANIM::NORMAL_0].AddFrame( ssm[39], 0.3f );

	//SALTANDO_DISPARANDO
	anim[ESTADO::SALTANDO_DISPARANDO][BUSTER_ANIM::NORMAL_0].AddFrame( ssm[41], 0.3f );

	//SALTANDO_CORRIENDO
	anim[ESTADO::SALTANDO_CORRIENDO][BUSTER_ANIM::NORMAL_0].AddFrame( ssm[26], 1.f );
	//
	anim[ESTADO::SALTANDO_CORRIENDO][BUSTER_ANIM::BUSTER_0].AddFrame( ssm[27], 1.f );
	anim[ESTADO::SALTANDO_CORRIENDO][BUSTER_ANIM::BUSTER_1].AddFrame( ssm[28], 1.f );
	anim[ESTADO::SALTANDO_CORRIENDO][BUSTER_ANIM::BUSTER_2].AddFrame( ssm[29], 1.f );
	//
	anim[ESTADO::SALTANDO_CORRIENDO][BUSTER_ANIM::MEGA_BUSTER_0].AddFrame( ssm[30], 1.f );
	anim[ESTADO::SALTANDO_CORRIENDO][BUSTER_ANIM::MEGA_BUSTER_1].AddFrame( ssm[31], 1.f );

	//SALTANDO_CORRIENDO_DISPARANDO
	anim[ESTADO::SALTANDO_CORRIENDO_DISPARANDO][BUSTER_ANIM::NORMAL_0].AddFrame( ssm[41], 0.3f );
}

void Megaman::flipX()
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

void Megaman::saltar()
{
	velY = initJumpForce;
	posY = this->getPosition().y;
}

bool Megaman::colisionConSuelo()
{
	float y = this->getPosition().y;

	if ( y >= posY ) {
		this->setPosition( this->getPosition().x, posY );
		return true;
	} else return false;
}

void Megaman::disparar()
{
	float x = this->getGlobalBounds().left + this->getGlobalBounds().width -1 * direccion;
	float y = this->getGlobalBounds().top + 10;
	shootTime = shoot_time;
	disparos->agregarDisparo( x, y, velDisparo * direccion, busterLvl );
}

void Megaman::dispararBuster()
{
	disparar();
	busterLvl = BUSTER_LVL::NORMAL;
	cambiarBusterAnim( BUSTER_ANIM::NORMAL_0 );
	busterLvlClock = 0.f;
	busterAnimClock = 0.f;
}

bool Megaman::secuenciaFinalizada( float time )
{
	return ( time < 0.f );
}

bool Megaman::checkDisparo( JOYSTICK j )
{
	if ( j.b && !j.pressingB && secuenciaFinalizada( shootTime ) ) {
		return true;
	} else {
		return false;
	}
}

bool Megaman::checkSalto( JOYSTICK j )
{
	if ( j.a && !j.pressingA ) {
		return true;
	} else {
		return false;
	}
}

bool Megaman::checkQuieto( JOYSTICK j )
{
	if ( !j.left && !j.right ) {
		return true;
	} else {
		return false;
	}
}

bool Megaman::checkDisparoBuster( JOYSTICK j )
{
	if ( ( !j.pressingB ) && ( busterLvl != BUSTER_LVL::NORMAL ) ) {
		return true;
	} else {
		return false;
	}
}