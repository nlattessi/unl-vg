#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <SFML\Graphics.hpp>

#include "ImageManager.h"
#include "Personaje.h"
#include "Contador.h"
#include "Cola.h"
#include "Pila.h"

//Declaración de constantes
const int	MAX_ASCENSO_SALTO_Y = 75;
const int	FIN_JUEGO = 30;
const int	PISO0_Y = 465;
const int	PISO1_Y = 426;
const int	PISO2_Y = 350;
const int	PISO3_Y = 275;
const int	PISO4_Y = 198;
const int	PISO5_Y = 126;
const int	PISO6_Y = 50;
const int	PUERTA_X = 750;
const int	PUERTA_Y = 26;
const int	FIN_PANTALLA_X = 800;
const int	FIN_PANTALLA_Y = 600;
const bool	WIN = true;

class Game
{
	public:
		Game();
		~Game();

		void				Run();

	private:
		sf::RenderWindow	window;		
		sf::Clock			clock, clockContador; // Un Clock para el dt y otro para el Contador
		sf::Font			font;
		sf::Sprite			background, puerta;
		imageManager		imgMgr;
		Personaje			jugador;
		bool				teclaSaltoPresionada;
		bool				isFinJuego;
		bool				isGanoJuego;
		Contador			contador;
		Cola				*colaPiso1, *colaPiso3, *colaPiso5;
		Pila				*pila1Piso2, *pila2Piso2, *pila1Piso4, *pila2Piso4, *pila1Piso6, *pila2Piso6;
		Shell				shellPiso1, shellPiso2, shellPiso3, shellPiso4, shellPiso5, shellPiso6;

		Cola*				cargarCola( imageManager &imgMgr );
		Pila*				cargarPila( imageManager &imgMgr );
		void				Draw();
		void				CheckCollision();
		void				colisionCola( Shell &shell, Cola* cola, const int posY );
		void				colisionPilaIzq( Shell &shell, Pila* pila1, Pila* pila2, const int posY );
		void				colisionPilaDer( Shell &shell, Pila* pila1, Pila* pila2, const int posY );
		void				finJuego( bool win );
};

#endif