#include "Game.h"

Game::Game(int _ancho, int _alto, string _titulo)
{
	//Ventana
	anchoWnd = _ancho;
	altoWnd = _alto;
	pWnd = new RenderWindow(VideoMode(anchoWnd, altoWnd, 32), _titulo);
	pWnd->ShowMouseCursor(false);

	//Variables
	tf = 0.0f;
	vidas = 5; //Comienzo con 5 vidas
	totalTeclas = 0;
	cantTeclasCorrectas = 0;
	sigNivel = 5; //El primer nivel se supera con 5 teclas correctas
	velocidadActual = 200.0f; //Velocidad inicial del juego

	//Cursor
	pCursor = new Cursor(anchoWnd, altoWnd);

	//Marco
	pMarco = new Marco(anchoWnd, altoWnd);

	//Tecla
	pTecla = new Tecla(anchoWnd, altoWnd, velocidadActual);

	//Circulo
	for (int i=0; i<4; i++)
		pCirculo[i] = NULL;
	//Tomo un tiempo al azar para saber cuando pongo circulos
	contadorCirculos = Randomizer::Random(5.0f, 10.0f);
	hayCirculos = false;
	tiempoActivoCirculos = 0.0f;

	//Fondo
	pFondo = new Fondo(anchoWnd, altoWnd);

	//Vida
	for (int i=0; i<10; i++)
		pVida[i] = NULL;

	for (int i=0; i<5; i++)
		pVida[i] = new Vida(anchoWnd, altoWnd, i);
}

Game::~Game()
{
	delete pWnd;
	delete pMarco;
	delete pTecla;
	for (int i=0; i<4; i++)
		delete pCirculo[i];
	for (int i=0; i<10; i++)
		delete pVida[i];
	delete pFondo;
}

void Game::ProcessEvent(Event &evt)
{
	switch (evt.Type)
	{
		//Evento: Cerrar ventana
		case sf::Event::Closed:
			pWnd->Close();
			break;

		//Evento: Presonar tecla
		case sf::Event::KeyPressed:

			//Chequeo si se apreto ESCAPE y salgo del programa.
			if (evt.Key.Code == sf::Key::Escape)
				pWnd->Close();

			//Chequeo si se apreto dentro del MARCO
			if ((pTecla->getY() >= pMarco->getYSup()) && (pTecla->getY() <= pMarco->getYInf()))
			{
				//Chequeo si coincide la tecla del teclado presionada con la que
				//corresponde al objeto TECLA actual
				if (evt.Key.Code == pTecla->getCodigo())
				{
					cout << "APRETO TECLA CORRECTA" << endl;
					totalTeclas++;
					cantTeclasCorrectas++;
					delete pTecla;
					pTecla = new Tecla(anchoWnd, altoWnd, velocidadActual);					
				}
				else
				{
					cout << "APRETO TECLA INCORRECTA" << endl;
					PerderVida(); //Como se equivoco, le resto vida
					if (hayCirculos) //Si hay circulos en pantalla, como el jugador se equivoco los borro
						BorrarCirculos();
					delete pTecla;
					pTecla = new Tecla(anchoWnd, altoWnd, velocidadActual);					
				}
			}
			else
			{
				cout << "APRETO TECLA FUERA DEL MARCO" << endl;
				PerderVida();
				if (hayCirculos)
						BorrarCirculos();				
				delete pTecla;				
				pTecla = new Tecla(anchoWnd, altoWnd, velocidadActual);				
			}
			break;

		//Evento: Mover cursor
		case sf::Event::MouseMoved:
			pCursor->Mover(evt.MouseMove.X, evt.MouseMove.Y); //Muevo el CURSOR con los valores correspondientes
			break;

		//Evento: Presionar mouse
		case sf::Event::MouseButtonPressed:
			if (hayCirculos) //Solo evaluo cuando hay circulos activos
			{
				//Variables para calcular la norma euclideana
				Vector2f pos;
				Vector2f diff;
				pos.x = (float)pWnd->GetInput().GetMouseX();
				pos.y = (float)pWnd->GetInput().GetMouseY();
				for (int i=0; i<4; i++) //Calculo para cada sprite activo
				{
					if (pCirculo[i] != NULL)
					{
						//Calculo norma euclideana para saber si se presiono sobre este circulo
						diff = pCirculo[i]->getSprite().GetPosition() - pos;
						if (pCirculo[i]->IsAdentro(diff) == true)
						{
							GanarVida();
							BorrarCirculos();
							break;
						}
					}
				}
			}
			break;

		default:
			break;
	}
}

void Game::ProcessCollisions()
{
}

void Game::UpdateGame()
{
	//Tomo el delta del tiempo
	tf = pWnd->GetFrameTime();

	//Actualizo la posicon de TECLA
	pTecla->Update(tf);

	//Le cambio el color a TECLA si esta dentro del MARCO
	if ((pTecla->getY() >= pMarco->getYSup()) && (pTecla->getY() <= pMarco->getYInf()))
		pTecla->setColor(Color(255, 0, 0));

	//Le vuelvo el color original a TECLA si pasa el MARCO
	if (pTecla->getY() <= pMarco->getYSup())
		pTecla->ColorOriginal();

	//Chequeo si TECLA salio de pantalla
	if (pTecla->getY() <= 0)
	{
		cout << "TECLA PASO MARCO SIN TOCAR" << endl;
		PerderVida();
		if (hayCirculos)
			BorrarCirculos();
		delete pTecla;
		pTecla = new Tecla(anchoWnd, altoWnd, velocidadActual);
	}

	//Si no hay circulos, reviso si es tiempo de colocarlos
	if ((!hayCirculos) && (clockCirculos.GetElapsedTime() >= contadorCirculos))	
		CrearCirculos();

	//Si hay circulos, reviso si es tiempo de borrarlos
	if ((hayCirculos) && (clockCirculos.GetElapsedTime() >= tiempoActivoCirculos))
		BorrarCirculos();

	//Chequeo si debo aumentar la velocidad y en caso positivo lo hago
	if (cantTeclasCorrectas >= sigNivel)
		AumentarVelocidad();
}

void Game::DrawGame()
{
	pWnd->Draw(pFondo->getSprite()); //Dibujo el objeto FONDO
	for (int i=0; i<10; i++) //Dibujo los objetos VIDA
	{
		if (pVida[i] != NULL)
			pWnd->Draw(pVida[i]->getSprite());
	}
	pWnd->Draw(pMarco->getSprite()); //Dibujo el objeto MARCO
	pWnd->Draw(pTecla->getSprite()); //Dibujo el objeto TECLA
	for (int i=0; i<4; i++) //Dibujo los objetos CIRCULO
	{
		if (pCirculo[i] != NULL)
			pWnd->Draw(pCirculo[i]->getSprite());
	}
	pWnd->Draw(pCursor->getSprite()); //Dibujo el objeto CURSOR
}

void Game::Go()
{
	//Objeto para recibir eventos
	Event evt;

	while (pWnd->IsOpened())
	{
		//Procesar eventos
		while (pWnd->GetEvent(evt))
			ProcessEvent(evt);

		//Procesar colisiones
		ProcessCollisions();

		//Actualizar estados de objetos
		UpdateGame();

		pWnd->Clear();
		DrawGame();
		pWnd->Display();
	}
}

void Game::PerderVida()
{
	cout<<"PERDIO VIDA!" << endl;
	vidas--; //Resto vida
	if (vidas <= 0) //Evaluo si termino el juego
		finJuego();

	delete pVida[vidas]; //Borro el ultimo objeto VIDA
	pVida[vidas] = NULL;
}

void Game::GanarVida()
{
	cout<<"GANO VIDA!" << endl;
	vidas++; //Aumento vida
	if (vidas >= 10) //Solo puede tener 10 vidas como maximo
		vidas = 10;

	//Creo un nuevo objeto VIDA en la ultima posicion del array
	pVida[vidas-1] = new Vida(anchoWnd, altoWnd, vidas-1);
}

void Game::CrearCirculos()
{
	for (int i=0; i<4; i++)
			//Tomo valor al azar para determinar cuantos circulos se activan
			if (Randomizer::Random(0,1) == 1) 
				pCirculo[i] = new Circulo(anchoWnd, altoWnd, i);

		hayCirculos = true;
		clockCirculos.Reset(); //Reinicio el clock
		//Tomo un valor al azar para determinar cuanto tiempo en pantalla se quedan
		tiempoActivoCirculos = Randomizer::Random(3.0f, 6.0f);
}

void Game::BorrarCirculos()
{
	for (int i=0; i<4; i++)
		if (pCirculo[i] != NULL)
		{
			delete pCirculo[i];
			pCirculo[i] = NULL;
		}

	hayCirculos = false;
	clockCirculos.Reset();
	contadorCirculos = Randomizer::Random(5.0f, 10.0f);
}

void Game::finJuego()
{
	Event evt; //Para procesar "Presione una tecla para salir..."
	Font fuente; //Almacena la fuente que va a usar el texto
	String texto; //Almacena el texto
	ostringstream buff; //Para concatenar un el texto y pasarselo al objeto String

	buff << "THE END" << endl << endl;
	buff << "En total apretaste: " << totalTeclas << " teclas" << endl  << endl;
	buff << "Presiona una tecla para salir...";

	fuente.LoadFromFile("Fuentes\\Orbitron Medium.ttf", 24); //Cargo la fuente a usar
	texto.SetFont(fuente); //La seteo en el objeto String
	texto.SetStyle(String::Bold); //Seteo el estilo Bold
	texto.SetSize(24); //Tamaño
	texto.SetColor(Color::Yellow); //Color rojo
	texto.SetText(buff.str()); //Le cargo el texto

	//Seteo el texto en el centro de la pantalla
	FloatRect rect (texto.GetRect());
	Vector2f pos(anchoWnd/2 - rect.GetWidth()/2, altoWnd/2 - rect.GetHeight()/2);
	texto.SetPosition(pos);

	//Dibujo y muestro el texto
	pWnd->Draw(texto);
	pWnd->Display();

	//Proceso eventos hasta que se presione una tecla con lo que salgo
	while (true)
		if (pWnd->GetEvent(evt))
			if (evt.Type == sf::Event::KeyPressed)
			{
				pWnd->Close();
				break;
			}
}

void Game::AumentarVelocidad()
{
	cout << "SE AUMENTO LA VELOCIDAD" << endl;
	cantTeclasCorrectas = 0; //Reinicio el contador de teclas correctas
	
	//Tomo valores al azar para determinar cuanto aumento de velocidad
	//y cuantas teclas deben presionarse para pasar al siguiente nivel
	velocidadActual = velocidadActual + Randomizer::Random(20.0f, 50.0f);
	sigNivel = sigNivel + Randomizer::Random(1,3);
}