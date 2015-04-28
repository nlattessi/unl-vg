#include "Nivel.h"
#include <fstream>
#include <iomanip>
using namespace std;

// Constructor: inicializa el Nivel
// tileset_filename: el nombre del archivo que contiene el tileset
// tileset_nw: numero de tiles de ancho del tileset
// tileset_nh: numero de tiles de alto del tileset
// levelSize_w: ancho del nivel en tiles
// levelSize_h: alto del nivel en tiles
Nivel::Nivel(std::string tileset_filename, int tileset_nw, int tileset_nh, unsigned levelSize_w, unsigned levelSize_h){
	// asignamos algunas variables
	levelSize.x=levelSize_w;
	levelSize.y=levelSize_h;
	this->tileset_filename=tileset_filename;
	tileSetSize.x=tileset_nw;
	tileSetSize.y=tileset_nh;
	// cargamos el tileset
	sm.Load(tileset_filename, tileSetSize.x, tileSetSize.y);
	//tileSize.x=sm[0].GetWidth();
	//tileSize.y=sm[0].GetHeight();
	tileSize.x = sm.GetRect(0).width;
	tileSize.y = sm.GetRect(0).height;
	// inicializamos la matriz de tiles
	Init();
}

// Constructor: cargar el nivel desde el archivo level_file
Nivel::Nivel(std::string level_file){
	Load(level_file);
}


// inicializa la matriz de tiles
void Nivel::Init(){
	// vaciamos la matriz de tiles (por las dudas si se llama
	// a Load() mas de una vez)
	tiles.clear();
	tiles.resize(0);
	
	// variables temporales para ir llenando la matriz
	// una fila y un tile
	vector<Tile> filaTemp;
	Tile tileTemp;
	
	// para calcular la posicion en pantalla de cada tile
	int posx, posy;
	
	// inicializamos la matriz
	for(unsigned i=0; i<levelSize.y; i++){
		// vaciamos la fila y le insertamos todos los tiles
		filaTemp.clear();
		for(unsigned j=0; j<levelSize.x; j++){
			// calculamos la posision del tile
			posx=j*tileSize.x;
			posy=i*tileSize.y;
			tileTemp.setPosition(posx, posy);
			// calculamos el rectangulo que va a ocupar el tile
			tileTemp.rect.left=posx;
			//tileTemp.rect.Right=posx+tileSize.x;
			tileTemp.rect.width = tileSize.x;
			tileTemp.rect.top = posy;
			//tileTemp.rect.Bottom=posy+tileSize.y;
			tileTemp.rect.height = tileSize.y;
			
			// inicializamos el numero de imagen
			tileTemp.iImage=-1;
			
			// insertamos al tile en la fila
			filaTemp.push_back(tileTemp);
		}
		// insertamos la fila en la matriz
		tiles.push_back(filaTemp);
	}

	/*sf::Texture *i = new sf::Texture;
	sf::Texture *j = new sf::Texture;
	sf::Texture *k = new sf::Texture;
	sf::Texture *l = new sf::Texture;
	*i = TextureManager::GetInstance().GetTexture("Media/parallax1.png");
	*j = TextureManager::GetInstance().GetTexture("Media/parallax2.png");
	*k = TextureManager::GetInstance().GetTexture("Media/parallax3.png");
	*l = TextureManager::GetInstance().GetTexture("Media/parallax4.png");
	capasParallax.push_back(new ParallaxLayer(*l, 0.0005, true, 0, 0, false, -5));
	capasParallax.push_back(new ParallaxLayer(*k, 0.0015, true, 0, 0, false, 15));
	capasParallax.push_back(new ParallaxLayer(*j, 0.002, true, 0, 0, false, 40));
	capasParallax.push_back(new ParallaxLayer(*i, 0.0035, true, 0, 0, false, 110));*/
}

// carga un nivel desde un archivo de nivel
void Nivel::Load(string filename){
	// abrimos el archivo
	ifstream entrada(filename.c_str());

	if ( entrada.is_open() )
		std::cout << "ABRIO" << std::endl;
	else
		std::cout << "NO ABRIO" << std::endl;

	// leemos el nombre del archivo de tilesets
	getline(entrada,tileset_filename);
	// cargamos el tamano del tileset y del nivel
	entrada>>tileSetSize.x>>tileSetSize.y;
	entrada>>levelSize.x>>levelSize.y;
	
	// cargamos el tileset
	sm.Load(tileset_filename, tileSetSize.x, tileSetSize.y);
	//tileSize.x=sm[0].GetWidth();
	//tileSize.y=sm[0].GetHeight();

	tileSize.x = sm.GetRect( 0 ).width;
	tileSize.y = sm.GetRect( 0 ).height;
	
	// inicializamos la matriz de tiles
	Init();
	
	// leemos la matriz de numeros de imagenes
	for(unsigned i=0; i<levelSize.y; i++){
		for(unsigned j=0; j<levelSize.x; j++){
			entrada>>tiles[i][j].iImage;
		}
	}
	
	// leemos la matriz que nos indica cuales
	// tiles son solidos
	for(unsigned i=0; i<levelSize.y; i++){
		for(unsigned j=0; j<levelSize.x; j++){
			//entrada>>tiles[i][j].solid;
			entrada>>tiles[i][j].tipo;
		}
	}
	// cerramos el archivo
	entrada.close();
	
	// finalmente asignamos las imagenes a los tiles
	// (si su numero de imagen es distinto de -1)
	int iImg;
	for(unsigned i=0; i<levelSize.y; i++){
		for(unsigned j=0; j<levelSize.x; j++){
			iImg=tiles[i][j].iImage;
			if(iImg!=-1){
				//tiles[i][j].SetImage(sm[iImg]);
				tiles[i][j].setTexture( TextureManager::GetInstance().GetTexture( tileset_filename ) );				
				tiles[i][j].setTextureRect( sm.GetRect( iImg ) );
			}
		}
	}
}


// guardamos el nivel en un archivo
void Nivel::Save(string filename){
	// abrimos el archivo de salida
	ofstream salida(filename.c_str());
	// guardamos el nombre del archivo con el tileset
	salida<<tileset_filename<<endl;
	// guardamos los tamanos del tileset y del nivel
	salida<<tileSetSize.x<<" "<<tileSetSize.y<<endl;
	salida<<levelSize.x<<" "<<levelSize.y<<endl;
	salida<<endl;
	
	// guardamos los numeros de imagen de cada tile
	for(unsigned i=0; i<levelSize.y; i++){
		for(unsigned j=0; j<levelSize.x; j++){
			salida<<setw(3)<<tiles[i][j].iImage<<" ";
		}
		salida<<endl;
	}
	salida<<endl;
	
	// para cada tile guardamos si es o no solido
	for(unsigned i=0; i<levelSize.y; i++){
		for(unsigned j=0; j<levelSize.x; j++){
			//salida<<setw(3)<<tiles[i][j].solid<<" ";
			salida<<setw(3)<<tiles[i][j].tipo<<" ";
		}
		salida<<endl;
	}
	// cerramos el archivo
	salida.close();
}


// llena el vector ovTiles con las coordenadas de los tiles que se superponen
// con el rectangulo r, nos es util para detectar colisiones y para saber que
// tiles debemos renderizar en caso de que no estemos viendo todo el nivel
void Nivel::GetOverlappingTiles(sf::FloatRect r, vector<sf::Vector2i> &ovTiles){
	// tanto i como j comienzan con las coordenadas (en tiles) del rectangulo r
	for(int i=r.top/tileSize.y; i< (r.top + r.height)/tileSize.y; i++){
		for(int j=r.left/tileSize.x; j < (r.left + r.width)/tileSize.x; j++){
			ovTiles.push_back(sf::Vector2i(i, j));
		}
	}
}


// dibuja el tilemap del nivel en la ventana w, para ello utiliza
// la funcion GetOverlappingTiles() para saber que tiles aparecen
// en la vista actual del nivel
void Nivel::Draw(sf::RenderWindow &w){

	/*for(unsigned i=0; i<capasParallax.size(); i++){
		capasParallax[i]->Draw(w);
	}*/
	
	// conseguimos los tiles que se ven en la vista actual
	vector<sf::Vector2i> ovTiles;
	//GetOverlappingTiles(levelView.GetRect(), ovTiles);

	float left = levelView.getCenter().x - (levelView.getSize().x / 2.f);
	float top = levelView.getCenter().y - (levelView.getSize().y / 2.f);
	sf::FloatRect rect( left, top, levelView.getSize().x, levelView.getSize().y );

	GetOverlappingTiles( rect, ovTiles );

	Tile temp;
	// dibujamos los tiles, siempre y cuando tengan una
	// imagen valida
	for(unsigned i=0; i<ovTiles.size(); i++){
		temp=tiles[ovTiles[i].x][ovTiles[i].y];
		if(temp.iImage!=-1){
			w.draw(temp);
		}
	}
}


// revisa si hay o no colision del rectangulo r con algun tile solido
// devuelve verdadero o falso segun haya colision o no
// devuelve en areaColision el area de interpenetracion con el tile
// en caso de haber colision con mas de un tile, devuelve
// el area de colision con el tile que tenga mayor area de colision
bool Nivel::HayColision(sf::FloatRect r, sf::FloatRect &areaColision){
	vector<sf::Vector2i> _tiles;
	GetOverlappingTiles(r, _tiles);
	sf::FloatRect tempResp; float maxResponse=0, sresponse;
	for(unsigned i=0; i<_tiles.size(); i++){
		if(tiles[_tiles[i].x][_tiles[i].y].tipo == 1){
			if(r.intersects(tiles[_tiles[i].x][_tiles[i].y].rect, tempResp)){
				sresponse=tempResp.width * tempResp.height;
				if(sresponse>maxResponse){
					maxResponse=sresponse;
					areaColision=tempResp;
				}
			}
		}
	}
	return maxResponse>0;
}

int Nivel::colisionItem(sf::FloatRect r)
{
	vector<sf::Vector2i> _tiles;
	GetOverlappingTiles(r, _tiles);
	sf::FloatRect tempResp; float maxResponse=0, sresponse;
	int tipo = 0;
	for(unsigned i=0; i<_tiles.size(); i++){
		if(tiles[_tiles[i].x][_tiles[i].y].tipo == 2){
			tipo = tiles[_tiles[i].x][_tiles[i].y].tipo;
			tiles[_tiles[i].x][_tiles[i].y].iImage = -1;
			return tipo;
		}
	}
	return tipo;
}

// devuelve el tamano del tile
sf::Vector2i Nivel::GetTileSize(){
	return tileSize;
}

// devuelve el tamano del nivel (en cantidad de tiles)
sf::Vector2i Nivel::GetLevelSize(){
	return levelSize;
}

// devuelve la vista actual del nivel
sf::View &Nivel::GetView(){
	return levelView;
}

// Mueve el centro de la vista a las coordenadas
// (newCenter.x, newCenter.y). Si la nueva vista se
// sale del nivel, se la corrige
void Nivel::SetViewCenter(sf::Vector2f newCenter){
	// el tamano de la mitad de la vista
	//sf::Vector2f halfSize=levelView.GetHalfSize();
	sf::Vector2f halfSize( levelView.getSize().x / 2.f, levelView.getSize().y / 2.f );
	static sf::Vector2f  oldCenter;

	// el tamano del nivel pero en coordenadas
	sf::Vector2f levelSizeCoords;
	levelSizeCoords.x=levelSize.x*tileSize.x;
	levelSizeCoords.y=levelSize.y*tileSize.y;
	
	// si el nuevo centro se sale fuera del nivel, lo corregimos
	if(newCenter.x-halfSize.x<0) newCenter.x=halfSize.x;
	if(newCenter.x+halfSize.x>levelSizeCoords.x) newCenter.x=levelSizeCoords.x-halfSize.x; 
	if(newCenter.y-halfSize.y<0) newCenter.y=halfSize.y;
	if(newCenter.y+halfSize.y>levelSizeCoords.y) newCenter.y=levelSizeCoords.y-halfSize.y;
	
	// actualiza las capas de parallax scrolling
	/*for(unsigned i=0; i<capasParallax.size(); i++){
		capasParallax[i]->SetPosition(levelView);
		capasParallax[i]->Move(-(oldCenter.x-newCenter.x), oldCenter.y-newCenter.y);
	}*/
	oldCenter=newCenter;

	// seteamos el nuevo centro de la vista
	levelView.setCenter(newCenter);
}


// Cumple la misma funcion que ScrollView() pero suavizando el scroll
// con un factor, tambien necesitamos el tiempo transcurrido
void Nivel::SetViewCenterSmooth(sf::Vector2f newCenter, float factor, float dt){
	// conseguimos el centro actual de la vista
	sf::Vector2f oldCenter=levelView.getCenter();
	
	// calculamos el desplazamiento como un proporcional a la diferencia
	// entre el viejo centro y el nuevo (y factor y el paso de tiempo)
	float scrollDeltax, scrollDeltay;
	scrollDeltax=(newCenter.x-oldCenter.x)*(factor*dt);
	scrollDeltay=(newCenter.y-oldCenter.y)*(factor*dt);
	
	// aplicamos el desplazamiento
	newCenter.x=oldCenter.x+scrollDeltax;
	newCenter.y=oldCenter.y+scrollDeltay;
	
	// seteamos el nuevo centro corrigiendolo si se sale fuera del nivel
	SetViewCenter(newCenter);
}


// inicializa la vista del nivel para que abarque todo el escenario
sf::View &Nivel::InitLevelView(){
	levelView=sf::View(sf::FloatRect(0,0,levelSize.x*tileSize.x, levelSize.y*tileSize.y));
	return levelView;
}

// inicializa la vista basandose en la resolucion de pantalla que utilzaremos
// y la cantidad de tiles de ancho y alto de la vista, crea la vista manteniendo
// la relacion de aspecto
sf::View &Nivel::InitLevelView(int res_x, int res_y, int tiles_x, int tiles_y){
	// si no nos especifican el tamano en tiles de la vista
	// buscamos una vista que abarque todo el nivel
	if(tiles_x<0) tiles_x=levelSize.x;
	if(tiles_y<0) tiles_y=levelSize.y;
	
	// aca vamos a guardar el tamano final de la vista (en tiles)
	float realtiles_x, realtiles_y;
	
	// la logica consiste en hacer coincidir la menor magnitud del Nivel
	// (ancho o alto) con la menor magnitud de la ventana
	
	// si la ventana es mas ancha que alta
	if(res_x>res_y){
		// buscamos la menor magnitud del nivel y ese tamano se
		// correspondera con el alto (menor tamano)
		// la magnitud restante la calculamos con regla de 3
		if(tiles_x>tiles_y){
			// el alto del nivel abarcara el alto de la ventana
			realtiles_y=tiles_y;
			realtiles_x=(res_x*tiles_y)/float(res_y);
		}else{
			// el ancho del nivel abarca el ancho de la ventana
			realtiles_x=tiles_x;
			realtiles_y=(res_y*tiles_x)/float(res_x);
		}
	}else{
		// si la ventana es mas alta que anca
		// hacemos lo mismo que antes, el menor lado de la ventana
		// le asignamos el menor lado del nivel
		if(tiles_x>tiles_y){
			// el alto del nivel abarcara el alto de la ventana 
			realtiles_y=tiles_y;
			realtiles_x=(res_y*tiles_x)/float(res_x);
		}else{
			// el ancho del nivel abarca el ancho de la ventana
			realtiles_x=tiles_x;
			realtiles_y=(res_y*tiles_x)/float(res_x);
		}
	}
	// seteamos la vista del nivel y hacemos un scroll para inicializarla/acomodarla
	//levelView.SetHalfSize(sf::Vector2f(realtiles_x*tileSize.x/2.0, realtiles_y*tileSize.y/2.0));
	//SetViewCenter(sf::Vector2f(0,0));
	levelView.setSize( sf::Vector2f( realtiles_x * tileSize.x, realtiles_y * tileSize.y ) );
	levelView.zoom( 0.5f );
	SetViewCenter( sf::Vector2f( 0, 0 ) );

	return levelView;
}


// dibuja una grilla sobre los tiles
void Nivel::DrawGrid(sf::RenderWindow &w){
	// coordenadas de la vista actual en tiles
	int x1, y1, x2, y2;
	sf::FloatRect r=levelView.getViewport();
	x1=r.left/tileSize.x;
	x2=((r.left + r.width)/tileSize.x)+1;
	y1=r.top/tileSize.y;
	y2=((r.top + r.height)/tileSize.y)+1;
	
	// dibuja las lineas verticales
	for(unsigned i=x1; i<=x2; i++){
		//sf::Shape Line = sf::Shape::Line(i*tileSize.x, y1*tileSize.y, i*tileSize.x, y2*tileSize.y, 1, sf::Color(255,255,255));
		//w.Draw(Line);
		sf::Vertex Line[] = { sf::Vertex(sf::Vector2f(i*tileSize.x, y1*tileSize.y)), sf::Vertex(sf::Vector2f(i*tileSize.x, y2*tileSize.y)) };		
		w.draw( Line, 1, sf::Lines );
	}

	// dibuja las lineas horizontales
	for(unsigned i=y1; i<=y2; i++){
		//sf::Shape Line = sf::Shape::Line(x1*tileSize.x, i*tileSize.y, x2*tileSize.x, i*tileSize.y, 1, sf::Color(255,255,255));
		//w.Draw(Line);
		sf::Vertex Line[] = { sf::Vertex(sf::Vector2f(x1*tileSize.x, i*tileSize.y)), sf::Vertex(sf::Vector2f(x2*tileSize.x, i*tileSize.y)) };		
		w.draw( Line, 1, sf::Lines );
	}
}


// genera y guarda una imagen con el tilemap
/*void Nivel::SaveToImage(string filename){
	// crea una imagen
	sf::Image imagen(levelSize.x*tileSize.x, levelSize.y*tileSize.y, sf::Color(0, 0, 0, 0));
	// dibuja los tiles en la imagen
	for(unsigned i=0; i<levelSize.y; i++){
		for(unsigned j=0; j<levelSize.x; j++){
			if(tiles[i][j].iImage!=-1){
				imagen.Copy(sm[tiles[i][j].iImage], j*tileSize.x, i*tileSize.y);
			}
		}
	}
	// guarda la imagen
	imagen.SaveToFile(filename);
}*/