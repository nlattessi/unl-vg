#include <cstring>
#include <conio2.h>
#include <cstdlib>

#ifndef AUTO_H
#define AUTO_H

#define CARRIL_I 40
#define CARRIL_D 44

class Auto {
protected:
	int x, xAnt, y, yAnt, grafx, grafy, estado;
	char **grafico;
	
public:
	int getX() {return x;}
	int getY() {return y;}
	void setEstado(int _estado) {estado = _estado;}
	
	virtual void mover() = 0;
	virtual void dibujar() = 0;
};

#endif
