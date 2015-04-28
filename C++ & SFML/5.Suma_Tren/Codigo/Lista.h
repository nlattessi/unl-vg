#ifndef LISTA_H
#define LISTA_H

#include "Nodo.h"

class Lista
{
	public:
		Lista( float speedX_);
		~Lista();

		void	insertar( int valor, sf::Sprite sprite );
		bool	listaVacia();
		void	ordenarSprites();
		Nodo*	getPrimero();
		void	update( float delta_time_seconds );
		Nodo*	getUltimo();
		void	borrarUltimo();
		void	borrar( int valor );

	private:
		Nodo*	primero;
		float	speedX;
};

#endif