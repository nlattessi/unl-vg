#ifndef MEGAMAN_H
#define MEGAMAN_H

#include <SFML\Graphics\Sprite.hpp>

#include "TextureManager.h"
#include "SpriteSheetManager.h"
#include "Animation.h"
#include "Disparos.h"

struct JOYSTICK
{
	bool down, left, right, a, b, pressingA, pressingB;
};

class Megaman : public sf::Sprite
{
	public:
		Megaman( std::string spriteSheetFile, std::string jsonFile, ManejadorDisparos *disparos );
		void update( JOYSTICK j, float dt );

	private:
		/* Estados */
		enum ESTADO {
			QUIETO,
			CORRIENDO,
			DISPARANDO,
			SALTANDO,
			DESLIZANDO,
			CORRIENDO_DISPARANDO,
			SALTANDO_DISPARANDO,
			SALTANDO_CORRIENDO,
			SALTANDO_CORRIENDO_DISPARANDO
		};
		ESTADO estado;
		void cambiarEstado( ESTADO nuevoEstado, bool continueFromCurrent = false );
		//
		enum BUSTER_LVL { NORMAL, BUSTER, MEGA_BUSTER };
		BUSTER_LVL busterLvl;

		/* Animaciones */
		enum BUSTER_ANIM { 
			NORMAL_0,
			BUSTER_0, BUSTER_1, BUSTER_2,
			MEGA_BUSTER_0, MEGA_BUSTER_1 };
		BUSTER_ANIM busterAnim;
		const float busterLvlChangeTime;
		float busterLvlClock;
		const float busterAnimChangeTime;
		float busterAnimClock;
		void cambiarBusterAnim( BUSTER_ANIM nuevoBusterAnim, bool continueFromCurrent = true );
		void updateBusterAnim( JOYSTICK j, float dt );
		//
		SpriteSheetManager ssm;
		Animation anim[9][6]; // 9 estados x 6 animaciones del Buster
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

		/* Slide */
		const float slide_time;
		float slideTime;

		/* Disparos */
		ManejadorDisparos *disparos;
		const float velDisparo;
		const float shoot_time;
		float shootTime;
		void disparar();
		void dispararBuster();

		/* Auxiliares */
		bool secuenciaFinalizada( float time );
		bool checkDisparo( JOYSTICK j );
		bool checkSalto( JOYSTICK j );
		bool checkQuieto( JOYSTICK j );
		bool checkDisparoBuster( JOYSTICK j );
};

#endif