#include "Escenario.h"


Escenario::Escenario()
{
	cant_mov = 0;
	for (int i=0; i<24; i++)
		for (int j=0; j<8; j++)
			escena[i][j] = 0;
	inserta_auto(LADO_I);
}

Escenario::~Escenario()
{
	
}

void Escenario::inserta_auto(int _carril)
{
	if (_carril == LADO_I)
	{
		escena[0][0] = 1; escena[0][1] = 1; escena[0][2] = 1; escena[0][3] = 1;
		escena[1][0] = 1; escena[1][1] = 1; escena[1][2] = 1; escena[1][3] = 1;
		escena[2][0] = 1; escena[2][1] = 1; escena[2][2] = 1; escena[2][3] = 1;
		escena[3][0] = 1; escena[3][1] = 1; escena[3][2] = 1; escena[3][3] = 1;
	}
	else
	{
		escena[0][4] = 1; escena[0][5] = 1; escena[0][6] = 1; escena[0][7] = 1;
		escena[1][4] = 1; escena[1][5] = 1; escena[1][6] = 1; escena[1][7] = 1;
		escena[2][4] = 1; escena[2][5] = 1; escena[2][6] = 1; escena[2][7] = 1;
		escena[3][4] = 1; escena[3][5] = 1; escena[3][6] = 1; escena[3][7] = 1;
	}
}

void Escenario::mover()
{
	for (int i=23; i>0; i--)
		for (int j=0; j<8; j++)
			escena[i][j] = escena[i-1][j];
	
	for (int j=0; j<8; j++)
		escena[0][j] = 0;
	
	cant_mov++;
	
	if (cant_mov == 10)
	{
		inserta_auto(rand()%2);
		cant_mov = 0;
	}
}

void Escenario::dibujar()
{
	for (int i=0; i<24; i++)
	{
		gotoxy(40,1+i);
		for (int j=0; j<8; j++)
			if (escena[i][j] != 0)
				cout<<escena[i][j];
			else
				cout<<' ';
	}
}
