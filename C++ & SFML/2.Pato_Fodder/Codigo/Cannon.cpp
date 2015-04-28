#include "Cannon.h"

Cannon::Cannon(int _ancho, int _alto, sf::SoundBuffer& sb, sf::Image& imagen)
{
	//Cargo sprite
	sprite.SetImage(imagen);	
	sprite.SetCenter(0, imagen.GetHeight()/2);
	sprite.SetPosition(_ancho/2, 400);

	//Cargo sonido
	Sound.SetBuffer(sb);
	
	//Inicializo las variables
	angulo = 0.0;
	direccion = 0;
	velRotacion = 200; //Para que sea m�s r�pida la rotaci�n y m�s f�cil para el jugador
	estado = LISTO;
	timerEstado = 0.0f;
	tiempoCarga = 1.0f; //El Ca�on tarda 1 segundo en cargar una nueva Bala.
}

Cannon::~Cannon(void)
{
}

void Cannon::Update(float _ft)
{	
	//Si se actualiz� la direcci�n usando
	//como control el TECLADO, roto el Sprite
	//seg�n la velocidad de rotaci�n
	if (direccion != 0)
	{
		sprite.Rotate(direccion * velRotacion * _ft);

		if ((sprite.GetRotation() > 180) && (direccion == 1))
			sprite.SetRotation(180);
		if ((sprite.GetRotation() > 270) && (direccion == -1))
			sprite.SetRotation(0);

		direccion = 0;
	}

	//Si el Ca��n est� cargando, actualizo el
	//timer y chequeo si ya pas� el tiempo
	//para cambiar a su estado LISTO
	if (estado == CARGANDO)
	{		
		timerEstado += _ft;
		if (timerEstado > tiempoCarga)
		{
			timerEstado = 0.0f;
			estado = LISTO;
		}
	}
}

void Cannon::Disparar()
{
	//Reproduzco sonido y 
	//cambio al estado CARGANDO
	Sound.Play();
	estado = CARGANDO;
}

void Cannon::Rotar(float _mx, float _my)
{
	//Utilizo el Teorema de Pitagoras 
	//para rotar el ca�on seg�n la
	//posici�n del mouse en pantalla.
	
	float x, y, a;

	//Obtengo la diferencia entre el centro
	//del sprite y la posicion del mouse
	y = _my - sprite.GetPosition().y;
	x = _mx - sprite.GetPosition().x;

	//Obtengo el �ngulo con la funcion
	//inversa de la tangente usando los lados
	//del tri�ngulo que forman el centro del sprite
	//y la posici�n del mouse. Paso el resultado
	//de radianes a grados.
	a = ((atan2(y,x)) * 180) / PI;	
	
	//Le cambio el signo ya que el origen de coordenadas de
	//de la RenderWindow es la esquina superior izquierda
	a = -a;

	//Desprecio las rotaciones por debajo de la linea horizontal
	if ((a < 0) && (a >= -90))
		a = 0;
	if (a < -90)
		a = 180;

	//Seteo la nueva rotaci�n
	sprite.SetRotation(a);
}