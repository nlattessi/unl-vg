#include "Tecla.h"

Tecla::Tecla(int _anchoWnd, int _altoWnd, float _velocidad)
{
	//Tomo un numero al azar para determinar que imagen
	//y codigo de tecla va a tener el objeto
	switch (Randomizer::Random(0,7))
	{
		case 0: //Flecha Izquierda
			imagen.LoadFromFile("Imagenes\\flecha_izquierda.png");
			codigo = Key::Left;
			break;

		case 1: //Flecha Derecha
			imagen.LoadFromFile("Imagenes\\flecha_derecha.png");
			codigo = Key::Right;
			break;

		case 2: //Flecha arriba
			imagen.LoadFromFile("Imagenes\\flecha_arriba.png");
			codigo = Key::Up;
			break;

		case 3: //Flecha abajo
			imagen.LoadFromFile("Imagenes\\flecha_abajo.png");
			codigo = Key::Down;
			break;

		case 4: //Letra W
			imagen.LoadFromFile("Imagenes\\letra_w.png");
			codigo = Key::W;
			break;

		case 5: //Letra A
			imagen.LoadFromFile("Imagenes\\letra_a.png");
			codigo = Key::A;
			break;

		case 6: //Letra S
			imagen.LoadFromFile("Imagenes\\letra_s.png");
			codigo = Key::S;
			break;

		case 7: //Letra D
			imagen.LoadFromFile("Imagenes\\letra_d.png");
			codigo = Key::D;
			break;

		default:
			break;
	}

	//Imagen y sprite
	sprite.SetImage(imagen);
	sprite.SetCenter(imagen.GetWidth()/2, imagen.GetHeight()/2);

	//Posicion
	x = _anchoWnd/2;
	y = _altoWnd;
	sprite.SetPosition(x, y);

	//Velocidad
	velocidad = _velocidad;

	//Color original del sprite
	colorOrig = sprite.GetColor();
}

Tecla::~Tecla()
{
}

void Tecla::Update(float _tf)
{
	y = y - velocidad*_tf;
	sprite.SetPosition(x, y);
}

void Tecla::ColorOriginal()
{
	sprite.SetColor(colorOrig);
}