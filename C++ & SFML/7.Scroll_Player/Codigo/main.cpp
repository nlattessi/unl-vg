#include <SFML/Graphics.hpp>

#include "TextureManager.h"
#include "Player.h"
#include "Nivel.h"


bool smoothScroll = false;
const int resx = 800;
const int resy = 400;

int main()
{
	// Creamos la ventana y definimos la porción visible del plano
	sf::RenderWindow window( sf::VideoMode( resx, resy ), "TP 2 - Nahuel Lattessi" );
	//window.setFramerateLimit(60);
	
	Nivel n("Media/lvl.lev");
	n.InitLevelView( resx, resy );
	window.setView( n.GetView() );

	// Creamos e inicializamos nuestra estructura joystick
	JOYSTICK j;
	j.down = j.left = j.right = j.a = j.b = j.pressingA = j.pressingB = false;

	// Creamos el manejador para los disparos
	ManejadorDisparos disparos;

	// Creamos e inicializamos a Player
	Player player( "Media/player.png", &disparos, &n );
	player.setPosition( 96, 64 );

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

		// hacemos scrolling
		if(!smoothScroll)n.SetViewCenter(player.getPosition());
		else n.SetViewCenterSmooth(player.getPosition(), 0.5, dt);
		
		//sf::FloatRect viewRect = n.GetView().getViewport();
		float left = n.GetView().getCenter().x - (n.GetView().getSize().x / 2.f);
		float top = n.GetView().getCenter().y - (n.GetView().getSize().y / 2.f);
		sf::FloatRect viewRect( left, top, n.GetView().getSize().x, n.GetView().getSize().y );

		// Actualizamos el estado de Player y los disparos
		player.update( j, dt );
		disparos.updateDisparos( dt, viewRect );		

		window.setView( n.GetView() );

		window.clear();
		n.Draw( window );
		window.draw( player );
		disparos.drawDisparos( window );
		window.display();

    }

    return 0;
}