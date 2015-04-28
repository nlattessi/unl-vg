#include "PantallaInicio.h"

PantallaInicio::PantallaInicio()
{
	//Cargo imagenes y sprites
	imgFondo.LoadFromFile("Imagenes\\FondoInicio.png");
	imgBoton.LoadFromFile("Imagenes\\boton.png");
	sprFondo.SetImage(imgFondo);
	sprBoton1.SetImage(imgBoton);
	sprBoton1.SetCenter(imgBoton.GetWidth()/2,imgBoton.GetHeight()/2);
	sprBoton2.SetImage(imgBoton);
	sprBoton2.SetCenter(imgBoton.GetWidth()/2,imgBoton.GetHeight()/2);

	//Cargo textos
	fuente.LoadFromFile("Fuentes\\Orbitron Medium.ttf", 24); //Cargo la fuente a usar
	
	txtTitulo.SetFont(fuente); //Fuente
	txtTitulo.SetStyle(sf::String::Bold); //Negrita
	txtTitulo.SetSize(48); //Tamaño
	txtTitulo.SetColor(sf::Color::Yellow); //Color
	//Creo Buffer, cargo texto y lo asigno al String
	std::ostringstream buff1;
	buff1<<"CUACBOOM!!!";
	txtTitulo.SetText(buff1.str());

	txtBoton1.SetFont(fuente); //Fuente
	txtBoton1.SetStyle(sf::String::Bold); //Negrita
	txtBoton1.SetSize(24); //Tamaño
	txtBoton1.SetColor(sf::Color::Red); //Color
	//Creo Buffer, cargo texto y lo asigno al String
	std::ostringstream buff2;
	buff2<<"Presionar 1"<<std::endl<<"para jugar con"<<std::endl<<"    TECLADO";
	txtBoton1.SetText(buff2.str());

	txtBoton2.SetFont(fuente); //Fuente
	txtBoton2.SetStyle(sf::String::Bold); //Negrita
	txtBoton2.SetSize(24); //Tamaño
	txtBoton2.SetColor(sf::Color::Red); //Color
	//Creo Buffer, cargo texto y lo asigno al String
	std::ostringstream buff3;
	buff3<<"Presionar 2"<<std::endl<<"para jugar con"<<std::endl<<"      MOUSE";
	txtBoton2.SetText(buff3.str());
}

PantallaInicio::~PantallaInicio()
{
}

int PantallaInicio::Mostrar(sf::RenderWindow& App)
{
	int salida = 0;
	sf::FloatRect rect;
	sf::Vector2f pos;

	//Posicion los sprites de los botones
	sprBoton1.SetPosition(App.GetWidth()/2-200, App.GetHeight()/2 + 100);
	sprBoton2.SetPosition(App.GetWidth()/2+200, App.GetHeight()/2 + 100);
	
	//Centro el texto en pantalla
	rect = txtTitulo.GetRect();
	pos.x = App.GetWidth()/2-rect.GetWidth()/2;
	pos.y = App.GetHeight()/2-rect.GetHeight()/2-200;
	txtTitulo.SetPosition(pos);

	//Posicion los textos de los botones
	rect = txtBoton1.GetRect();
	pos.x = App.GetWidth()/2-rect.GetWidth()/2-200;
	pos.y = App.GetHeight()/2-rect.GetHeight()/2+100;
	txtBoton1.SetPosition(pos);
	rect = txtBoton2.GetRect();
	pos.x = App.GetWidth()/2-rect.GetWidth()/2+200;
	pos.y = App.GetHeight()/2-rect.GetHeight()/2+100;
	txtBoton2.SetPosition(pos);

	//Dibujo la pantalla
	App.Draw(sprFondo);
	App.Draw(txtTitulo);
	App.Draw(sprBoton1);
	App.Draw(sprBoton2);
	App.Draw(txtBoton1);
	App.Draw(txtBoton2);
	App.Display();

	//Chequeo eventos para determinar
	//la elección del jugador
	while(App.IsOpened())
	{
		if (App.GetEvent(evt))
			if (evt.Type == sf::Event::Closed)
				App.Close();
			
			if (evt.Type == sf::Event::KeyPressed)
			{
				if (evt.Key.Code == sf::Key::Escape)
					App.Close();

				if (evt.Key.Code == sf::Key::Num1)
				{
					salida = 1;
					break;
				}

				if (evt.Key.Code == sf::Key::Num2)
				{
					salida = 2;
					break;
				}
			}
	}

	//Devuelvo la elección
	return salida;
}