#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SFML\Graphics.hpp>

//Declaración de constantes
const float	SPEED_X = 200.0f;
const float	SPEED_Y = 150.0f;

class Personaje : public sf::Sprite 
{
	public:
		Personaje( int x, int y );
		~Personaje();

		void			ActualizarSalto( bool teclaSaltoPresionada, float delta_time_seconds );
		void			update(float delta_time_seconds);
		inline void		InterrumpirSalto() { enAscenso = false; };
		int				getPisoActual();

	private:
		bool			saltoEnProceso, enAscenso;
		int				posicionTerrenoY, maxAscensoSaltoY;
		int				pisoActual;
};

#endif