#include "Jugador.h"

//Seteo de variables iniciales
Jugador::Jugador()
{
	x = xAnt = CARRIL_I;
	y = 20;
	grafx = grafy = 4;
	estado = INICIO;
	
	grafico = new char *[grafy];
	for (int i=0; i<grafy; i++)
		grafico[i] = new char[grafx];
	strcpy(grafico[0]," /\\ ");
	strcpy(grafico[1],"0--0");
	strcpy(grafico[2]," || ");
	strcpy(grafico[3],"0--0");
}

Jugador::~Jugador()
{
	delete[] grafico;
}

//Primero asumo que no se mueve y luego evaluo si se toco tecla para mover.
//De ser asi, cambio el estado para que sea redibujado
void Jugador::mover()
{
	estado = QUIETO;
	
	if ((GetAsyncKeyState(VK_LEFT)) && (x == CARRIL_D))
	{
		xAnt = x;
		x = CARRIL_I;
		estado = MOVIENDO;		
	}
	
	if ((GetAsyncKeyState(VK_RIGHT)) && (x == CARRIL_I))
	{
		xAnt = x;
		x = CARRIL_D;
		estado = MOVIENDO;
	}
}

//Solo dibujo si se mueve o si el auto no estaba dibujado
void Jugador::dibujar()
{
	char *blanco;
	blanco = new char[4];
	strcpy(blanco, "    ");
	
	textcolor(WHITE);
	if (estado == INICIO)
		for (int i=0; i<grafy; i++)
			cputsxy(x, y+i, grafico[i]);
	
	if (estado == MOVIENDO)
	{
		for (int i=0; i<grafy; i++)
			cputsxy(xAnt, y+i, blanco);
		
		for (int i=0; i<grafy; i++)
			cputsxy(x, y+i, grafico[i]);
	}
	delete blanco;
}
