#include "Bala.h"

Bala::Bala(float _v, sf::Sprite& _cannon, sf::Image& imagen)
{
	float cannonA, cannonX, cannonY, cannonH;

	//Cargo sprite
	sprite.SetImage(imagen);
	sprite.SetCenter(imagen.GetWidth()/2, imagen.GetHeight()/2);

	//Inicializo variables
	dt = 0.0f;
	cannonA = _cannon.GetRotation();
	cannonX = _cannon.GetPosition().x;
	cannonY = _cannon.GetPosition().y;
	//Tomo el tama�o sobre el eje x como el largo del ca�on
	//porque sin rotar la misma se encuentra en horizontal
	cannonH = _cannon.GetSize().x;

	//Descompongo la velocidad inicial
	vx = _v * (cos(cannonA/180*PI));
	vy = _v * (sin(cannonA/180*PI));

	//Posicion inicial bala seg�n la posici�n del ca�on
	//usando trigonometria
	xi = cannonX + ((cos(cannonA/180*PI) * cannonH));
	yi = cannonY - ((sin(cannonA/180*PI) * cannonH));

	sprite.SetPosition(xi, yi);
}

Bala::~Bala(void)
{
}

void Bala::Update(float _ft, float _velViento)
{		
	//Actualizo la posici�n de la bala
	//seg�n las form�las de tiro parab�lico.
	//Tambi�n modifico la velocidad en X seg�n el viento
	
	dt = dt + _ft;
	
	xf = (xi + (vx + _velViento) * _ft);
	xi = xf;

	yf = yi + (-vy * dt) + (0.5 * G *dt * dt);
	
	sprite.SetPosition(xf, yf);
}