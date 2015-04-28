#ifndef _PERSONAJE_H_
#define _PERSONAJE_H_

#include <SFML\Graphics.hpp>

//Declaración de constantes
const float			SPEED_X = 200.0f;
const float			SPEED_Y = 150.0f;

class Personaje : public sf::Sprite {
private:
	bool			saltoEnProceso, enAscenso;
	int				posicionTerrenoY, maxAscensoSaltoY;
public:
	Personaje( int x, int y );
	~Personaje();

	void			ActualizarSalto( bool teclaSaltoPresionada, float delta_time_seconds );
	void			update(float delta_time_seconds);
	inline void		InterrumpirSalto() { enAscenso = false; };
};

#endif