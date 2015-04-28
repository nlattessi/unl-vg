#include <SFML\Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;
#include <sstream> //Para poder usar el objeto ostringstream
#include <iostream>

//Objetos
#include "Cursor.h"
#include "Marco.h"
#include "Tecla.h"
#include "Circulo.h"
#include "Vida.h"
#include "Fondo.h"

class Game
{
private:
	RenderWindow *pWnd;
	void ProcessEvent (Event &evt);
	void DrawGame();
	void UpdateGame();
	void ProcessCollisions();

	//Variables
	float tf; //Tiempo de frame
	int vidas; //Cant de vidas que le quedan al jugador
	int totalTeclas; //Total de teclas correctas presionadas
	float velocidadActual; //La velocidad actual
	int cantTeclasCorrectas; //Guarda las teclas correctas presionadas para saber cuando subir la velocidad
	int sigNivel; //Determina cuando se aumenta la velocidad
	
	//Variables del objeto Ventana
	int anchoWnd;
	int altoWnd;

	//Variables del objeto Cursor
	Cursor *pCursor;

	//Variables del objeto Marco
	Marco *pMarco;

	//Variables del objeto Tecla
	Tecla *pTecla;

	//Variables del objeto Circulos	
	Circulo *pCirculo[4];
	Clock clockCirculos; //Cuenta el tiempo para saber si pongo o debo borrar circulos
	float contadorCirculos; //Tiempo que debe pasar para poner circulos
	bool hayCirculos; //Para saber si hay o no circulos activos
	float tiempoActivoCirculos; //Guarda cuanto tiempo se quedan los circulos en pantalla

	//Variables del objeto Fondo
	Fondo *pFondo;

	//Variables del objeto Vida
	Vida *pVida[10]; //10 es la cant. de vida maxima

	//Metodos auxiliares
	void CrearCirculos(); //Crea los circulos
	void BorrarCirculos(); //Borra los circulos
	void PerderVida(); //Resta vida al jugador
	void GanarVida(); //Aumenta vida del jugador
	void finJuego(); //Finaliza el juego mostrando el total de teclas presionadas
	void AumentarVelocidad(); //Aumenta la velocidad de la teclas

public:
	Game(int _ancho, int _alto, string _titulo);
	~Game();

	void Go();
};