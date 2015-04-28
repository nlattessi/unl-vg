#include <SFML/Window.hpp>

#include "Megaman.h"

//#include "Player.h"

int main()
{
	// Creamos la ventana y definimos la porción visible del plano
	sf::RenderWindow window( sf::VideoMode( 640, 480 ), "TP 1 - Nahuel Lattessi" );
	window.setFramerateLimit(60);
	sf::FloatRect viewRect( 0, 0, 320, 240 );
	sf::View view( viewRect );
	window.setView( view );

	// Creamos e inicializamos nuestra estructura joystick
	JOYSTICK j;
	j.down = j.left = j.right = j.a = j.b = j.pressingA = j.pressingB = false;

	// Creamos el manejador para los disparos
	ManejadorDisparos disparos;

	// Creamos e inicializamos a Mega Man
	Megaman megaman( "Data/Megaman.png", "Data/Megaman.json", &disparos );
	megaman.setPosition( 80, 126 );

	// Creamos el fondo
	sf::Sprite fondo(TextureManager::GetInstance().GetTexture("Data/fondo.png"));
	
	//
	sf::Clock clk;
	float dt;
	sf::Event event;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        //sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
			
			//A BORRAR
			if (event.type == sf::Event::KeyPressed) {
				switch(event.key.code) {
					case sf::Keyboard::Down:	j.down = true; break;
					case sf::Keyboard::Left:	j.left = true; break;
					case sf::Keyboard::Right:	j.right = true; break;
					case sf::Keyboard::A:		(j.a)? j.pressingA = true : j.a = true; break;
					case sf::Keyboard::S:		(j.b)? j.pressingB = true : j.b = true; break;
					default: break;
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				switch(event.key.code) {
					case sf::Keyboard::Down:	j.down = false; break;
					case sf::Keyboard::Left:	j.left = false; break;
					case sf::Keyboard::Right:	j.right = false; break;
					case sf::Keyboard::A:		j.a = j.pressingA = false; break;
					case sf::Keyboard::S:		j.b = j.pressingB = false; break;
					default: break;
				}
			}
        }

		dt = clk.restart().asSeconds();

		// Actualizamos el estado de Mega Man y los disparos
		megaman.update( j, dt );
		disparos.updateDisparos( dt, viewRect );
	
		clk.restart();

		// Dibujamos
		window.clear( sf::Color::Black );
		window.draw( fondo );
		disparos.drawDisparos( window );
		window.draw( megaman );
		window.display();
    }

    return 0;
}