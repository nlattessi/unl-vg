#include "Pato.h"

Pato::Pato(sf::SoundBuffer& sb, sf::Image& imagen1, sf::Image& imagen2, sf::Image& imagen3)
{
	//Cargo sprite y centro eligiendo 1 entre las 3 imágenes
	switch(sf::Randomizer::Random(1,3))
	{
	case 1:
		sprite.SetImage(imagen1);
		sprite.SetCenter(imagen1.GetWidth()/2, imagen1.GetHeight());
		break;
	case 2:
		sprite.SetImage(imagen2);
		sprite.SetCenter(imagen2.GetWidth()/2, imagen2.GetHeight());
		break;
	case 3:
		sprite.SetImage(imagen3);
		sprite.SetCenter(imagen3.GetWidth()/2, imagen3.GetHeight());
		break;
	default:
		break;
	}

	//Cargo sonido
	Sound.SetBuffer(sb);

	//Inicializo variables
	activo = false;
}

Pato::~Pato()
{
}

void Pato::Update(float _ft)
{
	//Actualizo posición del Pato según su estado.
	
	//Si está AVANZANDO, muevo según las fórmulas de MRU.
	//También aumento el contador del momento de detenerse.
	//Si se cumple, tomo un tiempo random (entre 2 y 5 seg)
	//como el tiempo que debe estar quieto en el aire
	//y cambio al estado QUIETO...
	//Si esta QUIETO, aumento el contador de tiempo quieto.
	//Si se cumple el tiempo, reinicio el contador del momento
	//de detenerse y cambio al estado AVANZANDO.
	if (estado == AVANZANDO)
		if (contadorDetenerse > tiempoDetenerse)
		{
			estado = QUIETO;
			tiempoQuieto = sf::Randomizer::Random(2.0f,5.0f);
			contadorQuieto = 0.0f;
		}
		else
		{
			yf = yi + (velocidad * _ft);
			yi = yf;
			//dt += _ft;
			contadorDetenerse += _ft;
		}

	if (estado == QUIETO)
	{		
		contadorQuieto += _ft;
		if (contadorQuieto > tiempoQuieto)
		{
			estado = AVANZANDO;
			contadorDetenerse = 0.0f;
		}
	}

	sprite.SetPosition(x, yf);
}

void Pato::Activar()
{
	//Activo al Pato inicializando las variables
	//y tomando una velocidad random.
	activo = true;
	estado = AVANZANDO;
	x = sf::Randomizer::Random(100.0f, 700.0f);
	yi = 0.0f;
	//dt = 0.0f;
	tiempoDetenerse = sf::Randomizer::Random(2.0f,10.0f);
	contadorDetenerse = tiempoQuieto = contadorQuieto = 0.0f;
	velocidad = sf::Randomizer::Random(5.0f, 20.0f);
	sprite.SetPosition(x, yi);	
}

void Pato::Activar(float _v, int _modo)
{
	//Activo al Pato inicializando las variables
	//y eligiendo una velocidad según si debe ser
	//igual o mayor que la original.
	activo = true;
	estado = AVANZANDO;
	x = sf::Randomizer::Random(100.0f, 700.0f);
	yi = 0.0f;
	//dt = 0.0f;
	tiempoDetenerse = sf::Randomizer::Random(2.0f,10.0f);
	contadorDetenerse = tiempoQuieto = contadorQuieto = 0.0f;

	if (_modo == 1) //_modo == 1 -> Misma velocidad
		velocidad = _v;
	else //_modo == 2 -> Mayor velocidad que el anterior
		velocidad = _v + sf::Randomizer::Random(5.0f, 20.0f);

	sprite.SetPosition(x, yi);
}