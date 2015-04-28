#ifndef NODO_H
#define NODO_H

#include <iostream>

#include "Shell.h"

class Nodo 
{
	public:
		Nodo( Shell shell_, Nodo *sig_ = NULL );
		~Nodo();

		Shell	getShell();

	private:
		Shell	shell;
		Nodo*	sig;
		bool	toLeft;

	friend class Cola;
	friend class Pila;
	friend class Game;
};

#endif