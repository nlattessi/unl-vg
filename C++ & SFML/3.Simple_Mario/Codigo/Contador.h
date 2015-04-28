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

protected:
	float		tiempoInicio;
	float		tiempoFin;
	sf::Font	font;
	sf::Text	textoContador;
	bool		fin;
};


#endif