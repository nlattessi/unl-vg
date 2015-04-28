#ifndef PILA_H
#define PILA_H

#include <iostream>

#include "Nodo.h"

class Pila
{
	public:
		Pila();
		~Pila();
		
		void	push( Shell shell );
		Shell	pop();
		Shell*	top();
		Nodo*	getCabeza();

	private:
		Nodo*	cabeza;
};

#endif