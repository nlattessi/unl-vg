#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <sstream>

#include <SFML\Graphics.hpp>

#include "ImageManager.h"
#include "Contador.h"
#include "Lista.h"

const float	FIN_PANTALLA_X = 800.0f;
const float CARRIL_1 = 0.0f;
const float CARRIL_2 = 190.0f;
const float CARRIL_3 = 290.0f;
const float CARRIL_4 = 390.0f;
const float CARRIL_5 = 490.0f;
const bool	WIN = true;
const int	FIN_SUMA = 10;
const float SPEED_X = 150.0f;

class Game
{
	public:
		Game();
		~Game();

		void				Run();

	private:
		sf::RenderWindow	window;		
		sf::Clock			clock, clockContador; // Un Clock para el dt y otro para el Contador
		sf::Font			font1, font2;
		imageManager		imgMgr;
		bool				finJuego;
		bool				ganoJuego;
		Contador*			contador;
		Lista*				tren;
		sf::Sprite*			vagon1;
		sf::Sprite*			vagon2;
		sf::Sprite*			vagon3;
		bool				isSuma;
		sf::RectangleShape	rectangulo;
		sf::Text			text, textErrores;
		sf::String			buffer;
		int					tamBuffer;
		int					primerNumero;
		int					segundoNumero;
		int					tercerNumero;
		int					resultado;
		int					errores;

		void				armarSuma();
		void				Draw();
		void				drawSuma();
		void				CheckCollision();
		void				finalizarJuego( bool win );
};

#endif