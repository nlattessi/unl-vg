#include "Entidad.h"

class Circulo : public Entidad
{
private:
	int imgAncho, imgAlto;

	//Metodo auxiliar para obtener la norma de un vector,
	//necesario para obtener la norma euclideana
	inline float norma(Vector2f _vec) { return sqrtf(_vec.x*_vec.x+_vec.y*_vec.y); };

public:
	Circulo(int _anchoWnd, int _altoWnd, int _pos);
	~Circulo();

	//Metodo para determinar si el cursor está dentro
	//del circulo
	bool IsAdentro(Vector2f _diff);
};