#include "Contador.h"

Contador::Contador( float tiempoActual, float tiempoJuego )
{
	if( !font.loadFromFile( "Recursos/Fuentes/arial.ttf" ) ) {
		//ERROR
	}
	textoContador.setFont( font );
	textoContador.setColor( sf::Color::Black );
	textoContador.setStyle( sf::Text::Bold );
	textoContador.setCharacterSize( 20 );
	tiempoMax = tiempoJuego;
	tiempoInicio = tiempoActual + tiempoMax;
	tiempoFin = 0.0f;
	fin = false;
}

Contador::~Contador()
{
}

void Contador::Update( float delta_time_seconds )
{
	tiempoFin = delta_time_seconds;	
	int seconds = ( (int) ( tiempoInicio - tiempoFin ) );
	if( seconds > 0) 
	{
		char buffer[20];
		sprintf( buffer, "Tiempo: %i", seconds );
		textoContador.setString( buffer );
	}
	else
	{
		textoContador.setString( "El tiempo finalizo..." );
		fin = true;
	}
}

/*void Contador::reset( float tiempoActual )
{
	tiempoInicio = tiempoActual + tiempoMax;
}*/

/*void Contador::setFont( sf::Font font )
{
	textoContador.setFont( font );
}*/

void Contador::setPosition( float x, float y)
{
	textoContador.setPosition( x, y );
}