#include "Circulo.h"

Circulo::Circulo(int _anchoWnd, int _altoWnd, int _pos)
{
	//Imagen y sprite
	imagen.LoadFromFile("Imagenes\\rcircle.png");
	imgAncho = imagen.GetWidth();
	imgAlto = imagen.GetHeight();
	sprite.SetImage(imagen);
	sprite.SetCenter(sprite.GetSize().x/2.0f, sprite.GetSize().y/2.0f);

	//Posicion
	//0: Sup Izq - 1: Sup Der - 2: Inf izq - 3: Inf der
	switch (_pos)
	{
		case 0:
			sprite.SetPosition(imgAncho/2, imgAlto/2);
			break;

		case 1:
			sprite.SetPosition(_anchoWnd-imgAncho/2, imgAlto/2);
			break;

		case 2:
			sprite.SetPosition(imgAncho/2, _altoWnd-imgAlto/2);
			break;

		case 3:
			sprite.SetPosition(_anchoWnd-imgAncho/2, _altoWnd-imgAlto/2);
			break;

		default:
			break;
	}
}

Circulo::~Circulo()
{
}

bool Circulo::IsAdentro(Vector2f _diff)
{
	if (norma(_diff) < imgAlto/2)
		return true;
	else
		return false;
}