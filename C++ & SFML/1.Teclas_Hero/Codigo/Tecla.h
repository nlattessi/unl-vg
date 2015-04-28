#include "Entidad.h"

class Tecla : public Entidad
{
private:
	float velocidad; //Guarda la velocidad
	Key::Code codigo; //Guarda la tecla del teclado correspondiente
	Color colorOrig; //Guarda el color original para poder restablecerlo
	float x, y; //Guarda la posicion del sprite, para asi poder moverlo

public:
	Tecla(int _anchoWnd, int _altoWnd, float _velocidad);
	~Tecla();

	//Metodo para actualizar su posicion
	void Update(float _Tf);

	//Metodo para volver a la imagen original del sprite
	void ColorOriginal();

	//Getters
	inline Key::Code getCodigo() { return codigo; };
	inline float getY() { return y; };

	//Setters
	inline void setColor(Color _color) { sprite.SetColor(_color); };
};
