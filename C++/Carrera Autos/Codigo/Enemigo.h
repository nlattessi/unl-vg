#include <iostream>
#include "Auto.h"

#ifndef ENEMIGO_H
#define ENEMIGO_H

#define NO_VISIBLE 0
#define VISIBLE 1
#define SALIENDO 2

class Enemigo : public Auto {
private:
	int color;
	
public:
	Enemigo();
	~Enemigo();

	void mover();
	void dibujar();
};

#endif
