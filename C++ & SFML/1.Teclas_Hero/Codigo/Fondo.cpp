#include "Fondo.h"

Fondo::Fondo(int _anchoWnd, int _altoWnd)
{
	//Tomo un numero al azar y cargo una imagen
	//distinta según cual salió
	switch (Randomizer::Random(1,7))
	{
		case 1:
			imagen.LoadFromFile("Imagenes\\background1.jpg");
			sprite.SetImage(imagen);
			//Escalo por si la resolucion elegida es menor o mayor a 640x480
			sprite.SetScale(_anchoWnd/(float)imagen.GetWidth(), _altoWnd/(float)imagen.GetHeight());
			break;

		case 2:
			imagen.LoadFromFile("Imagenes\\background2.jpg");
			sprite.SetImage(imagen);
			sprite.SetScale(_anchoWnd/(float)imagen.GetWidth(), _altoWnd/(float)imagen.GetHeight());
			break;

		case 3:
			imagen.LoadFromFile("Imagenes\\background3.jpg");
			sprite.SetImage(imagen);
			sprite.SetScale(_anchoWnd/(float)imagen.GetWidth(), _altoWnd/(float)imagen.GetHeight());
			break;

		case 4:
			imagen.LoadFromFile("Imagenes\\background4.jpg");
			sprite.SetImage(imagen);
			sprite.SetScale(_anchoWnd/(float)imagen.GetWidth(), _altoWnd/(float)imagen.GetHeight());
			break;

		case 5:
			imagen.LoadFromFile("Imagenes\\background5.jpg");
			sprite.SetImage(imagen);
			sprite.SetScale(_anchoWnd/(float)imagen.GetWidth(), _altoWnd/(float)imagen.GetHeight());
			break;

		case 6:
			imagen.LoadFromFile("Imagenes\\background6.jpg");
			sprite.SetImage(imagen);
			sprite.SetScale(_anchoWnd/(float)imagen.GetWidth(), _altoWnd/(float)imagen.GetHeight());
			break;

		//De salir 7, no cargo nada imagen y queda el
		//fondo negro
		default:		
			break;
	}
}

Fondo::~Fondo()
{
}