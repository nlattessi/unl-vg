#include "Entidad.h"

class Fondo : public Entidad
{
public:
	Fondo(sf::Image& imagen) { sprite.SetImage(imagen); };
	~Fondo() {};
};