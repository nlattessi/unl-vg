#include "Entidad.h"
#include <math.h> //Para poder usar las funciones sin() y cos()
#define PI 3.14159265 //Defino a Pi como constante
#define G 9.81 //Defino a G (gravedad) como constante

class Bala : public Entidad
{
private:
	float xi, xf, yi, yf, vx, vy, dt;

public:
	Bala(float _v, sf::Sprite& _cannon, sf::Image& imagen);
	~Bala(void);

	void Update(float _ft, float _velViento);
};