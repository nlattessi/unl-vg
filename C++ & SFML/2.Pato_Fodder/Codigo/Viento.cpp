#include "Viento.h"

Viento::Viento()
{
	dirViento = 0;
	fuerzaViento = 0;
	timerViento = 0.0f;
	cambiaViento = 10.0f; //Cambio el viento cada 10 segundos
}

Viento::~Viento()
{
}

void Viento::Update(float _ft)
{
	//Actualizo el viento y cambio
	//su dirección y velocidad si
	//se cumple el tiempo seteado

	timerViento += _ft;
	if (timerViento > cambiaViento) //Veo si es momento de cambiar el viento
	{
		switch (sf::Randomizer::Random(0,2))
		{
			case 0: //0: sin viento
				dirViento = 1;
				break;
			case 1: //1: viento izq
				dirViento = -1;
				break;
			case 2: //2: viento der.
				dirViento = 1;
				break;
		}
		
		if (dirViento != 0)
			fuerzaViento = (sf::Randomizer::Random(0, 10)) * 10; //Tomo una fuerza aleatoria
		timerViento = 0.0f; //Reinicio el contador
	}
}