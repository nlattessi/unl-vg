#include "Score.h"

//Al crear el Score, intento cargar el archivo de puntajes al array.
//Si no puedo, lo inicializo.
Score::Score()
{
	puntajes = new Puntaje[5];
	
	std::ifstream fpuntajes("puntajes.dat", std::ios::in | std::ios::binary);
	if (fpuntajes.is_open())
		for (int i=0; i<5; i++)
		{
			fpuntajes.read((char *)&puntajes[i].largo, sizeof(int));
			puntajes[i].nombre = new char[puntajes[i].largo];
			fpuntajes.read(puntajes[i].nombre, (puntajes[i].largo+1)*sizeof(char));
			fpuntajes.read((char *)&puntajes[i].puntos, sizeof(int));
		}
	else
		for (int i=0; i<5; i++)
		{
			puntajes[i].largo = 1;
			puntajes[i].nombre = new char[1];
			strcpy(puntajes[i].nombre, "x");
			puntajes[i].puntos = 0;
		}
	fpuntajes.close();
}

Score::~Score()
{	
	delete[] puntajes;
}

//Guardo los puntajes recorriendo el array y volcandolo al archivo
void Score::guardarPuntajes()
{
	std::ofstream fpuntajes("puntajes.dat", std::ios::binary | std::ios::out | std::ios::trunc);
	
	for (int i=0; i<5; i++)
	{
		fpuntajes.write((char *)&puntajes[i].largo, sizeof(int));
		fpuntajes.write(puntajes[i].nombre, (puntajes[i].largo+1)*sizeof(char));
		fpuntajes.write((char *)&puntajes[i].puntos, sizeof(int));
	}
	
	fpuntajes.close();
}

//Recibe un puntaje y lo agrega al array si es record.
void Score::insertarPuntaje(int _puntos)
{
	Puntaje nuevo, temp1, temp2;
	
	char buff[10];
	int pos = -1;
	
	//Evaluo si es record y guardo la posicion que le corresponde.
	for (int i=0; i<5; i++)
		if (_puntos >= puntajes[i].puntos)
		{
			pos = i;
			break;
		}
	
	//Si es record, le aviso al jugador y le pido su nombre.
	//Luego, creo un nuevo puntaje con los datos correspondientes, lo agrego
	//al array y desplazo cada objeto del mismo.
	if (pos > -1)
	{
		clrscr();
		gotoxy(30,15);
		textcolor(LIGHTRED);
		std::cout<<"Nuevo record!";
		gotoxy(30,16);
		textcolor(LIGHTGREEN);
		std::cout<<"Ingrese su nombre: ";
		textcolor(WHITE);
		std::cin>>buff;
		
		nuevo.largo = strlen(buff);
		nuevo.nombre = new char[nuevo.largo+1];
		strcpy(nuevo.nombre, buff);
		nuevo.puntos = _puntos;
		
		temp1 = puntajes[pos];
		puntajes[pos] = nuevo;
		
		for (int j=pos+1; j<5; j++)
		{
			temp2 = puntajes[j];
			puntajes[j] = temp1;
			temp1 = temp2;
		}
	}
	//De no haber record, lo informo.
	else
	{
		clrscr();
		gotoxy(30,15);
		textcolor(LIGHTRED);
		std::cout<<"Ups, no hubo record...";
		textcolor(WHITE);
		Sleep(2000);
	}
}

//Recorro el array escribiendo cada puntaje.
void Score::listar(int _x, int _y)
{
	gotoxy(_x, _y);
	std::cout<<"Mejores Puntajes:";
	
	for (int i=0; i<5; i++)
	{
		if (puntajes[i].puntos == 0)
			continue;
		
		gotoxy(_x, _y+2+i);
		std::cout<<puntajes[i].puntos<<" - "<<puntajes[i].nombre;
	}
}
