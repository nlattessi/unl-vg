#ifndef COLA_H
#define COLA_H

#include <iostream>

#include "Nodo.h"

class Cola
{
	public:
		Cola();
		~Cola();
		
		void	Anadir( Shell shell );
		void	Anadir( sf::Texture textura );
		Shell	Leer();

	private:
		Nodo*	primero;
		Nodo*	ultimo;
};

#endif