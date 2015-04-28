#include "Game.h"

Game::Game() : jugador( PISO0_Y, MAX_ASCENSO_SALTO_Y ), contador( clockContador.getElapsedTime().asSeconds(), FIN_JUEGO )
{	
	// Inicializo recursos
	std::srand( std::time( NULL ) );
	window.create( sf::VideoMode( 800, 600, 32 ), "TP2 - Nahuel Lattessi" );
	window.setFramerateLimit( 60 );
	imgMgr.addResourceDirectory( "Recursos/Imagenes/" );
	background.setTexture( imgMgr.getImage( "fondo_plataformas.png" ));
	puerta.setTexture( imgMgr.getImage( "puerta.png" ) );
	puerta.setPosition( PUERTA_X, PUERTA_Y );

	// Inicializo al jugador
	jugador.setTexture( imgMgr.getImage( "jumper.png" ) );
	jugador.setPosition( 50, PISO0_Y );
	teclaSaltoPresionada = false;
	isFinJuego = false;
	isGanoJuego = false;

	// Inicializo pilas y colas
	// 1º piso
	colaPiso1 = cargarCola( imgMgr );
	// 2º piso
	pila1Piso2 = cargarPila( imgMgr );
	pila2Piso2 = new Pila();
	// 3º piso
	colaPiso3 = cargarCola( imgMgr );
	// 4º piso
	pila1Piso4 = cargarPila( imgMgr );
	pila2Piso4 = new Pila();
	// 5º piso
	colaPiso5 = cargarCola( imgMgr );
	// 6º piso
	pila1Piso6 = cargarPila( imgMgr );
	pila2Piso6 = new Pila();
	
	//Cargo los nodos activos de cada piso
	shellPiso1 = colaPiso1->Leer();
	shellPiso1.setPosicion( 0, PISO1_Y );
	shellPiso2 = pila1Piso2->pop();
	shellPiso2.setPosicion( 0, PISO2_Y );
	shellPiso3 = colaPiso3->Leer();
	shellPiso3.setPosicion( 0, PISO3_Y );
	shellPiso4 = pila1Piso4->pop();
	shellPiso4.setPosicion( 0, PISO4_Y );
	shellPiso5 = colaPiso5->Leer();
	shellPiso5.setPosicion( 0, PISO5_Y );
	shellPiso6 = pila1Piso6->pop();
	shellPiso6.setPosicion( 0, PISO6_Y );
}



Game::~Game() 
{
	delete colaPiso1, colaPiso3, colaPiso5;
	delete pila1Piso2, pila2Piso2, pila1Piso4, pila2Piso4, pila1Piso6, pila2Piso6;
}

void Game::Run()
{
	while( window.isOpen() ) 
	{
		float delta_time_seconds = clock.restart().asSeconds();
		
		sf::Event event;
		while( window.pollEvent( event )) {
			if( event.type == sf::Event::Closed ) {
				window.close();
			}
			if ( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space ) {
				teclaSaltoPresionada = true;
			}
			if ( event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space ) {
				teclaSaltoPresionada = false;
			}
		}

		if ( contador.GetFin() || isFinJuego )
		{
			finJuego( isGanoJuego );
			while( window.isOpen() ) {
				sf::Event event;
				while( window.pollEvent( event )) {
					if( event.type == sf::Event::Closed ) {
						window.close();
					}
				}
			}
		} else {
			contador.Update( clockContador.getElapsedTime().asSeconds() );
			shellPiso1.Update( delta_time_seconds );
			shellPiso2.Update( delta_time_seconds );
			shellPiso3.Update( delta_time_seconds );
			shellPiso4.Update( delta_time_seconds );
			shellPiso5.Update( delta_time_seconds );
			shellPiso6.Update( delta_time_seconds );
			jugador.update( delta_time_seconds );
			jugador.ActualizarSalto( teclaSaltoPresionada, delta_time_seconds );

			CheckCollision();
			Draw();
		}
	}
}

Cola* Game::cargarCola( imageManager &imgMgr )
{
	Shell* shell;
	Cola *cola = new Cola();
	shell = new Shell();
	shell->setTexture( imgMgr.getImage( "shell_amarillo.png" ) );
	cola->Anadir( *shell );
	shell = new Shell();
	shell->setTexture( imgMgr.getImage( "shell_azul.png" ) );
	cola->Anadir( *shell );
	shell = new Shell();
	shell->setTexture( imgMgr.getImage( "shell_rojo.png" ) );
	cola->Anadir( *shell );
	shell = new Shell();
	shell->setTexture( imgMgr.getImage( "shell_verde.png" ) );
	cola->Anadir( *shell );
	return cola;
}

Pila* Game::cargarPila( imageManager &imgMgr )
{
	Shell* shell;
	Pila *pila = new Pila();
	shell = new Shell();
	shell->setTexture( imgMgr.getImage( "shell_rojo.png" ) );
	pila->push( *shell );
	shell = new Shell();
	shell->setTexture( imgMgr.getImage( "shell_amarillo.png" ) );
	pila->push( *shell );
	shell = new Shell();
	shell->setTexture( imgMgr.getImage( "shell_verde.png" ) );
	pila->push( *shell );
	shell = new Shell();
	shell->setTexture( imgMgr.getImage( "shell_azul.png" ) );
	pila->push( *shell );
	return pila;
}

void Game::CheckCollision()
{
	switch ( jugador.getPisoActual() ) {
		case 1 :
			if ( shellPiso1.getSprite().getGlobalBounds().intersects( jugador.getGlobalBounds() ) ) {
				isFinJuego = true;
			}
			break;

		case 2 :
			if ( shellPiso2.getSprite().getGlobalBounds().intersects( jugador.getGlobalBounds() ) ) {
				isFinJuego = true;
			}
			break;

		case 3 :
			if ( shellPiso3.getSprite().getGlobalBounds().intersects( jugador.getGlobalBounds() ) ) {
				isFinJuego = true;
			}
			break;

		case 4 :
			if ( shellPiso4.getSprite().getGlobalBounds().intersects( jugador.getGlobalBounds() ) ) {
				isFinJuego = true;
			}
			break;

		case 5 :
			if ( shellPiso5.getSprite().getGlobalBounds().intersects( jugador.getGlobalBounds() ) ) {
				isFinJuego = true;
			}
			break;

		case 6 :
			if ( shellPiso6.getSprite().getGlobalBounds().intersects( jugador.getGlobalBounds() ) ) {
				isFinJuego = true;
			} else if ( jugador.getGlobalBounds().intersects( puerta.getGlobalBounds() ) ) {
				isFinJuego = true;
				isGanoJuego = true;
			}
			break;
	}

	// Chequeo de colision en 1º piso
	if( shellPiso1.getSprite().getGlobalBounds().left > FIN_PANTALLA_X ) {
		colisionCola( shellPiso1, colaPiso1, PISO1_Y );
	}

	// Chequeo de colision en 2º piso
	// Por derecha
	if ( shellPiso2.getSprite().getGlobalBounds().left > FIN_PANTALLA_X ) {
		colisionPilaIzq( shellPiso2, pila1Piso2, pila2Piso2, PISO2_Y );
	}
	// Por izquierda
	if ( shellPiso2.getSprite().getGlobalBounds().left + shellPiso2.getSprite().getGlobalBounds().width < 0 ) {
		colisionPilaDer( shellPiso2, pila1Piso2, pila2Piso2, PISO2_Y );
	}

	// Chequeo de colision en 3º piso
	if( shellPiso3.getSprite().getGlobalBounds().left > FIN_PANTALLA_X ) {
		colisionCola( shellPiso3, colaPiso3, PISO3_Y );
	}

	// Chequeo de colision en 4º piso
	// Por derecha
	if ( shellPiso4.getSprite().getGlobalBounds().left > FIN_PANTALLA_X ) {
		colisionPilaIzq( shellPiso4, pila1Piso4, pila2Piso4, PISO4_Y );
	}
	// Por izquierda
	if ( shellPiso4.getSprite().getGlobalBounds().left + shellPiso4.getSprite().getGlobalBounds().width < 0 ) {
		colisionPilaDer( shellPiso4, pila1Piso4, pila2Piso4, PISO4_Y );
	}

	// Chequeo de colision en 5º piso
	if( shellPiso5.getSprite().getGlobalBounds().left > FIN_PANTALLA_X ) {
		colisionCola( shellPiso5, colaPiso5, PISO5_Y );
	}

	// Chequeo de colision en 6º piso
	// Por derecha
	if ( shellPiso6.getSprite().getGlobalBounds().left > FIN_PANTALLA_X ) {
		colisionPilaIzq( shellPiso6, pila1Piso6, pila2Piso6, PISO6_Y );
	}
	// Por izquierda
	if ( shellPiso6.getSprite().getGlobalBounds().left + shellPiso6.getSprite().getGlobalBounds().width < 0 ) {
		colisionPilaDer( shellPiso6, pila1Piso6, pila2Piso6, PISO6_Y );
	}
}

void Game::colisionCola( Shell &shell, Cola* cola, const int posY )
{
	cola->Anadir( shell );
	shell = cola->Leer();
	shell.setPosicion( 0, posY );
}

void Game::colisionPilaIzq( Shell &shell, Pila* pila1, Pila* pila2, const int posY )
{
	shell.cambiarDireccion();
	pila2->push( shell );
	if ( pila1->getCabeza() ) {
		shell = pila1->pop();
		shell.setPosicion( 0, posY );
	} else {
		shell = pila2->pop();
		shell.setPosicion( FIN_PANTALLA_X, posY );
	}
}

void Game::colisionPilaDer( Shell &shell, Pila* pila1, Pila* pila2, const int posY )
{
	shell.cambiarDireccion();
	pila1->push( shell );
	if ( pila2->getCabeza() ) {
		shell = pila2->pop();
		shell.setPosicion( FIN_PANTALLA_X, posY );
	} else {
		shell = pila1->pop();
		shell.setPosicion( 0, posY );
	}
}

void Game::Draw()
{
	
	window.clear();
	window.draw( background );
	window.draw( puerta );
	window.draw( jugador );
	window.draw( shellPiso1.getSprite() );
	window.draw( shellPiso2.getSprite() );
	window.draw( shellPiso3.getSprite() );
	window.draw( shellPiso4.getSprite() );
	window.draw( shellPiso5.getSprite() );
	window.draw( shellPiso6.getSprite() );	
	window.draw( contador.GetText() );
	window.display();
}

void Game::finJuego( bool win )
{
	sf::Text text;
	sf::String string;
	if( !font.loadFromFile( "Recursos/Fuentes/arial.ttf" ) ) {
		//ERROR
	}
	text.setFont( font );
	text.setCharacterSize( 48 );
	text.setStyle( sf::Text::Style::Bold );

	if ( win )
	{
		text.setColor( sf::Color::Green );
		string = "GANASTE!";		
	} else {
		text.setColor( sf::Color::Yellow );
		string = "PERDISTE...";		
	}	
	text.setString( string );
	text.setPosition( 250, 250 );
	window.draw( text );
	window.display();
}

