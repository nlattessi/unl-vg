#ifndef _GAME_H_
#define _GAME_H_

#include <SFML\Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "ImageManager.h"
#include "Personaje.h"
#include "Bloque.h"
#include "Contador.h"

//Declaración de constantes
const int					POSICION_TERRENO_Y = 460;
const int					MAX_ASCENSO_SALTO_Y = 100;
const int					FIN_JUEGO = 60;

typedef struct {
	sf::Sprite bloque;
	sf::Text texto;
} BloqueTexto;

class Game {
public:
	Game();
	~Game();

	void					Run();

private:
	sf::RenderWindow		window;
	/** un Clock para el dt y otro para el Contador **/
	sf::Clock				clock, clockContador; 
	sf::Font				font;
	sf::Sprite				background;
	imageManager			imgMgr;
	Personaje				jugador;
	bool					teclaSaltoPresionada;
	bool					ganoJuego;
	Contador				contador;
	std::vector<Bloque>		bloques;
	std::vector<int>		valores;
	int						posValor;

	void					Draw();
	void					CheckCollision();
	void					FinJuego();
};

#endif