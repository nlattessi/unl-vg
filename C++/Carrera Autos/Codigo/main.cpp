#include "Juego.h"

//Genero la semilla de azar, creo el objeto juego y lo arranco
int main (int argc, char *argv[]) {
	
	srand(time(NULL));
	
	Juego j;
	
	j.jugar();
	
	return 0;
}

