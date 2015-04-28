#include "Game.h"

Game::Game(int _ancho, int _alto, std::string _titulo)
{
	//Creo la ventana
	pWnd = new sf::RenderWindow(sf::VideoMode(_ancho, _alto, 32), _titulo);
	pWnd->ShowMouseCursor(false);

	//Inicio variables generales
	ft = 0.0f;
	vidas = 3;
	botonApretado = false;

	//Inicio variables de disparo
	angulo = 0;
	v0 = 0.0f;
	ajusteVelDisparo = 300;

	//Muestro la pantalla de inicio y
	//determino el tipo de control
	control = pantallaInicio.Mostrar(*pWnd);

	//Cargo los medios (sonidos e imagenes)
	//y los textos
	CargarMedios();
	CargarTextos();

	//Creo el objeto Fondo
	//pFondo = new Fondo(_ancho, _alto, ImgFondo);
	pFondo = new Fondo(ImgFondo);

	//Creo el objeto Cannon
	pCannon = new Cannon(_ancho, _alto, SBuffBoom, ImgCannon);

	//Inicializo las Balas
	for (int i=0; i<BALAS; i++)
		pBalas[i] = NULL;

	//Inicializo los Patos
	for (int i=0; i<PATOS; i++)
		pPatos[i] = new Pato(SBuffCuack, ImgPato1, ImgPato2, ImgPato3);

	//Activo los 3 primeros patos
	pPatos[0]->Activar();
	pPatos[1]->Activar();
	pPatos[2]->Activar();
}

Game::~Game()
{
	//Borro todos los punteros
	delete pWnd;
	delete pFondo;
	delete pCannon;
	for (int i=0; i<BALAS; i++)
		delete pBalas[i];
	for (int i=0; i<PATOS; i++)
		delete pPatos[i];
}

void Game::ProcessEvent(sf::Event &evt)
{
	switch (evt.Type)
	{
		//Evento: Cerrar ventana
		case sf::Event::Closed:
			pWnd->Close();
			break;

		//Evento: Presionar tecla
		case sf::Event::KeyPressed:

			//Chequeo si se apreto ESCAPE y salgo del programa.
			if (evt.Key.Code == sf::Key::Escape)
				pWnd->Close();
			
			//Si el control es TECLADO, chequeo si se apreto la barra espaciadora
			//y seteo que se acumule velocidad para el disparo
			if ((control == TECLADO) && (evt.Key.Code == sf::Key::Space)
				//&& (botonApretado == false) && (pCannon->getEstado() == CANNON_LISTO))
				&& (botonApretado == false))
				botonApretado = true;			
			break;

		//Evento: Soltar tecla
		//Si suelto la barra espaciadora, disparar
		//la bala con la velocidad acumulada
		case sf::Event::KeyReleased:
			if ((evt.Key.Code == sf::Key::Space) && (control == TECLADO)
				&& (botonApretado == true))
				if (pCannon->getEstado() == CANNON_LISTO)
				{
					pCannon->Disparar();
					Disparar();
				}
				else
				{
					botonApretado = false;
					v0 = 0.0f;
				}
			break;

		//Evento: Mover mouse. 
		//Roto el cañon según la posición del mouse.
		case sf::Event::MouseMoved:
			if (control == MOUSE)
				pCannon->Rotar(evt.MouseMove.X, evt.MouseMove.Y);
			break;
		
		//Evento: Presionar botón mouse.
		////Si el control es MOUSE, chequeo si se apreto el click izquierdo
		//y seteo que se acumule velocidad para el disparo
		case sf::Event::MouseButtonPressed:
			if ((evt.MouseButton.Button == sf::Mouse::Button::Left)
				&& (control == MOUSE) && (botonApretado == false))
				botonApretado = true;
			break;

		//Evento: Soltar botón mouse.
		//Si suelto el click izquierdo, disparar
		//la bala con la velocidad acumulada
		case sf::Event::MouseButtonReleased:
			if ((evt.MouseButton.Button == sf::Mouse::Button::Left)
				&& (control == MOUSE) && (botonApretado == true))
				if (pCannon->getEstado() == CANNON_LISTO)
				{
					pCannon->Disparar();
					Disparar();
				}
				else
				{
					botonApretado = false;
					v0 = 0.0f;
				}
			break;

		default:
			break;
	}
}

void Game::ProcessEventUnbuffered(const sf::Input &Input)
{
	//Cambio la direccion de rotación del sprite según
	//que tecla se presionó
	if ((Input.IsKeyDown(sf::Key::Left)) && (control == TECLADO))
		pCannon->MoverIzq();
	if ((Input.IsKeyDown(sf::Key::Right)) && (control == TECLADO))
		pCannon->MoverDer();
}

void Game::ProcessCollisions()
{
	//Recorro los arrays de Patos y Balas
	//y chequeo colisiones. De haber, desplumo
	//al pato y destruyo la bala
	for (int i=0; i<BALAS; i++)
	{
		for (int j=0; j<PATOS; j++)
		{
			if ((pBalas[i] != NULL) && (pPatos[j]->isActivo()))
			{
				if (CheckColision(*pBalas[i], *pPatos[j]))
				{
					DesplumarPato(*pPatos[j]);
					delete pBalas[i];
					pBalas[i] = NULL;
				}
			}
		}
	}
}

void Game::UpdateGame()
{
	float xBala, yBala, yPato;

	//Tomo el tiempo del frame
	ft = pWnd->GetFrameTime();

	//Actualizo el Viento y su texto
	Viento.Update(ft);
	std::ostringstream buffViento;
	buffViento<<"Viento: "<<Viento.getVelocidad();
	txtViento.SetText(buffViento.str());
	
	//Aumento la Potencia del disparo si está la barra o el click izquierdo
	//apretado y actualizo el texto
	if (botonApretado)
	{
		v0 += (ajusteVelDisparo * ft);
		
		std::ostringstream buff;
		buff.precision(2);
		buff<<std::fixed<<"Potencia: "<<v0;
		txtPotencia.SetText(buff.str());
	}

	//Actualizo la posicion y el estado
	//del Cañon junto con su texto
	pCannon->Update(ft);
	std::ostringstream buffCannon;
	if (pCannon->getEstado() == LISTO)
		buffCannon<<"CAÑON: LISTO!";
	else
		buffCannon<<"CAÑON: CARGANDO...";
	txtCannon.SetText(buffCannon.str());

	//Actualizo la posicion de las Balas activas
	for (int i=0; i<BALAS; i++)
	{
		if (pBalas[i] != NULL)
		{
			//Actualizo la posicion de la Bala teniendo en cuenta el Viento
			pBalas[i]->Update(ft, Viento.getVelocidad());
			//Chequeo si salio de la pantalla y la destruyo de ser asi
			xBala = pBalas[i]->getSprite().GetPosition().x;
			yBala = pBalas[i]->getSprite().GetPosition().y;
			if ((xBala < 0) || (xBala > 800) || (yBala < 0) || (yBala > 400))
			{
				delete pBalas[i];
				pBalas[i] = NULL;
			}
		}
	}

	//Actualizo la posicion de los Patos activos
	for (int i=0; i<PATOS; i++)
		if (pPatos[i]->isActivo() == true)
		{
			//Actualizo la posicion del Pato
			pPatos[i]->Update(ft);
		
			//Chequeo si llegó a tierra y de ser asi
			//desactivo al Pato y resto vida
			yPato = pPatos[i]->getSprite().GetPosition().y;
			if (yPato >= 400)
			{
				pPatos[i]->Desactivar();
				PerderVida();
			}
		}
}

void Game::DrawGame()
{
	pWnd->Draw(pFondo->getSprite()); //Dibujo el objeto Fondo
	pWnd->Draw(txtVidas); //Dibujo el texto de Vidas
	pWnd->Draw(txtPotencia); //Dibujo el texto de la Potencia del disparo
	pWnd->Draw(txtViento); //Dibujo el texto del Viento
	pWnd->Draw(txtCannon); //Dibujo el texto del Cañon
	pWnd->Draw(pCannon->getSprite()); //Dibujo el objeto Cannon

	//Dibujo a las Balas
	for (int i=0; i<BALAS; i++)
		if (pBalas[i] != NULL)
			pWnd->Draw(pBalas[i]->getSprite());

	//Dibujo a los Patos
	for (int i=0; i<PATOS; i++)
		if (pPatos[i]->isActivo() == true)
			pWnd->Draw(pPatos[i]->getSprite());
}

void Game::Go()
{
	//Objeto para recibir eventos
	sf::Event evt;

	//Creo el objeto Input y lo asocio a la ventana
	const sf::Input &Input = pWnd->GetInput();

	while (pWnd->IsOpened())
	{
		//Proceso eventos
		while (pWnd->GetEvent(evt))
			ProcessEvent(evt);

		//Proceso los eventos unbuffered
		ProcessEventUnbuffered(Input);

		//Proceso las colisiones
		ProcessCollisions();

		//Actualizo el estado de los objetos
		UpdateGame();

		//Limpio
		pWnd->Clear();

		//Dibujo
		DrawGame();

		//Muestro
		pWnd->Display();
	}
}


//FUNCIONES AUXILIARES
void Game::PerderVida()
{
	//Resto vida. Si llego a 0, termino el juego
	vidas--;
	if (vidas == 0)
		FinJuego();
	else
	{
		//Actualizo el texto de las Vidas
		std::ostringstream buff;
		buff<<"Vidas: "<<vidas;
		txtVidas.SetText(buff.str());
	}
}

void Game::FinJuego()
{
	sf::Event evt; //Para procesar "Presione una tecla para salir..."
	sf::String texto; //Almacena el texto
	std::ostringstream buff; //Para concatenar un el texto y pasarselo al objeto String

	buff << "THE END" << std::endl << std::endl;
	buff << "Los Patos mutantes han tomado la Tierra!" << std::endl  << std::endl;
	buff << "Presiona una tecla para salir...";

	texto.SetFont(fuente); //Fuente
	texto.SetStyle(sf::String::Bold); //Negrita
	texto.SetSize(24); //Tamaño
	texto.SetColor(sf::Color::Red); //Color
	texto.SetText(buff.str()); //Le cargo el texto

	//Seteo el texto en el centro de la pantalla
	sf::FloatRect rect (texto.GetRect());
	sf::Vector2f pos(pWnd->GetWidth()/2 - rect.GetWidth()/2, pWnd->GetHeight()/2 - rect.GetHeight()/2);
	texto.SetPosition(pos);

	//Dibujo y muestro el texto
	pWnd->Draw(texto);
	pWnd->Display();

	//Proceso eventos hasta que se presione una tecla
	//o cierro la ventan con lo que salgo
	while (true)
		if (pWnd->GetEvent(evt))
		{
			if (evt.Type == sf::Event::KeyPressed)
			{
				pWnd->Close();
				break;
			}
			if (evt.Type == sf::Event::Closed)
			{
				pWnd->Close();
				break;
			}
		}
}

bool Game::CheckColision(Bala &bala, Pato &pato)
{
	//Chequeo la colision entre 2 objetos utilizando sus sprites
	//para tomar los puntos del "bounding box" y chequear si
	//hay intersección, como se vió en la Unidad 8.

	float posxBala, xiBala, xfBala, posxPato, xiPato, xfPato;
	float posyBala, yiBala, yfBala, posyPato,yiPato, yfPato;
	bool interseccionx = false;
	bool intersecciony = false;

	//Cargo los parametros de los sprites correspondientes.
	//Utilizo "TransformToGlobal" para obtener la posición
	//global (es decir, según la pantalla) de la esquina
	//superior izquierda del sprite.
	//BALA
	posxBala = bala.getSprite().GetPosition().x;
	posyBala = bala.getSprite().GetPosition().y;
	xiBala = bala.getSprite().TransformToGlobal(sf::Vector2f(0,0)).x;
	xfBala = bala.getSprite().GetSize().x + xiBala;
	yiBala = bala.getSprite().TransformToGlobal(sf::Vector2f(0,0)).y;
	yfBala = bala.getSprite().GetSize().y + yiBala;
	//PATO
	posxPato = pato.getSprite().GetPosition().x;
	posyPato = pato.getSprite().GetPosition().y;
	xiPato = pato.getSprite().TransformToGlobal(sf::Vector2f(0,0)).x;
	xfPato = pato.getSprite().GetSize().x + xiPato;
	yiPato = pato.getSprite().TransformToGlobal(sf::Vector2f(0,0)).y;
	yfPato = pato.getSprite().GetSize().y + yiPato;

	//Chequeo si hay interseccion en eje X
	if (posxBala < posxPato)
		if (xfBala > xiPato)
			interseccionx = true;

	if (posxBala > posxPato)
		if (xfPato > xiBala)
			interseccionx = true;

	if (posxBala == posxPato)
		interseccionx = true;
		
	//Chequeo si hay interseccion en eje Y
	if (posyBala < posyPato)
		if (yfBala > yiPato)
			intersecciony = true;

	if (posyBala > posyPato)
		if (yfPato > yiBala)
			intersecciony = true;

	if (posyBala == posyPato)
		intersecciony = true;

	//Si hay interesección en ambos ejes devuelvo true
	if (interseccionx && intersecciony)
		return true;

	return false;
}

void Game::DesplumarPato(Pato &pato)
{
	int cont, cantPatos;
	float v = pato.GetVelocidad(); //Guardo la velocidad del pato desplumado
	pato.Desactivar(); //Desactivo al pato
	pato.Cuack(); //Reproduzco el "Cuack"

	//Elijo al azar una de las 3 opciones que pueden
	//ocurrir al desplumar un pato
	switch(sf::Randomizer::Random(1,3))
	{
		case 1: //Aparece un Pato en la parte superior con la misma velocidad que el anterior
			for (int i=0; i<PATOS; i++)
				if (pPatos[i]->isActivo() == false)
				{
					pPatos[i]->Activar(v, 1);
					break;
				}
			break;

		case 2: //Aparece un Pato con mayor velocidad que el anterior
			for (int i=0; i<PATOS; i++)
				if (pPatos[i]->isActivo() == false)
				{
					pPatos[i]->Activar(v, 2);
					break;
				}
			break;

		case 3: //Aparecen 2 o 3 Patos en la parte superior con velocidades arbitrarias
			cont = 0;
			cantPatos = sf::Randomizer::Random(2,3);
			for (int i=0; i<PATOS; i++)
				if (pPatos[i]->isActivo() == false)
				{
					pPatos[i]->Activar();
					cont++;
					if (cont == cantPatos)
						break;
				}
			break;
				
		default:
			break;
	}
}

void Game::Disparar()
{
	//Recorro el array de Balas hasta encontrar
	//la primera sin usar y la creo

	for (int i=0; i<BALAS; i++)
	{
		if (pBalas[i] == NULL)
		{	
			pBalas[i] = new Bala(v0, pCannon->getSprite(), ImgBala);
			break;
		}
	}

	botonApretado = false;
	v0 = 0;
}

void Game::CargarMedios()
{
	//Cargo las imagenes
	ImgFondo.LoadFromFile("Imagenes\\fondo.png");
	ImgBala.LoadFromFile("Imagenes\\ironball.png");
	ImgCannon.LoadFromFile("Imagenes\\Cannon.png");
	ImgPato1.LoadFromFile("Imagenes\\pato_cae_1.png");
	ImgPato2.LoadFromFile("Imagenes\\pato_cae_2.png");
	ImgPato3.LoadFromFile("Imagenes\\pato_cae_3.png");

	//Cargo el sonido "Quack" y "Boom"
	SBuffCuack.LoadFromFile("Sonidos\\quack.wav");
	SBuffBoom.LoadFromFile("Sonidos\\shoot.wav");
}

void Game::CargarTextos()
{
	//Cargo la fuente a usar
	fuente.LoadFromFile("Fuentes\\Orbitron Medium.ttf");
	
	//Inicio de texto de cant. de vidas
	txtVidas.SetFont(fuente); //Fuente
	txtVidas.SetSize(18); //Tamaño
	txtVidas.SetColor(sf::Color::Black); //Color
	txtVidas.SetPosition(5,570); //Posición
	//Creo Buffer, cargo texto y lo asigno al String
	std::ostringstream buffVidas;
	buffVidas<<"Vidas: "<<vidas;
	txtVidas.SetText(buffVidas.str());

	//Inicio de texto de potencia
	txtPotencia.SetFont(fuente); //Fuente
	txtPotencia.SetSize(18); //Tamaño
	txtPotencia.SetColor(sf::Color::Black); //Color
	txtPotencia.SetPosition(200,570); //Posición
	//Creo Buffer, cargo texto, le preciso 2 digitos y lo asigno al String
	std::ostringstream buffPotencia;
	buffPotencia.precision(2);
	buffPotencia<<std::fixed<<"Potencia: "<<v0;
	txtPotencia.SetText(buffPotencia.str());

	//Inicio de texto del Cañon
	txtCannon.SetFont(fuente); //Fuente
	txtCannon.SetSize(18); //Tamaño
	txtCannon.SetColor(sf::Color::Black); //Color
	txtCannon.SetPosition(400,570); //Posicion
	//Creo Buffer, cargo texto y lo asigno al String
	std::ostringstream buffCannon;
	buffCannon<<"CAÑON: LISTO!";
	txtCannon.SetText(buffCannon.str());

	//Inicio de texto del viento
	txtViento.SetFont(fuente); //Fuente
	txtViento.SetSize(18); //Tamaño
	txtViento.SetColor(sf::Color::Black); //Color
	txtViento.SetPosition(650,570); //Posicion
	//Creo Buffer, cargo texto y lo asigno al String
	std::ostringstream buffViento;
	buffViento<<"Viento: "<<Viento.getVelocidad();
	txtViento.SetText(buffViento.str());
}