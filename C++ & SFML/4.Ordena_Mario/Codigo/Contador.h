#ifndef _CONTADOR_H_
#define _CONTADOR_H_

#include <SFML\Graphics.hpp>
#include <iostream>

const int TIEMPO_JUEGO = 60;

class Contador
{
public:
	Contador( float tiempoActual );
	~Contador();

	void		Update( float delta_time_seconds );
	sf::Text	GetText() { return textoContador; }
	void		ReducirTiempo() { tiempoInicio -= 10.0f; }
	bool		GetFin() { return fin; }

protected:
	float		tiempoInicio;
	float		tiempoFin;
	sf::Font	font;
	sf::Text	textoContador;
	bool		fin;
};


#endif