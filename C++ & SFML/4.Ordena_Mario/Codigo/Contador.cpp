#include "Contador.h"

Contador::Contador( float tiempoActual )
{
	if( !font.loadFromFile( "Recursos/Fuentes/arial.ttf" ) ) {
		//ERROR
	}
	textoContador.setFont( font );
	textoContador.setCharacterSize( 60 );
	tiempoInicio = tiempoActual + TIEMPO_JUEGO;
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
	if( seconds >= 0) 
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