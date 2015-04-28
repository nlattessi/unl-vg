#include <SFML\Graphics.hpp>
#include <sstream> //Para poder usar el objeto ostringstream

class PantallaInicio
{
private:
	sf::Image imgFondo;
	sf::Image imgBoton;
	sf::Sprite sprFondo;
	sf::Sprite sprBoton1, sprBoton2;
	sf::Font fuente;
	sf::String txtTitulo, txtBoton1, txtBoton2;
	sf::Event evt;

public:
	PantallaInicio();
	~PantallaInicio();

	int Mostrar(sf::RenderWindow& App);
};