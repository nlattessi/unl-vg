#include "Animation.h"
#include <iostream>

// construye la animacion inicializando todas las variables
Animation::Animation(bool loop){
	this->loop=loop;
	Reset();
}

// agrega un nuevo cuadro con su respectiva duracion
void Animation::AddFrame(sf::IntRect &i, float frameLenght){
	rects.push_back(&i);
	frameTimes.push_back(frameLenght);
	nFrames++;
}

// avanza la animacion en base al tiempo transcurrido
// tiene en cuenta si debe hacer un loop o finalizar
// ademas devuelve un puntero a la IntRectn actual de
// la animacion para un uso mas comodo
sf::IntRect &Animation::Animate(float dt){
	currentFrameElapsed+=dt;
	if(currentFrameElapsed>frameTimes[iframe]){
		currentFrameElapsed-=frameTimes[iframe];
		iframe++;
		if(iframe>=rects.size()){
			if(loop)
				// volvemos al principio
				iframe=0;
			else{
				// la animacion finalizo
				iframe--;
				end=true;
			}
		}
	}
	return *rects[iframe];
}

// devuelve un puntero a la imagen actual de la animacion
sf::IntRect &Animation::GetCurrentFrame(){
	return *rects[iframe];
}

// estas 2 funciones permiten controlar si se debe
// o no hacer loop
void Animation::SetLoop(bool loop){
	this->loop=loop;
}

bool Animation::GetLoop(){
	return loop;
}

// permite saber si la animacion termino
// (en caso de que no haga loop)
bool Animation::Ended(){
	return end;
}

// reinicializa la animacion
void Animation::Reset(){
	iframe=0; currentFrameElapsed=0; end=false;
}

// estas funciones permiten un mayor control
// nos van a ser utiles mas adelante
void Animation::SetCurrentFrameNum(int i){
	iframe=i;
}

int Animation::GetCurrentFrameNum(){
	return iframe;
}

float Animation::GetCurrentFrameElapsedTime(){
	return currentFrameElapsed;
}

// Para uso con clase FRAME
void Animation::AddFrame( Frame &f, float frameLenght )
{
	frames.push_back( &f );
	frameTimes.push_back( frameLenght );
	nFrames++;
}

sf::IntRect &Animation::animateNew( float dt )
{
	currentFrameElapsed += dt;
	if ( currentFrameElapsed > frameTimes[iframe] ) {
		currentFrameElapsed -= frameTimes[iframe];
		iframe++;
		if ( iframe >= frames.size() ) {
			if ( loop )
				// volvemos al principio
				iframe = 0;
			else {
				// la animacion finalizo
				iframe--;
				end = true;
			}
		}
	}
	return frames[iframe]->rect;
}

sf::IntRect &Animation::GetCurrentFrameNew()
{
	return frames[iframe]->rect;
}

sf::Vector2f Animation::getOffset()
{
	return frames[iframe]->offset;
}