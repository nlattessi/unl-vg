#include "Cursor.h"

Cursor::Cursor(int _anchoWnd, int _altoWnd)
{
	//Imagen y sprite
	imagen.LoadFromFile("Imagenes\\cursor.png");
	sprite.SetImage(imagen);
	sprite.SetCenter(imagen.GetWidth()/2, imagen.GetHeight()/2);

	//No centro la posicion ya que el cursor tiene la punta en su extremo superior izquierdo
}

Cursor::~Cursor()
{
}