#include <iostream>
#include <fstream>
#include <cstring>
#include <conio2.h>
#include <windows.h>

#ifndef SCORE_H
#define SCORE_H

//Estructura para guardar los puntajes a archivo
typedef struct
{
	char *nombre;
	int largo;
	int puntos;
} Puntaje;
	
class Score {
private:
	//Array de puntajes
	Puntaje *puntajes;
	
public:
	Score();
	~Score();
	
	void guardarPuntajes();
	void insertarPuntaje(int _puntos);
	void listar(int _x, int _y);
};

#endif
