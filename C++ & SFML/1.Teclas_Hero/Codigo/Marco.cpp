#include "Marco.h"

Marco::Marco(int _anchoWnd, int _altoWnd)
{
	//Imagen y sprite
	imagen.LoadFromFile("Imagenes\\cuad_blue.png");
	sprite.SetImage(imagen);
	sprite.SetCenter(imagen.GetWidth()/2, imagen.GetHeight()/2);

	//Posicion
	//A la posicion Y le resto 120 para que esté un
	//poco más arriba en la pantalla
	sprite.SetPosition(_anchoWnd/2, _altoWnd/2 - 120);	
}

Marco::~Marco()
{
}
