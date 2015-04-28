#include "Vida.h"

Vida::Vida(int _anchoWnd, int _altoWnd, int _num)
{
	//Imagen y sprite
	imagen.LoadFromFile("Imagenes\\heart.png");
	sprite.SetImage(imagen);
	sprite.SetCenter(imagen.GetWidth()/2, imagen.GetHeight()/2);

	//Seteo la posicion del sprite en base a que numero de vida es
	switch(_num + 1) //Porque el array va del 0 a 9
	{
		case 1: //En el centro de la pantalla, primera linea superior
			sprite.SetPosition(_anchoWnd/2, imagen.GetHeight()/2);
			break;

		case 2: //A la derecha de la primera vida
			sprite.SetPosition(_anchoWnd/2 + imagen.GetWidth(), imagen.GetHeight()/2);
			break;

		case 3: //A la izquierda de la primera vida
			sprite.SetPosition(_anchoWnd/2 - imagen.GetWidth(), imagen.GetHeight()/2);
			break;

		case 4: //A la derecha de la segunda vida
			sprite.SetPosition(_anchoWnd/2 + 2*imagen.GetWidth(), imagen.GetHeight()/2);
			break;

		case 5: //A la izquierda de la tercera vida
			sprite.SetPosition(_anchoWnd/2 - 2*imagen.GetWidth(), imagen.GetHeight()/2);
			break;

		case 6: //A la derecha de la cuarta vida
			sprite.SetPosition(_anchoWnd/2 + 3*imagen.GetWidth(), imagen.GetHeight()/2);
			break;

		case 7: //A la izquierda de la quinta vida
			sprite.SetPosition(_anchoWnd/2 - 3*imagen.GetWidth(), imagen.GetHeight()/2);
			break;

		case 8: //A la derecha de la sexta vida
			sprite.SetPosition(_anchoWnd/2 + 4*imagen.GetWidth(), imagen.GetHeight()/2);
			break;

		case 9: //A la izquierda de la septima vida
			sprite.SetPosition(_anchoWnd/2 - 4*imagen.GetWidth(), imagen.GetHeight()/2);
			break;

		case 10: //A la derecha de la octava vida
			sprite.SetPosition(_anchoWnd/2 + 5*imagen.GetWidth(), imagen.GetHeight()/2);
			break;

		default:
			break;
	}
}

Vida::~Vida()
{
}