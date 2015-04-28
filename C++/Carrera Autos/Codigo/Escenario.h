#include <conio2.h>
#include <cstdlib>
#include <iostream>
using namespace std;

#ifndef ESCENARIO_H
#define ESCENARIO_H

#define LADO_I 0
#define LADO_D 0

class Escenario {
private:
	int escena[24][8];
	int cant_mov;
	
	void inserta_auto(int _carril);
	
public:
	Escenario();
	~Escenario();
		
	void mover();
	void dibujar();
};

#endif
