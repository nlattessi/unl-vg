#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML/Graphics/Sprite.hpp>

// Para uso con clase FRAME
#include "Frame.h"

class Animation
{	
	public:
		Animation(bool loop=true);
		// permite agregar un nuevo frame con su duracion
		void AddFrame(sf::IntRect &, float lenght);
	
		// permite avanzar la animacion un tiempo dt
		// y devolver el sf::IntRect actual
		sf::IntRect &Animate(float dt);
		sf::IntRect &GetCurrentFrame();
	
		// algunas funciones para controlar la animacion
		void SetLoop(bool loop);
		bool GetLoop();
		void Reset();
		bool Ended();
	
		// otras funciones para tener mayor control
		float GetCurrentFrameElapsedTime();
		void SetCurrentFrameNum(int i);
		int GetCurrentFrameNum();

		// Para uso con clase FRAME
		void AddFrame( Frame &, float frameLenght );
		sf::IntRect &animateNew( float dt );
		sf::IntRect &GetCurrentFrameNew();
		sf::Vector2f getOffset();

		int getSize() { return rects.size(); };

	private:
		// punteros a los sf::IntRect
		std::vector<sf::IntRect *> rects;
		// duracion de cada frame
		std::vector<float> frameTimes;
		// tiempo que ha sido mostrado el frame actual
		float currentFrameElapsed;
		// nro de frame actual y nro total de frames
		int iframe, nFrames;
		// banderas para saber si la animacion debe
		// ciclar o de lo contrario si ya finalizo
		bool loop, end;

		// Para uso con clase FRAME
		std::vector<Frame *> frames;

};

#endif