#ifndef NIVEL_H
#define NIVEL_H

#include <iostream>
#include <vector>
#include "SpriteSheetManager.h"
#include <SFML/Graphics/RenderWindow.hpp>

#include "TextureManager.h"

class Tile : public sf::Sprite
{
	public:

		enum TIPO { EMPTY, SOLID, COLLECTABLE };

		int iImage;
		//bool solid;
		int tipo;
		sf::FloatRect rect;
		friend class Nivel;
};

class Nivel
{
	public:
		//Constructores
		Nivel(std::string tileset_file, int ntilesx, int ntilesy, unsigned levelSize_w, unsigned levelSize_h);
		Nivel(std::string level_file);
		//Nivel( unsigned levelSize_w, unsigned levelSize_h );

		// salvar y guardar un nivel
		void Load(std::string file);
		void Save(std::string file);

		// tamano de tiles y del nivel
		sf::Vector2i GetTileSize();
		sf::Vector2i GetLevelSize();

		// dibujar el nivel en pantalla
		void Draw(sf::RenderWindow &w);

		// probar si hay colision del nivel con el rectangulo r
		bool HayColision(sf::FloatRect r, sf::FloatRect &areaColision);

		// probar si hay colision con un item. Devuelvo el tipo
		int colisionItem(sf::FloatRect r);

		// funciones para inicializar la vista
		sf::View &InitLevelView(int res_x, int res_y, int tiles_x=-1, int tiles_y=-1);
		sf::View &InitLevelView();

		// funciones para realizar scrolling
		void ScrollView(sf::Vector2f newCenter);
		void ScrollViewSmooth(sf::Vector2f newCenter, float factor, float dt);

		// algunas funciones utiles
		void DrawGrid(sf::RenderWindow &w);
		//void SaveToImage(std::string filename);

		// devuelve la vista del nivel
		sf::View &GetView();
		// mueve la vista (realiza scrolling)
		void SetViewCenter(sf::Vector2f newCenter);
		// mueve la vista de forma suave
		void SetViewCenterSmooth(sf::Vector2f newCenter, float factor, float dt);

	private:
		// nombre del archivo tileset
		std::string tileset_filename;
		// manejador de las imagenes del tileset
		SpriteSheetManager sm;
		// la matriz (o vector de vectores) de tiles
		std::vector< std::vector<Tile> > tiles;
		// tamano del nivel en tiles (ancho x alto)
		sf::Vector2i levelSize;
		// tamano del tileset en tiles (ancho x alto)
		sf::Vector2i tileSetSize;
		// tamano de los tiles (ancho x alto)
		sf::Vector2i tileSize;

		// la vista del nivel
		sf::View levelView;

		//std::vector<ParallaxLayer *> capasParallax;
	
		// inicializa la matriz de tiles
		void Init();
	
		// nos da los tiles que se solapan con el rectangulo r
		// (para detectar colisiones e evitar dibujar todo el escenario)
		void GetOverlappingTiles(sf::FloatRect r, std::vector<sf::Vector2i> &_tiles);
};

#endif