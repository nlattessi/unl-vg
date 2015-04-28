#include "Enemigo.h"

//Seteo de variables iniciales
Enemigo::Enemigo()
{
	//Tomo al azar el modelo y el carril
	int n = rand()%2;
	int g = rand()%3;
	if (n == 0)
		x = xAnt = CARRIL_I;
	else
		x = xAnt = CARRIL_D;
	
	y = yAnt = 0;
	grafx = grafy = 4;
	estado = VISIBLE;
	
	grafico = new char *[grafy];
	for (int i=0; i<grafy; i++)
		grafico[i] = new char[grafx];
	if (g == 0)
	{
		strcpy(grafico[0]," /\\ ");
		strcpy(grafico[1],"0--0");
		strcpy(grafico[2]," || ");
		strcpy(grafico[3],"0--0");
	}
	else if (g == 1)
	{
		strcpy(grafico[0]," \\/ ");
		strcpy(grafico[1],"o--o");
		strcpy(grafico[2]," || ");
		strcpy(grafico[3],"o--o");
	}
	else
	{
		strcpy(grafico[0]," >< ");
		strcpy(grafico[1],"0--0");
		strcpy(grafico[2]," || ");
		strcpy(grafico[3],"0--0");
	}
	
	//Tomo al azar el color
	color = (rand()%15 + 1);
}

Enemigo::~Enemigo()
{
	delete[] grafico;
}

//Muevo si esta VISIBLE. De no estarlo, altero los estados
//y la posicion (para no ser evaluado en colision)
void Enemigo::mover()
{
	if (estado != NO_VISIBLE)
	{
		yAnt = y;
		y++;
	}
	
	if (y == 21)
		estado = SALIENDO;
	if (y == 22)
	{
		estado = NO_VISIBLE;
		y = 24;
	}
}

//Si esta visible, borro posicion anterior y dibujo todo.
//De estar saliendo, borro todo.
void Enemigo::dibujar()
{
	char *blanco;
	blanco = new char[4];
	strcpy(blanco, "    ");
	
	textcolor(color);
	if (estado == VISIBLE)
	{
		//cputsxy(x, yAnt, "    ");
		cputsxy(x, yAnt, blanco);
	
		for (int i=0; i<grafy; i++)			
			cputsxy(x, y+i, grafico[i]);
	}

	if (estado == SALIENDO)
	{
		cputsxy(x, yAnt, blanco);
		for (int i=0; i<grafy; i++)
			cputsxy(x, y+i, blanco);
	}
	textcolor(WHITE);
	delete blanco;
}
