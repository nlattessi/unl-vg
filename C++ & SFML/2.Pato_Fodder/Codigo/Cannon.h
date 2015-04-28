#include "Entidad.h"

#include <math.h>
#define PI 3.14159265 //Defino a Pi como constante
//Estados del Cañon
#define LISTO 1
#define CARGANDO 2

class Cannon : public Entidad
{
private:
	float angulo;
	int direccion;
	int velRotacion;
	sf::Sound Sound;
	int estado;
	float timerEstado;
	float tiempoCarga;

public:
	Cannon(int _ancho, int _alto, sf::SoundBuffer& sb, sf::Image& imagen);
	~Cannon(void);

	void Update(float _ft);
	void Rotar(float _mx, float _my);
	void Disparar();

	inline int getEstado() { return estado; };
	inline void MoverIzq() { direccion = 1; };
	inline void MoverDer() { direccion = -1; };
};