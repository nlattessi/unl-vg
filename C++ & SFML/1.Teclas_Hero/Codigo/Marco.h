#include "Entidad.h"

class Marco : public Entidad
{
public:
	Marco(int _anchoWnd, int _altoWnd);
	~Marco();

	//Metodo que devuelve los limites superiores
	//e inferiores del sprite
	inline int getYSup() { return sprite.GetPosition().y - imagen.GetHeight()/2; };
	inline int getYInf() { return sprite.GetPosition().y + imagen.GetHeight()/2; };
};