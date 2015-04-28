#include <windows.h>
#include "Auto.h"

#ifndef JUGADOR_H
#define JUGADOR_H

#define INICIO 0
#define QUIETO 1
#define MOVIENDO 2

class Jugador : public Auto {
private:
	
public:
	Jugador();
	~Jugador();
	
	void mover();
	void dibujar();
};

#endif
