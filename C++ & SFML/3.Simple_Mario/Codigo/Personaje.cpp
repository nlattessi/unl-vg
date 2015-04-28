#include "Personaje.h"
Personaje::Personaje( int x, int y ) 
{
	enAscenso = false;
	saltoEnProceso = false;
	posicionTerrenoY = x;
	maxAscensoSaltoY = y;
	pisoActual = 0;
}

Personaje::~Personaje() {
}

void Personaje::ActualizarSalto( bool teclaSaltoPresionada, float delta_time_seconds )
{
	//Se chequea si se presionó la tecla de salto y si el proceso aún no inicio.
	if( teclaSaltoPresionada && !saltoEnProceso ) {
		saltoEnProceso = true;
		enAscenso = true;
	}

	//Bloque que maneja el salto y su descenso a través del eje y.
	if( saltoEnProceso ) {

		//Se controla cuando se llega al maximo de altura de salto
		if( getPosition().y <= posicionTerrenoY - maxAscensoSaltoY ) {
			enAscenso = false;
			if ( pisoActual < 6 ) { // Si no estoy en el ultimo piso, subo uno. Con esto cuando estoy en el 6° puedo saltar para esquivar y volver al mismo.
				posicionTerrenoY -= maxAscensoSaltoY;
			}
		}

		//Se ejecuta el movimiento hacia arriba o abajo en eje y
		if( enAscenso ) {
			move( 0.0f, -1.0f * SPEED_Y * delta_time_seconds );
		} else {
			move( 0.0f, SPEED_Y * delta_time_seconds );
		}

		//Se controla cuando el personaje vuelve a tocar la eje y del terreno
		if( getPosition().y >= posicionTerrenoY ) {
			saltoEnProceso = false; //Permite que finalize un ciclo de salto y que comienze uno nuevo			
			setPosition( getPosition().x, posicionTerrenoY ); //Se fuerza la posicion del personaje en la linea de terreno
			if (pisoActual < 6 ) {
				pisoActual++; // Si no estoy en el ultimo piso, subo uno
			}
		}
	}
}

void Personaje::update(float delta_time_seconds) 
{
	//Esta es la mejor manera de detectar teclas presionadas para cuando se necesita un movimiento constante y fluido.
	//Como por ejemplo el movimiento de un personaje.
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left )) {
		move( -1.0f * SPEED_X * delta_time_seconds, 0.0f );
	}
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right )) {
		move( 1.0f * SPEED_X * delta_time_seconds, 0.0f );
	}

	sf::Vector2f position = getPosition();
	if( position.x <= -1.0f ) {
		position.x = 800.0f + 1.0f;
	} else if( position.x >= 801.0f ) {
		position.x = -1.0f;
	}
	setPosition( position );
}

int Personaje::getPisoActual()
{
	return pisoActual;
}