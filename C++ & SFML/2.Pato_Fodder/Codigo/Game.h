//Objetos
#include "Fondo.h"
#include "Bala.h"
#include "Cannon.h"
#include "PantallaInicio.h"
#include "Pato.h"
#include "Viento.h"

//Defino tipos de control
#define TECLADO 1
#define MOUSE 2

//Defino cantidad de Patos y Balas máximos
#define PATOS 20
#define BALAS 5

//Defino estados del Cañon
#define CANNON_LISTO 1
#define CANNON_CARGANDO 2

class Game
{
private:
	void ProcessEvent(sf::Event &evt);
	void ProcessCollisions();
	void UpdateGame();
	void DrawGame();
	
	//Funciones auxiliares
	void PerderVida();
	void FinJuego();
	bool CheckColision(Bala &bala, Pato &pato);
	void DesplumarPato(Pato &pato);
	void Disparar();
	void CargarMedios();
	void CargarTextos();

	//Variables para almacenar imagenes
	sf::Image ImgFondo, ImgBala, ImgCannon, ImgPato1, ImgPato2, ImgPato3;

	//Variables para almacenar sonidos
	sf::SoundBuffer SBuffCuack;
	sf::SoundBuffer SBuffBoom;

	//Proceso de eventos sin buffer
	void ProcessEventUnbuffered(const sf::Input &Input);
	bool botonApretado;

	//Ventana
	sf::RenderWindow *pWnd;

	//PantallaInicio
	PantallaInicio pantallaInicio;
	int control;

	//Fondo
	Fondo *pFondo;

	//Cañon
	Cannon *pCannon;

	//Array de Balas
	Bala *pBalas[BALAS];

	//Array de Patos
	Pato *pPato;
	Pato *pPatos[PATOS];

	//Viento
	Viento Viento;

	//Texto de la cant. de vidas
	sf::String txtVidas;
	sf::Font fuente;

	//Texto de la potencia
	sf::String txtPotencia;

	//Texto del viento
	sf::String txtViento;

	//Texto del estado del Cañon
	sf::String txtCannon;

	//Variables generales
	float ft; //Tiempo de frame
	int vidas;

	//Variables del disparo
	float angulo;
	float v0;
	//Variable que ajusta la potencia del disparo sumandose
	//a la velocidad inicial, para que el jugador no deba cargar
	//tanta potencia para hacer un disparo rápido
	int ajusteVelDisparo;

public:
	Game(int _alto, int _ancho, std::string _titulo);
	~Game(void);

	void Go();
};