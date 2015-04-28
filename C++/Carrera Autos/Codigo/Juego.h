#include <ctime>
#include <iostream>
#include <cstdio>
#include <windows.h>
#include <conio2.h>

#include "Jugador.h"
#include "Enemigo.h"
#include "Score.h"

#ifndef JUEGO_H
#define JUEGO_H

class Juego {
private:	
	Jugador jugador;
	Enemigo *enemigos[4];
	Score score;
	
	int ultimoEnemigo;
	int contador, contadorActual;
	int velocidad;
	int nivel, ultimoNivel;
	int puntos;
	int vidas;
	bool colision;
	clock_t tempo;
	clock_t paso;
	
	bool checkColision(int _posxJ, int _posyJ, int _posxE, int _posyE);
	void mostrarPuntos();
	void mostrarVidas();
	void mostrarNivel();
	void evaluaNivel();
	void cambioNivel();
	void reset();
	void actualizarEnemigos();
	void choque();
	
public:
	Juego();
	~Juego();
	
	void jugar();
};

#endif
