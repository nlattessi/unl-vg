#include "Pila.h"

Pila::Pila()
{
	cabeza = NULL;
}

Pila::~Pila()
{
	Nodo* aux;
	while ( cabeza ) {
		aux = cabeza;
		cabeza = cabeza->sig;
		delete aux;
	}
}

void Pila::push( Shell shell )
{
	Nodo* nuevo = new Nodo( shell, cabeza );
	cabeza = nuevo;
}

Shell* Pila::top()
{
	Nodo* nodo;
	
	if ( !cabeza ) {
		return NULL;
	}
	nodo = cabeza;
	
	return &nodo->getShell();
}

Shell Pila::pop()
{
	Nodo* nodo;
	Shell shell;

	if ( !cabeza ) {
		return shell;
	}
	nodo = cabeza;
	cabeza = nodo->sig;
	shell = nodo->getShell();
	delete nodo;
	return shell;
}

Nodo* Pila::getCabeza()
{
	return cabeza;
}