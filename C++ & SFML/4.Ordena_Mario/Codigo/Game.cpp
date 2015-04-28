#include "Game.h"

Game::Game() : jugador( POSICION_TERRENO_Y, MAX_ASCENSO_SALTO_Y ), contador( clockContador.getElapsedTime().asSeconds() ), valores(), bloques()
{	
	std::srand( std::time( NULL ) );

	window.create( sf::VideoMode( 800, 600, 32 ), "TP1 - Parte 2 - Nahuel Lattessi" );
	window.setFramerateLimit( 60 );

	imgMgr.addResourceDirectory( "Recursos/Imagenes/" );

	background.setTexture( imgMgr.getImage( "fondo.jpg" ));

	jugador.setTexture( imgMgr.getImage( "jumper.png" ) );
	jugador.setPosition( 400, POSICION_TERRENO_Y );

	if( !font.loadFromFile( "Recursos/Fuentes/comic.ttf" ) ) {
		//ERROR
	}

	//Creo arreglo de valores y bloques
	for( int i=0; i<10; i++) 
	{
		int n = std::rand() %999 + 1;
		sf::Text text;
		text.setFont( font );
		text.setCharacterSize( 16 );
		text.setColor( sf::Color::Yellow );
		text.setStyle( sf::Text::Style::Bold );
		char buff[20];
		std::sprintf( buff, "%i", n );
		text.setString( buff );
		text.setPosition( 75 + 70 * i, 400 );
		sf::Sprite sprite;
		sprite.setTexture( imgMgr.getImage( "bloque_pared.png" ) );
		sprite.setPosition( 70 + 70 * i,  390 );
		Bloque b;
		b.SetSprite( sprite );
		b.SetTexto( text );
		b.SetValor( n );
		bloques.push_back( b );
		valores.push_back( n );
	}

	//Ordeno el vector de valores para poder evaluar
	//si el jugador golpea el bloque correcto según
	//el valor que debería ser
	for( int i=0; i<9; i++ )
	{
		for( int j=0; j<9-i; j++ )
		{
			if( valores[j] > valores[j+1] )
			{
				int min = valores[j];
				valores[j] = valores[j+1];
				valores[j+1] = min;
			}
		}
	}
	posValor = 0; //indice del vector "valores"

	teclaSaltoPresionada = false;	
	ganoJuego = false;
}

Game::~Game() 
{
	valores.clear();
	bloques.clear();
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
			if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space ) {
				teclaSaltoPresionada = true;
			}
			if( event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space ) {
				teclaSaltoPresionada = false;
			}
		}

		if( contador.GetFin() || ganoJuego )
		{
			FinJuego();
			//Espero a que cierren la ventana
			while( window.isOpen() )
			{
				sf::Event event;
				while( window.pollEvent( event )) {
					if( event.type == sf::Event::Closed ) {
						window.close();
					}
				}
			}
		}
		else
		{
			contador.Update( clockContador.getElapsedTime().asSeconds() );		
			jugador.update( delta_time_seconds );
			jugador.ActualizarSalto( teclaSaltoPresionada, delta_time_seconds );			
			CheckCollision();		
			Draw();
		}		
	}
}

void Game::CheckCollision() {
	std::vector<Bloque>::iterator it;
	for( it = bloques.begin(); it != bloques.end(); it++ ) {
		if( jugador.getGlobalBounds().intersects( it->GetSprite().getGlobalBounds() ) )
		{
			jugador.InterrumpirSalto();
			if( valores[posValor] == it->GetValor() )
			{				
				it->CambiarColor();
				if( posValor < 9 ) 
					posValor++;
				else
					ganoJuego = true;
			}
			else
			{
				//Reducir Clock
				contador.ReducirTiempo();
			}			
		}
	}
}

void Game::Draw() {
	
	window.clear();
	window.draw( background );
	for( std::vector<Bloque>::iterator it = bloques.begin(); it != bloques.end(); ++it )
	{
		window.draw( it->GetSprite() );
		window.draw( it->GetText() );
	}
	window.draw( jugador );
	window.draw( contador.GetText() );
	window.display();
}

void Game::FinJuego()
{
	//Ordeno los bloques
	for( int i=0; i<9; i++ )
	{
		for( int j=0; j<9-i; j++ )
		{
			if( bloques[j].GetValor() > bloques[j+1].GetValor() )
			{
				Bloque min = bloques[j];
				bloques[j] = bloques[j+1];
				bloques[j+1] = min;
			}
		}
	}

	//Vuelvo a ordenar las posiciones de los sf::Sprite y sf::Text
	for( int i=0; i<10; i++)
	{
		sf::Sprite sprite = bloques[i].GetSprite();
		sprite.setPosition( 70 + 70 * i,  390 );
		sf::Text text = bloques[i].GetText();
		text.setPosition(75 + 70 * i, 400 );
		bloques[i].SetSprite( sprite );
		bloques[i].SetTexto( text );
	}
	Draw();
}