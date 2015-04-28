#include "Entidad.h"

//Defino los estados del Pato
#define AVANZANDO 1
#define MOVLATERAL 2
#define QUIETO 3

class Pato : public Entidad
{
private:	
	float velocidad;
	float direccion;
	float x, yi, yf, dt;
	float tiempoDetenerse, contadorDetenerse;
	float tiempoQuieto, contadorQuieto;
	bool activo;
	int estado;
	sf::Sound Sound;

public:
	Pato(sf::SoundBuffer& sb, sf::Image& imagen1, sf::Image& imagen2, sf::Image& imagen3);
	~Pato();

	void Update(float _ft);
	void Activar();
	void Activar(float _v, int _modo);

	inline bool isActivo() { return activo; };
	inline void Desactivar() { activo = false; };
	inline float GetVelocidad() { return velocidad; };
	inline void Cuack() { Sound.Play(); };
};