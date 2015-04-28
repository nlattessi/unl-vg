#include "Juego.h"

//Seteo variables de nivel 1
Juego::Juego()
{
	contadorActual = 20;
	velocidad = 8;
	puntos = 0;
	nivel = 1;
	ultimoNivel = 3;	
	vidas = 3;
	colision = false;	
	tempo = clock();
	paso = CLOCKS_PER_SEC/velocidad;
}

Juego::~Juego()
{
	delete[] enemigos;
}

//Chequeo la colision con cada enemigo activo, dada si el jugador
//se encuentra en misma posicion del array del enemigo.
bool Juego::checkColision(int _posxJ, int _posyJ, int _posxE, int _posyE)
{
	bool salida = false;
	
	for (int i=0; i<4; i++)
	{
		if (enemigos[i] == NULL)
			continue;
		
		if ((jugador.getX() == enemigos[i]->getX()) &&
			(enemigos[i]->getY() >= 17 && enemigos[i]->getY() <= 22))
		{
			salida = true;
			break;
		}
	}
	return salida;
}

void Juego::mostrarPuntos()
{
	gotoxy(1,1);
	std::cout<<"PUNTOS: "<<puntos;
}

void Juego::mostrarVidas()
{
	gotoxy(1,3);
	std::cout<<"VIDAS: "<<vidas;
}

void Juego::mostrarNivel()
{
	gotoxy(1,5);
	std::cout<<"NIVEL: "<<nivel;
}

//Muevo a cada enemigo activo y lo dibujo.
//Luego evaluo si se cumple el contador para lanzar un nuevo enemigo.
void Juego::actualizarEnemigos()
{
	for (int i=0; i<4; i++)
		if (enemigos[i] != NULL)
		{
			enemigos[i]->mover();
			enemigos[i]->dibujar();
		}
	
	contador++;
	if (contador == contadorActual)
	{	
		ultimoEnemigo++;
		if (ultimoEnemigo == 4)
			ultimoEnemigo = 0;
		enemigos[ultimoEnemigo] = new Enemigo();
		contador = 0;
	}
}

//Evaluo en base al puntaje y al nivel si aumento la dificultad
void Juego::evaluaNivel()
{
	if ((puntos >= 1000) && (nivel == 1))
	{
		nivel = 2;
		cambioNivel();
	}
	if ((puntos >= 2000) && (nivel == 2))
	{
		nivel = 3;
		cambioNivel();
	}
	if ((puntos >= 4000) && (nivel == 3))
	{
		nivel = 4;
		cambioNivel();
	}
	if ((puntos >= 10000) && (nivel == 4))
	{
		nivel = 5;
		cambioNivel();
	}
	if ((puntos >= 20000) && (nivel == 5))
	{
		nivel = 6;
		cambioNivel();
	}
	if ((puntos >= 10000*ultimoNivel))
	{
		nivel++;
		cambioNivel();
		ultimoNivel++;
	}
}

//Cambia las variables que determinan la dificultad
void Juego::cambioNivel()	
{
	switch (nivel)
	{
	case 2:
		velocidad = 10;
		paso = CLOCKS_PER_SEC/velocidad;
		contadorActual = 15;
		break;
	case 3:
		velocidad = 10;
		paso = CLOCKS_PER_SEC/velocidad;
		contadorActual = 14;
		break;
	case 4:
		velocidad = 14;
		paso = CLOCKS_PER_SEC/velocidad;
		contadorActual = 12;
		break;
	case 5:
		velocidad = 18;
		paso = CLOCKS_PER_SEC/velocidad;
		contadorActual = 10;
		break;
	case 6:
		velocidad = 22;
		paso = CLOCKS_PER_SEC/velocidad;
		contadorActual = 9;
		break;
	default:
		velocidad=+2;
		if (((nivel == 8) || (nivel == 10)) && (contadorActual != 7))
			contadorActual--;
		paso = CLOCKS_PER_SEC/velocidad;
	}
	
	//Notifico al jugador y reinicio el juego con las nueva dificultad
	clrscr();
	gotoxy(31,10);
	std::cout<<"Cambio de nivel";
	std::cout<<std::endl<<std::endl;
	gotoxy(30,11);
	std::cout<<"Comienza nivel: "<<nivel;
	gotoxy(30,14);
	std::cout<<"Presiona una tecla para continuar...";
	getchar();
	clrscr();
	reset();
}


//Resta vida, muestra info por pantalla y evalua si sigue o sale del juego
void Juego::choque()
{
	vidas--;
	gotoxy(35,15);
	textcolor(LIGHTRED);
	std::cout<<"BOOOOOOOOOOOOOOOOOOOOOOOOOOOOOM";
	textcolor(WHITE);
	Sleep(1000);
	if (vidas > 0)
	{	
		clrscr();
		gotoxy(30,15);
		std::cout<<"Te queda "<<vidas<<" vidas";
		gotoxy(30,17);
		std::cout<<"Presiona una tecla para continuar...";
		getchar();
		clrscr();
		reset();
	}
	else
	{
		//Si sale, inserta el puntaje del jugador, muestra la lista y sale del juego
		clrscr();
		gotoxy(30,15);
		textcolor(YELLOW);
		std::cout<<"GAME OVER";
		Sleep(2000);
		score.insertarPuntaje(puntos);
		clrscr();
		gotoxy(30,10);
		textcolor(LIGHTBLUE);
		std::cout<<"FIN DEL JUEGO";
		textcolor(WHITE);
		score.listar(30,12);
		Sleep(4000);
		score.guardarPuntajes();
		exit(EXIT_SUCCESS);
	}
		
}

//Pone a 0 las variables iniciales y dibujo en pantalla todos los elementos
void Juego::reset()
{
	contador = 0;
	for (int i=0; i<4; i++)
		enemigos[i] = NULL;
	ultimoEnemigo = 0;
	enemigos[ultimoEnemigo] = new Enemigo();
	jugador.setEstado(INICIO);
	jugador.dibujar();
	mostrarPuntos();
	mostrarVidas();
	mostrarNivel();
	score.listar(1,10);
}

//Metodo principal
void Juego::jugar()
{	
	//Cargo las variables de la partida a 0
	reset();
	
	//Loop principal
	while (true)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
			break;
		
		//Actualizo el auto del jugador
		jugador.mover();
		jugador.dibujar();
		
		//Chequeo colision
		colision = checkColision(jugador.getX(), jugador.getY(),
			enemigos[ultimoEnemigo]->getX(), enemigos[ultimoEnemigo]->getY());
		if (colision)
		{
			//Si hay, disparo el metodo choque
			choque();
			//Si no perdio el jugador, continuo la partida
			if (vidas > 0)
				continue;
		}
		
		//Si se cumplio el timer del enemigo (dado por su velocidad), lo actualizo
		if (tempo+paso < clock())
		{
			//Aumento puntaje
			puntos+=10;
			mostrarPuntos();
			
			//Actualizo y luego evaluo si aumento la dificultad
			actualizarEnemigos();
			evaluaNivel();

			//Reinicio el timer
			tempo = clock();
		}
	}
}
