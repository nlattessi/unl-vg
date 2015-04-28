#include "Game.h"

Game::Game()
{	
	// Inicializo recursos
	std::srand( std::time( NULL ) );
	window.create( sf::VideoMode( 800, 600, 32 ), "TP3 - Nahuel Lattessi" );
	window.setFramerateLimit( 60 );
	imgMgr.addResourceDirectory( "Recursos/Imagenes/" );
	if( !font1.loadFromFile( "Recursos/Fuentes/comic.ttf" ) ) {
		//ERROR
	}
	if( !font2.loadFromFile( "Recursos/Fuentes/arial.ttf" ) ) {
		//ERROR
	}
	contador = new Contador( clockContador.getElapsedTime().asSeconds(), FIN_SUMA);
	contador->setPosition( 250.0f, 150.0f );
	finJuego = false;
	ganoJuego = false;

	// Inicializo variables de la ecuacion de suma
	isSuma = false;
	errores = 0;
	text.setFont( font2 );
	text.setColor( sf::Color::Black );
	text.setPosition( 270.0f, 200.0f );
	textErrores.setFont( font2 );
	textErrores.setStyle( sf::Text::Bold );
	textErrores.setColor( sf::Color::Black );
	textErrores.setPosition( 400.0f, 150.0f );
	textErrores.setCharacterSize( 20 );
	std::ostringstream temp;
	temp << "Errores: " << errores;
	textErrores.setString( temp.str() );
	rectangulo.setSize( sf::Vector2f( 300.0f, 150.0f ) );
	rectangulo.setFillColor( sf::Color::White );
	rectangulo.setPosition( 250.0f, 150.0f );	
	
	// Inicializo al tren y los vagones sueltos
	tren = new Lista( SPEED_X );
	sf::Sprite spriteAux;
	spriteAux.setTexture( imgMgr.getImage( "locomotora.png" ) );
	tren->insertar( 0, spriteAux );
	spriteAux.setTexture( imgMgr.getImage( "vagon.png" ) );
	tren->insertar( rand() % 99 + 1, spriteAux );
	tren->insertar( rand() % 99 + 1, spriteAux );
	tren->ordenarSprites();
	vagon1 = new sf::Sprite( imgMgr.getImage( "vagon.png" ) );
	vagon1->setPosition( 300, CARRIL_2);
	vagon2 = new sf::Sprite( imgMgr.getImage( "vagon.png" ) );
	vagon2->setPosition( 450, CARRIL_3);
	vagon3 = new sf::Sprite( imgMgr.getImage( "vagon.png" ) );
	vagon3->setPosition( 600, CARRIL_4);
}

Game::~Game()
{
	delete tren;
	delete vagon1, vagon2, vagon3;
	delete contador;
}

void Game::Run()
{
	while( window.isOpen() ) 
	{
		float delta_time_seconds = clock.restart().asSeconds();
		sf::Event event;
		while( window.pollEvent( event )) {
			if ( event.type == sf::Event::Closed ) {
				window.close();
			}
			// Guardo input del usuaro del resultado
			// de suma (solo me quedo con los numeros)
			if ( event.type == sf::Event::TextEntered && isSuma ) {
				if ( event.text.unicode < 128 ) {
					char ch = static_cast<char> ( event.text.unicode );
					if ( ch >= '0' && ch <= '9' ) {
						buffer += ch;
						text.setString( buffer );
					}
				}
			}
			// Analizo el resultado enviado por el usuario.
			// Si es incorrecto, sumo un error y hago una nueva suma
			// Si es correcto, agrego el vagon con ese resultado.
			if ( event.type == sf::Event::KeyPressed && isSuma ) {
				if ( event.key.code == sf::Keyboard::Return ) {
					std::ostringstream temp;
					temp << resultado;
					if ( sf::String::InvalidPos == text.getString().find( temp.str() ) ) {
						errores++;
						tren->borrar(tren->getUltimo()->getValor());
						std::ostringstream temp;
						temp << "Errores: " << errores;
						textErrores.setString( temp.str() );
						if ( errores == 3 ) {
							finJuego = true;
							ganoJuego = false;
						} else {
							armarSuma();						
						}
					} else {
						isSuma = false;
						sf::Sprite sprite( imgMgr.getImage( "vagon.png" ) );
						tren->insertar( resultado, sprite );
						tren->ordenarSprites();
						if ( vagon1 ) {
							delete vagon1;
							vagon1 = NULL;
						} else if ( vagon2 ) {
							delete vagon2;
							vagon2 = NULL;
						} else if ( vagon3 ) {
							delete vagon3;
							vagon3 = NULL;
						}
					}
				}
				// Si el jugador quiere borrar utilizo el tamaño
				// del buffer de entrada para determinar hasta
				// donde puede borrar
				if ( event.key.code == sf::Keyboard::BackSpace ) {
					float size = buffer.getSize() - 1;
					if ( size != tamBuffer ) {
						buffer.erase( buffer.getSize() - 1 );
						text.setString( buffer );
					} 					
				}
			}
		}
		// Si finalizó el juego ejecuto finalizarJuego()
		// y mantengo la ventan abierta hasta que el
		// jugador la cierre
		if ( finJuego ) {
			finalizarJuego( ganoJuego );
			while( window.isOpen() ) {
				sf::Event event;
				while( window.pollEvent( event ) ) {
					if( event.type == sf::Event::Closed ) {
						window.close();
					}
				}
			}
		} else {
			// Actualizo en base a si el tren esta detenido
			// por una suma o si éstá en movimiento
			if ( isSuma ) {
				contador->Update( clockContador.getElapsedTime().asSeconds() );
				if ( contador->GetFin() ) {
					errores++;
					std::ostringstream temp;
					temp << "Errores: " << errores;
					textErrores.setString( temp.str() );
					if ( errores == 3 ) {
						finJuego = true;
						ganoJuego = false;
					} else {
						armarSuma();
					}
				}
				drawSuma();
			} else {
				tren->update( delta_time_seconds );
				CheckCollision();
				Draw();
			}
		}
	}
}

void Game::CheckCollision()
{
	Nodo* nodoAux;
	nodoAux = tren->getPrimero();
	// Evaluo si la locomotora se choca con un vagon suelto
	// y armo la suma de ser asi
	if ( vagon1 && nodoAux->getSprite().getGlobalBounds().intersects( vagon1->getGlobalBounds() ) ) {
			armarSuma();
	} else if ( vagon2 && nodoAux->getSprite().getGlobalBounds().intersects( vagon2->getGlobalBounds() ) ) {
			armarSuma();
	} else if ( vagon3 && nodoAux->getSprite().getGlobalBounds().intersects( vagon3->getGlobalBounds() ) ) {
			armarSuma();
	}
	// Chequeo cada vagon si llega al fin de pantalla
	// y si es asi lo muevo al siguiente carril
	while ( nodoAux ) {
		if ( nodoAux->getSprite().getGlobalBounds().left > FIN_PANTALLA_X ) {
			if ( nodoAux->getSprite().getPosition().y == CARRIL_1 ) {
				nodoAux->setSpritePosition( 0, CARRIL_2 );
			} else if ( nodoAux->getSprite().getPosition().y == CARRIL_2 ) {
				nodoAux->setSpritePosition( 0, CARRIL_3 );
			} else if ( nodoAux->getSprite().getPosition().y == CARRIL_3 ) {
				nodoAux->setSpritePosition( 0, CARRIL_4 );
			} else if ( nodoAux->getSprite().getPosition().y == CARRIL_4 ) {
				nodoAux->setSpritePosition( 0, CARRIL_5 );
			} 
		}
		nodoAux = nodoAux->sig;
	}
	// Chequeo si pasó el ultimo vagón por la salida
	if ( tren->getUltimo()->getSprite().getPosition().y == CARRIL_5 ) {
		if ( tren->getUltimo()->getSprite().getGlobalBounds().left > FIN_PANTALLA_X ) {
			finJuego = true;
			ganoJuego = true;
		}
	}
}

void Game::Draw()
{
	window.clear();
	Nodo* nodoAux;
	sf::Text texto;
	std::ostringstream temp;
	texto.setFont( font1 );
	texto.setCharacterSize( 36 );
	texto.setColor( sf::Color::Yellow );
	texto.setStyle( sf::Text::Style::Bold );
	// Dibujo la locomotora primero
	// porque no tiene valor
	nodoAux = tren->getPrimero();	
	window.draw( nodoAux->getSprite() );
	nodoAux = nodoAux->sig;
	// Dibujo el sprite de cada vagon y su valor
	while ( nodoAux ) {	
		temp << nodoAux->getValor();
		texto.setString( temp.str());
		texto.setPosition( nodoAux->getSprite().getPosition().x + 50, nodoAux->getSprite().getPosition().y + 5 );
		window.draw( nodoAux->getSprite() );
		window.draw( texto );
		nodoAux = nodoAux->sig;
		temp.str("");
	}
	// Dibujo los vagones sueltos
	// si todavia no fueron sumados
	if ( vagon1 ) {
		window.draw( *vagon1 );
	}
	if ( vagon2 ) {
		window.draw( *vagon2 );
	}
	if ( vagon3 ) {
		window.draw( *vagon3 );
	}
	window.display();
}

void Game::drawSuma()
{
	window.clear();
	Nodo* nodoAux;
	sf::Text texto;
	std::ostringstream temp;
	texto.setFont( font1 );
	texto.setCharacterSize( 36 );
	texto.setColor( sf::Color::Yellow );
	texto.setStyle( sf::Text::Style::Bold );
	// Dibujo la locomotora primero
	// porque no tiene valor
	nodoAux = tren->getPrimero();	
	window.draw( nodoAux->getSprite() );
	nodoAux = nodoAux->sig;
	// Dibujo el sprite de cada vagon y su valor
	while ( nodoAux ) {	
		temp << nodoAux->getValor();
		texto.setString( temp.str());
		texto.setPosition( nodoAux->getSprite().getPosition().x + 50, nodoAux->getSprite().getPosition().y + 5 );
		window.draw( nodoAux->getSprite() );
		window.draw( texto );
		nodoAux = nodoAux->sig;
		temp.str("");
	}
	// Dibujo los vagones sueltos
	// si todavia no fueron sumados
	if ( vagon1 ) {
		window.draw( *vagon1 );
	}
	if ( vagon2 ) {
		window.draw( *vagon2 );
	}
	if ( vagon3 ) {
		window.draw( *vagon3 );
	}
	//Dibujo el cuadro de suma
	window.draw( rectangulo );
	window.draw( contador->GetText() );
	window.draw( textErrores );
	window.draw( text );
	window.display();
}


void Game::armarSuma()
{
	// Establezco los numeros al azar,
	// guardo el resultad y armo el string
	std::ostringstream str;
	primerNumero = rand() % 99 + 1;
	segundoNumero = rand() % 99 + 1;
	tercerNumero = rand() % 99 + 1;
	resultado = primerNumero + segundoNumero + tercerNumero;
	str << primerNumero << " + " << segundoNumero << " + " << tercerNumero << " = ";
	text.setString( str.str() );
	buffer = str.str();
	tamBuffer = buffer.getSize() - 1;
	isSuma = true;
	delete contador;
	contador = new Contador( clockContador.getElapsedTime().asSeconds(), FIN_SUMA);
	contador->setPosition( 250.0f, 150.0f );
}

void Game::finalizarJuego( bool win )
{
	sf::Text text;
	sf::String string;
	text.setFont( font1 );
	text.setCharacterSize( 48 );
	text.setStyle( sf::Text::Style::Bold );
	if ( win ) {
		text.setColor( sf::Color::Green );
		string = "GANASTE!";
	} else {
		text.setColor( sf::Color::Yellow );
		string = "PERDISTE...";	
	}	
	text.setString( string );
	text.setPosition( 250, 250 );
	window.clear();
	window.draw( text );
	window.display();
}