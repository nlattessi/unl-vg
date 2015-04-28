#ifndef CONTADOR_H
#define CONTADOR_H

#include <SFML\Graphics.hpp>
#include <iostream>

class Contador
{
public:
	Contador( float tiempoActual, float tiempoJuego );
	~Contador();

	void		Update( float delta_time_seconds );
	sf::Text	GetText() { return textoContador; }
	bool		GetFin() { return fin; }
	//void		reset( float tiempoActual );
	//void		setFont( sf::Font font );
	void		setPosition( float x, float y);

protected:
	float		tiempoInicio;
	float		tiempoFin;
	float		tiempoMax;
	sf::Font	font;
	sf::Text	textoContador;
	bool		fin;
};


#endif