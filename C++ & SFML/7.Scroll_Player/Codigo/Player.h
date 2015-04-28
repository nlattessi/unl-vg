#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics\Sprite.hpp>

#include "TextureManager.h"
#include "SpriteSheetManager.h"
#include "Animation.h"
#include "Disparos.h"
#include "Nivel.h"

struct JOYSTICK
{
	bool up, down, left, right, a, b, pressingA, pressingB;
};

class Player : public sf::Sprite
{
	public:
		//Player( std::string spriteSheetFile, ManejadorDisparos *disparos );
		Player( std::string spriteSheetFile, ManejadorDisparos *disparos, Nivel *n );
		void update( JOYSTICK j, float dt );

	private:
		/* Estados */
		enum ESTADO { QUIETO, CORRIENDO, DISPARANDO, SALTANDO, SALTANDO_CORRIENDO };
		ESTADO estado;
		void cambiarEstado( ESTADO nuevoEstado, bool continueFromCurrent = false );

		/* Animaciones */
		SpriteSheetManager ssm;
		Animation animaciones[5];
		void initAnimaciones();

		/* Movimiento en X */
		const float velX;
		int direccion;
		void flipX();


		/* Movimiento en Y */
		const float initJumpForce;
		const float gravity;
		float velY;
		float posY;
		bool isFalling;
		void saltar();
		bool colisionConSuelo();

		/* Disparos */
		ManejadorDisparos* disparos;
		const float velDisparo;
		const float shoot_time;
		float shootTime;
		void disparar();

		/* Nivel */
		Nivel *n;
		// para saber si al moverse chocara con alguna pared, suelo o el techo	
		bool ChocaraPared(float dt, float &distAjuste);
		bool ChocaraTecho(float dt, float &distAjuste);
		bool ChocaraSuelo(float dt, float &distAjuste);
		// devuelve el bounding box
		sf::FloatRect GetAABB();

		/* Auxiliares */
		bool secuenciaFinalizada( float time );
		bool checkDisparo( JOYSTICK j );
		bool checkSalto( JOYSTICK j );
		bool checkQuieto( JOYSTICK j );
};

#endif 