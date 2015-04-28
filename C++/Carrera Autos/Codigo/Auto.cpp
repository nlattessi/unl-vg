/*#include "Auto.h"
#include <iostream>
#include <cstdio>
using namespace std;

Auto::Auto()
{
	posx = posxAnt = CARRIL_I;
	posy = 20;
	grafx = grafy = 4;
	
	//carril = CARRIL_I;
	estado = INICIO;
	
	grafico = new char *[grafy];
	for (int i=0; i<grafy; i++)
		grafico[i] = new char[grafx];
	strcpy(grafico[0], "xxxx");
	strcpy(grafico[1], "xxxx");
	strcpy(grafico[2], "xxxx");
	strcpy(grafico[3], "xxxx");
}

Auto::~Auto()
{
	delete[] grafico;
}

void Auto::mover(int _mov)
{
	//gotoxy(1,20); cout<<_mov;
	//gotoxy(1,21); cout<<estado;
	//gotoxy(1,22); cout<<carril;
	
	/*if ((carril == CARRIL_I) && (_mov == DER))
	{		
		carril = CARRIL_D;
		estado = MOVIENDO;
	}
	
	if ((carril == CARRIL_D) && (_mov == IZQ))
	{
		carril = CARRIL_I;
		estado = MOVIENDO;
	}*/
	
	/*if ((_mov == IZQ) && (posx == CARRIL_D))
	{
		posxAnt = posx;
		posx = CARRIL_I;
		estado = MOVIENDO;
	}
	
	if ((_mov == DER) && (posx == CARRIL_I))
	{
		posxAnt = posx;
		posx = CARRIL_D;
		estado = MOVIENDO;
	}
}

void Auto::dibujar()
{
	
	
	//if ((estado == INICIO) || (estado == QUIETO))
	if (estado == INICIO)
		for (int i=0; i<grafy; i++)
			cputsxy(posx, posy+i, grafico[i]);
	
	if (estado == MOVIENDO)
	{
		for (int i=0; i<grafy; i++)
			cputsxy(posxAnt, posy+i, "    ");
		
		for (int i=0; i<grafy; i++)
			cputsxy(posx, posy+i, grafico[i]);
	}
}*/
