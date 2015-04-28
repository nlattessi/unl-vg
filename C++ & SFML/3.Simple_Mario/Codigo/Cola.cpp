#include "Cola.h"

Cola::Cola()
{
	primero = ultimo = NULL;
}

Cola::~Cola()
{
	Nodo* nodoAux;
	while( ultimo ) {
		nodoAux = ultimo;
		ultimo = ultimo->sig;
		delete nodoAux;
	}
}

void Cola::Anadir( Shell shell )
{
	Nodo* nuevo = new Nodo( shell );
	if ( ultimo ) {
		ultimo->sig = nuevo;
	}
	ultimo = nuevo;
	if ( !primero ) {
		primero = nuevo;
	}
}

void Cola::Anadir( sf::Texture textura )
{
	Shell shell;
	shell.setTexture( textura );
		Nodo* nuevo = new Nodo( shell );
	if ( ultimo ) {
		ultimo->sig = nuevo;
	}
	ultimo = nuevo;
	if ( !primero ) {
		primero = nuevo;
	}
}

Shell Cola::Leer()
{
	Nodo* nodo;
	Shell shell;

	nodo = primero;
	if ( !nodo ) {
		return shell;
	}
	primero = nodo->sig;
	shell = nodo->getShell();
	delete nodo;
	if ( !primero ) {
		ultimo = NULL;
	}
	return shell;
}