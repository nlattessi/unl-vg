#include "Entidad.h"

class Cursor : public Entidad
{
public:
	Cursor(int _anchoWnd, int _altoWnd);
	~Cursor();

	//Metodo que mueve el sprite seg�n la posici�n que recibe
	//del evento al mover el mouse
	inline void Mover(int _x, int _y) { sprite.SetPosition(_x, _y); };
};