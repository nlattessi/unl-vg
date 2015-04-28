#include "Lista.h"

Lista::Lista( float speedX_)
{
	primero = NULL;
	speedX = speedX_;
}

Lista::~Lista()
{
	Nodo* nodoAux;
	while ( primero ) {
		nodoAux = primero;
		primero = primero->sig;
		delete nodoAux;
	}
}

void Lista::insertar( int valor, sf::Sprite sprite )
{
	Nodo* anterior;
	if ( listaVacia() || ( primero->valor > valor ) ) {
		primero = new Nodo( valor, sprite );
	} else {
		anterior = primero;
		while ( anterior->sig && ( anterior->sig->valor <= valor ) ) {
			anterior = anterior->sig;
		}
		anterior->sig = new Nodo( valor, sprite, anterior->sig );
	}
}

void Lista::borrar( int valor ) 
{
	Nodo* anterior = NULL;
	Nodo* nodoAux = primero;
	while ( nodoAux && ( nodoAux->valor < valor ) ) {
		anterior = nodoAux;
		nodoAux = nodoAux->sig;
	}
	if ( !nodoAux || ( nodoAux->valor != valor ) ) {
		return;
	} else {
		if ( !anterior ) {
			primero = nodoAux->sig;
		} else {
			anterior->sig = nodoAux->sig;			
		}
		delete nodoAux;
	}
}

bool Lista::listaVacia()
{
	if ( primero == NULL ) {
		return true;
	}
	return false;
}

void Lista::ordenarSprites()
{
	Nodo* nodoAux;
	float x, y;
	nodoAux = primero;
	x = primero->sprite.getPosition().x;
	y = primero->sprite.getPosition().y;
	nodoAux = primero->sig;	
	while ( nodoAux ) {
		x -= 130;
		nodoAux->sprite.setPosition(x,y);
		nodoAux = nodoAux->sig;
	}
}

Nodo* Lista::getPrimero()
{
	return primero;
}

void Lista::update( float delta_time_seconds )
{
	Nodo* nodoAux;
	nodoAux = primero;
	while ( nodoAux ) {
		nodoAux->sprite.move( 1.0f * speedX * delta_time_seconds, 0.0f );
		nodoAux = nodoAux->sig;
	}
}

Nodo* Lista::getUltimo()
{
	Nodo* ultimo;
	ultimo = primero;
	if ( !listaVacia() ) {
		while ( ultimo->sig ) {
			ultimo = ultimo->sig;
		}
	}
	return ultimo;
}